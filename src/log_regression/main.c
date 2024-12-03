#include <stdio.h>
#include <math.h>
#include <assert.h>

int main() {
    int n;
    printf("\n  C program for Exponential Curve fitting\n\n");
    printf("Enter the value of number of terms n:\n");
    scanf("%d",&n);

    float x[20];
    printf("Enter the values of x:\n");
    for (int i=0; i<=n-1; i++) {
        scanf("%f",&x[i]);
    }
    float y[20];
    printf("Enter the values of y:\n");
    for (int i=0; i<=n-1; i++) {
        scanf("%f",&y[i]);
    }

    Term out = log_regression(n, x, y);
    printf("\n\n The curve is y = ln(x*%4.3f)*%4.3f = x\n", out.exponent, out.coefficient);
    return 0;
}