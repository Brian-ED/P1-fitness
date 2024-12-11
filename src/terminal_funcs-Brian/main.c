#include <assert.h>
#include <stdio.h>
#include <time.h>
#include "../Parsa/Funktioner.c"
#include "../Lukas/progression.c"
#include "../welcome_back/welcome_back.c"
#include "terminal-funcs.c"


int main(void) {
    GetDate();
    printf("Day %d, Week %lf.\n", day_of_the_week, week_number);
    ReadInDataFile();

//    printf("%d\n", age);
//    printf("%d\n", height);
//    printf("%d\n", weight);
//    printf("%c\n", gender);
//    printf("%f\n", protein);
//    printf("%f\n", calorie);
    return 0;
}