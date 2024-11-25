#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "src/Parsa/Funktioner.c"
#include "src/frontend-brian/frontend.c"

// #define BACKGROUND_IMAGE "content/workout-images.png"
// #include "src/frontend-brian/frontend.c"

int main() {
    char answer;

    // This is a "Label" named start_app.
    // This means that if you run "goto start_app;",
    // we jump to this line and continue running code.
    start_app:
        printf("Welcome, have you opened the app before?\n");
        printf("Type [Y] for yes, [N] for no:\n");
        scanf("%c", &answer);

        if (answer == 'y' || answer == 'Y') {
            goto welcome_back;
        } else if (answer == 'n' || answer == 'N') {
            goto start_introduction;
        } else {
            goto start_app; // starting over
        }

    welcome_back: // User has been in the application before, so we say welcome back.
        printf("Welcome back!");
        goto end_program; // TODO: "goto end_program;" ends the program, but when a user comes back, they should be going to the "update weight" question.

    start_introduction:
        printf("Hey! you need to type in your user information!");
        Introduction();
        why();
        info();
        program();
        needs();
        goto the_program_made;

    the_program_made:
        goto end_program;

    end_program:
        return 0;
}