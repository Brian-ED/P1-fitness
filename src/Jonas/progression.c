#include <stdio.h>
#include <string.h>


void scan_program(char *exercise){
    int text;
    char *name = strcat(exercise, ".prog.txt");
    printf("%s", name);

    FILE* ex_prog = fopen(name, "r");

    if(ex_prog == NULL){
        ex_prog = fopen(name, "ab+");
    }

    if(getc(ex_prog) == EOF){
        FILE* ex_prog = fopen(name, "w");
        printf("please enter the starting weight");
        scanf("%d",&text);
        fprintf(ex_prog, " %d", text);
        fclose(ex_prog);
    } else {
        FILE* ex_prog = fopen(name, "a");
        printf("Please enter you new weight:");
        fprintf(ex_prog, " %d", text);
        scanf("%d",&text);
        fprintf(ex_prog, " %d", text);
        fclose(ex_prog);
    }
}

void weight_recommendation(void){
    FILE* ex_prog = fopen(name, "r");
    int weight;
    if(ex_prog != NULL) {
        while(getc(ex_prog) != EOF)
        fscanf(ex_prog,"%d", &weight);
        fclose(ex_prog);
    } else {
        exit(EXIT_FALIURE);
    }
    int recom_weight_10 = weight * 1.1;
    int recom_weight_30 = weight * 1.3;

    printf("Vi anbefaler at dit næste løft ligger i intervallet: %d-%d kg.", recom_weight_10, recom_weight_30);
}

void regression(void){
    FILE* ex_prog = fopen(name, "r");
    if(ex_prog != NULL) {
        int weight[];
        while(getc(ex_prog) != EOF){
            fscanf(ex_prog,"%d", weight);
        }
    } else {
        exit(EXIT_FALIURE);
    }
}