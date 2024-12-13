#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int week_number = -1;
int day_of_the_week = -1;
int age;
int height;
int weight;
char gender;
float protein;
float calorie;
int program_days;

#include "../utils.c"
#include "../log_regression-Brian/log_regression.c"
#include "../Lukas/progression.c"
#include "../Lukas2/read_from_list.c"
#include "../Parsa/Funktioner.c"
#include "../welcome_back-Jonas/welcome_back.c"
#include "../terminal_funcs-Brian/terminal-funcs.c"

int main(void){
    
    char exercise[80] = "new_ex";
    GetDate();

    scan_prog(exercise);
    return 0;
}


