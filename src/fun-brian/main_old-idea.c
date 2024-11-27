#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "../Parsa/Funktioner.c"

#define BACKGROUND_IMAGE "../../content/workout-images.png"
#include "../frontend-brian/frontend.c"

#define MAX_TABS_COUNT 20

typedef struct Tab {
    void (*func)();
    char title[8];
} Tab;

Tab tabs[MAX_TABS_COUNT] = { 0 };

void TabSwitcher() {
    int key = GetKeyPressed()-'0';
    if (key>0 && key<9 && tabs[key].func != NULL) {
        tabs[key].func();
    }
}

// User has been in the application before, so we say welcome back.
void welcome_back() {
    printf("Welcome back!");
    // TODO: Program ends here, but when a user comes back, they should be going to the "update weight" question.
}

void the_program_made() {
    // TODO
}

void start_introduction() {
    printf("Hey! you need to type in your user information!");
    the_program_made();
}

Vector2 bs = {0.3, 0.2};
float by = 11.0/15.0;

void start_app() {
    while (1) {
        DrawNewFrame();
        DrawTitle("               Welcome,\nhave you opened the app before?", 0.05, AtPos(0.5, 0.3));
        if (DrawButton("Yes", 0.05, InArea(AtPos(0.3, by), bs)))
            welcome_back();
        if (DrawButton("No", 0.05, InArea(AtPos(0.7, by), bs)))
            start_introduction();
    }
}

#define FILENAME "data.txt"

enum GUI_TYPE {
    BUTTON_GUI_TYPE,
    TITLE_GUI_TYPE,
};

//    "%d %f %f %f", // TITLE_GUI_TYPE

int main() {
    // Read in
    FILE* ex_prog = fopen(FILENAME, "rw");
    if (ex_prog == NULL){
        ex_prog = fopen(FILENAME, "ab+");
        fprintf(ex_prog, "0 %f %f %f %f %f\n", 0.05, 0.5, 11.0/15.0, 0.3, 0.2);
        fprintf(ex_prog, "1 %f %f %f\n", 0.2, 0.5, 0.5);
        fprintf(ex_prog, "1 %f %f %f\n", 0.2, 0.5, 0.5);
        fprintf(ex_prog, "0 %f %f %f %f %f\n", 0.05, 0.5, 11.0/15.0, 0.3, 0.2);
        fprintf(ex_prog, "1 %f %f %f\n", 0.2, 0.5, 0.5);
    }
    if (ex_prog == NULL) {
        printf("FILE WRITE ERROR");
        exit(1);
    }

    float th, x, y, w, h;
    int ret;
    int t = 0;
    while (getc(ex_prog) != EOF) {
        ret = fscanf(ex_prog, "%d ", &t);
        if (ret!=1) {
            printf("ERROR: reading file (1)\n");
            exit(1);
        }
        switch (t)
        {
        case 0:
            ret = fscanf(ex_prog, "%f %f %f %f %f\n", &th, &x, &y, &w, &h);
            if (ret!=5) {printf("ERROR: reading file (2)\n");exit(1);}
            printf("ret: %d. Else: %f %f %f %f %f\n", ret, th, x, y, w, h);
            break;
        case 1:
            ExportData(const unsigned char *data, int dataSize, "file.h"); // Export data to code (.h), returns true on success

            ret = fscanf(ex_prog, "%f %f %f\n", &th, &x, &y);
            if (ret!=3) {printf("ERROR: reading file (3)\n");exit(1);}
            printf("ret: %d. Else: %f %f %f\n", ret, th, x, y);
            break;
        default:
            break;
        }
    }

//    OpenApplication();
//    start_app();


    // Write out

    return 0;
}