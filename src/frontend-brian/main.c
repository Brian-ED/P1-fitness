#include <stdio.h>
#include <math.h>

#define BACKGROUND_IMAGE "../../content/workout-images.png"
#include "frontend.c"

int main() {

    // Opens the application window and adds a background.
    OpenApplication();

    // Title height, used to draw it later
    float title_text_height = 0.2;

    // Button's text height
    float button_text_height = 0.05;

    // We'll close the window when the button is pressed
    int button_pressed = 0;

    // Main application loop
    while (!button_pressed) {

        // We prepare a new frame on screen for the user to see
        DrawNewFrame();

        // Draw the title
        DrawTitle("Fitness", title_text_height, AtPos(0.5, 0.5));

        // Draw the button and asks if it was pressed,
        // so button_pressed becomes true if button was pressed
        button_pressed = DrawButton("Type your\nWhy", button_text_height, InArea(AtPos(0.5, 11.0/15.0), WithSize(0.3, 0.2)));

        // If button was pressed, print something
        if (button_pressed) {
            printf("You pressed the middle button!\n");
        }
    }

    return 0;
}
