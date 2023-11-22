#include<stdio.h>
#include<stdlib.h>

#define N 1000

void transpose(int *dst, int *src, int dim){
    // dst[i][j] = src[j][i] 
    for(int i = 0, layer = 0; layer < dim; i++){
        int j = (i % dim) * dim + i / dim;
        dst[j] = src[i];
        layer += (i + 1) % dim == 0 ? 1 : 0;  
    }
}

void transpose_unroll(int *dst, int *src, int dim, int unroll){
    // with -Ofast optimization, the best unroll is 20
    int layer = 0;
    int i, end = dim - unroll + 1;
    for(i = 0; layer < end ; i++){
        int cond, j;
        j = (i % dim) * dim + i / dim;
        for(int k = 0; k < unroll; k++){
            // we could unroll this loop
            dst[j + k] = src[i + k * dim];
        }
        cond = (i + 1) % dim == 0;
        layer += cond ? unroll : 0;
        i += cond ? (unroll - 1) * dim : 0;

    }
    for(; layer < dim; i++){
        int j;
        j = (i % dim) * dim + i / dim;
        dst[j] = src[i];
        layer += (i + 1) % dim == 0 ? 1 : 0;  
    }
}

int main(){
    int dst[N][N], src[N][N];

    srand(100);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            int num = rand() % 100;
            src[i][j] = num;
            // printf("%2d ", num);
        }
        // printf("\n");
    }

    // printf("\n");
    for(int i = 0; i < 1000; i++) {
        // with -Ofast
        transpose((int *)dst, (int *)src, N); // 14s per 10000 loop
        transpose_unroll((int *)dst, (int *)src, N, 20); // 1.9s per 10000 loop
    }
    // for(int i = 0; i < N; i++){
    //     for(int j = 0; j < N; j++){
    //         printf("%d ", src[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("Done\n");
    return 0;
}