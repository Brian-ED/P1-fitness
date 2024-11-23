#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.c"

#define BACKGROUND_SPEED 0.5
#define FRAMES_PER_SECOND 60
#define TEXT_LENGTH 30

Texture background_image;
int debug_mode_grid = false;
float background_x = 0;
float background_y = 0;

//------------------------------------------------------------------------------------------
// Function Definitions
//------------------------------------------------------------------------------------------
Vector2 GetWindowSize() {
    return (Vector2){GetScreenWidth(), GetScreenHeight()};
};

Rectangle PosAndSizeToRectangle(Vector2 position, Vector2 size) {
    return (Rectangle){
        .x = position.x,
        .y = position.y,
        .width = size.x,
        .height = size.y};
}

float Min(Vector2 v) {
    return v.x > v.y ? v.y : v.x;
}

Vector2 AtPos(float x, float y) {
    return (Vector2){x, y};
}

Vector2 WithSize(float x, float y) {
    return (Vector2){x, y};
}

Rectangle InArea(Vector2 position, Vector2 size) {
    return (Rectangle){position.x, position.y, size.x, size.y};
}

void DrawBackgroundWithFade(float fade) {
    Color whiteFade = Fade(WHITE, fade);
    Vector2 window_size = GetWindowSize();

    background_x += 2 * BACKGROUND_SPEED;
    background_y += 1 * BACKGROUND_SPEED;
    background_x = fmodf(background_x, background_image.width);
    background_y = fmodf(background_y, background_image.height);

    float scale = Min(Vector2Divide(window_size, (Vector2){background_image.width, background_image.height}));


    // drawing the image until it fills the entire background of the window
    for (float i = scale*(background_x-background_image.width); i < window_size.x; i += background_image.width * scale)
    {
        for (float j = scale*(background_y-background_image.height); j < window_size.y; j += background_image.height * scale)
        {
            // Draw a part of a texture defined by the rectangle texture_source
            DrawTextureEx(background_image, (Vector2){i, j}, 0, scale, whiteFade); // Draw a Texture2D with extended parameters
        }
    }

    // Toggle debug mode if user pressed ctrl+D
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_D)) {
        debug_mode_grid = !debug_mode_grid;
    }

    // Toggle
    if (debug_mode_grid) {
        DrawFPS(10, 10);
        GuiGrid(InArea(AtPos(0,0), GetWindowSize()), Vector2Scale(GetWindowSize(),0.1), 1, NULL);
    }

    // Finish all printing out to terminal
    fflush(stdout);
}

void DrawNewFrame() {
    EndDrawing(); // Begins the drawing of next frame
    BeginDrawing(); // Begins the drawing of next frame

    ClearBackground(RAYWHITE);
    DrawBackgroundWithFade(0.6);
    if (WindowShouldClose()) {
        exit(0);
    }
}

void DrawTitle(char *title, float font_size, Vector2 position_of_title_0_to_1) {
    float x = GetWindowSize().x * position_of_title_0_to_1.x;
    float y = GetWindowSize().y * position_of_title_0_to_1.y;

    int width_of_title = MeasureText(title, Min(GetWindowSize())*font_size);
    int height_of_title = Min(GetWindowSize())*font_size;

    Vector2 text_position = {
        x - width_of_title/2,
        x - height_of_title/2,
    };
    DrawRectangle(text_position.x-7, text_position.y-7, width_of_title+14, height_of_title+14, BLACK);
    DrawRectangle(text_position.x-4, text_position.y-4, width_of_title+8, height_of_title+8, WHITE);
    DrawText(title, text_position.x, text_position.y, Min(GetWindowSize())*font_size, BLACK);
}

//------------------------------------------------------------------------------------
// Function for starting the fitness application
//------------------------------------------------------------------------------------
void OpenApplication() {

    // Make it so that only important warnings are printed out
    SetTraceLogLevel(LOG_WARNING);

    // Open the actual window
    InitWindow(450, 800, "Fitness");

    // Make the window resizable
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // Setting exit key to nothing, so the ESCAPE key doesn't turn off the application
    SetExitKey(KEY_NULL);

    // run at 60 frames-per-second
    SetTargetFPS(FRAMES_PER_SECOND);

    // Loading background image
    background_image = LoadTexture(BACKGROUND_IMAGE);

    float seconds_since_start = 0.0;

    // Main application loop
    while (seconds_since_start < 2)
    {
        if (WindowShouldClose()) {
            exit(0);
        }
        Vector2 window_size = GetWindowSize();

        // x frame = 1 second
        // x = second/frame = 1/FRAMES_PER_SECOND
        // x = 1/FRAMES_PER_SECOND
        seconds_since_start += 1.0 / (float)FRAMES_PER_SECOND;

        BeginDrawing();
            if (seconds_since_start < 1) {
                ClearBackground(BLACK);
                DrawRectangle(0, 0, window_size.x, window_size.y, Fade(RAYWHITE, seconds_since_start));
            } else {
                ClearBackground(RAYWHITE);
                float fade = seconds_since_start - 1;
                DrawBackgroundWithFade(fade * 0.6);
            }
        EndDrawing();
    }
    BeginDrawing();
}

int DrawButton(char *text, float font_size, Rectangle area_0_to_1) {
    Vector2 rec_size = Vector2Multiply(GetWindowSize(), (Vector2){area_0_to_1.width, area_0_to_1.height});
    Vector2 rec_middle = Vector2Multiply(GetWindowSize(), (Vector2){area_0_to_1.x, area_0_to_1.y});
    Vector2 rec_top_left = Vector2Subtract(rec_middle, Vector2Scale(rec_size, 0.5));
    Rectangle r = PosAndSizeToRectangle(rec_top_left, rec_size);
    GuiSetStyle(DEFAULT, TEXT_SIZE, (int)( Min(GetWindowSize()) * font_size));
    GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, (int)(Min(GetWindowSize())*font_size));

    return GuiButton(r, text);
}
