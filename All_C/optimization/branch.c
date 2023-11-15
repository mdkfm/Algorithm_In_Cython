#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>

// when the branch jmp is hardly predicted
// cmov is more effective than jmp
// we could write code that could generate cmov directly

// demo: compare a[i] and b[i], a[i] = min, b[i] = max
void minmax1(long a[], long b[], long n){
    // command style
    long i;
    for(i = 0; i < n; i++){
        if(a[i] > b[i]){
            long t = a[i];
            a[i] = b[i];
            b[i] = t;
        }
    }
}

void minmax2(long a[], long b[], long n){
    // cmov style
    long i;
    for(i = 0; i < n; i++){
        long min = a[i] < b[i] ? a[i] : b[i];
        long max = a[i] < b[i] ? b[i] : a[i];
        a[i] = min;
        b[i] = max;
    }
}

#define N 100000

void main(){
    long a[N], b[N];
    int i;
    srand(10);
    for(i = 0; i < N; i++){
        a[i] = rand();
        b[i] = rand();
    }

    struct timeval start, end;
    long timeuse;

    gettimeofday(&start, NULL);
    minmax1(a, b, N);
    gettimeofday(&end, NULL);
    timeuse = 1000000*(end.tv_sec - start.tv_sec) + end.tv_usec-start.tv_usec;
    printf("time = %08ld us\n", timeuse);

    gettimeofday(&start, NULL);
    minmax2(a, b, N);
    gettimeofday(&end, NULL);
    timeuse = 1000000*(end.tv_sec - start.tv_sec) + end.tv_usec-start.tv_usec;
    printf("time = %08ld us\n", timeuse);

}