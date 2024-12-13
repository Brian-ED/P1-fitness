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



typedef enum Level {
    Beginner,
    Intermediate,
    Expert
} Level;

typedef enum Type {
    OlympicWeightlifting,
    Plyometrics,
    Powerlifting,
    Strength,
    Stretching,
    Strongman
} Type;

typedef enum Equipment {
    Bands,
    FoamRoll,
    Barbell,
    Kettlebells,
    BodyOnly,
    Machine,
    Cable,
    MedicineBall,
    Dumbbell,
    None,
    EZCurlBar,
    Other,
    ExerciseBall,
    Unknown
} Equipment;

typedef struct Exercise {
    char name[STR_SIZE];
    char musclegroup[STR_SIZE];
    Equipment equipment;
    Type type;
    Level level;
    float rating;
    char alternative_exercises[MAX_ALTERNATIVE_EXERCISES][STR_SIZE];
    char *exercise_info;
    char *instructions;
} Exercise;


typedef struct { /* search parameter bounds type */
    Level level;
    Type type;
    float rating;
    char musclegroup[STR_SIZE];
} search_params_t;

int read_exercises(Exercise *exercises, int max_exercises) {
    FILE *exercise_file = fopen("dd.txt", "r");
    if (!exercise_file) {
        perror("Error opening file");
        return -1;
    }

    int index = 0;
    while (index < max_exercises && !feof(exercise_file)) {
        Exercise *exercise = &exercises[index];

        // Allocate memory for dynamic fields
        exercise->exercise_info = calloc(LONG_STR_SIZE, sizeof(char));
        exercise->instructions = calloc(LONG_STR_SIZE, sizeof(char));
        if (!exercise->exercise_info || !exercise->instructions) {
            perror("Memory allocation failed");
            fclose(exercise_file);
            return -1;
        }

        // Read from file
        int fields_read = fscanf(
            exercise_file,
            "%49[^|] | %49[^|] | %d | %d | %d | %f | %49[^|] | %49[^|] | %49[^|] | %49[^|] | %49[^|] | %4999[^|] | %4999[^\n]",
            exercise->name,
            exercise->musclegroup,
            (int *)&exercise->equipment,
            (int *)&exercise->type,
            (int *)&exercise->level,
            &exercise->rating,
            exercise->alternative_exercises[0],
            exercise->alternative_exercises[1],
            exercise->alternative_exercises[2],
            exercise->alternative_exercises[3],
            exercise->alternative_exercises[4],
            exercise->exercise_info,
            exercise->instructions);

        // Check for successful read
        if (fields_read != 13) {
            printf("Error reading exercise data at index %d\n", index);
            free(exercise->exercise_info);
            free(exercise->instructions);
            break;
        }

        index++;
    }

    fclose(exercise_file);
    return index; // Number of exercises read
}

int filter_exercises(Exercise *input, int input_count, Exercise *output, search_params_t params) {
    int output_count = 0;
    for (int i = 0; i < input_count; i++) {
        if (strcmp(input[i].musclegroup, params.musclegroup) == 0 &&
            input[i].level == params.level &&
            input[i].type == params.type &&
            input[i].rating >= params.rating) {
            output[output_count++] = input[i];
        }
    }
    return output_count;
}
int compare_by_rating(const void *a, const void *b) {
    float rating_a = ((Exercise *)a)->rating;
    float rating_b = ((Exercise *)b)->rating;
    return (rating_a > rating_b) - (rating_a < rating_b);
}

void sort_exercises_by_rating(Exercise *exercises, int count) {
    qsort(exercises, count, sizeof(Exercise), compare_by_rating);
}
