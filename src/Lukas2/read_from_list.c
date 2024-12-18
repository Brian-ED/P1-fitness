// NOTE: "Lukas/progression.c" must be included before including this file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 100
#define ALTERNATIVE_EXERCISES_MAX 9

typedef struct {
    char name[STR_SIZE];
    char muscletarget[STR_SIZE];
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
typedef struct {
    int  week;
    int  amount_of_sets;
    int  weight;
    int  sets[6];
}progression1;

// Purpose unknown
//void get_category_names_exercises(Exercise *exercise, int exercise_length, char musclegroup_names[30][STR_SIZE], char equipment_names[30][STR_SIZE], char type_names[30][STR_SIZE], char level_names[30][STR_SIZE]);

void resolve_backslash(char *text);
void resolve_newline(char *text);
void print_exercises(Exercise *exercise, int exercise_length);
int compare(const void *s1, const void *s2);
void filter_exercises_by_type(Exercise *exercise, int *exercise_length);
Exercise_index get_index_from_list(Exercise *exercise, char musclegroup[STR_SIZE],char muscletarget[STR_SIZE], int exercise_length);
void delete_spaces(char str[]);
void clean_exercise_database(Exercise *exercise, int exercise_length);
int change_exercise(int exercise_to_change, Exercise *exercise, int *alt_count, int exercise_length);
int find_exercise_in_struct(Exercise *exercise, int exercise_length, char exercise_name[STR_SIZE], int defaultIndex);
void change_workout_program(Exercise *exercise, int exercise_length);
void Chose_workout(char workout_name[STR_SIZE]);


Workout_Program workout_program; // Array of exercises

void SaveProgramToWorkoutFile() {
    FILE *workout_file = openSafe("workouts/Custom Workout.txt", "w+");
    FILE *workout_names = openSafe("workouts/workout_names", "a");
    FILE *current_workout = openSafe("exercises/current_workout", "w+");

    fprintf(current_workout, "%s", "workouts/Custom Workout.txt");

    fprintf(workout_file, "%s | %d | %d | %d | %d | %d | %d | %d | %d |\n",
        workout_program.workoutname,
        workout_program.amount_of_workouts,
        workout_program.amount_of_exercises[0],
        workout_program.amount_of_exercises[1],
        workout_program.amount_of_exercises[2],
        workout_program.amount_of_exercises[3],
        workout_program.amount_of_exercises[4],
        workout_program.amount_of_exercises[5],
        workout_program.amount_of_exercises[6]
    );
    for (int i = 0; i < workout_program.amount_of_workouts; i++){
        for (int j = 0; j < workout_program.amount_of_exercises[i]; j++){
            fprintf(workout_file, "%s| %d\n",
                workout_program.exercise_name[i][j],
                workout_program.amount_of_sets[i][j]);
        }
    }
    fclose(workout_file);
    fclose(workout_names);
    fclose(current_workout);

}

void read_workout_program(char workout_name[STR_SIZE]) {
    FILE *workout_file = openSafe(workout_name, "r");
    fscanf(workout_file, "%99[^|] | %d | %d | %d | %d | %d | %d | %d | %d |\n",
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
            fscanf(workout_file, "%99[^|] | %d\n",
                workout_program.exercise_name[i][j],
                &workout_program.amount_of_sets[i][j]
            );
        }
    }
    fclose(workout_file);
}

void print_workout_program(Exercise *exercise, int exercise_length){

    Exercise exercise_to_print[100];
    int choice = -1;
    int exercise_count = 0;

    while (1){
        exercise_count = 0;
        for (int i = 0; i < workout_program.amount_of_workouts; i++){
        printf("This is your workoutprogram for day %d:\n", i + 1);
        printf("Index: Name:                                              Sets:  Musclegroup:    Muscletarget:   Equipment:\n");
            for(int j = 0; j < workout_program.amount_of_exercises[i]; j++){
                int exercise_index = find_exercise_in_struct(
                    exercise,
                    exercise_length,
                    workout_program.exercise_name[i][j],
                    -1);
                if (exercise_index == -1){
                    printf("Exercise not in list\n");
                    continue;;
                }
                exercise_to_print[exercise_count] = exercise[exercise_index];
                printf("%-6d %-50s %-6d %-15s %-15s %-15s\n",
                                                            exercise_count,
                                                            exercise_to_print[exercise_count].name,
                                                            workout_program.amount_of_sets[i][j],
                                                            exercise_to_print[exercise_count].musclegroup,
                                                            exercise_to_print[exercise_count].muscletarget,
                                                            exercise_to_print[exercise_count].equipment);
                exercise_count++;
            }
        }

        printf("\nEnter the index of an exercise to view more info, or -1 to exit: ");
        scanf("%d", &choice);

        if (choice == -1) break;

        if (choice >= 0 && choice < exercise_count) {
            resolve_backslash(exercise_to_print[choice].exercise_info);
            resolve_newline(exercise_to_print[choice].exercise_info);
            printf("\nDetails for '%s':\n%s\n", exercise_to_print[choice].name, exercise_to_print[choice].exercise_info);
        } else {
            printf("Invalid choice. Please try again.\n");
        }

        printf("\nPress -1 to quit or any other number to continue reviewing exercises: ");
        scanf("%d", &choice);
        if (choice == -1) break;
    }
}

Exercise *read_exercises(int *exercise_lenght) {
    FILE* exercise_file = fopen("out copy 2.txt", "r");

    if (exercise_file == NULL) {
        perror("Error opening file\n");
        exit(1);
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
            "%99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %f | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %4999[^\n]\n",
            exercise[exercise_index].name,
            exercise[exercise_index].muscletarget,
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

        if (amount_of_successful_readings != 17) {
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


    //read_workout_program();
    clean_exercise_database(exercise, exercise_index);
    filter_exercises_by_type(exercise, &exercise_index);
    Exercise *filtered_exercises = (Exercise *)malloc(exercise_index*sizeof(Exercise));
    memcpy(filtered_exercises, exercise, exercise_index*sizeof(Exercise));
    free(exercise);

    qsort(filtered_exercises, exercise_index, sizeof(Exercise), compare);

    fclose(exercise_file);
    char answer;
    printf("do you want to change your workout? enter 'y' for yes and 'n' for no\n");
    scanf(" %c", &answer);
    while (answer != 'y' && answer != 'n'){
        printf("please enter a valid answer\n");
        printf("do you want to change your workout? enter 'y' for yes and 'n' for no\n");
        scanf(" %c", &answer);
    }
    if (answer == 'y'){
        change_workout_program(filtered_exercises, exercise_index);
    }
    *exercise_lenght = exercise_index;

    return filtered_exercises;

}

void return_random_quote() {
    FILE* file = fopen("Quotes.txt", "r");
    int count_lines_file = count_lines(file);
    char quotes[count_lines_file][5000];

    if (file == NULL) {
        perror("Error opening file\n");
        exit(1);
    }

    for (int i = 0; i < count_lines_file; i++){
        fscanf(file, "%4999[^\n]\n", quotes[i]);
    }
    int size = sizeof(quotes) / sizeof(quotes[0]);
    srand(time(NULL));
    int random_index = rand() %size;

    fclose(file);
    printf("%s\n",quotes[random_index]);
}



void print_exercises(Exercise *exercise, int exercise_length){
    // Print and free the data
    for (int i = 0; i < exercise_length; i++){

        resolve_backslash(exercise[i].exercise_info);
        resolve_newline(exercise[i].exercise_info);

        printf("%s\n%s\n%s\n%s\n%s\n%s\n%f\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
            exercise[i].name,
            exercise[i].muscletarget,
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
    int c;
    if ((c = strcmp(e1->type        , e2->type         )) != 0) return c;
    if ((c = strcmp(e1->musclegroup , e2->musclegroup  )) != 0) return c;
    if ((c = strcmp(e1->muscletarget, e2->muscletarget )) != 0) return c;
    if ((c = strcmp(e1->level       , e2->level        )) != 0) return c;
    if ((c = intcmp(e1->rating      , e2->rating       )) != 0) return c;
    if ((c = strcmp(e1->name        , e2->name         )) != 0) return c;
    return 0;
}
void get_category_names_exercises(Exercise *exercise, int exercise_length, char musclegroup_names[30][STR_SIZE], char equipment_names[30][STR_SIZE], char type_names[30][STR_SIZE], char level_names[30][STR_SIZE]){

    int musclegroup_names_index = 0;
    int equipment_names_index = 0;
    int type_names_index = 0;
    int level_names_index = 0;
    int list_count;


    for (list_count = 0; list_count < exercise_length; list_count++) {

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

void filter_exercises_by_type(Exercise *exercise, int *exercise_length) {

    int index_count_list = 0;
    char filter_word[STR_SIZE] = "Strength";
    for (int i = 0; i < *exercise_length; i++) {
        if (!strcmp(exercise[i].type, filter_word)) {
            exercise[index_count_list] = exercise[i];
            index_count_list++;
        } else {
            free(exercise[i].exercise_info);
        }
    }
    *exercise_length = index_count_list;
}

// run two binary searches to find the upper and lower bounds
Exercise_index get_index_from_list(Exercise *exercise, char musclegroup[STR_SIZE], char muscletarget[STR_SIZE], int exercise_length){

    // binary search to find the upper bound
    int lower_bound = 0;
    int speed = exercise_length;
    int dir = 1;
    int preference = -1;
    while (speed /= 2) { // Approching a fixed-point
        lower_bound += dir*speed;

        // Bound checks
        // c1 c2 → result
        //  0  0 → preference
        // -1 -1 → -1
        //  1  1 →  1
        //  0  1 →  1
        //  0 -1 → -1
        //  1 -1 →  1
        // -1  1 → -1
        //
        //  1  0 → impossible
        // -1  0 → impossible
        int c2 = strcmp(exercise[lower_bound].musclegroup, musclegroup);
        int c1 = strcmp(exercise[lower_bound].muscletarget, muscletarget);
        if (c1>0) {c1= 1;} if (c2>0) {c2= 1;}
        if (c1<0) {c1=-1;} if (c2<0) {c2=-1;}

        if (c1 == 0 && c2 == 0) {
            // 0  0 → preference
            dir = preference;
        } else if (c1 == c2) {
            // -1 -1 → -1
            //  1  1 →  1
            dir = c1;
        } else if (c1 == 0){
            //  0  1 →  1
            //  0 -1 → -1
            dir = c2;
        } else if (c2!=0) {
            //  1 -1 →  1
            // -1  1 → -1
            dir = c1;
        } else {
            //  1  0 → impossible
            // -1  0 → impossible
            printf("%d %d a\n",c1,c2);
            perror("Incorrect Binary Search implementation\n");
            assert(0);
        }
    }
    // NOTICE: To make sure lower_bound points at first valid index, not the index to the left of it,
    // the "!=" here makes sure only to shift right if the musclegroups aren't the same.
    if (exercise[lower_bound].musclegroup != musclegroup) {
        lower_bound++;
    }

    // binary search to find the lower bound
    int upper_bound = 0;
    speed = exercise_length;
    dir = 1;
    preference = 1;
    while (speed /= 2) { // Approching a fixed-point
        upper_bound += dir*speed;
        int c2 = strcmp(exercise[upper_bound].musclegroup, musclegroup);
        int c1 = strcmp(exercise[upper_bound].muscletarget, muscletarget);
        if (c1>0) {c1= 1;} if (c2>0) {c2= 1;}
        if (c1<0) {c1=-1;} if (c2<0) {c2=-1;}

        if (c1 == 0 && c2 == 0) {
            dir = preference;
        } else if (c1 == c2) {
            dir = c1;
        } else if (c1 == 0){
            dir = c2;
        } else if (c1!=0 && c2!=0) {
            dir = c1;
        } else {
            printf("%d %d a\n",c1,c2);
            perror("Incorrect Binary Search implementation\n");
            assert(0);
        }
    }
    // NOTICE: To make sure upper_bound points after last valid index, not the index to the left of it,
    // the "==" here makes sure only to shift right if the musclegroups are the same.
    if (exercise[upper_bound].musclegroup == musclegroup) {
        upper_bound--;
    }

    return (Exercise_index){
        .i1 = lower_bound,
        .i2 = upper_bound,
    };
}

void clean_exercise_database(Exercise *exercise, int exercise_length){
    for (int i=0; i<exercise_length; i++){
        delete_spaces(exercise[i].name);
        delete_spaces(exercise[i].musclegroup);
        delete_spaces(exercise[i].muscletarget);
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

int find_exercise_in_struct(Exercise *exercise, int exercise_length, char exercise_name[STR_SIZE], int default_index){
    int exercise_index = 0;
    while (exercise_index < exercise_length && strcmp(exercise[exercise_index].name, exercise_name)) {
        exercise_index++;
    }
    if (exercise_index == exercise_length) {
        return default_index;
    }
    return exercise_index;
}

int change_exercise(int exercise_to_change, Exercise *exercise, int *alt_count, int exercise_length){
    int next_exercise_index;
    Exercise_index index_from_list = get_index_from_list(exercise, exercise[exercise_to_change].musclegroup, exercise[exercise_to_change].muscletarget, exercise_length);
    if (exercise_to_change+1 >= index_from_list.i2) {
        next_exercise_index = index_from_list.i1;
    } else {
        next_exercise_index = exercise_to_change+1;
    }
    if (*alt_count >= ALTERNATIVE_EXERCISES_MAX || exercise[exercise_to_change].alternative_exercises[*alt_count][0] == '-') {
        *alt_count = 0;
        return next_exercise_index;
    }
    (*alt_count)++;
    //eg havi sett alt_count at index'a vid -1 tí annars loypur tad um tad fyrsta alternative exercise
    return find_exercise_in_struct(exercise, exercise_length, exercise[exercise_to_change].alternative_exercises[*alt_count-1], next_exercise_index);
}

// calculate next suggested progression for user
progression1 calculate_new_weight1(char *filename, int *new_weight, int *new_reps, int *new_sets){
    progression1 last_weight;
    // Reads in data from exercise file
    double x[300], y[300];
    int n = 0;
    int last_weight_change = 0;
    FILE *file = fopen(filename, "r");
    while (fscanf(
        file, "%d %d %d %d %d %d %d %d %d",
        &last_weight.week,
        &last_weight.amount_of_sets,
        &last_weight.weight,
        &last_weight.sets[0],
        &last_weight.sets[1],
        &last_weight.sets[2],
        &last_weight.sets[3],
        &last_weight.sets[4],
        &last_weight.sets[5]
    ) == 9 ) {
        if (last_weight.weight != last_weight_change){
            last_weight_change = last_weight.weight;
            x[n] = last_weight.week; // TODO: use actual weeks
            y[n] = last_weight.weight;
            n++;
        }
    }
    printf("%lf\n",x[0]);
    printf("%lf\n",y[0]);
    int new_weight_rec= 0;
    if (n > 3){
        Term t = log_regression(n, x, y);
        printf("aa: %lf\n",t.coefficient);
        new_weight_rec = 0.5+t.coefficient*log(t.exponent*(last_weight.week+1));
        printf("aa: %lf\n",t.exponent);
    }

    *new_sets = last_weight.amount_of_sets;
    *new_weight = last_weight.weight;

    int new_weight_lower = 0.5+last_weight.weight*1.1;
    int new_weight_upper = 0.5+last_weight.weight*1.2;

    int new_repsNew = 0;

    for (int i = 8; i <= 12; i++){
        int count = 0;
        for (int j = 0; j < last_weight.amount_of_sets; j++){
            if (last_weight.sets[j] >= i){
                count++;
            }
        }
        if (count == 4){
            new_repsNew = i + 1;
        }
    }

    if (new_repsNew < last_weight.sets[0]){
        *new_reps = last_weight.sets[0];
    } else if (new_repsNew > 12){
        *new_reps = 8;
        printf("You have reached your maximum reps for this exercise, and you must therefore choose a new weight.\n");
        printf("As a recommendation you should chose a weight that lies between: %d kg and %d kg. The recomended weight is now: %d\n",new_weight_lower, new_weight_upper, new_weight_rec);
        scanf("%d", new_weight);
    } else *new_reps = new_repsNew;

    fclose(file);
    return last_weight;
}

// write new progression to txt file
progression1 new_progression1(char *filename, progression1 last_weight, int new_weight, int new_reps, int new_sets){
    progression1 new_weight_data = { 0 };
    FILE *file = fopen(filename, "a");

    for (int i = 0; i < 6; i++){
        new_weight_data.sets[i] = 0;
    }

    printf("The target sets are %d, the target reps are %d and the target weight is %d kg\n", new_sets, new_reps, new_weight);


    for (int i = 0; i < new_sets; i++){
        printf("please enter the amount of reps you have taken for set 1: (target: %d | last time: %d)\n", new_reps, last_weight.sets[i]);
        scanf("%d", &new_weight_data.sets[i]);
    }

    // TODO: use weeks gotten from GetDate
    new_weight_data.week = week_number;
    new_weight_data.amount_of_sets = new_sets;
    new_weight_data.weight = new_weight;

    fprintf(file, "%d %d %d %d %d %d %d %d %d\n", new_weight_data.week,
                                        new_weight_data.amount_of_sets,
                                         new_weight_data.weight,
                                         new_weight_data.sets[0],
                                         new_weight_data.sets[1],
                                         new_weight_data.sets[2],
                                         new_weight_data.sets[3],
                                         new_weight_data.sets[4],
                                         new_weight_data.sets[5]);
    return new_weight_data;
}

void scan_prog1(char *exercise, int sets){
    int text;
    printf("your current exercise is: %s\n", exercise);
    char *name = strcat(exercise, ".prog.txt");
    char location_name[80] ="exercises/";
    strcat(location_name, name);
    FILE* ex_prog = fopen(location_name, "r");
    printf("hello");

    int new_weight = 0;
    int new_reps = 0;
    int new_sets = 0;
    progression1 last_weight = {0};
    if(ex_prog == NULL){
        ex_prog = fopen(location_name, "w");
        new_reps = 8;
        printf("please enter a starting weight: ");
        scanf("%d", &new_weight);
        new_sets = sets;
    } else {
        last_weight = calculate_new_weight1(location_name, &new_weight, &new_reps, &new_sets);
    }
    progression1 new_weight_data = new_progression1(location_name, last_weight, new_weight, new_reps, new_sets);

    fclose(ex_prog);
}


void Chose_workout(char workout_name[STR_SIZE]){
    FILE* file = fopen("workouts/workout_names", "r");
    int workout_count = count_lines(file);
    int workout_index;
    char workout_names[STR_SIZE][100];
    char letter = 'a';
    char choice;

    for (workout_index = 0; workout_index < workout_count; workout_index++){
        fscanf(file, "%99[^\n]\n", workout_names[workout_index]);
    }

    printf("enter letter to the right of the workout you chose: \n");
    for (int i = 0; i < workout_count; i++){
        printf("%-60s(%c)\n", workout_names[i], letter);
        letter++;
    }
    scanf(" %c", &choice);
    while (choice < 'a' || choice > letter){
        printf("please enter a valid input\n");
        scanf(" %c", &choice);
    }
    letter = 'a';
    for (int i = 0; i < workout_count; i++){
        if (choice == letter){
            strcpy(workout_name, workout_names[i]);
            strcat(workout_name, ".txt");
            break;
        }
        letter++;
    }
    fclose(file);
}
void change_workout_program(Exercise *exercise, int exercise_length){

    int alt_count = 0;
    char workout_name[STR_SIZE];
    Chose_workout(workout_name);
    char workout_name_address[STR_SIZE] = "workouts/";
    strcat(workout_name_address, workout_name);
    read_workout_program(workout_name_address);
    char choice[7];
    for (int i = 0; i < workout_program.amount_of_workouts; i++){
        printf("please chose a exercise to change by entering the letter to the right, or press q when satisfied with the workout\n");
        for (int j = 0; j < workout_program.amount_of_exercises[i]; j++) {
            char letter = 'a' + j;
            printf("%-60s (%c)\n", workout_program.exercise_name[i][j], letter);
        }
        scanf(" %c", &choice[i]);
        if (choice[i] == 'q'){
            continue;
        } else if (choice[i] < 'a' || choice[i] >= 'a' + workout_program.amount_of_exercises[i]) {
            printf("please chose a valid input\n");
            i--;
            continue;
        }else {
            int exercise_index = choice[i] - 'a';
            if (exercise_index >= 0 && exercise_index < workout_program.amount_of_exercises[i]) {
                //printf("Valid input for exercise: %s\n", workout_program.exercise_name[i][exercise_index]);
                int default_index = -1;
                int exercise_index_change = find_exercise_in_struct(exercise, exercise_length, workout_program.exercise_name[i][exercise_index], default_index);
                if (exercise_index == -1) {
                    printf("exercise not found in database");
                    //!!modify to delete exercise later and ask user for new
                    i--;
                    break;
                } else {
                    int new_exercise_index = change_exercise(exercise_index_change, exercise, &alt_count, exercise_length);
                    printf("You have changed the exercise: %s. The new exercise is: %s\n", workout_program.exercise_name[i][exercise_index], exercise[new_exercise_index].name);
                    strcpy(workout_program.exercise_name[i][exercise_index], exercise[new_exercise_index].name);
                    i--;
                }
            }

        }
    }
    SaveProgramToWorkoutFile();
}

void DoEachSet(Exercise *exercises, int exercise_lenght) {
    char workout_name[STR_SIZE];
    int workout_day;
    FILE* file = fopen("exercises/current_workout", "r");
    fscanf(file, "%99[^|] | %d", workout_name, &workout_day);
    fclose(file);
    read_workout_program(workout_name);

    char answer;
    printf("do you want to reveiw your workout? enter 'y' for yes and 'n' for no\n");
    scanf(" %c", &answer);
    while (answer != 'y' && answer != 'n'){
        printf("please enter a valid answer\n");
        printf("do you want to reveiw your workout? enter 'y' for yes and 'n' for no\n");
        scanf(" %c", &answer);
    }
    if (answer == 'y'){
        print_workout_program(exercises, exercise_lenght);
    }
    printf("Now doing workout: \"%s\"\n",workout_program.workoutname);

    answer = 0;
    printf("do you want to start next workout session? enter 'y' for yes and 'n' for no\n");
    scanf(" %c", &answer);
    while (answer != 'y' && answer != 'n'){
        printf("please enter a valid answer\n");
        printf("do you want to start next workout session? enter 'y' for yes and 'n' for no\n");
        scanf("%c", &answer);
    }
    if (answer == 'y'){
        for (int j = 0; j < workout_program.amount_of_exercises[workout_day-1]; j++) {
            int amount_of_sets = workout_program.amount_of_sets[workout_day-1][j];
            char *name = workout_program.exercise_name[workout_day-1][j];
            scan_prog1(name, amount_of_sets);
        }
    }
    if (workout_day == workout_program.amount_of_workouts) {
        workout_day = 1;
    } else {
        workout_day++;
    }
    FILE* file1 = fopen("exercises/current_workout", "w+");
    fprintf(file1,"%s|%d", workout_name, workout_day);

    fclose(file1);
}
