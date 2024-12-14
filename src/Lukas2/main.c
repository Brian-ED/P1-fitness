#include "../include_me_in_mains.c"

int main(void){
    //GetDate();
    //DoEachSet();
    char workout_name[STR_SIZE];
    Chose_workout(workout_name);
    printf("%s", workout_name);
    return 0;
}
