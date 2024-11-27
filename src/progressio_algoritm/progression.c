#include <stdio.h>
#include <string.h>


void scan_program(char *exercise){
    int *text;
    char *name = strcat(exercise, ".prog.txt");
    printf("%s", name);

    FILE* ex_prog = fopen(name, "r");

    if(ex_prog == NULL){
        FILE* ex_prog = fopen(name, "ab+");
    }

    if(getc(ex_prog) == EOF){
        FILE* ex_prog = fopen(name, "w");
        printf("please enter the starting weight");
    }
    else 
        printf("your ")


    fclose(ex_prog);

}


