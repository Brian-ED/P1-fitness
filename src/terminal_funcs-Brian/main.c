#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

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
#include "../Parsa/Funktioner.c"
#include "../Lukas/progression.c"
#include "../Lukas2/read_from_list.c"
#include "../welcome_back-Jonas/welcome_back.c"
#include "terminal-funcs.c"


int main(void) {
    GetDate();
    printf("Day %d, Week %d.\n", day_of_the_week, week_number);
    ReadInDataFile();

//    printf("%d\n", age);
//    printf("%d\n", height);
//    printf("%d\n", weight);
//    printf("%c\n", gender);
//    printf("%f\n", protein);
//    printf("%f\n", calorie);
    return 0;
}