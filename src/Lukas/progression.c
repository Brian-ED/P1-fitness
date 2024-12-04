#include <stdio.h>
#include <string.h>
#include <math.h>
typedef struct {
    int  week;
    int  weight;
    int  lift_1;
    int  lift_2;
    int  lift_3;
    int  lift_4;
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
    int starting_weight = 0;
    if(ex_prog == NULL){
        ex_prog = fopen(name, "ab+");
        printf("please enter a starting weight: ");
        scanf("%d", &starting_weight);
        fprintf(ex_prog, "%d %d", 1, starting_weight);
    }
    progression last_weight[1] = {0};
    progression new_weight_data[1] = {0};
    int new_weight = 0;
    int new_reps = 0;

    calculate_new_weight(name, last_weight, &new_weight, &new_reps);
    new_progression(name, new_weight_data, last_weight, new_weight, new_reps);

    fclose(ex_prog);
}

void calculate_new_weight(char *filename, progression last_weight[], int *new_weight, int *new_reps){

    FILE *file = fopen(filename, "r");
    while (fscanf(file, "%d %d %d %d %d %d", &last_weight[0].week,
                                             &last_weight[0].weight,
                                             &last_weight[0].lift_1,
                                             &last_weight[0].lift_2,
                                             &last_weight[0].lift_3,
                                             &last_weight[0].lift_4) == 6){
    }

    *new_weight = last_weight[0].weight;

    int upper_total = 0;

    int new_weight_lower = floor(last_weight[0].weight*1.1);
    int new_weight_upper = floor(last_weight[0].weight*1.3);

    if (last_weight[0].lift_1 >= 8 && last_weight[0].lift_2 >= 8 && last_weight[0].lift_3 >= 8 && last_weight[0].lift_4 >= 8){
        upper_total+=1;
    } if (last_weight[0].lift_1 >= 9 && last_weight[0].lift_2 >= 9 && last_weight[0].lift_3 >= 9 && last_weight[0].lift_4 >= 9){
        upper_total+=1;
    } if (last_weight[0].lift_1 >= 10 && last_weight[0].lift_2 >= 10 && last_weight[0].lift_3 >= 10 && last_weight[0].lift_4 >= 10){
        upper_total+=1;
    } if (last_weight[0].lift_1 >= 11 && last_weight[0].lift_2 >= 11 && last_weight[0].lift_3 >= 11 && last_weight[0].lift_4 >= 11){
        upper_total+=1;
    } if (last_weight[0].lift_1 >= 12 && last_weight[0].lift_2 >= 12 && last_weight[0].lift_3 >= 12 && last_weight[0].lift_4 >= 12){
        upper_total+=1;
    }

    if        (upper_total == 0){
        *new_reps = 8;
    } else if (upper_total == 1){
        *new_reps = 9;
    } else if (upper_total == 2){
        *new_reps = 10;
    } else if (upper_total == 3){
        *new_reps = 11;
    } else if (upper_total == 4){
        *new_reps = 12;
    } else if (upper_total == 5){
        *new_reps = 8;
        printf("you have reached your maximum reps for this exercise, and you must therefore choose a new weight.\n");
        printf("as a recommendation you should chose a weight that lies between: %d kg and %d kg.\n",new_weight_lower, new_weight_upper);
        scanf("%d", new_weight);
    }
    //printf("%d", upper_total);

fclose(file);

}

void new_progression(char *filename, progression new_weight_data[], progression last_weight[], int new_weight, int new_reps){

    FILE *file = fopen(filename, "a");

    printf("these are the target reps for today: %d and this is the target weight: %d\n", new_reps, new_weight);

    printf("please enter the amount of reps you have taken for set 1: (target %d)\n", new_reps);
    scanf("%d", &new_weight_data[0].lift_1);
    printf("please enter the amount of reps you have taken for set 2: (target %d)\n", new_reps);
    scanf("%d", &new_weight_data[0].lift_2);
    printf("please enter the amount of reps you have taken for set 3: (target %d)\n", new_reps);
    scanf("%d", &new_weight_data[0].lift_3);
    printf("please enter the amount of reps you have taken for set 4: (target %d)\n", new_reps);
    scanf("%d", &new_weight_data[0].lift_4);

    new_weight_data[0].week = last_weight[0].week + 1;
    new_weight_data[0].weight = new_weight;

    fprintf(file, "%d %d %d %d %d %d\n", new_weight_data[0].week,
                                         new_weight_data[0].weight,
                                         new_weight_data[0].lift_1,
                                         new_weight_data[0].lift_2,
                                         new_weight_data[0].lift_3,
                                         new_weight_data[0].lift_4);
}
