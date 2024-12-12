#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define STR_SIZE 50
#define LONG_STR_SIZE 5000
#define MAX_EXERCISES 12
#define MAX_SETS 12
#define MAX_DAYS 5
#define MAX_DAYS 5
#define MIN_RATING 5


// Added by Brian
#define MAX_ALTERNATIVE_EXERCISES 5


typedef enum Level {Beginner, Intermediate, Expert}Level;
typedef enum Type {OlympicWeightlifting, Plyometrics, Powerlifting, Strength, Stretching, Strongman}Type;
typedef enum Equipment {Bands, FoamRoll, Barbell, Kettlebells, BodyOnly, Machine, Cable, MedicineBall, Dumbbell, None, EZCurlBar, Other, ExerciseBall, Unknown}Equipment;

typedef struct Exercise{
    char name[STR_SIZE];
    char musclegroup[STR_SIZE];
    Equipment equipment;
    Type type;
    Level level;
    float rating;
    Exercise *alternative_exercises[MAX_ALTERNATIVE_EXERCISES];
    char *exercise_info;     // Pointer for dynamic allocation
    char *instructions;      // Pointer for dynamic allocation
} Exercise;

typedef struct { /* search parameter bounds type */
    Level level;
    Type type;
    float rating;
    char musclegroup[STR_SIZE];
} search_params_t;


search_params_t get_params(Exercise exercise_to_switch) {
    search_params_t params;
    //char choice;
    params.level = Beginner;
    params.type = Strength;
    params.rating = MIN_RATING;
    strcpy(params.musclegroup, exercise.musclegroup);

    return params;
}

int match(Exercise exercise_to_validate, search_params_t params){
    return (strcmp(exercise.musclegroup, params.musclegroup) <= 0 &&
            !(params.level == exercise.level) <= 0 &&
            !(params.type == exercise.type) <= 0 &&
            params.rating <= exercise.rating);
}


Exercise sort_exercise_to_show(Exercise exercise){
    //sort exercises that meet criteria
    Exercise sorted_exercises;

    return sorted_exercises;
}

void show(int exercise_count, Exercise exercise) {
    //show exercises after sorting

    for (int i = 0; i < exercise_count; i++){
        printf("%20s", exercise[i].name);
        printf("%5f", exercise.rating);
    }

}

void display_match(Exercise exercise, search_params_t params) {
    //display all exercises that meet criteria after they have been sorted
    Exercise exercise_criteria[100];
    int exercise_index = 0;

    for (int i = 0; i < 1000; i++){
        if (match(exercise[i], params)) == 1{
            exercise_criteria[exercise_criteria] = exercise[i];
            exercise_index++;
        }
    }
    sorted_exercises = sort_exercise_to_show(exercise_criteria);
    show(exercise_index, sorted_exercises);

}



//when user want to change exercise, we want to print a list with either all alternative exercises
// or print a list with all exercises in that musclegroup
void search_struct_replace(char *name){

}

void search_struct_new(char *musclegroup, char *rating, char *level);
//when user want to create a new workoutprogram, we want to print a list with all exercises in that musclegroup



void print_struct(Exercise exercise){

}

// Added by Brian
Exercise *scan_in_exercises();
int is_valid_exercise(Exercise exercise);
void filter_invalid_exercises_in_place(Exercise *exercises);
