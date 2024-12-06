#include <stdio.h>
#include <math.h>

int main() {
    // Input data points (x, y)
    double x[] = {1, 2, 3, 4, 5}; // Independent variable
    double y[] = {2.3, 2.8, 3.6, 4.5, 5.1}; // Dependent variable
    int n = 5;

    double log_x[n];
    double y_pred[n];

    double mean_log_x=0.0, mean_y=0.0, numerator = 0.0, denominator = 0.0;
    int i;
    for (i = 0; i < n; i++) {
        log_x[i] = log(x[i]);
        mean_log_x += log_x[i];
        mean_y += y[i]/n;
    }
    // Calculate slope (b) and intercept (a)
    for (i = 0; i < n; i++) {
        double num = log_x[i] - mean_log_x/n;
        numerator += num * (y[i] - mean_y);
        denominator += num * num;
    }
    double b = numerator / denominator;
    double a = mean_y - b * mean_log_x/n;

    // Calculate R^2
    double ss_tot = 0.0, ss_res = 0.0;
    for (i = 0; i < n; i++) {
        y_pred[i] = a + b * log_x[i]; // Predicted y value
        ss_tot += (y[i] - mean_y) * (y[i] - mean_y);
        ss_res += (y[i] - y_pred[i]) * (y[i] - y_pred[i]);
    }
    double r_squared = 1 - ss_res/ss_tot;

    // Output results
    printf("Logarithmic Model: y = %.3f + %.3f * ln(x)\n", a, b);
    printf("R^2: %.3f\n", r_squared);

    return 0;
}