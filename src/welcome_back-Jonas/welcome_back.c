#include <stdio.h>

void show_welcome_back(){
    printf("Welcome back!\n");
}

int AskUserIfTheyWantToChangeProgramOrExercises(){
    char yes;
    printf("Do you want to change how many days a week for exercises, and/or the exercises themselves?\n");
    printf("Type 1 for yes.\nType 0 for no\n");
    while ((yes = getchar()) == '\n') {}
    return yes == '1';
}

int UserWantsToChangeOptionsAndOrWorkout(){
    char yes;
    printf("Do you want to change personal info?\n");
    printf("Type 1 for yes.\nType 0 for no\n");
    while ((yes = getchar()) == '\n') {}
    return yes == '1';
}

int change_exercises_or_not(){
    char yes;
    printf("Do you want to change exercises?\n");
    printf("Type 1 for yes.\nType 0 for no\n");
    while ((yes = getchar()) == '\n') {}
    return yes == '1';
}
