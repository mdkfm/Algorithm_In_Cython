#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

// write / read depandency will reduce efficiency
// if write / read depandent, the read operation should be excuted after the write

void cumsum1(double *a, int len, double *result){
    int i;
    result[0] = a[0];
    // in loop, write and read of result[i] are depandent
    for(i = 1; i < len; i++){
        result[i] = result[i - 1] * a[i];
    }
}


void cumsum2(double *a, int len, double *result){
    int i;
    double acc = a[0];
    result[0] = acc;
    
    // use a tmp variable to cal cumsum
    // there is only write operation of result[i]
    for(i = 1; i < len; i++){
        acc *= a[i];
        result[i] = acc;
    }
}

#define N 300000

void main(){
    double a[N], b[N];
    int i;
    srand(10);
    for(i = 0; i < N; i++){
        a[i] = rand();
    }

    for(i = 0; i < 10000; i++){
        cumsum1(a, N, b);
        cumsum2(a, N, b);

    }
}