#include <stdio.h>
#include <bool.h>

void welcome_back(){
    printf("Welcome back!");
    bool update_personal_info;
    if(update_personal_info) {
        goto type_starter_personal_info;
    }
}
void change_program_or_exercises(){
    printf("Do you want to change workout program or exercises");
    bool yes;
    if(yes){
        goto days_a_week;
    }
    else{
        goto work_out_program;
    }
}