#include <stdio.h>
#include <string.h>

#define MIN_STOCK 1111 /* minimum stock number */
#define MAX_STOCK 9999 /* maximum stock number */
#define MAX_PRICE 1000.00 /* maximum product price */
#define STR_SIZ 80 /* number of characters in a string */

typedef struct { /* product structure type */
    int stock_num; /* stock number */
    char category[STR_SIZ];
    char tech_descript[STR_SIZ];
    double price;
} product_t;

typedef struct { /* search parameter bounds type */
    int low_stock, high_stock;
    char low_category[STR_SIZ], high_category[STR_SIZ];
    char low_tech_descript[STR_SIZ], high_tech_descript[STR_SIZ];
    double low_price, high_price;
} search_params_t;

search_params_t get_params(void);
void display_match(FILE *databasep, search_params_t params);
char menu_choose(search_params_t params);
int match(product_t prod, search_params_t params);
void show(product_t prod);

/*
 * Prompts the user to enter the search parameters
 */
search_params_t get_params(void) {
    search_params_t params;
    char choice;

    params.low_stock = MIN_STOCK;
    params.high_stock = MAX_STOCK;
    strcpy(params.low_category, "");
    strcpy(params.high_category, "zzzzzzzz");
    strcpy(params.low_tech_descript, "");
    strcpy(params.high_tech_descript, "zzzzzzzz");
    params.low_price = 0.0;
    params.high_price = MAX_PRICE;

    do {
        choice = menu_choose(params);

        switch (choice) {
            case 'a':
                printf("Enter low bound for stock number> ");
                scanf("%d", &params.low_stock);
                break;
            case 'b':
                printf("Enter high bound for stock number> ");
                scanf("%d", &params.high_stock);
                break;
            case 'c':
                printf("Enter low bound for category> ");
                scanf("%s", params.low_category);
                break;
            case 'd':
                printf("Enter high bound for category> ");
                scanf("%s", params.high_category);
                break;
            case 'e':
                printf("Enter low bound for technical description> ");
                scanf("%s", params.low_tech_descript);
                break;
            case 'f':
                printf("Enter high bound for technical description> ");
                scanf("%s", params.high_tech_descript);
                break;
            case 'g':
                printf("Enter low bound for price> ");
                scanf("%lf", &params.low_price);
                break;
            case 'h':
                printf("Enter high bound for price> ");
                scanf("%lf", &params.high_price);
                break;
            case 'q':
                printf("Search parameters accepted.\n");
                break;
            default:
                printf("Invalid choice. Please select again.\n");
        }
    } while (choice != 'q');

    return params;
}

/*
 * Displays a lettered menu with the current values of search parameters.
 * Returns the letter the user enters.
 */
char menu_choose(search_params_t params) {
    char choice;

    printf("\nSelect by letter a search parameter to set or enter q to\naccept parameters shown.\n\n");
    printf(" Search parameter \t Current value\n");
    printf("[a] Low bound for stock number \t\t %4d\n", params.low_stock);
    printf("[b] High bound for stock number \t %4d\n", params.high_stock);
    printf("[c] Low bound for category \t\t %s\n", params.low_category);
    printf("[d] High bound for category \t\t %s\n", params.high_category);
    printf("[e] Low bound for technical description \t %s\n", params.low_tech_descript);
    printf("[f] High bound for technical description \t %s\n", params.high_tech_descript);
    printf("[g] Low bound for price \t\t $%7.2f\n", params.low_price);
    printf("[h] High bound for price \t\t $%7.2f\n\n", params.high_price);

    printf("Selection> ");
    scanf(" %c", &choice);

    return choice;
}

/*
 * Determines whether record prod satisfies all search parameters
 */
int match(product_t prod, search_params_t params) {
    return (strcmp(params.low_category, prod.category) <= 0 &&
            strcmp(prod.category, params.high_category) <= 0 &&
            strcmp(params.low_tech_descript, prod.tech_descript) <= 0 &&
            strcmp(prod.tech_descript, params.high_tech_descript) <= 0 &&
            params.low_price <= prod.price &&
            prod.price <= params.high_price);
}

/*
 * Displays each field of prod. Leaves a blank line after the product display.
 */
void show(product_t prod) {
    printf("Stock Number: %d\n", prod.stock_num);
    printf("Category: %s\n", prod.category);
    printf("Technical Description: %s\n", prod.tech_descript);
    printf("Price: $%.2f\n\n", prod.price);
}

/*
 * Displays records of all products in the inventory that satisfy search
 * parameters.
 */
void display_match(FILE *databasep, search_params_t params) {
    product_t next_prod; /* current product from database */
    int no_matches = 1; /* flag indicating if no matches have been found */
    int status; /* input file status */

    /* Advances to first record with a stock number greater than or
       equal to lower bound. */
    for (status = fread(&next_prod, sizeof(product_t), 1, databasep);
         status == 1 && params.low_stock > next_prod.stock_num;
         status = fread(&next_prod, sizeof(product_t), 1, databasep)) {}

    /* Displays a list of the products that satisfy the search parameters */
    printf("\nProducts satisfying the search parameters:\n");

    while (status == 1 && next_prod.stock_num <= params.high_stock) {
        if (match(next_prod, params)) {
            no_matches = 0;
            show(next_prod);
        }
        status = fread(&next_prod, sizeof(product_t), 1, databasep);
    }

    /* Displays a message if no products found */
    if (no_matches)
        printf("Sorry, no products available\n");
}