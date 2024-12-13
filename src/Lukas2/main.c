#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#include "../Lukas/progression.c"
#include "read_from_list.c"

int main(void){
    read_exercises();
    return 0;
}