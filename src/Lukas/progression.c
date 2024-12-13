#include <stdio.h>
#include <string.h>
#include <math.h>
typedef struct {
    int  week;
    int  weight;
    int  sets[4];
}progression;

// calculate next suggested progression for user
void calculate_new_weight(char *filename, progression last_weight[], int *new_weight, int *new_reps);

// write new progression to txt file
void new_progression(char *filename, progression new_weight_data[], progression last_weight[], int new_weight, int new_reps);

void scan_prog(char *exercise){
    int text;
    char *name = strcat(exercise, ".prog.txt");
    printf("%s", name);
    printf("%s\n", name);

    FILE* ex_prog = fopen(name, "r");
    int new_weight = 0;
    int new_reps = 0;
    int is_new = 0;

    if(ex_prog == NULL){
        ex_prog = fopen(name, "ab+");
        is_new = 1;
        new_reps = 8;
        printf("please enter a starting weight: ");
        scanf("%d", &new_weight);
    }
    progression last_weight[1] = {0};
    progression new_weight_data[1] = {0};

    if (is_new == 0){
        calculate_new_weight(name, last_weight, &new_weight, &new_reps);
    }
    new_progression(name, new_weight_data, last_weight, new_weight, new_reps);

    fclose(ex_prog);
}

void calculate_new_weight(char *filename, progression last_weight[], int *new_weight, int *new_reps){

    FILE *file = fopen(filename, "r");
    while (fscanf(file, "%d %d %d %d %d %d", &last_weight[0].week,
                                             &last_weight[0].weight,
                                             &last_weight[0].sets[0],
                                             &last_weight[0].sets[1],
                                             &last_weight[0].sets[2],
                                             &last_weight[0].sets[3]) == 6){
    }

    *new_weight = last_weight[0].weight;

    int new_weight_lower = floor(last_weight[0].weight*1.1);
    int new_weight_upper = floor(last_weight[0].weight*1.2);

    int new_repsNew = 0;

    for (int i = 8; i <= 12; i++){
        int count = 0;
        for (int j = 0; j < 4; j++){
            if (last_weight[0].sets[j] >= i){
                count++;
            }
        }
        if (count == 4){
            new_repsNew = i + 1;
        }
    }

    if (new_repsNew < last_weight[0].sets[0]){
        *new_reps = last_weight[0].sets[0];
    } else if (new_repsNew > 12){
        *new_reps = 8;
        printf("You have reached your maximum reps for this exercise, and you must therefore choose a new weight.\n");
        printf("As a recommendation you should chose a weight that lies between: %d kg and %d kg.\n",new_weight_lower, new_weight_upper);
        scanf("%d", new_weight);
    } else *new_reps = new_repsNew;

    fclose(file);
}

void new_progression(char *filename, progression new_weight_data[], progression last_weight[], int new_weight, int new_reps){

    FILE *file = fopen(filename, "a");

    printf("The target reps for today are %d and the target weight is %d kg\n", new_reps, new_weight);

    printf("please enter the amount of reps you have taken for set 1: (target: %d | last time: %d)\n", new_reps, last_weight[0].sets[0]);
    scanf("%d", &new_weight_data[0].sets[0]);
    printf("please enter the amount of reps you have taken for set 2: (target: %d | last time: %d)\n", new_reps, last_weight[0].sets[1]);
    scanf("%d", &new_weight_data[0].sets[1]);
    printf("please enter the amount of reps you have taken for set 3: (target: %d | last time: %d)\n", new_reps, last_weight[0].sets[2]);
    scanf("%d", &new_weight_data[0].sets[2]);
    printf("please enter the amount of reps you have taken for set 4: (target: %d | last time: %d)\n", new_reps, last_weight[0].sets[3]);
    scanf("%d", &new_weight_data[0].sets[3]);

    new_weight_data[0].week = last_weight[0].week + 1;

    new_weight_data[0].weight = new_weight;

    fprintf(file, "%d %d %d %d %d %d\n", new_weight_data[0].week,
                                         new_weight_data[0].weight,
                                         new_weight_data[0].sets[0],
                                         new_weight_data[0].sets[1],
                                         new_weight_data[0].sets[2],
                                         new_weight_data[0].sets[3]);
}
