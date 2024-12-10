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
    fprintf(stdin, "\n");
    fprintf(stdout, "\n");
    fflush(stdout);
    fflush(stdin);
    Introduction();
    node *firstnode = scaningwhy();
    info();
    program();
    needs();
    to_file(firstnode, age, height, weight, gender, protein, calorie);
    free_space(firstnode);
    printf("open the document \"User_Data\" to view relevant data related to your training journey");
    system("notepad User_Data");
}

void start_app() {
    char answer;
    printf("Welcome, have you opened the app before?\n");
    printf("Type [Y] for yes, [N] for no:\n");
    scanf("%c", &answer);
    printf("\n");

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