#include <stdio.h>
#include <string.h>
#include <math.h>
typedef struct {
    int  week;
    int  weight;
    int  sets[4];
}progression;

// calculate next suggested progression for user
progression calculate_new_weight(char *filename, int *new_weight, int *new_reps){
    progression last_weight;

    // Reads in data from exercise file
    double x[300], y[300];
    int n = 0;
    FILE *file = fopen(filename, "r");
    while (fscanf(
        file, "%d %d %d %d %d %d",
        &last_weight.week,
        &last_weight.weight,
        &last_weight.sets[0],
        &last_weight.sets[1],
        &last_weight.sets[2],
        &last_weight.sets[3]
    ) == 6 ) {
        x[n] = last_weight.week; // TODO: use actual weeks
        y[n] = last_weight.weight;
        n++;
    }
    Term t = log_regression(n, x, y);

    // +0.5 before rounding down rounds to nearest
    *new_weight = 0.5+t.coefficient*log(t.exponent*(last_weight.week+1));

    int new_weight_lower = 0.5+last_weight.weight*1.1;
    int new_weight_upper = 0.5+last_weight.weight*1.2;

    int new_repsNew = 0;

    for (int i = 8; i <= 12; i++){
        int count = 0;
        for (int j = 0; j < 4; j++){
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
        printf("As a recommendation you should chose a weight that lies between: %d kg and %d kg.\n",new_weight_lower, new_weight_upper);
        scanf("%d", new_weight);
    } else *new_reps = new_repsNew;

    fclose(file);
    return last_weight;
}

// write new progression to txt file
progression new_progression(char *filename, progression last_weight, int new_weight, int new_reps){
    progression new_weight_data = { 0 };

    FILE *file = openCreate(filename, "a");

    printf("The target reps for today are %d and the target weight is %d kg\n", new_reps, new_weight);

    printf("please enter the amount of reps you have taken for set 1: (target: %d | last time: %d)\n", new_reps, last_weight.sets[0]);
    scanf("%d", &new_weight_data.sets[0]);
    printf("please enter the amount of reps you have taken for set 2: (target: %d | last time: %d)\n", new_reps, last_weight.sets[1]);
    scanf("%d", &new_weight_data.sets[1]);
    printf("please enter the amount of reps you have taken for set 3: (target: %d | last time: %d)\n", new_reps, last_weight.sets[2]);
    scanf("%d", &new_weight_data.sets[2]);
    printf("please enter the amount of reps you have taken for set 4: (target: %d | last time: %d)\n", new_reps, last_weight.sets[3]);
    scanf("%d", &new_weight_data.sets[3]);

    // TODO: use weeks gotten from GetDate
    new_weight_data.week = last_weight.week + 1;

    new_weight_data.weight = new_weight;

    fprintf(file, "%d %d %d %d %d %d\n", new_weight_data.week,
                                         new_weight_data.weight,
                                         new_weight_data.sets[0],
                                         new_weight_data.sets[1],
                                         new_weight_data.sets[2],
                                         new_weight_data.sets[3]);
    return new_weight_data;
}

void scan_prog(char *exercise){
    int text;
    char *name = strcat(exercise, ".prog.txt");
    printf("%s", name);
    printf("%s\n", name);

    FILE* ex_prog = fopen(name, "r");
    int new_weight = 0;
    int new_reps = 0;

    if(ex_prog == NULL){
        ex_prog = fopen(name, "ab+");
        new_reps = 8;
        printf("please enter a starting weight: ");
        scanf("%d", &new_weight);
    }

    progression last_weight = calculate_new_weight(name, &new_weight, &new_reps);

    progression new_weight_data = new_progression(name, last_weight, new_weight, new_reps);

    fclose(ex_prog);
}
