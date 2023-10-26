#include<stdio.h>
#include<limits.h>

int uadd_ok(unsigned x, unsigned y){
    return (x + y) > x;
}

int tadd_ok(int x, int y){
    return !((x > 0 && y > 0 && x + y <= 0) || (x < 0 && y < 0 && x + y >= 0));
}

// int tadd_ok(int x, int y){
//     int sum = x + y;
//     return (sum - x == y) && (sum - y == x);
// }


void main(){
    int x = 0x7FFFFFFF;
    int y = 0x7FFFFFFF;
    printf("%d, %d\n", INT_MAX, INT_MIN);
    printf("%d: %d + %d = %d\n", tadd_ok(x, y), x, y, x + y);
}