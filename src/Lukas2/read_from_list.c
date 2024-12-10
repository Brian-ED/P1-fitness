#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 100
#define LONG_STR_SIZE 5000
#define MAX_EXERCISES 12
#define MAX_SETS 12
#define MAX_DAYS 5

typedef struct {
    char name[STR_SIZE];
    char musclegroup[STR_SIZE];
    char equipment[STR_SIZE];
    char type[STR_SIZE];
    char level[STR_SIZE];
    float rating;
    char alternative_exercises[9][STR_SIZE];
    char* exercise_info;     // Pointer for dynamic allocation

} Exercise;

void resolve_backslash(char text[5000]);
void resolve_newline(char text[5000]);
void print_exercises(Exercise *exercise, int exercise_lenght);
int compare(const void *s1, const void *s2);

void read_exercises() {
    FILE* exercise_file = fopen("out copy.txt", "r");
    if (exercise_file == NULL) {
        perror("Error opening file");
        return;
    }

    int exercise_index = 0;
    Exercise exercise[1000] = {0}; // Array of exercises
    while(1){

        // Allocate memory for large fields dynamically
        exercise[exercise_index].exercise_info = calloc(5000, sizeof(char));
        
        // Ensure malloc succeeded
        if (!exercise[exercise_index].exercise_info) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        // Read the data from the file
        if (fscanf(exercise_file,
            "%99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %f | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %4999[^\n]",
            exercise[exercise_index].name,
            exercise[exercise_index].musclegroup,
            exercise[exercise_index].equipment,
            exercise[exercise_index].type,
            exercise[exercise_index].level,
            &exercise[exercise_index].rating,
            exercise[exercise_index].alternative_exercises[0],
            exercise[exercise_index].alternative_exercises[1],
            exercise[exercise_index].alternative_exercises[2],
            exercise[exercise_index].alternative_exercises[3],
            exercise[exercise_index].alternative_exercises[4],
            exercise[exercise_index].alternative_exercises[5],
            exercise[exercise_index].alternative_exercises[6],
            exercise[exercise_index].alternative_exercises[7],
            exercise[exercise_index].alternative_exercises[8],
            exercise[exercise_index].exercise_info) == 16) {



            // Break the loop if fscanf doesn't read all fields
            // Free dynamically allocated memory for each exercise
        } else {
            break;
        }

        exercise_index++;
        if (exercise_index >= 1000) {
            printf("Maximum number of exercises reached.\n");
            break;
        }
    }
    //print_exercises(exercise, exercise_index);
    qsort(exercise, exercise_index, sizeof(Exercise), compare);
    print_exercises(exercise, exercise_index);
    printf("%d", exercise_index);
    fclose(exercise_file);

}



void print_exercises(Exercise *exercise, int exercise_lenght){
    // Print and free the data


    for (int i = 0; i < exercise_lenght; i++){


        resolve_backslash(exercise[i].exercise_info);
        resolve_newline(exercise[i].exercise_info);

        printf("%s\n%s\n%s\n%s\n%s\n%f\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
            exercise[i].name,
            exercise[i].musclegroup,
            exercise[i].equipment,
            exercise[i].type,
            exercise[i].level,
            exercise[i].rating,
            exercise[i].alternative_exercises[0],
            exercise[i].alternative_exercises[1],
            exercise[i].alternative_exercises[2],
            exercise[i].alternative_exercises[3],
            exercise[i].alternative_exercises[4],
            exercise[i].alternative_exercises[5],
            exercise[i].alternative_exercises[6],
            exercise[i].alternative_exercises[7],
            exercise[i].alternative_exercises[8],
            exercise[i].exercise_info);
    }
}


void resolve_backslash(char text[5000]){
    char e[5000];
    strcpy(e,text);
    int a_index = 0;
    int e_index = 0;
    while (e[e_index]) {
        if (e[e_index]=='\\' && e[e_index + 1]=='n') {
            e[a_index] = '\n';
            e_index++;
        } else {
            e[a_index] = e[e_index];
        }
        a_index++;
        e_index++;
    }
    e[a_index] = '\0';
    strcpy(text, e);
}
void resolve_newline(char text[5000]){
    char e[5000];
    strcpy(e,text);
    int a_index = 0;
    int e_index = 0;
    int char_count = 0;
    while (e[e_index]) {
        if (char_count > 130 && e[e_index]==' ') {
            e[a_index] = '\n';
            char_count = 0;
        } else {
            if (e[e_index]=='\n') {
                char_count = 0;
            }
            e[a_index] = e[e_index];
            char_count++;
        }
        a_index++;
        e_index++;
    }
    a_index = 0;
    e_index = 0;
    char_count = 0;
    strcpy(text, e);
}

int compare(const void *s1, const void *s2){
    Exercise *e1 = (Exercise *)s1;
    Exercise *e2 = (Exercise *)s2;
    int type_compare = strcmp(e1->type, e2->type);
    if (type_compare == 0) {
        int musclegroup_compare = strcmp(e1->musclegroup, e2->musclegroup);
        if (musclegroup_compare != 0) {
            return musclegroup_compare;
        } else {
            int level_compare = strcmp(e1->level, e2->level);
            if (level_compare != 0) {
                return level_compare;
            } else {
                if (e1->rating < e2->rating) return -1;
                if (e1->rating > e2->rating) return 1;
                if (e1->rating == e2->rating) {
                    int name_compare = strcmp(e1->name, e2->name);
                    return name_compare;
                }
            }
        }
    }
    return type_compare;
}
