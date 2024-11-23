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
// Type and Structure Definitions
//------------------------------------------------------------------------------------------
typedef struct {
    char *title;
    char *middle_button;
    char *left_button;
    char *right_button;
    void (*customUIFunction)(void); // This is if for if you want to add custom UI features
} Interface;

//------------------------------------------------------------------------------------------
// Function Definitions
//------------------------------------------------------------------------------------------
Vector2 GetWindowSize()
{
    return (Vector2){GetScreenWidth(), GetScreenHeight()};
};

Rectangle PosAndSizeToRectangle(Vector2 position, Vector2 size)
{
    return (Rectangle){
        .x = position.x,
        .y = position.y,
        .width = size.x,
        .height = size.y};
}

float Max(Vector2 v)
{
    return v.x > v.y ? v.y : v.x;
}

// Draw text (using default font)
void DrawTextV(char *text, Vector2 pos, int fontSize, Color color)
{
    DrawText(text, pos.x, pos.y, fontSize, color);
}

void DrawBackgroundTexture(float fade)
{
    Color whiteFade = Fade(WHITE, fade);
    Vector2 window_size = GetWindowSize();

    background_x += 2 * BACKGROUND_SPEED;
    background_y += 1 * BACKGROUND_SPEED;
    background_x = fmodf(background_x, background_image.width);
    background_y = fmodf(background_y, background_image.height);

    float scale = Max(Vector2Divide(window_size, (Vector2){background_image.width, background_image.height}));


    // drawing the image until it fills the entire background of the window
    for (float i = scale*(background_x-background_image.width); i < window_size.x; i += background_image.width * scale)
    {
        for (float j = scale*(background_y-background_image.height); j < window_size.y; j += background_image.height * scale)
        {
            // Draw a part of a texture defined by the rectangle texture_source
            DrawTextureEx(background_image, (Vector2){i, j}, 0, scale, whiteFade); // Draw a Texture2D with extended parameters
        }
    }
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
    while (!(WindowShouldClose() || seconds_since_start > 2))
    {
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
                DrawBackgroundTexture(fade * 0.6);
            }
            DrawFPS(10, 10);
        EndDrawing();
    }
}

//------------------------------------------------------------------------------------
// Function for starting the fitness application
//------------------------------------------------------------------------------------
char *UseInterface(Interface interface)
{
    // Variabe definitions
    float seconds_since_transition = 0;
    char *buttonPressed = NULL;

    // Main application loop
    while (!WindowShouldClose())
    {
        seconds_since_transition += 1.0 / (float)FRAMES_PER_SECOND;
        Vector2 window_size = GetWindowSize();
        Vector2 windowMiddle = Vector2Scale(window_size, 0.5);
        int fontSize = Max(window_size) / 10;
        GuiSetStyle(DEFAULT, TEXT_SIZE, (int)((float)fontSize * (1.0 / 3.0)));
        GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, (int)((float)fontSize * (1.0 / 3.0)));

        if (IsKeyPressed(KEY_D))
        {
            debug_mode_grid = !debug_mode_grid;
        }
        int isTransitioning = seconds_since_transition < 1;
        float fade = 1.0;
        if (isTransitioning)
        {
            fade = seconds_since_transition;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawBackgroundTexture(0.6);

            int width_of_title = MeasureText(interface.title, fontSize);
            int height_of_title = fontSize;
            Vector2 TextSize = {width_of_title, height_of_title};
            Vector2 text_position = Vector2Subtract(windowMiddle, Vector2Scale(TextSize, 0.5));
            DrawRectangleV(Vector2Subtract(text_position, (Vector2){7, 7}), Vector2Add(TextSize, (Vector2){14, 14}), Fade(BLACK, fade));
            DrawRectangleV(Vector2Subtract(text_position, (Vector2){4, 4}), Vector2Add(TextSize, (Vector2){8, 8}), Fade(WHITE, fade));
            DrawTextV(interface.title, text_position, fontSize, Fade(BLACK, fade));

            if (!isTransitioning)
            {
                Vector2 rec_size = Vector2Multiply(window_size, (Vector2){0.3, 0.2});
                Vector2 rec_middle = {windowMiddle.x, window_size.y * (11.0 / 15.0)};
                Vector2 rec_top_left = Vector2Subtract(rec_middle, Vector2Scale(rec_size, 0.5));
                Rectangle r = PosAndSizeToRectangle(rec_top_left, rec_size);

                int any_button_pressed = 0;
                if (interface.middle_button != NULL)
                {
                    int is_button_pressed = GuiButton(r, interface.middle_button);
                    if (is_button_pressed)
                    {
                        any_button_pressed = true;
                        buttonPressed = interface.middle_button;
                    }
                }
            }

            DrawFPS(10, 10);

            if (debug_mode_grid) {
                GuiGrid(PosAndSizeToRectangle(Vector2Zero(), window_size), NULL, window_size.x / 10, 1, NULL);
            }
        EndDrawing();

        fflush(stdout);
        if (buttonPressed != NULL) {
            return buttonPressed;
        }
    }
    return "";
}
