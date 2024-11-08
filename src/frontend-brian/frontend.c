#include <raylib.h>

typedef enum {
  WINDOW_MODE_MAIN_MENU,
} WindowMode;

WindowMode window_mode = WINDOW_MODE_MAIN_MENU;

void Start() {
  SetTraceLogLevel(LOG_WARNING);

  const int screenWidth = 800;
  const int screenHeight = 450;
  const int fontSize = 40;

  int frames_since_transition = WINDOW_MODE_MAIN_MENU;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - window flags");

  Texture tex = LoadTexture("../../content/workout-images.png");
  Vector2 texPosition = {.x=-400, .y=-300};
  Rectangle texSource = {.x=0, .y=0, .width=936, .height=1000};

  // run at 60 frames-per-second
  SetTargetFPS(60);

  char *fitnessTitle = "Fitness";
  int LengthOfFitnessTitle = MeasureText(fitnessTitle, fontSize);

  while (!WindowShouldClose()) {

    WindowMode last_window_mode = window_mode;
    int window_changed = (last_window_mode != window_mode);

    frames_since_transition += 1;

    if (window_changed) {
      frames_since_transition = 0;
    }

    BeginDrawing();
      texPosition.x += 2;
      texPosition.y += 1;
      ClearBackground(BLACK);

      if (window_mode == WINDOW_MODE_MAIN_MENU) {
        if (frames_since_transition<60) {
          // Get color lerp interpolation between two colors, factor [0.0f..1.0f]
          DrawRectangle(0, 0, screenWidth, screenHeight, Fade(RAYWHITE, (float)frames_since_transition/60.0f));
        } else if (frames_since_transition<60*2) {
          Color blackFade = Fade(BLACK, (float)(frames_since_transition-60)/60.0f);
          Color whiteFade = Fade(WHITE, (float)(frames_since_transition-60)/60.0f);
          DrawTextureRec(tex, texSource, texPosition, whiteFade);            // Draw a part of a texture defined by a rectangle
          DrawText(fitnessTitle, (screenWidth-LengthOfFitnessTitle)/2 , screenHeight/2 - 50, fontSize, blackFade);
          ClearBackground(RAYWHITE);
        } else {
          DrawTextureRec(tex, texSource, texPosition, WHITE);            // Draw a part of a texture defined by a rectangle
          DrawText(fitnessTitle, (screenWidth-LengthOfFitnessTitle)/2, screenHeight/2 - 50, fontSize, BLACK);
          ClearBackground(RAYWHITE);
        }
        DrawFPS(10, 10);
      }
    EndDrawing();
  }

  UnloadTexture(tex);
  CloseWindow();
}
