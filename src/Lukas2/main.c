#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "Create_workout_program.c"
#include "read_from_list.c"

//#include "Create_workout_program copy.c"
int main(void){



    // const int MAX_EXERCISES = 1000;
    //Exercise exercises[MAX_EXERCISES];
    //int count = readExercises("dddd.txt", exercises, MAX_EXERCISES);
    //if (count < 0) {
    //    return 1;
    //}
    //printExercises(exercises, count);
    //writeExercisesToFile("output_exercises.txt", exercises, count);
    //writeExercisesToFile1("output_exercises_names.txt", exercises, count);
    //add_rec_program();
    //scan_exercises();

    read_exercises();

    char word[100] = "strength           ";
   
    delete_spaces(word);

//    printf("\n%sa\n",word);


    return 0;
}