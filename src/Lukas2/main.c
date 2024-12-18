#include "../include_me_in_mains.c"

int main(void){
    int exercise_lenght;
    return_random_quote();

    Exercise *exercises = read_exercises(&exercise_lenght);
    GetDate();
    DoEachSet(exercises, exercise_lenght);
    return 0;
}
 