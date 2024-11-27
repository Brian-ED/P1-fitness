#include <stdio.h>
#include <string.h>


void scan_program(char *exercise){
    int *text;
    char *name = strcat(exercise, ".prog.txt");
    printf("%s", name);
    printf("%s\n", name);


    FILE* ex_prog = fopen(name, "r");

    if(ex_prog == NULL){
        FILE* ex_prog = fopen(name, "ab+");
    }

    if(getc(ex_prog) == EOF){
        FILE* ex_prog = fopen(name, "w");
        printf("please enter the starting weight");
        scanf("%d",text);
        fprintf(ex_prog, " %d", text);
        fclose(ex_prog);
    } else {
        FILE* ex_prog = fopen(name, "a");
        printf("Please enter you new weight:");
        scanf("%d",text);
        fprintf(ex_prog, " %d", text);
        fclose(ex_prog);
    }
}

void calculate_new_weight(void){

}

void regression(){

}