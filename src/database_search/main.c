#include <stdio.h>
#include <string.h>


#include "searching_database.c"


int main(void) {
    char inv_filename[STR_SIZ]; /* name of inventory file */
    FILE *inventoryp; /* inventory file pointer */
    search_params_t params; /* search parameter bounds */

    ///* Get name of inventory file and open it */
    printf("Enter name of inventory file> ");
    scanf("%s", inv_filename);
    inventoryp = fopen(inv_filename, "rb");
    if (!inventoryp) {
        perror("Error opening file\n");
        return 1;
    }

    /* Get the search parameters */
    params = get_params();

    /* Display all products that satisfy the search parameters */
    display_match(inventoryp, params);

    fclose(inventoryp);
    return 0;
}