#include "../include/deque.h"

void display(void *x){
    printf("%ld ", *(long*)x);
}

void main(){
    auto_ptr(Deque) deque = deque_new(10, sizeof(long));
    deque_appendLeft(deque, long, 1);
    deque_appendLeft(deque, long, 2);
    deque_appendRight(deque, long, 3);
    deque_appendRight(deque, long, 4);
    deque_display(deque, display);

    long x;
    x = deque_popLeft(deque, long);
    printf("%ld\n", x);
    x = deque_popRight(deque, long);
    deque_display(deque, display);

    long y = deque_get(deque, 0, long);
    printf("%ld\n", y);
}