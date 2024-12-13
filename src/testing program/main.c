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
#include "functions.c"

enum Level {Beginner, Intermediate, Expert};
enum Type {OlympicWeightlifting, Plyometrics, Powerlifting, Strength, Stretching, Strongman};
enum Equipment {Bands, FoamRoll, Barbell, Kettlebells, BodyOnly, Machine, Cable, MedicineBall, Dumbbell, None, EZCurlBar, Other, ExerciseBall, Unknown};

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



int main() {
    Exercise exercises[1000];
    int exercise_count = 0;

    read_exercises(exercises, &exercise_count);

    printf("Total exercises loaded: %d\n", exercise_count);

    search_params_t params = {
        .level = Intermediate,
        .type = Strength,
        .rating = 7.0,
        .musclegroup = "Quadriceps"
    };

    Exercise filtered_exercises[1000];
    int filtered_count = filter_exercises(exercises, exercise_count, filtered_exercises, params);

    printf("Filtered exercises: %d\n", filtered_count);

    sort_exercises_by_rating(filtered_exercises, filtered_count);

    for (int i = 0; i < filtered_count; i++) {
        printf("%s (Rating: %.1f)\n", filtered_exercises[i].name, filtered_exercises[i].rating);
    }

    // Clean up dynamically allocated memory
    for (int i = 0; i < exercise_count; i++) {
        free(exercises[i].exercise_info);
        free(exercises[i].instructions);
    }

    return 0;
}
