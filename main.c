#include <stdio.h>
#include <stdlib.h>

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

    welcome_back:
        printf("Welcome back!");
        goto end_program;

    start_introduction:
        printf("Hey! you need to type in your user information!");
        goto end_program;

    end_program:
        return 0;
}