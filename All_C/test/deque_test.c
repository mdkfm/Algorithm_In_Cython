#include "../include/deque.h"

void display(void *x){
    printf("%ld ", *(long*)x);
}

#define test_type long

void main(){
    auto_ptr(Deque) deque = deque_new(10, sizeof(test_type), display);
    deque_appendLeft(deque, tmp_mptr((test_type)1));
    deque_appendLeft(deque, tmp_mptr((test_type)2));
    deque_appendRight(deque, tmp_mptr((test_type)3));
    deque_appendRight(deque, tmp_mptr((test_type)4));
    deque_display(deque);

    auto_ptr(Monad) x = deque_popLeft(deque);
    printf("%ld\n", *(long*)x->data);
    monad_share(deque_popRight(deque), &x);
    printf("%ld\n", *(long*)x->data);
    deque_display(deque);

    auto_ptr(Monad) y = deque_getLeft(deque, 0);
    printf("%ld\n", *(long*)y->data);
}