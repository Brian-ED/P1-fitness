#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create proposed workout with our structs of excersises


// Defining our input
char input[150];

//
int likedworkout(){
    while (1) { // Loop until valid input is provided
        printf("Do you like this workout? yes/no\n");
        scanf("%s", input);

        // Compare input strings
        if (strcmp(input, "yes") == 0) {
            return 1;
        } else if (strcmp(input, "no") == 0) {
            printf("Which exercise don't you like? \n");
            scanf("%s", input);
            return 0;
        } else {
            printf("Invalid input, please pick between 'yes' or 'no'.\n");
        }
    }
}
   /* printf("Do you like this workout? yes/no\n");
    scanf("%s", input);
    if(!strcmp(input, "yes")) {
        return 1;
    } else if(!strcmp(input, "no")) {
        printf("Which exercise don't you like? \n");
        scanf("%s",input);
        return 0;
    } else{
        printf("Invalid input, please pick between yes or no\n");
    }
*/
