#include <stdio.h>
#include <bool.h>

void welcome_back(){
    printf("Welcome back!");
}

bool update_personal_info_or_not(){
    bool yes;
    printf("Do you want to change personal info?");
    scanf("%c", yes);
    return yes;
}

bool change_days_a_week_or_not(){
    bool yes;
    printf("Do you want to change how many days you can work out a week?\n
    Type 1 for yes.\nType 0 for no");
    scanf("%c", yes);
    return yes;
}

bool change_exercises_or_not(){
    bool yes;
    printf("Do you want to change exercises?\n
    Type 1 for yes.\nType 0 for no");
    scanf("%c", yes);
    return yes;
}