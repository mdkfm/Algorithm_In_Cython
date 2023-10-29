#include<stdio.h>
#include<limits.h>

typedef unsigned char *byte_pointer;

/* swap two value by swaping bytes */
void bytes_swap(byte_pointer a, byte_pointer b, size_t len){
    size_t i;
    unsigned char tmp = 0;
    for(i = 0; i < len; i++){
        tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
}

/* show the bytes of start with len */
void show_bytes(byte_pointer start, size_t len){
    size_t i;
    for(i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    
    printf("\n");
}

/* use byte_pointer to check byte order */
int is_little_endian(){
    int x = INT_MIN; /* INT_MIN declared in limits.h */
    byte_pointer p = (byte_pointer) &x;
    return !(*p);
}

/* use bit calculation to check */ 
/* whether machine use the arithmetic shift right */
int is_arithmetic_shift(){
    int x = -1; /* is all 1 */
    /* if arithmetic, x >> 1 is also all 1 */
    return !~(x >> 1);
}

/* the transform order is important */
void multitrans(){
    short ax = -12345;
    unsigned uy = ax;
    printf("short -> unsigned: ");
    show_bytes((byte_pointer) &ax, 2);
    show_bytes((byte_pointer) &uy, 4);
    printf("%u\n", uy);

    int n = ax;
    unsigned y = n;
    printf("short -> int -> unsigned: ");
    show_bytes((byte_pointer) &n, 4);
    show_bytes((byte_pointer) &y, 4);
    
    unsigned short us = ax;
    unsigned uu = us;
    printf("short -> unsigned short -> unsigned: ");
    show_bytes((byte_pointer) &us, 4);
    show_bytes((byte_pointer) &uu, 4);
}


/* int divide by the power of 2, round to zero */
/* when x >= 0, x >> k */
/* when x < 0, (x + (1 << k) - 1) >> k */
// int div_2expk(int x, unsigned k){
//     return (x<0 ? x + (1 << k) - 1 : x) >> k;
// }

/* in fact, use the arithmetic shift right */
int div_2expk(int x, unsigned k){
    int bias = (x >> 31) & ((1 << k) - 1);
    return (x + bias) >> k;
}

void test_div_2expk(){
    int a = -53;
    unsigned k = 2;
    printf("div_2expk: %d/2^%d = %d, ", a, k, div_2expk(a, k));
    printf("%d/2^%d = %d\n", -a, k, div_2expk(-a, k));
    printf("Answer: %d, %d\n", a / (1 << k), (-a) / (1 << k));
}


/* in float, there are the special nums: POS_INFINITY, NEG_INFINITY, NEG_ZERO */
#define POS_INFINITY 1e400 /* 1e400 positive overflow in float32 and float64 */
#define NEG_INFINITY -POS_INFINITY
#define NEG_ZERO (-1.0 / POS_INFINITY)
void test_infinity(){
    double pinf = POS_INFINITY, ninf = NEG_INFINITY, nzero = NEG_ZERO;
    printf("The positive infinity: %f, bytes: ",pinf);
    show_bytes((byte_pointer) &pinf, sizeof(double));
    printf("The negtive infinity: %f, bytes: ",ninf);
    show_bytes((byte_pointer) &ninf, sizeof(double));
    printf("The negtive zero:: %f, bytes: ",nzero);
    show_bytes((byte_pointer) &nzero, sizeof(double));
}

void main(){
    if(is_little_endian()){
        printf("This is a little endian machine\n\n");
    }
    else{
        printf("This is a big endian machine\n\n");
    }
    if(is_arithmetic_shift()){
        printf("This machine is with arithmetic shift\n\n");
    }
    else{
        printf("This machine is with logic shift\n\n");
    }

    test_infinity();
}