#include <stdio.h>
#include <math.h>

#define BACKGROUND_IMAGE "../../content/workout-images.png"
#include "frontend.c"

int main() {

    // Opens the application window and adds a background.
    OpenApplication();

    // title height, used to draw it later
    float title_text_height = 0.2;

    // button's text height
    float button_text_height = 0.05;

    // We'll close the window when the button
    int button_pressed = 0;

    // Main application loop
    while (!button_pressed) {
        DrawNewFrame();

        DrawTitle("Fitness", title_text_height, AtPos(0.5, 0.5));

        button_pressed = DrawButton("Type your\nWhy", button_text_height, InArea(AtPos(0.5, 11.0/15.0), WithSize(0.3, 0.2)));
        if (button_pressed) {
            printf("You pressed the middle button!\n");
        }
    }

    return 0;
}
