#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 100
#define BUF_SIZE 65536
#define ALTERNATIVE_EXERCISES_MAX 9

typedef struct {
    char name[STR_SIZE];
    char musclegroup[STR_SIZE];
    char equipment[STR_SIZE];
    char type[STR_SIZE];
    char level[STR_SIZE];
    float rating;
    char alternative_exercises[ALTERNATIVE_EXERCISES_MAX][STR_SIZE];
    char* exercise_info;     // Pointer for dynamic allocation
} Exercise;
typedef struct {
    int i1, i2;
} Exercise_index;

typedef struct{
    char workoutname[STR_SIZE];
    int amount_of_workouts;
    int amount_of_exercises[7];
    char exercise_name[7][12][STR_SIZE];
    int amount_of_sets[7][12];
} Workout_Program;

void read_workout_program(){
    FILE* workout_file = fopen("workouts.txt", "r");

    if (workout_file == NULL) {
        perror("Error opening file\n");
        return;
    }

    Workout_Program workout_program; // Array of exercises

    fscanf(workout_file, "%99[^|] | %d | %d | %d | %d | %d | %d | %d | %d |",
    workout_program.workoutname,
    &workout_program.amount_of_workouts,
    &workout_program.amount_of_exercises[0],
    &workout_program.amount_of_exercises[1],
    &workout_program.amount_of_exercises[2],
    &workout_program.amount_of_exercises[3],
    &workout_program.amount_of_exercises[4],
    &workout_program.amount_of_exercises[5],
    &workout_program.amount_of_exercises[6]
    );
    for (int i = 0; i < workout_program.amount_of_workouts; i++){

        for (int j = 0; j < workout_program.amount_of_exercises[i]; j++){
            fscanf(workout_file, "%99[^|] |", workout_program.exercise_name[i][j]);
            fscanf(workout_file, "%d |", &workout_program.amount_of_sets[i][j]);
            //printf("%s", workout_program.exercise_name[i][j]);
            //printf("%d", workout_program.amount_of_sets[i][j]);
        }
    }
}


void resolve_backslash(char *text);
void resolve_newline(char *text);
void print_exercises(Exercise *exercise, int exercise_lenght);
int compare(const void *s1, const void *s2);
void get_category_names_exercises(Exercise *exercise, int exercise_lenght, char musclegroup_names[30][STR_SIZE], char equipment_names[30][STR_SIZE], char type_names[30][STR_SIZE], char level_names[30][STR_SIZE]);
void filter_exercises_by_type(Exercise *exercise, int *exercise_lenght);
Exercise_index get_index_from_list(Exercise *exercise, char musclegroup[STR_SIZE], int exercise_lenght);
void delete_spaces(char str[]);
void clean_struct(Exercise *exercise, int exercise_lenght);
int change_exercise(Exercise exercise_to_change, Exercise *exercise);
int find_exercise_in_struct(Exercise *exercise, char exercise_name[STR_SIZE]);

// count_lines implementation found at https://stackoverflow.com/a/70708991
int count_lines(FILE* file)
{
    char buf[BUF_SIZE];
    int counter = 0;

    while (!feof(file)) {
        size_t res = fread(buf, 1, BUF_SIZE, file);
        if (ferror(file))
            return -1;

        for(int i = 0; i < res; i++)
            if (buf[i] == '\n')
                counter++;

    }
    rewind(file);
    return counter;
}

void read_exercises() {
    FILE* exercise_file = fopen("out copy.txt", "r");

    if (exercise_file == NULL) {
        perror("Error opening file\n");
        return;
    }

    int exerciseCount = count_lines(exercise_file);

    Exercise *exercise = (Exercise *)malloc(exerciseCount*sizeof(Exercise)); // Array of exercises
    if (exercise == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    int exercise_index;
    for (exercise_index = 0; exercise_index < exerciseCount; exercise_index++) {

        // Allocate memory for large fields dynamically
        char *exercise_info = calloc(5000, sizeof(char));

        // Ensure malloc succeeded
        if (!exercise_info) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        int amount_of_successful_readings = fscanf(exercise_file,
            "%99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %f | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %4999[^\n]\n",
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
            exercise_info
        );

        if (amount_of_successful_readings != 16) {
            printf("reading excercises from file unsuccessful\n");
            exit(EXIT_FAILURE);
        }

        // Optimize the size of exercise_info
        int exercise_info_length = strlen(exercise_info);
        char *new_exercise_info = (char *)malloc((exercise_info_length+1)*sizeof(char));
        strcpy(new_exercise_info, exercise_info);
        free(exercise_info);

        if (new_exercise_info == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        exercise[exercise_index].exercise_info = new_exercise_info;
    }

    read_workout_program();
    clean_struct(exercise, exercise_index);
    //print_exercises(exercise, exercise_index);
    int new_exercise_index = change_exercise(exercise[396], exercise);
    filter_exercises_by_type(exercise, &exercise_index);
    Exercise *filtered_exercises = (Exercise *)malloc(exercise_index*sizeof(Exercise));
    memcpy(filtered_exercises, exercise, exercise_index*sizeof(Exercise));
    free(exercise);

    qsort(filtered_exercises, exercise_index, sizeof(Exercise), compare);
    fclose(exercise_file);
    char musclegroup_names[30][STR_SIZE] = {0};
    char equipment_names[30][STR_SIZE] = {0};
    char type_names[30][STR_SIZE] = {0};
    char level_names[30][STR_SIZE] = {0};
    get_category_names_exercises(filtered_exercises, exercise_index, musclegroup_names, equipment_names, type_names, level_names);
    char MG[STR_SIZE] = "Quadriceps";
    Exercise_index index = get_index_from_list(filtered_exercises, MG, exercise_index);
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

void resolve_backslash(char *text){
    int a_index = 0;
    int e_index = 0;
    while (text[e_index]) {
        if (text[e_index]=='\\' && text[e_index + 1]=='n') {
            text[a_index] = '\n';
            e_index++;
        } else {
            text[a_index] = text[e_index];
        }
        a_index++;
        e_index++;
    }
    text[a_index] = '\0';
}

void resolve_newline(char *text){
    int a_index = 0;
    int e_index = 0;
    int char_count = 0;
    while (text[e_index]) {
        if (char_count > 130 && text[e_index]==' ') {
            text[a_index] = '\n';
            char_count = 0;
        } else {
            if (text[e_index]=='\n') {
                char_count = 0;
            }
            text[a_index] = text[e_index];
            char_count++;
        }
        a_index++;
        e_index++;
    }
}

int intcmp(int x, int y) {
    return (x > y) - (x < y);
}

int compare(const void *s1, const void *s2){
    Exercise *e1 = (Exercise *)s1;
    Exercise *e2 = (Exercise *)s2;
    int type_compare        = strcmp(e1->type       , e2->type       );
    int musclegroup_compare = strcmp(e1->musclegroup, e2->musclegroup);
    int level_compare       = strcmp(e1->level      , e2->level      );
    int rating_compare      = intcmp(e1->rating     , e2->rating     );
    int name_compare        = strcmp(e1->name       , e2->name       );
    if (type_compare        != 0) return type_compare;
    if (musclegroup_compare != 0) return musclegroup_compare;
    if (level_compare       != 0) return level_compare;
    if (rating_compare      != 0) return rating_compare;
    if (name_compare        != 0) return name_compare;
    return 0;
}

void get_category_names_exercises(Exercise *exercise, int exercise_lenght, char musclegroup_names[30][STR_SIZE], char equipment_names[30][STR_SIZE], char type_names[30][STR_SIZE], char level_names[30][STR_SIZE]){

    int musclegroup_names_index = 0;
    int equipment_names_index = 0;
    int type_names_index = 0;
    int level_names_index = 0;
    int list_count;


    for (list_count = 0; list_count < exercise_lenght; list_count++) {

        char *temp_musclegroup = exercise[list_count].musclegroup;
        char *temp_equipment = exercise[list_count].equipment;
        char *temp_type = exercise[list_count].type;
        char *temp_level = exercise[list_count].level;

        int in_list = 1;
        for (int i = 0; i < musclegroup_names_index; i++) {
            if (!strcmp(musclegroup_names[i], temp_musclegroup))
                in_list = 0;
        }
        if (in_list == 1) {
            strcpy(musclegroup_names[musclegroup_names_index], temp_musclegroup);
            musclegroup_names_index++;
        }

        in_list = 1;
        for (int i = 0; i < equipment_names_index; i++) {
            if (!strcmp(equipment_names[i], temp_equipment))
                in_list = 0;
        }
        if (in_list == 1) {
            strcpy(equipment_names[equipment_names_index], temp_equipment);
            equipment_names_index++;
        }

        in_list = 1;
        for (int i = 0; i < type_names_index; i++) {
            if (!strcmp(type_names[i], temp_type))
                in_list = 0;
        }
        if (in_list == 1) {
            strcpy(type_names[type_names_index], temp_type);
            type_names_index++;
        }

        in_list = 1;
        for (int i = 0; i < level_names_index; i++) {
            if (!strcmp(level_names[i], temp_level))
                in_list = 0;
        }
        if (in_list == 1) {
            strcpy(level_names[level_names_index], temp_level);
            level_names_index++;
        }
    }

}

void filter_exercises_by_type(Exercise *exercise, int *exercise_lenght) {

    int index_count_list = 0;
    char filter_word[STR_SIZE] = "Strength";
    for (int i = 0; i < *exercise_lenght; i++) {
        if (!strcmp(exercise[i].type, filter_word)) {
            exercise[index_count_list] = exercise[i];
            index_count_list++;
        } else {
            free(exercise[i].exercise_info);
        }
    }
    *exercise_lenght = index_count_list;
}

Exercise_index get_index_from_list(Exercise *exercise, char musclegroup[STR_SIZE], int exercise_lenght){

    Exercise_index index;

    int i;
    for (i = 0; i < exercise_lenght; i++){
        if(!strcmp(exercise[i].musclegroup, musclegroup)){
            index.i1 = i;
            break;
        }
    }
    if (i == exercise_lenght) {
        perror("get_index_from_list: index not found\n");
        exit(EXIT_FAILURE);
    }
    for (int j = index.i1; j < exercise_lenght; j++){
        if(strcmp(exercise[j].musclegroup, musclegroup)){
            index.i2 = j;
            break;
        }
    }
    return index;
}

void clean_struct(Exercise *exercise, int exercise_lenght){
    for (int i=0; i<exercise_lenght; i++){
        delete_spaces(exercise[i].name);
        delete_spaces(exercise[i].musclegroup);
        delete_spaces(exercise[i].equipment);
        delete_spaces(exercise[i].type);
        delete_spaces(exercise[i].level);
        for (int j=0; j<ALTERNATIVE_EXERCISES_MAX; j++) {
            delete_spaces(exercise[i].alternative_exercises[j]);
        }
    }
}

void delete_spaces(char str[]){
    int i = strlen(str)-1;
    while (i>0 && str[i]==' ') {i--;}
    str[i+1] = '\0';
}

int change_exercise(Exercise exercise_to_change, Exercise *exercise){

    int new_exercise;
    int new_exercise_index;

    for (int i = 0; i < 9; i++){
        if (exercise_to_change.alternative_exercises[i][0] != '-'){
            new_exercise_index = find_exercise_in_struct(exercise, exercise_to_change.alternative_exercises[i]);
            break;
        }
    }
    return new_exercise_index;
}

int find_exercise_in_struct(Exercise *exercise, char exercise_name[STR_SIZE]){
    int exercise_index;

    for (exercise_index = 0; exercise_index < 900; exercise_index++){
        if (!strcmp(exercise[exercise_index].name, exercise_name)){
            break;
        }
        exercise_index++;
    }
    return exercise_index;
}
