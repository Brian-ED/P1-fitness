#include "../include_me_in_mains.c"

int main(void){
    int exercise_length;
    return_random_quote();

    Exercise *exercises = read_exercises(&exercise_length);
    change_workout_program(exercises, exercise_length);

    GetDate();
    DoEachSet(exercises, exercise_length);
    return 0;
}
