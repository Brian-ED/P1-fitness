#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "src/Parsa/Funktioner.c"
#define BACKGROUND_IMAGE "content/workout-images.png"
#include "src/frontend-brian/frontend.c"

int main() {
    char answer;

    // This is a "Label" named start_app.
    // This means that if you run "goto start_app;",
    // we jump to this line and continue running code.
    start_app:
        printf("Welcome, have you opened the app before?\n");
        printf("Type [Y] for yes, [N] for no:");
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
       Introduction();
       node *firstnode = scaningwhy();
       info();
       program();
       needs();
       to_file(firstnode, age, height, weight, gender2, protein, calorie);
       free_space(firstnode);
       printf("open the document \"User_Data\" to view relevant data related to your training journey");
       system("notepad C:\\Users\\parsa\\OneDrive\\Desktop\\P1-fitness\\src\\Parsa\\User_Data");
       goto the_program_made;

    the_program_made:
        goto end_program;

    end_program:
        return 0;
}