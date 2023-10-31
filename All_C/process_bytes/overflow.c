#include<stdio.h>
#include<limits.h>
#include<stdlib.h>

//***************** Overflow usually occurs during calculation *****************//
/* There are some methods to check the calculation whether overflow */

/* test the unsigned add */
int uadd_ok(unsigned x, unsigned y){
    return (x + y) > x;
}

void test_uadd(){
    unsigned a = 0x11111111;
    unsigned b = 0x11111111;
    printf("Max unsigned int: %u\n", UINT_MAX);  /* 32 bits */
    printf("%d: %u + %u = %u\n", uadd_ok(a, b), a, b, a + b);
}

int tadd_ok(int x, int y){
    return !((x > 0 && y > 0 && x + y <= 0) || (x < 0 && y < 0 && x + y >= 0));
}

int umult_ok(unsigned x, unsigned y){
    unsigned p = x * y;
    return !x || p / x == y;
}

int tmult_ok(int x, int y){
    int p = x * y;
    return !x || p / x == y;
}

/* We could use a more big int to receive the result */
/* In fact, this is more readable and exact */
// int tmult_ok(__int32_t x, __int32_t y){
//     __int64_t result = x * (__int64_t) y;
//     return (result <= INT_MAX) && (result >= INT_MIN);
// }

void test_tadd_tmult(){
    int x = 0x7FFFFFFF;
    int y = 0x80000000;
    printf("Max int: %d, Min int: %d\n", INT_MAX, INT_MIN);  /* 32 bits */
    printf("%d: %d + %d = %d\n", tadd_ok(x, y), x, y, x + y);
    printf("%d: %d * %d = %d\n", tmult_ok(x, y), x, y, x * y);
}


//***************** The overflow also occurs when use unsigned *****************//

float sum_elements(float a[], unsigned length){
    int i;
    float result = 0;

    /* use i < length instead of i <= length */
    // for(i = 0; i<= length - 1; i++) may overflow
    for(i = 0; i < length; i++){
        result += a[i];
    }
    return result;
}

/* size_t is unsigned */
/* the second parameter of maaloc is size_t */
/* We could check overflow before malloc */
void *malloc_not_overflow(int ele_num, size_t ele_size){
    u_int64_t required = ele_num * (u_int64_t) ele_size;
    size_t request = (size_t) required;
    if(request != required){
        /* Overflow occurred */
        return NULL;
    }
    void * result = malloc(request);
    if(result == NULL){
        /* malloc failed */
        return NULL;
    }
    return result;
}


//***************** Float *****************//

/* when we transform a big float to a int, which int could not denote */
/* The Intel set it to be TMin */
void test_float2int(){
    float y = 1e400; /* overflow as inf*/
    int x = y;
    printf("Ifinity %f to int: %d\n", y, x);
}

/* The float32 could only denote 23 effective digits */
/* The float64 is 52 */
/* When we transfer a int with many effective digits to float */
/* It may underflow */
void test_int2float(){
    int x = 987654321; /* int32*/
    float y = x; /* float32*/
    int z = y;
    printf("int %d to float32 %.2f to int %d\n", x, y, z);

    /* So, we should make sure the num of float digits big enough */
    double b = x; /* float64 */
    int c = b;
    printf("int %d to float64 %.2lf to int %d\n", x, b, c);

    long int a = 998877665544332211; /* int64 */
    long double d = a; /* float128 */
    long int e = d;
    printf("int %ld to float64 %.2Lf to int %ld\n", a, d, e);
}

/* Because the round behavior */ 
/* the calculation between big float and small float may underflow */
void test_float_calculation(){
    float x = 3.14, y = 1e10;
    printf("(%.2f + %.2f) - %.2f = %.2f\n", x, y, y, (x + y) - y);
    printf("%.2f - %.2f + %.2f = %.2f\n", y, y, x, y - y + x);
}


void main(){
    test_float_calculation();

}