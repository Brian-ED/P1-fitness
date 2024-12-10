#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "src/Parsa/Funktioner.c"
#include "src/Jonas/progression.c"

// #define BACKGROUND_IMAGE "content/workout-images.png"
// #include "src/frontend-brian/frontend.c"

void update_weight() {/*TODO*/}
void GetStats() {/*TODO*/}
void CreateProgressiveOverloadProgram() {/*TODO*/}
void WaitingOnInputFromUser() {/*TODO*/}
void IfUserNeedsGuidanceShowDescription() {/*TODO*/}
void ProgramRecievesInput() {/*TODO*/}
void ShowUserTheirStats() {/*TODO*/}
void LikeOrDislikeCertainExercises() {/*TODO*/}
void HowManyDaysAWeek() {/*TODO*/}

// This function marks when the workout program is setup and complete for the rest of the app's runtime.
// Only a restart can make it back here.
void TakesStatsAndCreateAProgressiveOverloadProgram() {
    GetStats();
    CreateProgressiveOverloadProgram();

    WaitingOnInputFromUser();
    IfUserNeedsGuidanceShowDescription();
    ProgramRecievesInput();
    ShowUserTheirStats();
    ShowUserTheirStats();
    CreateProgressiveOverloadProgram();
    exit(0);
}

void ChangeAmountOfDaysOrPreferredExercises() {
    printf("If you want to change days working out and exercies, input [D].");
    printf("If you just want to change exercies, input [E]");
    // TODO handle inputs other than E and D.
    char answer;
    scanf("%c", &answer);
    if (answer == 'D' || answer == 'd') {
        HowManyDaysAWeek();
    } else {
        LikeOrDislikeCertainExercises();
    }
}

void AskUserIfTheyWantToChangeExercises() {
    printf("Would you like to change workout program or exercises? [Y] for yes, [N] for no.\n");
    char answer;
    scanf("%c", &answer);
    if (answer == 'Y' || answer == 'y') {
        ChangeAmountOfDaysOrPreferredExercises();
    } else {
        TakesStatsAndCreateAProgressiveOverloadProgram();
    }
}

void UpdateWeight() {
    // TODO
};


// User has been in the application before, so we say welcome back.
void welcome_back() {
    char answer;

    printf("Welcome back!\n");

    printf("Do you want to update weight? [Y] for yes, [N] for no.\n");
    scanf("%c", &answer);
    if (answer == 'Y' || answer == 'y') {
        UpdateWeight();
    }
    AskUserIfTheyWantToChangeExercises();
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