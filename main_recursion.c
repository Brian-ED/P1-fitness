#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "src/Parsa/Funktioner.c"

// #define BACKGROUND_IMAGE "content/workout-images.png"
// #include "src/frontend-brian/frontend.c"

// User has been in the application before, so we say welcome back.
void welcome_back() {
    printf("Welcome back!");
    // TODO: Program ends here, but when a user comes back, they should be going to the "update weight" question.
}

void the_program_made() {
    // TODO
}

void start_introduction() {
    printf("Hey! you need to type in your user information!");
    Introduction();
    why();
    info();
    program();
    needs();
    the_program_made();
}

void start_app() {
    char answer;
    printf("Welcome, have you opened the app before?\n");
    printf("Type [Y] for yes, [N] for no:\n");
    scanf("%c", &answer);

    if (answer == 'y' || answer == 'Y') {
        welcome_back();
    } else if (answer == 'n' || answer == 'N') {
        start_introduction();
    } else {
        start_app(); // starting over
    }
}

int main() {
    start_app();
    return 0;
}