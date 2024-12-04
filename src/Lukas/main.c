#include <stdio.h>
#include <math.h>
#include "progression.c"

void scan_prog(char *exercise);


int main(void){

    char exercise[80] = "bench press";

    scan_prog(exercise);

    return 0;
}


