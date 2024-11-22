#include <stdio.h>
#include <math.h>

#define BACKGROUND_IMAGE "../../content/workout-images.png"
#include "frontend.c"

int main() {
  OpenApplication();

  char *why_text = "Type your\nWhy";
  ui_center_button_text = why_text;

  char *button_pressed = StartScreen();

  if (button_pressed == why_text) {
    printf("You pressed the button!\n");
  }

  return 0;
}
