#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.c"

#define BACKGROUND_SPEED 0.5
#define FRAMES_PER_SECOND 60
#define SECONDS_PER_FRAME (1.0/(float)FRAMES_PER_SECOND)
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
    if (v.x > v.y) {
        return v.y;
    } else {
        return v.x;
    }
}

float Max(Vector2 v) {
    if (v.x < v.y) {
        return v.y;
    } else {
        return v.x;
    }
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

// Sets up a new frame without a background
void DrawNewEmptyFrame() {
    EndDrawing(); // Ends drawing the last frame
    BeginDrawing(); // Begins drawing the next frame
    if (WindowShouldClose()) {
        UnloadTexture(background_image);
        EndDrawing();
        CloseWindow();
        exit(0);
    }
}

// Draw background with a specific fade, making it semi-transparent
void DrawBackgroundWithFade(float fade_0_to_1) {

    // whiteFade will decide how much the background fades
    Color whiteFade = Fade(WHITE, fade_0_to_1);

    // move backgrounds at the speed BACKGROUND_SPEED
    background_x += 2 * BACKGROUND_SPEED;
    background_y += 1 * BACKGROUND_SPEED;

    // mod the position of the background so that it's always on the top left of the screen
    background_x = fmodf(background_x, background_image.width);
    background_y = fmodf(background_y, background_image.height);

    // scale background when window size is changed
    float scale = Min(Vector2Divide(GetWindowSize(), AtPos(background_image.width, background_image.height)));

    // drawing the background_image until it fills the entire background of the window, because the background image is smaller than the window size
    for (float i = scale*(background_x-background_image.width); i < GetWindowSize().x; i += background_image.width * scale) {
        for (float j = scale*(background_y-background_image.height); j < GetWindowSize().y; j += background_image.height * scale) {
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

// Sets up a new frame to draw on, usually called in a while loop.
// Background is also drawn with this function.
void DrawNewFrame() {
    // First draws an empty frame
    DrawNewEmptyFrame();

    // Then with background raywhite
    ClearBackground(RAYWHITE);

    // Then background with background image but faded a bit
    DrawBackgroundWithFade(0.6);
}

// Draw text on a white background with a black border.
void DrawTitle(char *title, float text_height_0_to_1, Vector2 position_of_title_0_to_1) {

    // Translate from 0_to_1 units to use pixels instead, which is gotten by multiplying by GetWidnowSize()
    // Min() is used, so that the text scales to window size by the size that's smallest.
    float text_pixel_height = Min(GetWindowSize())*text_height_0_to_1;

    // spacing is the distance between the lines of the title.
    SetTextLineSpacing(text_pixel_height);

    float height_of_title = MeasureTextEx(GetFontDefault(), title, text_pixel_height, 10).y;
    float width_of_title = MeasureText(title, text_pixel_height);
    Vector2 position = Vector2Multiply(GetWindowSize(), position_of_title_0_to_1);
    Vector2 text_top_left = {
        position.x - width_of_title/2,
        position.y - height_of_title/2,
    };
    // TODO: make border scale, or text scale to be smaller.
    // Currently the border is too thick when window is small and too thin when window is large.
    DrawRectangle(text_top_left.x-7, text_top_left.y-7, width_of_title+14, height_of_title+14, BLACK);
    DrawRectangle(text_top_left.x-4, text_top_left.y-4, width_of_title+8, height_of_title+8, WHITE);
    DrawText(title, text_top_left.x, text_top_left.y, text_pixel_height, BLACK);
}

int DrawButton(char *text, float text_height_0_to_1, Rectangle area_0_to_1) {
    Vector2 rec_size = Vector2Multiply(GetWindowSize(), (Vector2){area_0_to_1.width, area_0_to_1.height});
    Vector2 rec_middle = Vector2Multiply(GetWindowSize(), (Vector2){area_0_to_1.x, area_0_to_1.y});
    Vector2 rec_top_left = Vector2Subtract(rec_middle, Vector2Scale(rec_size, 0.5));
    Rectangle r = PosAndSizeToRectangle(rec_top_left, rec_size);
    GuiSetStyle(DEFAULT, TEXT_SIZE, Min(GetWindowSize()) * text_height_0_to_1);
    GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, Min(GetWindowSize())*text_height_0_to_1);

    return GuiButton(r, text);
}

//------------------------------------------------------------------------------------
// Function for starting the fitness application
//------------------------------------------------------------------------------------
void OpenApplication() {

    // Make it so that only important warnings are printed out
    SetTraceLogLevel(LOG_WARNING);

    // Open the actual window
    InitWindow(440, 956, "Fitness");
    SetWindowMinSize(1, 1);

    // Make the window resizable
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // Setting exit key to nothing, so the ESCAPE key doesn't turn off the application
    SetExitKey(KEY_NULL);

    // run at 60 frames-per-second
    SetTargetFPS(FRAMES_PER_SECOND);

    // Loading background image
    background_image = LoadTexture(BACKGROUND_IMAGE);

    // Setup the first frame.
    // The BeginDrawing here is useful for DrawNewEmptyFrame, since now it can both stop last frame and start a new one
    BeginDrawing();

    // Starting the first animation, 1 second long, from black to RayWhite.
    // RayWhite is a nicer shade of White
    for (float t=0; t<1; t+=SECONDS_PER_FRAME) {

        // Setup frame without background
        DrawNewEmptyFrame();

        // Transition from black by making a black background and drawing white ontop with fade.
        ClearBackground(BLACK);

        // Using ClearBackground to draw a transparent background doesn't work, so drawing a rectangle should work.
        DrawRectangleV(AtPos(0, 0), GetWindowSize(), Fade(RAYWHITE, t));
    }

    // Another animation, from white to the fitness icons background
    for (float t=0; t<1; t+=SECONDS_PER_FRAME) {
        DrawNewEmptyFrame();
        ClearBackground(RAYWHITE);
        DrawBackgroundWithFade(t * 0.6);
    }
}
