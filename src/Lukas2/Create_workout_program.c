#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define STR_SIZE 50
#define LONG_STR_SIZE 5000
#define MAX_EXERCISES 12
#define MAX_SETS 12
#define MAX_DAYS 5

typedef struct {
    char musclegroup[STR_SIZE];
    int index;
    char name[STR_SIZE];
    char compound_or_isolation[3];
    char recommended[3];
} Exercise;

typedef struct{
    char name[STR_SIZE];
    char musclegroup[STR_SIZE];
    char equipment[STR_SIZE];
    char type[STR_SIZE];
    char level[STR_SIZE];
    char rating[STR_SIZE];
    char alternative_exercises[5][STR_SIZE];
    char exercise_info[LONG_STR_SIZE];
    char benefits[LONG_STR_SIZE];
    char instructions[LONG_STR_SIZE];
}Exercise1;

typedef struct {
    int number_of_exercises;
    char exercise_group[MAX_EXERCISES][STR_SIZE];
    int exercise_sets[MAX_EXERCISES];
    char exercise_kind[MAX_EXERCISES][3];
    char exercise_rec[MAX_EXERCISES][3];
} Workout;

void read_exercises(){
    FILE* exercise_file = fopen("dd.txt", "r");
    int exercise_index = 1;
    Exercise1 exercise[1000] = {0};
    char filename[STR_SIZE];

    char line[10000]; // Ensure it can hold the longest possible line
    while (fgets(line, sizeof(line), exercise_file)) {
        sscanf(line, "%49[^|] | %49[^|] | %49[^|] | %49[^|] | %49[^|] | %49[^|] | %49[^|] | %49[^|] | %49[^|] | %49[^|] | %49[^|] | %499[^|] | %4999[^|] | %4999[^\n]",
            exercise[exercise_index].name,
            exercise[exercise_index].musclegroup,
            exercise[exercise_index].equipment,
            exercise[exercise_index].type,
            exercise[exercise_index].level,
            exercise[exercise_index].rating,
            exercise[exercise_index].alternative_exercises[0],
            exercise[exercise_index].alternative_exercises[1],
            exercise[exercise_index].alternative_exercises[2],
            exercise[exercise_index].alternative_exercises[3],
            exercise[exercise_index].alternative_exercises[4],
            exercise[exercise_index].exercise_info,
            exercise[exercise_index].benefits,
            exercise[exercise_index].instructions);
        exercise_index++;
    }
    fclose(exercise_file);
    for (int i = 0; i < exercise_index; i++){
        char buffer[LONG_STR_SIZE];


        while (fgets()){


        }
        fgets()




        printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                                exercise[exercise_index].name,
                                exercise[exercise_index].musclegroup,
                                exercise[exercise_index].equipment,
                                exercise[exercise_index].type,
                                exercise[exercise_index].level,
                                exercise[exercise_index].rating,
                                exercise[exercise_index].alternative_exercises[0],
                                exercise[exercise_index].alternative_exercises[1],
                                exercise[exercise_index].alternative_exercises[2],
                                exercise[exercise_index].alternative_exercises[3],
                                exercise[exercise_index].alternative_exercises[4],
                                exercise[exercise_index].exercise_info,
                                exercise[exercise_index].benefits,
                                exercise[exercise_index].instructions);
    }

}




//read exercises from txt file and save then in an array
void scan_exercises(){

    FILE* group_file = fopen("exercises/all_groups.txt", "r");

    Exercise exercise[1000] ={ 0 };
    char filename[STR_SIZE];
    int exersice_index = 0;
        while (fscanf(group_file, "%s", filename) == 1){
            char filepath[100] = "exercises/";
            strcat(filepath,filename);
            FILE* ex_file = fopen(filepath, "r");


            while(fscanf(ex_file, "%d %50[^|] | %s | %s", &exercise[exersice_index].index,
                                                        exercise[exersice_index].name,
                                                        exercise[exersice_index].compound_or_isolation,
                                                        exercise[exersice_index].recommended) == 4){
                strcpy(exercise[exersice_index].musclegroup, filename);
                exercise[exersice_index].musclegroup[strlen(exercise[exersice_index].musclegroup)-4] = '\0';
              exersice_index++;
            }

            fclose(ex_file);
        }
        fclose(group_file);
    printf("%d\n",exersice_index);

    for (int i = 0; i < exersice_index; i++){
       printf("%d   %s    %s    %s   %s\n", exercise[i].index,
                                            exercise[i].name,
                                            exercise[i].musclegroup,
                                            exercise[i].compound_or_isolation,
                                            exercise[i].recommended);
    }
}

void add_rec_program() {
    char workout_name[STR_SIZE] = {0};
    int workout_day;
    int number_exercises[MAX_DAYS] = {0};
    char repetitive;

    printf("Enter a name for your workout:\n");
    scanf("%s", workout_name);

    printf("Enter kind of workout: 3 for 3-day program (fullbody) | 4 for 4-day program (upper/lower) | 5 for 5-day program (upper/lower, push/pull, legs)\n");
    scanf("%d", &workout_day);

    if (workout_day < 3 || workout_day > 5) {
        printf("Invalid number of workout days. Please select 3, 4, or 5.\n");
        return;
    }
    if (workout_day == 3 || workout_day == 4){
        printf("do you want to make this workoutprogram repetitive? (y/n)");
        scanf("%c", &repetitive);
        if (repetitive != 'y' || repetitive != 'n') {
            printf("Invalid character, please select y/n\n");
            return;
        }
    }

    for (int i = 0; i < workout_day; i++) {
        printf("Enter the number of exercises for day %d:\n", i + 1);
        scanf("%d", &number_exercises[i]);

        if (number_exercises[i] < 1 || number_exercises[i] > MAX_EXERCISES) {
            printf("Invalid number of exercises for day %d. Must be between 1 and %d.\n", i + 1, MAX_EXERCISES);
            return;
        }
    }


    Workout workoutPlan[MAX_DAYS] = {0};


    for (int i = 0; i < workout_day; i++) {
        workoutPlan[i].number_of_exercises = number_exercises[i];

        for (int j = 0; j < number_exercises[i]; j++) {
            printf("Enter muscle group for exercise %d day %d (back, biceps, calves, chest, glutes, legs, shoulders, or triceps):\n", j + 1, i + 1);
            scanf("%s", workoutPlan[i].exercise_group[j]);

            printf("Enter sets for exercise %d day %d (3 - 5):\n", j + 1, i + 1);
            scanf("%d", &workoutPlan[i].exercise_sets[j]);

            printf("Enter kind for exercise %d day %d (compound: cp or isolation: i):\n", j + 1, i + 1);
            scanf("%s", workoutPlan[i].exercise_kind[j]);

            printf("Enter recommendation preference for exercise %d day %d (recommended: r or not recommended: /r):\n", j + 1, i + 1);
            scanf("%s", workoutPlan[i].exercise_rec[j]);

            // Display entered data for confirmation
            printf("Exercise: %s, Sets: %d, Kind: %s, Recommended: %s\n",
                   workoutPlan[i].exercise_group[j],
                   workoutPlan[i].exercise_sets[j],
                   workoutPlan[i].exercise_kind[j],
                   workoutPlan[i].exercise_rec[j]);
        }
    }

    // Display the complete workout plan
    printf("\nWorkout Plan: %s\n", workout_name);
    for (int i = 0; i < workout_day; i++) {
        printf("\nDay %d:\n", i + 1);
        for (int j = 0; j < workoutPlan[i].number_of_exercises; j++) {
            printf("  Muscle Group: %s, Sets: %d, Kind: %s, Recommended: %s\n",
                   workoutPlan[i].exercise_group[j],
                   workoutPlan[i].exercise_sets[j],
                   workoutPlan[i].exercise_kind[j],
                   workoutPlan[i].exercise_rec[j]);
        }
    }
}





//create a workoutplan and create a txt file that contains the workoutplan

//fullbody: 2x chest 2x back 2x legs
//Upperbody: 2x Chest 1x shoulders 2x back 1x triceps
//Lowerbody:






//ask user if he wants to use a recommended workoutprogram or create a costum workout

//create workoutprogram with different different amount of days(3-5), exercises and sets(3-5):
