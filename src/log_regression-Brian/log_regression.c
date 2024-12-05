typedef struct {
  double coefficient, exponent;
} Term;

Term log_regression(int n, double *y, double *x) {
    double sumx=0, sumy=0, sumxy=0, sumx2=0;

    for(int i=0; i<=n-1; i++) {
        double Y = log(y[i]);
        sumx  += x[i];
        sumx2 += x[i]*x[i];
        sumy  += Y;
        sumxy += x[i]*Y;
    }

    double num = n*sumx2 - sumx*sumx;
    Term out = {
        .coefficient = exp((sumx*sumxy - sumx2*sumy)/num),
        .exponent = num/(n*sumxy - sumx*sumy)
    };
    return out;
}
