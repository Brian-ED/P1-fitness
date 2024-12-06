#include <stdio.h>
#include <stdlib.h>

int main() {
    float amount_weight;
    int sets;
    int reps;
    char proceeding;
    char tooheavy;

    printf("Please enter the amount of weight you're lifting: ");
    while (scanf("%f", &amount_weight) != 1){
        printf("\n Please enter numerals\n");
        scanf("%*s");
    }


    printf("Please enter the number of reps you have done: ");
    while (scanf("%d", &reps) != 1){
        printf("\nPlease enter numerals\n");
        scanf("%*s");

    }

    printf("Please enter the number of sets you completed: ");
    while (scanf("%d", &sets)!= 1){
        printf("\nPlease enter numerals\n");
        scanf("%*s");
    }

    printf("\nAcknowledged: You are currently lifting %.2f kg for %d reps and %d sets.\n", amount_weight, reps, sets);

    float suggested_weight = amount_weight + 2.0;
    printf("The suggested weight for next week is %.2f kg\n", suggested_weight);

    if (suggested_weight > amount_weight * 1.5) {
        printf("\nCAUTION: The increase of the weight might be too intense. You might need to decrease the weight.\n");
    }

    printf("\nIs the suggested increase too much, too easy, or spot on? (type 't' for too much, 'e' for too easy, 's' for spot on): ");
    scanf(" %c", &tooheavy);

    if (tooheavy == 't' || tooheavy == 'T') {
        suggested_weight -= 2.0;
        printf("\nReducing the increased weight. New suggested weight: %.2f kg\n", suggested_weight);
    } else if (tooheavy == 'e' || tooheavy == 'E') {
        suggested_weight += 2.0;
        printf("\nIncreasing the increased weight. New suggested weight: %.2f kg\n", suggested_weight);
    } else if (tooheavy == 's' || tooheavy == 'S') {
        printf("\nYou chose to stay with the suggested weight: %.2f kg\n", suggested_weight);
    } else {
        printf("\nInvalid choice. Keeping the suggested weight: %.2f kg\n", suggested_weight);
    }

    printf("\nProgressive overload plan:\n");
    for (int week = 1; week <= 4; week++) {
        printf("Week %d: %.2f kg for %d sets of %d reps\n", week, suggested_weight + (week * 2.0), sets, reps);
    }

    printf("\nWould you like to try lifting a different weight? Yes (y) / No (n): ");
    scanf(" %c", &proceeding);

    if (proceeding == 'n' || proceeding == 'N') {
        printf("\nThank you for using the fitness program. Remember to lift safely and have a good workout. Good luck!\n");
        return 0;
    } else {
        printf("\nFeel free to restart the program with new inputs.\n");
    }

    return 0;
}
