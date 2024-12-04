#include <stdio.h>
#include <math.h>

#define BACKGROUND_IMAGE "../../../content/workout-images.png"
#include "../../frontend-brian/frontend.c"

int main() {

    // Opens the application window and adds a background.
    OpenApplication();

    // Title height, used to draw it later
    float title_text_height = 0.2/*t2*/;

    // Button's text height
    float button_text_height = 0.05/*t1*/;

    // We'll close the window when the button
    int button_pressed = 0;

    // Main application loop
    while (!button_pressed) {

        // We prepare a new frame on screen for the user to see
        DrawNewFrame();/*T1*/

        // Draw the title
        DrawTitle("Fitness", title_text_height, AtPos(0.5/*x2*/, 0.5/*y2*/));

        // Draw the button and asks if it was pressed,
        // so button_pressed becomes true if button was pressed
        button_pressed = DrawButton("Type your\nWhy", button_text_height, InArea(AtPos(0.5/*x1*/, 0.733/*y1*/), WithSize(0.3/*w1*/, 0.2/*h1*/)));

        DrawButton("Type your\nHalliluja", 0.1/*t4*/, InArea(AtPos(0.5/*x4*/, 0.2/*y4*/), WithSize(0.6/*w4*/, 0.2/*h4*/)));

        // If button was pressed, print something
        if (button_pressed) {
            printf("You pressed the middle button!\n");
        }
    }

    return 0;
}
