#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.c"

#define BACKGROUND_SPEED 0.5
#define FRAMES_PER_SECOND 60
#define SECONDS_PER_FRAME (1.0/(float)FRAMES_PER_SECOND)

Texture background_image;
int debug_mode_grid = 0;
float background_x = 0;
float background_y = 0;

//------------------------------------------------------------------------------------------
// Function Definitions
//------------------------------------------------------------------------------------------

// Returns window size in pixels as a vector
Vector2 GetWindowSize() {
    // Vector2 here is the type for the following struct, struct is whatever is in the "{}"
    return (Vector2){GetScreenWidth(), GetScreenHeight()};
};

float Min(Vector2 v) {
    if (v.x > v.y) {
        return v.y;
    } else {
        return v.x;
    }
}

float Max(Vector2 v) {
    if (v.x < v.y) {
        return v.y; // When getting y from the struct v, use the . notation v.y
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

Rectangle ScaleArea(Rectangle area, Vector2 scale) {
    return (Rectangle){
        scale.x*area.x,
        scale.y*area.y,
        scale.x*area.width,
        scale.y*area.height,
    };
}

Rectangle ResizeArea(Rectangle area, Vector2 scale) {
    return (Rectangle){
        area.x,
        area.y,
        area.width,
        area.height,
    };
}

Rectangle AreaToRaylibRec(Rectangle area) {
    Rectangle retArea = ScaleArea(area, GetWindowSize());
    retArea.x -= retArea.width /2; // Moving to top left
    retArea.y -= retArea.height/2; // Moving to top left
    return retArea;
}

Vector2 SizeOfArea(Rectangle area) {
    return WithSize(area.width, area.height);
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
void DrawBackgroundWithFade(float fade_0to1) {

    // whiteFade will decide how much the background fades
    Color whiteFade = Fade(WHITE, fade_0to1);

    // move backgrounds at the speed BACKGROUND_SPEED
    background_x += 2 * BACKGROUND_SPEED;
    background_y += 1 * BACKGROUND_SPEED;

    // mod the position of the background so that it's always on the top left of the screen
    background_x = fmodf(background_x, background_image.width);
    background_y = fmodf(background_y, background_image.height);

    // scale background when window size is changed
    float scale = Min(Vector2Divide(
        GetWindowSize(),
        WithSize(background_image.width, background_image.height)
    ));

    // drawing the background_image until it fills the entire background of the window, because the background image is smaller than the window size
    for (float x = scale*(background_x-background_image.width); x < GetWindowSize().x; x += background_image.width * scale) {
        for (float y = scale*(background_y-background_image.height); y < GetWindowSize().y; y += background_image.height * scale) {
            // Draw a part of a texture defined by the rectangle texture_source
            DrawTextureEx(background_image, AtPos(x, y), 0, scale, whiteFade); // Draw a Texture2D with extended parameters
        }
    }

    // Toggle debug mode if user pressed ctrl+D
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_D)) {
        debug_mode_grid = !debug_mode_grid;
    }

    // Draw grid if debug mode is on
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

// Draw a white box with black background
void DrawBox(Rectangle area) {
    Rectangle black = AreaToRaylibRec(area);
    Rectangle white = black;

    float border_scale = 0.05*Min(SizeOfArea(white));
    white.x      += border_scale/2;
    white.y      += border_scale/2;
    white.width  -= border_scale;
    white.height -= border_scale;

    // TODO: make border scale, or text scale to be smaller.
    // Currently the border is too thick when window is small and too thin when window is large.
    DrawRectangle(black.x, black.y, black.width, black.height, BLACK);
    DrawRectangle(white.x, white.y, white.width, white.height, WHITE);
}

// Draw text on a white background with a black border.
void DrawTitle(char *title, float text_height_0to1, Vector2 position_of_title_0to1) {

    // Translate from 0to1 units to use pixels instead, which is gotten by multiplying by GetWidnowSize()
    // Min() is used, so that the text scales to window size by the size that's smallest.
    float text_pixel_height = Min(GetWindowSize())*text_height_0to1;

    // spacing is the distance between the lines of the title.
    SetTextLineSpacing(text_pixel_height);

    Vector2 title_size = {
        MeasureText(title, text_pixel_height),
        MeasureTextEx(GetFontDefault(), title, text_pixel_height, 10).y
    };
    DrawBox(InArea(position_of_title_0to1, Vector2Divide(title_size, GetWindowSize())));

    Vector2 position = Vector2Multiply(GetWindowSize(), position_of_title_0to1);
    Vector2 text_top_left = Vector2Subtract(position, Vector2Scale(title_size,0.5));
    DrawText(title, text_top_left.x, text_top_left.y, text_pixel_height, BLACK);
}

int DrawButton(char *text, float text_height_0to1, Rectangle area_0to1) {
    Rectangle area = AreaToRaylibRec(area_0to1);
    GuiSetStyle(DEFAULT, TEXT_SIZE, Min(GetWindowSize()) * text_height_0to1);
    GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, Min(GetWindowSize())*text_height_0to1);

    return GuiButton(area, text);
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
