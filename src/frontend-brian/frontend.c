#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.c"

#define BACKGROUND_SPEED 0.5


//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum {
  WINDOW_MODE_MAIN_MENU,
} WindowMode;

WindowMode window_mode = WINDOW_MODE_MAIN_MENU;

Vector2 GetWindowSize() {
    return (Vector2){GetScreenWidth(), GetScreenHeight()};
};

Vector2 Vector2Mod(Vector2 divided, Vector2 divider) {
    int xd = (int)divider.x;
    int yd = (int)divider.y;
    return (Vector2){
        (float)( ((int)divided.x % xd + xd) % xd),
        (float)( ((int)divided.y % yd + yd) % yd),
    };
}

Rectangle Vector2ToRectangle(Vector2 position, Vector2 size) {
    return (Rectangle){
        .x      = position.x,
        .y      = position.y,
        .width  = size.x,
        .height = size.y
    };
}

float Min(Vector2 v) {
    return v.x>v.y ?v.x :v.y;
}
float Max(Vector2 v) {
    return v.x>v.y ?v.y :v.x;
}

// Draw text (using default font)
void DrawTextV(char *text, Vector2 pos, int fontSize, Color color) {
    DrawText(text, pos.x, pos.y, fontSize, color);
}

void DrawBackgroundTexture(Texture tex, Rectangle texSource, Vector2 texOffset, float fade) {
    Color whiteFade = Fade(WHITE, fade);
    Vector2 texSize = {texSource.width, texSource.height};
    Vector2 backgroundSize = GetWindowSize();

    // drawing the image until it fills the entire background
    for (float i=texOffset.x; i<backgroundSize.x; i+=texSource.width) {
        for (float j=texOffset.y; j<backgroundSize.y; j+=texSource.height) {
            // Draw a part of a texture defined by a rectangle
            DrawTextureRec(tex, texSource, (Vector2){i, j}, whiteFade);
        }
    }
}

//------------------------------------------------------------------------------------
// Function for starting the fitness application
//------------------------------------------------------------------------------------
void StartApplication(char *background_image_file_path) {

    // Variabe definitions
    Vector2 window_size = {800.0, 450.0};
    float seconds_since_transition = 0;
    bool buttonOn = false;

    // Setup before running app
    //--------------------------------------------------------------------------------------

    // Make it so that only important warnings are printed out
    SetTraceLogLevel(LOG_WARNING);

    // Open the actual window
    InitWindow((int)window_size.x, (int)window_size.y, "Fitness");

    // Make it so the window is resizable when the app is run on Windows, Linux and Mac
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // Setting exit key to nothing, so the ESCAPE key doesn't turn off the application
    SetExitKey(KEY_NULL);

    // Loading background image
    Texture tex = LoadTexture(background_image_file_path);
    Vector2 texPosition = {.x=0, .y=0};
    Vector2 texSize = {.x=936, .y=1000};
    Rectangle texSource = {.x=0, .y=0, .width=texSize.x, .height=texSize.y};
    Color titleColor = BLACK;

    // run at 60 frames-per-second
    int fps = 60;
    SetTargetFPS(fps);

    // Main application loop
    while (!WindowShouldClose()) {
        window_size = GetWindowSize();
        Vector2 windowMiddle = Vector2Scale(window_size, 0.5);
        int fontSize = Max(window_size)/10;
        GuiSetStyle(DEFAULT, TEXT_SIZE, (int)((float)fontSize*(1.0/3.0)));
        GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, (int)((float)fontSize*(1.0/3.0)));

        WindowMode last_window_mode = window_mode;
        int window_changed = (last_window_mode != window_mode);

        // x frame = 1 second
        // x = second/frame
        // fps = frame/second
        // x = 1/fps
        seconds_since_transition += 1.0/(float)fps;

        if (window_changed) {
            seconds_since_transition = 0.0;
        }

        BeginDrawing();

            texPosition.x += 2 * BACKGROUND_SPEED;
            texPosition.y += 1 * BACKGROUND_SPEED;
            texPosition = Vector2Mod(texPosition, (Vector2){texSource.width, texSource.height});
            texPosition = Vector2Subtract(texPosition, texSize);
            ClearBackground(BLACK);

            if (window_mode == WINDOW_MODE_MAIN_MENU) {
                if (seconds_since_transition<1) {
                    // Get color lerp interpolation between two colors, factor [0.0f..1.0f]
                    DrawRectangle(0, 0, window_size.x, window_size.y, Fade(RAYWHITE, seconds_since_transition));
                } else {
                    int isTransitioning = seconds_since_transition<2;
                    float fade = 1.0;
                    if (isTransitioning) {
                        fade = seconds_since_transition-1;
                    }
                    DrawBackgroundTexture(tex, texSource, texPosition, fade*0.6);

                    char *fitnessTitle = "Fitness";
                    int LengthOfFitnessTitle = MeasureText(fitnessTitle, fontSize);
                    Vector2 TextSize = {LengthOfFitnessTitle, fontSize};
                    Vector2 TextPos = Vector2Subtract(windowMiddle, Vector2Scale( TextSize, 0.5));
                    DrawTextV(fitnessTitle, TextPos, fontSize, Fade(titleColor,fade));

                    if (!isTransitioning) {
                        Vector2 recSize = Vector2Multiply(window_size, (Vector2){0.20, 0.2});
                        Vector2 recMiddle = {windowMiddle.x, window_size.y*(11.0/15.0)};
                        Vector2 recTopLeft = Vector2Subtract(recMiddle, Vector2Scale(recSize,0.5));
                        Rectangle r = Vector2ToRectangle(recTopLeft, recSize);
                        buttonOn = GuiButton(r, "Type your\nwhy");
                    }

                    ClearBackground(RAYWHITE);
                }
                DrawFPS(10, 10);
            }
            if (buttonOn) {
                printf("ON!!\n");
            }else{
                printf("OFF!!\n");
            }

            fflush(stdout);
        EndDrawing();
    }

    UnloadTexture(tex);
    CloseWindow();
}
