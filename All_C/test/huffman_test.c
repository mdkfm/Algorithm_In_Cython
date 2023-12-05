/* Created by skf on 23-12-2. */
#include <malloc.h>

#include "../include/data.h"
#include "../include/huffman.h"


int main(){
    /* test */
    long unsigned a[12] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    double b[12] = {0.07, 0.19, 0.02, 0.06, 0.32, 0.03, 0.21, 0.11, 0.01, 0.18};

    double sum = 0;
    for(int i = 0; i < 10; i++){
        sum += b[i];
        printf("%c %lf\n", (char)a[i], b[i]);
    }
    printf("sum %lf\n", sum);
    HuffmanTree *tree = huffman_new((Elem *)a, b, 10);
    if(tree == NULL){
        printf("malloc error\n");
        return 0;
    }
    printf("%d\n", tree == NULL);
    printf("huffman tree:\n");

    huffman_display(tree);
    huffman_delete(tree);
}