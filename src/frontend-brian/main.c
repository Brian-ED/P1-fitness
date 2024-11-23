#include <stdio.h>
#include <math.h>

#define BACKGROUND_IMAGE "../../content/workout-images.png"
#include "frontend.c"

Interface titleWindow = {
    .title = "Fitness",
    .middle_button = "Type your\nWhy",
};

int main() {
    OpenApplication();

    char *button_pressed = UseInterface(titleWindow);

    if (button_pressed == titleWindow.middle_button) {
        printf("You pressed the middle button!\n");
    }

    return 0;
}
