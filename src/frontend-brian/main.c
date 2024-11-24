#include <stdio.h>
#include <math.h>

#define BACKGROUND_IMAGE "../../content/workout-images.png"
#include "frontend.c"

int main() {
    OpenApplication();

    char *title = "Fitness";
    char *title2 = "Fit\nness";
    float title_height = 0.2;


    char *button_text = "Type your\nWhy";
    float button_text_height = 0.03;

    int button_pressed = 0;

    // Main application loop
    while (!button_pressed) {
        DrawNewFrame();

        DrawTitle(title, title_height, AtPos(0.5, 0.5));
        DrawTitle(title2, title_height, AtPos(0.5, 0.2));

        button_pressed = DrawButton(button_text, button_text_height, InArea(AtPos(0.5, 11.0/15.0), WithSize(0.3, 0.2)));
        if (button_pressed) {
            printf("You pressed the middle button!\n");
        }
    }

    return 0;
}
