#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "../Parsa/Funktioner.c"

#define BACKGROUND_IMAGE "../../content/workout-images.png"
#include "../frontend-brian/frontend.c"

//#define MAX_TABS_COUNT 20
//
//typedef struct Tab {
//    void (*func)();
//    char title[8];
//} Tab;
//
//Tab tabs[MAX_TABS_COUNT] = { 0 };
//
//void TabSwitcher() {
//    int key = GetKeyPressed()-'0';
//    if (key>0 && key<9 && tabs[key].func != NULL) {
//        tabs[key].func();
//    }
//}

#define FLOATS_LEN (7*2 + 5*1)
#define SEP INFINITY
#define FILENAME "save_data"

enum GUI_TYPE {
    BUTTON_GUI_TYPE,
    TITLE_GUI_TYPE,
};

Vector2 bs = {0.3, 0.2};
float by = 11.0/15.0;
double *main_data = NULL;
int main_data_size = 0;
double default_floats[FLOATS_LEN] = {
    0, 0.05, 0.3, 11.0/15.0, 0.3, 0.2, SEP, // Button
    1, 0.05, 0.5, 0.3,                 SEP, // Title
    0, 0.05, 0.7, 11.0/15.0, 0.3, 0.2, SEP, // Button
};

void Save() {
    // Write out
    if (!SaveFileData(FILENAME, main_data, FLOATS_LEN*sizeof(double))) {
        printf("ERROR: Exporting failed.\n");
    }
}

void DrawIcon(int icon, Vector2 pos, int pixel_size){
    GuiDrawIcon(icon, pos.x, pos.y, pixel_size, BLACK);
}

void start_app() {while (1) {
    DrawNewFrame();
    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        if (IsKeyPressed(KEY_S)) { // Save
            Save();
        }
        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_R)) { // Reset all buttons/text
            free(main_data);
            main_data = malloc(FLOATS_LEN*sizeof(double));
            main_data_size = FLOATS_LEN;
            memcpy(main_data, default_floats, FLOATS_LEN*sizeof(double));
        }
    }
// TODO replace buffer, by instead using same array but indexing negative
    for (int i=0, bl=0; i<main_data_size; i++) {
        if (main_data[i] != SEP) continue;

        if (main_data[bl] == BUTTON_GUI_TYPE) {
            Vector2 p = Vector2Divide(GetMousePosition(), GetWindowSize());
            float h = main_data[bl+1];
            Vector2 pos = {main_data[bl+2], main_data[bl+3]};
            Vector2 size = {main_data[bl+4], main_data[bl+5]};

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && main_data[bl+2]-0.3<p.x && main_data[bl+2]>p.x) {
                main_data[i-4]+=GetMouseDelta().x/GetWindowSize().x;
            }
            DrawButton("Text", main_data[bl+1], InArea(pos, WithSize(main_data[bl+4], main_data[bl+5])));
            Vector2 mover_pos = Vector2Multiply(Vector2Subtract(pos, Vector2Scale(size,0.5)),GetWindowSize());
            DrawIcon(ICON_CURSOR_MOVE_FILL, mover_pos, 2);
            Vector2 icon_size = Vector2Scale(Vector2Invert(GetWindowSize()), RAYGUI_ICON_SIZE);
            Vector2 sizer_pos = {
                pos.x + size.x/2 - 2*icon_size.x,
                pos.y + size.y/2 - 2*icon_size.y,
            };
            Rectangle sizer_rec = InArea(sizer_pos, icon_size);
            sizer_pos = Vector2Multiply(sizer_pos, GetWindowSize());

            DrawIcon(ICON_CURSOR_SCALE_LEFT_FILL, sizer_pos, 2);
        };
        if (main_data[bl] == TITLE_GUI_TYPE) {
            DrawTitle("Text", main_data[bl+1], AtPos(main_data[bl+2], main_data[bl+3]));
        }
        bl = i+1;
    }
}}


int main() {

    // Read in
    if (FileExists(FILENAME)) {
        int dataSize = 0;
        unsigned char *data_in = LoadFileData(FILENAME, &dataSize); // Load file data as byte array (read)
        if (dataSize%8 != 0) {
            printf("ERROR: Import failed, bytes not 8-alligned, so aren't storing doubles.\n");
            exit(1);
        }
        main_data = malloc(dataSize*sizeof(char));
        memcpy(main_data, data_in, dataSize);
        main_data_size = dataSize/8;
        printf("%d,", main_data_size);
        for (int i=0; i<main_data_size; i++){
            printf("%f, ",main_data[i]);
        }
        printf("\n");
        UnloadFileData(data_in);                         // Unload file data allocated by LoadFileData()
    } else {
        main_data = malloc(FLOATS_LEN*sizeof(double));
        main_data_size = FLOATS_LEN;
        memcpy(main_data, default_floats, FLOATS_LEN*sizeof(double));
    }
    if (main_data == NULL) {
        printf("UNKNOWN ERROR: Probably incorrect file handling in Brian's code\n");
    }

    OpenApplication();
    start_app();



    return 0;
}