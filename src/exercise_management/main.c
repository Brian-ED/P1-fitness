#define PATH_TO_DATA "../../data/"
#include "../include_me_in_mains.c"

int main(void){
    return_random_quote();
    change_workout_program();

    GetDate();

    int exercise_length;
    Exercise *exercises = read_exercises(&exercise_length);
    DoEachSet(exercises, exercise_length);
    return 0;
}
