#include<stdio.h>


typedef unsigned char *byte_pointer;

void bytes_swap(byte_pointer a, byte_pointer b, size_t len){
    size_t i;
    unsigned char tmp = 0;
    for(i = 0; i < len; i++){
        tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
}

void show_bytes(byte_pointer start, size_t len){
    size_t i;
    for(i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    
    printf("\n");
}


void multitrans(){
    short ax = -12345;
    unsigned uy = ax; 
    show_bytes((byte_pointer) &ax, 2);
    show_bytes((byte_pointer) &uy, 4);
    printf("%u\n", uy);

    int n = ax;
    unsigned y = n;
    show_bytes((byte_pointer) &n, 4);
    show_bytes((byte_pointer) &y, 4);
    
    unsigned short us = ax;
    unsigned uu = us;
    show_bytes((byte_pointer) &us, 4);
    show_bytes((byte_pointer) &uu, 4);
}

float sum_elements(float a[], unsigned length){
    int i;
    float result = 0;

    for(i = 0; i < length; i++){
        result += a[i];
    }
    return result;
}

void main(){
    float a[] = {1, 2 ,3};
    printf("%f", sum_elements(a, 3));
}