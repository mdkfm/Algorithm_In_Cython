#include<stdio.h>
#include<string.h>

void inplace_swap(int *a, int *b){
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int bis(int x, int m){
    return x | m;
}

int bic(int x, int m){
    return x & ~m;
}

int bool_or(int x, int y){
    int result = bis(x, y);
    return result;
}

int bool_xor(int x, int y){
    int result = bis(bic(x, y), bic(y, x));
    return result;
}



void main(){
    int c[] = {1, 2, 3, 3};
    test(c, 4);

}