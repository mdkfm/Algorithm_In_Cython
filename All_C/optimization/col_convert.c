#include<stdio.h>
#include<stdlib.h>

#define N 1000

void col_convert(int *G, int dim){
    int end = dim * dim;
    for(int i = 0, layer = 0; i < end; i++){
        int j = (i % dim) * dim + i / dim;
        int result = G[i] || G[j]; 
        G[i] = result;
        G[j] = result;
        int cond = (i + 1) % dim == 0;
        i += cond ? layer + 2 : 0;
        layer += cond ? 1 : 0;
    }
}

void col_convert_unroll(int *G, int dim, int unroll){
    // with -Ofast optimization, the best unroll is 20
    int layer = 0;
    int i, end = dim - unroll + 1;
    for(i = 0; layer < end ; i++){
        int cond, j;
        j = (i % dim) * dim + i / dim;
        for(int k = 0; k < unroll; k++){
            int result = G[i + k * dim] || G[j + k];
            G[i + k * dim] = result;
            G[j + k] = result;
        }
        cond = (i + 1) % dim == 0;
        layer += cond ? unroll : 0;
        i += cond ? (unroll - 1) * dim : 0;

    }
    for(; layer < dim; i++){
        int j;
        j = (i % dim) * dim + i / dim;
        int result = G[i] || G[j]; 
        G[i] = result;
        G[j] = result;
        layer += (i + 1) % dim == 0 ? 1 : 0;  
    }
}

int main(){
    int src[N][N];
    srand(10);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            int num = rand() % 2 || i == j;
            src[i][j] = num;
            // printf("%2d ", num);
        }
        // printf("\n");
    }

    // printf("\n");
    for(int i = 0; i < 1000; i++) {
        // with -Ofast
        col_convert((int*)src, N);
        col_convert_unroll((int*)src, N, 5);
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