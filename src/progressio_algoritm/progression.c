#include <stdio.h>
#include <string.h>


void scan_prog(char *exercise){

    char *name = strcat(exercise, ".prog.txt");
    printf("%s\n", name);


    FILE* ex_prog = fopen(name, "r");

    if (ex_prog == NULL){
        FILE* ex_prog = fopen(name, "ab+");
    }

     if (getc(ex_prog) == EOF){
        printf("please enter the starting weight\n");
    }
   

    fclose(ex_prog);

}






