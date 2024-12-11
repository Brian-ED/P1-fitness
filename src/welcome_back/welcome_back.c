#include <stdio.h>
#include <bool.h>

void show_welcome_back(){
    printf("Welcome back!\n");
}

bool AskUserIfTheyWantToChangeProgramOrExercises(){
    char yes;
    printf("Do you want to change how many days a week for exercises, and/or the exercises themselves?\n");
    printf("Type 1 for yes.\nType 0 for no\n");
    while ((yes = getchar()) == '\n') {}
    return yes == '1';
}

bool UserWantsToChangeOptionsAndOrWorkout(){
    char yes;
    printf("Do you want to change personal info?\n");
    printf("Type 1 for yes.\nType 0 for no\n");
    while ((yes = getchar()) == '\n') {}
    return yes == '1';
}

bool change_days_a_week_or_not(){
    char yes;
    printf("Do you want to change how many days you can work out a week?\n");
    printf("Type 1 for yes.\nType 0 for no\n");
    while ((yes = getchar()) == '\n') {}
    return yes == '1';
}

bool change_exercises_or_not(){
    char yes;
    printf("Do you want to change exercises?\n");
    printf("Type 1 for yes.\nType 0 for no\n");
    while ((yes = getchar()) == '\n') {}
    return yes == '1';
}

// Temporary function
void HowManyDaysAWeek() {
    printf("How many days a week?");
}

void ChangeWorkoutViaAskingQuestions() {
    if (change_days_a_week_or_not()) {
        HowManyDaysAWeek();
    }
    if (change_exercises_or_not()) {
        LikeOrDislikeCertainExercises();
    }
}