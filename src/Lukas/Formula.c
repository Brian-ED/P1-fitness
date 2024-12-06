#include <stdio.h>
#include <math.h>

// Function to calculate weekly progression
double calculate_progression(double start_weight, double weekly_increment, int week, double max_weight) {
    double progression = start_weight + week * weekly_increment;
    if (progression > max_weight) {
        progression = max_weight; // Cap the progression at max_weight
    }
    return progression;
}

