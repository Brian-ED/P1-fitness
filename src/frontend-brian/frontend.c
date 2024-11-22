#include <raylib.h>
#include <raymath.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.c"

#define BACKGROUND_SPEED 0.5
#define FRAMES_PER_SECOND 60


int debug_mode_grid = false;
char *ui_center_button_text = NULL;

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum {
  WINDOW_MODE_MAIN_MENU,
} ApplicationMode;

ApplicationMode window_mode = WINDOW_MODE_MAIN_MENU;

Vector2 GetWindowSize() {
    return (Vector2){GetScreenWidth(), GetScreenHeight()};
};

Rectangle PosAndSizeToRectangle(Vector2 position, Vector2 size) {
    return (Rectangle){
        .x      = position.x,
        .y      = position.y,
        .width  = size.x,
        .height = size.y
    };
}

float Max(Vector2 v) {
    return v.x>v.y ?v.y :v.x;
}

// Draw text (using default font)
void DrawTextV(char *text, Vector2 pos, int fontSize, Color color) {
    DrawText(text, pos.x, pos.y, fontSize, color);
}

void DrawBackgroundTexture(Texture background, float background_x, float background_y, float fade) {
    Color whiteFade = Fade(WHITE, fade);
    Vector2 window_size = GetWindowSize();

    float scale = Max(Vector2Divide(window_size, (Vector2){background.width, background.height}));

    background_x *= scale;
    background_y *= scale;

    background_x -= background.width;
    background_y -= background.height;

    // drawing the image until it fills the entire background
    for (float i=background_x; i<window_size.x; i+=background.width*scale) {
        for (float j=background_y; j<window_size.y; j+=background.height*scale) {
            // Draw a part of a texture defined by the rectangle texture_source
            DrawTextureEx(background, (Vector2){i, j}, 0, scale, whiteFade);  // Draw a Texture2D with extended parameters
        }
    }
}

//------------------------------------------------------------------------------------
// Function for starting the fitness application
//------------------------------------------------------------------------------------
void OpenApplication() {

    // Setup before running app
    //--------------------------------------------------------------------------------------

    // Make it so that only important warnings are printed out
    SetTraceLogLevel(LOG_WARNING);

    // Open the actual window
    InitWindow(450, 800, "Fitness");

    // Make it so the window is resizable when the app is run on Windows, Linux and Mac
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // Setting exit key to nothing, so the ESCAPE key doesn't turn off the application
    SetExitKey(KEY_NULL);

    // run at 60 frames-per-second
    SetTargetFPS(FRAMES_PER_SECOND);

}

//------------------------------------------------------------------------------------
// Function for starting the fitness application
//------------------------------------------------------------------------------------
char *StartScreen() {

    // Variabe definitions
    float seconds_since_transition = 0;
    char *buttonPressed = NULL;

    // Loading background image
    Texture tex = LoadTexture(BACKGROUND_IMAGE);
    float background_x = 0;
    float background_y = 0;

    Color titleColor = BLACK;

    // Main application loop
    while (!WindowShouldClose()) {
        Vector2 window_size = GetWindowSize();
        Vector2 windowMiddle = Vector2Scale(window_size, 0.5);
        int fontSize = Max(window_size)/10;
        GuiSetStyle(DEFAULT, TEXT_SIZE, (int)((float)fontSize*(1.0/3.0)));
        GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, (int)((float)fontSize*(1.0/3.0)));

        ApplicationMode last_window_mode = window_mode;
        int window_changed = (last_window_mode != window_mode);

        // x frame = 1 second
        // x = second/frame = 1/FRAMES_PER_SECOND
        // x = 1/FRAMES_PER_SECOND
        seconds_since_transition += 1.0/(float)FRAMES_PER_SECOND;

        if (window_changed) {
            seconds_since_transition = 0.0;
        }

        if (IsKeyPressed(KEY_D)) {
            debug_mode_grid = !debug_mode_grid;
        }
        BeginDrawing();
            background_x += 2 * BACKGROUND_SPEED;
            background_y += 1 * BACKGROUND_SPEED;
            background_x = fmodf(background_x, tex.width);
            background_y = fmodf(background_y, tex.height);
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
                    DrawBackgroundTexture(tex, background_x, background_y, fade*0.6);

                    char *fitnessTitle = "Fitness";
                    int LengthOfFitnessTitle = MeasureText(fitnessTitle, fontSize);
                    Vector2 TextSize = {LengthOfFitnessTitle, fontSize};
                    Vector2 text_position = Vector2Subtract(windowMiddle, Vector2Scale(TextSize, 0.5));
                    DrawRectangleV(Vector2Subtract(text_position, (Vector2){7,7}), Vector2Add(TextSize, (Vector2){14,14}), Fade(BLACK,fade));
                    DrawRectangleV(Vector2Subtract(text_position, (Vector2){4,4}), Vector2Add(TextSize, (Vector2){8,8}), Fade(WHITE,fade));
                    DrawTextV(fitnessTitle, text_position, fontSize, Fade(titleColor,fade));

                    if (!isTransitioning) {
                        Vector2 rec_size = Vector2Multiply(window_size, (Vector2){0.3, 0.2});
                        Vector2 rec_middle = {windowMiddle.x, window_size.y*(11.0/15.0)};
                        Vector2 rec_top_left = Vector2Subtract(rec_middle, Vector2Scale(rec_size,0.5));
                        Rectangle r = PosAndSizeToRectangle(rec_top_left, rec_size);

                        int any_button_pressed = 0;
                        if (ui_center_button_text != NULL) {
                            int is_button_pressed = GuiButton(r, ui_center_button_text);
                            if (is_button_pressed) {
                                any_button_pressed = true;
                                buttonPressed = ui_center_button_text;
                            }
                        }
                        if (any_button_pressed) {
                            ui_center_button_text = NULL;
                        }
                    }

                    ClearBackground(RAYWHITE);
                }
                DrawFPS(10, 10);
            }

            if (debug_mode_grid) {
                GuiGrid(PosAndSizeToRectangle(Vector2Zero(), window_size), NULL,  window_size.x/10, 1, NULL);
            }

            if (buttonPressed != NULL) {
                return buttonPressed;
            }

            fflush(stdout);
        EndDrawing();
    }
    return "";
}
