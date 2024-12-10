#include <stdio.h>
#include <math.h>

// below is a file path to the thebackground image, .. means go out of folder, and name of folder means go into folder, seperated by "/"s
#define BACKGROUND_IMAGE "../../content/workout-images.png"
#include "frontend.c"

int DrawCheckbox(Vector2 pos, char *text, int checked) {
    float size = 0.05*Min(GetWindowSize());
    bool checkedBool = checked;
    GuiCheckBox((Rectangle){pos.x, pos.y, size, size}, text, &checkedBool);                          // Check Box control, returns true when active
    return checkedBool;
}

int main() {

    // Opens the application window and adds a background.
    OpenApplication();

    // Title height, used to draw it later
    float title_text_height = 0.2;

    // Button's text height
    float button_text_height = 0.05;

    // We'll close the window when the button is pressed
    int button_pressed = 0;
    int checked = 0;

    // Main application loop
    while (!button_pressed) {

        // We prepare a new frame on screen for the user to see
        DrawNewFrame();

        // Draw the title
        DrawTitle("Fitness", title_text_height, AtPos(0.5, 0.5));

        // Draw the button and asks if it was pressed,
        // so button_pressed becomes true if button was pressed
        button_pressed = DrawButton("Press to begin", button_text_height,
            InArea(AtPos(0.5, 0.8), WithSize(0.3, 0.2))
            // same as (Rectangle){.x=0.5, .y=0.8, .width=.3, .height=0.2}
        );
        int checked = DrawCheckbox(AtPos(20,20), "Hello", checked);

        // If button was pressed, print something
        if (button_pressed) {
            printf("You pressed the middle button!\n");
        }
    }

    return 0;
}
