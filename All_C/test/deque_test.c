#include "../include/deque.h"

void main(){
    Deque *deque = deque_new(10);
    deque_appendLeft(deque, (Elem)(long)1);
    deque_appendLeft(deque, (Elem)(long)2);
    Elem buf = deque_get(deque, 0);
    printf("%ld\n", buf.num_int64);
    deque_display(deque);
}