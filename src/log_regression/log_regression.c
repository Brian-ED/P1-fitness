typedef struct {
    float coefficient, exponent;
} Term;

Term log_regression(int n, float *x, float *y) {
    float sumx=0, sumy=0, sumxy=0, sumx2=0;

    for(int i=0; i<=n-1; i++) {
        float Y = log(y[i]);
        sumx  += x[i];
        sumx2 += x[i]*x[i];
        sumy  += Y;
        sumxy += x[i]*Y;
    }

    Term out = {
        .coefficient = 1/exp((sumx2*sumy - sumx*sumxy)/(n*sumx2-sumx*sumx)),
        .exponent = (n*sumx2 - sumx*sumx)/(n*sumxy - sumx*sumy)
    };
    return out;
}
