#include <stdio.h>
#include <string.h>


void scan_prog(char *exercise){

    char *name = strcat(exercise, ".prog.txt");
    printf("%s", name);


    FILE* ex_prog = fopen(name, "r");

    if (ex_prog == NULL){
//      Here is a mistake.
//      You are re-declaring the variable with a type.
//      this means you aren't overwriting ex_prog, but creating a new variable.
//      ↓↓↓↓↓
        FILE* ex_prog = fopen(name, "ab+");
    }

     if (getc(ex_prog) == EOF){
        printf("please enter the starting weight");
    }
    else 
        printf("your ");


    fclose(ex_prog);

}


