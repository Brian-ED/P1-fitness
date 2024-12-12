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
typedef struct {
    int i1, i2;
} Exercise_index;

void resolve_backslash(char text[5000]);
void resolve_newline(char text[5000]);
void print_exercises(Exercise *exercise, int exercise_lenght);
int compare(const void *s1, const void *s2);
void get_category_names_exercises(Exercise *exercise, int exercise_lenght, char musclegroup_names[30][STR_SIZE], char equipment_names[30][STR_SIZE], char type_names[30][STR_SIZE], char level_names[30][STR_SIZE]);
void filter_exercises_by_type(Exercise *exercise, int *exercise_lenght);
Exercise_index get_index_from_list(Exercise *exercise, char musclegroup[STR_SIZE], int exercise_lenght);
void delete_spaces(char str[]);
void clean_struct(Exercise *exercise, int exercise_lenght);
int change_exercise(Exercise exercise_to_change, Exercise *exercise);
int find_exercise_in_struct(Exercise *exercise, char exercise_name[STR_SIZE]);

#include <stdio.h>

#define BUF_SIZE 65536

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
        printf("%d\n",exercise_index);

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
        free(exercise_info);

        if (new_exercise_info == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        exercise[exercise_index].exercise_info = new_exercise_info;
    }
    clean_struct(exercise, exercise_index);
    print_exercises(exercise, exercise_index);
    int new_exercise_index = change_exercise(exercise[396], exercise);
    filter_exercises_by_type(exercise, &exercise_index);
    qsort(exercise, exercise_index, sizeof(Exercise), compare);
    fclose(exercise_file);
    char musclegroup_names[30][STR_SIZE] = {0};
    char equipment_names[30][STR_SIZE] = {0};
    char type_names[30][STR_SIZE] = {0};
    char level_names[30][STR_SIZE] = {0};

    get_category_names_exercises(exercise, exercise_index, musclegroup_names, equipment_names, type_names, level_names);
    char MG[STR_SIZE] = "Quadriceps";
    Exercise_index index = get_index_from_list(exercise, MG, exercise_index);
    for (int i = index.i1; i < index.i2; i++) {
        //printf("%s\n", exercise[i].name);
    }
    //printf("\n%s\n",exercise[8].name);
    
    //printf("\n%s\n",exercise[new_exercise_index].name);
    printf("done\n");
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
    //for (int i = 0; i < musclegroup_names_index; i++) {
    //    printf("%s\n", musclegroup_names[i]);
    //    int len = strlen(musclegroup_names[i]);
    //    printf("%d\n", len);
    //}

}

void filter_exercises_by_type(Exercise *exercise, int *exercise_lenght) {

    int index_count_list = 0;
    char filter_word[STR_SIZE] = "Strength";
    for (int i = 0; i < *exercise_lenght; i++) {
        if (!strcmp(exercise[i].type, filter_word)) {

            exercise[index_count_list] = exercise[i];
            index_count_list++;
        }
    }
    *exercise_lenght = index_count_list;
}

Exercise_index get_index_from_list(Exercise *exercise, char musclegroup[STR_SIZE], int exercise_lenght){

    Exercise_index index;

    for (int i = 0; i < exercise_lenght; i++){
        if(!strcmp(exercise[i].musclegroup, musclegroup)){
            index.i1 = i;
            break;
        }
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

    for ( int i = 0; i < exercise_lenght; i++){
            delete_spaces(exercise[i].name);
            delete_spaces(exercise[i].musclegroup);
            delete_spaces(exercise[i].equipment);
            delete_spaces(exercise[i].type);
            delete_spaces(exercise[i].level);
            delete_spaces(exercise[i].alternative_exercises[0]);
            delete_spaces(exercise[i].alternative_exercises[1]);
            delete_spaces(exercise[i].alternative_exercises[2]);
            delete_spaces(exercise[i].alternative_exercises[3]);
            delete_spaces(exercise[i].alternative_exercises[4]);
            delete_spaces(exercise[i].alternative_exercises[5]);
            delete_spaces(exercise[i].alternative_exercises[6]);
            delete_spaces(exercise[i].alternative_exercises[7]);
            delete_spaces(exercise[i].alternative_exercises[8]);

    }
}

void delete_spaces(char str[]){
    int len = strlen(str);

    for (int i = len-1; i > 0; i--){
        if (str[i] != ' '){
            str[i+1] = '\0';
            break;
        }
    }
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
    //get_index_from_list
    return new_exercise_index;
}
#include <stdlib.h>
int find_exercise_in_struct(Exercise *exercise, char exercise_name[STR_SIZE]){
    int exercise_index;

    FILE *file = fopen("out.txt", "w+");

    for (exercise_index = 0; exercise_index < 900; exercise_index++){
        fprintf(file, "|%s|%s|\n", exercise[exercise_index].name, exercise_name);
        if (!strcmp(exercise[exercise_index].name, exercise_name)){
            //printf("\n%s %s\n", exercise[exercise_index].name, exercise_name);
            printf("hit\n");
            break;
        }
        exercise_index++;
//        printf("\n%d", exercise_index);
    }
//    printf("\n%d", exercise_index);
    return exercise_index;
}
