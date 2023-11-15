#include<stdlib.h>
#include<stdio.h>

double poly_unroll(double a[], double x, long degree){
    long i;
    double acc0 = a[0], acc1 = a[1] * x, acc2 = a[2] * x * x, acc3 = a[3] * x * (x * x);
    double muled0 = x, muled1 = x*muled0, muled2 = x*muled1, muled3 = x * muled2, xpwr = muled3;
    for(i = 4; i < degree - 3; i += 4){
        acc0 += a[i] * xpwr;
        acc1 += a[i + 1] * (xpwr * muled0);
        acc2 += a[i + 2] * (xpwr * muled1);
        acc3 += a[i + 3] * (xpwr * muled2);
        xpwr *= muled3;
    }
    for(; i < degree; i++){
        acc0 += a[i] * xpwr;
        xpwr *= x;
    }
    return (acc0 + acc1) + (acc2 + acc3);
}

#define N 100000

void main(){
    double x = 0.99, a[N], result;
    srand(10);
    int i;
    for(i = 0; i < N; i++){
        a[i] = rand() % 10;
    }
    for(i = 0; i < 100000; i++){
        result = poly_unroll(a, x, N - 1);
    }
    // result: 447.045104
    printf("%lf\n", result);
}