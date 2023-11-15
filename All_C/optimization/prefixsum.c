#include<stdlib.h>
#include<stdio.h>

void psum(float a[], float p[], long n){
    long i;
    float acc = a[0];
    p[0] = acc;
    for(i = 1; i < n; i++){
        acc += a[i];
        p[i] = acc;
    }
}

void psum_unroll(float a[], float p[], long n){
    // 4 * 4 unroll, reach throughput limit
    // in theory, 3 * 3 unroll reachs throughput limit
    long i;
    float acc0 = a[0], acc1 = a[1] + acc0, acc2 = a[2] + acc1, acc3 = a[3] + acc2;
    p[0] = acc0; p[1] = acc1, p[2] = acc2, p[3] = acc3;
    for(i = 4; i < n - 3; i += 4){
        acc0 += a[i];
        acc1 += a[i + 1];
        acc2 += a[i + 2];
        acc3 += a[i + 3];
        p[i] = acc0;
        p[i + 1] = acc1;
        p[i + 2] = acc2;
        p[i + 3] = acc3;
    }
    for(; i < n; i++){
        acc0 += a[i];
        p[i] = acc0;
    }
}

#define N 100000

void main(){
    float a[N], result[N];
    srand(10);
    int i;
    for(i = 0; i < N; i++){
        a[i] = rand();
    }
    for(i = 0; i < 40000; i++){
        psum(a, result, N);        // 71 us / call
        psum_unroll(a, result, N); // 23 us / call
    }
    // result: 447.045104
    printf("Over\n");
}