typedef struct Term {
  double coefficient, exponent;
} Term;

Term log_regression(int n, double *x, double *y) {
    double sumx=0, sumy=0, sumxy=0, sumx2=0;

    for(int i=0; i<n; i++) {
        double Y = log(x[i]);
        sumx  += y[i];
        sumx2 += y[i]*y[i];
        sumy  += Y;
        sumxy += y[i]*Y;
    }

    double num = n*sumx2 - sumx*sumx;
    Term out = {
        .coefficient = num/(n*sumxy - sumx*sumy),
        .exponent = exp((sumx*sumxy - sumx2*sumy)/num)
    };

    return out;

}
