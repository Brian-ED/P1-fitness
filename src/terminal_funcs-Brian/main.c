#define PATH_TO_DATA "../../data/"
#include "../include_me_in_mains.c"

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