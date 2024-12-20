// This type is used to make the log_regression() function able
// to return two floats, coefficient and exponent.
typedef struct Term {
  double coefficient, exponent;
} Term;

// Takes x and y values, and applies log_regression to get
// a coefficient and exponent for predicting future y values given x values.
// The given "function" is literally the two variables, use them with this formula:
// y = ln(x*exponent)*coefficient
Term log_regression(int n, float *x, float *y) {
    double sumx=0; // sum of all floats in x.
    double sumy=0; // log applied to each value in the y array, then sum of that.
    double sumxy=0; // first multiplies each value in x with the log of each value in y, and sums that.
    double sumx2=0; // sum of the square of each value in x.

    // "Your ancestors called it Magic, but you call it Math.
    // I come from a land where they are one and the same." -  Thor Odinson
    for(int i=0; i<=n-1; i++) {
        float Y = log(y[i]);
        sumx  += x[i];
        sumx2 += x[i]*x[i];
        sumy  += Y;
        sumxy += x[i]*Y;
    }

    // Magic turned to a coefficient and exponent that we're returning
    Term out = {
        .coefficient = 1/exp((sumx2*sumy - sumx*sumxy)/(n*sumx2-sumx*sumx)),
        .exponent = (n*sumx2 - sumx*sumx)/(n*sumxy - sumx*sumy)
    };
    return out;
}
