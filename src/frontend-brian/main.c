#include <stdio.h>
#include <math.h>

#define BACKGROUND_IMAGE "../../content/workout-images.png"
#include "frontend.c"

int main() {
    OpenApplication();

    char *title = "Fitness";
    char *middle_button = "Type your\nWhy";
    int button_pressed = 0;
    float fontSize = 0.1;

    // Main application loop
    while (!button_pressed) {
        DrawNewFrame();

        DrawTitle(title, fontSize, AtPos(0.5, 0.5));

        button_pressed = DrawButton(middle_button, fontSize/3.0, 0.5, 11.0/15.0, 0.3, 0.2);
        if (button_pressed) {
            printf("You pressed the middle button!\n");
        }

    }

    return 0;
}
