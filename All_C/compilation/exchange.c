/* gcc -Og -S exchange.c, get the compilation */

/* gcc -Og -o exchange -c mstore.c */
/* objdump -d exchange, disassembly */
#include<stdio.h>
long exchange(long *xp, long y){
    long x = *xp;
    *xp = y;
    return x;
}

void swap(long *x, long *y){
    long tmp = *x;
    *x = *y;
    *y = tmp;
}

void main(){
    long a = 4, b = 3;
    b = exchange(&a, b);
    printf("a = %ld, b = %ld\n", a, b);
}