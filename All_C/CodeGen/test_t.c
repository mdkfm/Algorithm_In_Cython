//
// Created by skf on 24-1-6.
//

#include <stdio.h>
#include "basic/gnuc.h"


#define STACK_DType int
#include "container/stack.h"
#undef STACK_DType


#define STACK_DType double
#include "container/stack.h"
#undef STACK_DType


#define DEQUE_DType int
#include "container/deque.h"
#undef DEQUE_DType

#define HEAP_DType double
#include "container/heap.h"
#undef HEAP_DType

int main(){
    auto_ptr(Stack) stack = stackT(int).new(10, NULL);
    stackT(int).append(stack, 1);
    stackT(int).append(stack, 2);
    stackT(int).append(stack, 3);
    stackT(int).append(stack, 4);

    stackT(int).display(stack);
    printf("\n");

    auto_ptr(Stack) stack2 = stackT(double).new(10, NULL);
    stackT(double).append(stack2, 1.1);
    stackT(double).append(stack2, 2.2);
    stackT(double).append(stack2, 3.3);
    stackT(double).append(stack2, 4.4);

    stackT(double).display(stack2);
    printf("\n");

    auto_ptr(Deque) deque = dequeT(int).new(10, NULL);

    dequeT(int).appendRight(deque, 1);
    dequeT(int).appendRight(deque, 2);
    dequeT(int).appendLeft(deque, 3);
    dequeT(int).appendLeft(deque, 4);

    dequeT(int).display(deque);
    printf("\n");

    auto_ptr(Heap) heap = heapT(double).new(10, NULL, NULL);
    heapT(double).push(heap, 1.1);
    heapT(double).push(heap, 2.2);
    heapT(double).push(heap, 3.3);
    heapT(double).push(heap, 4.4);

    heapT(double).display(heap);
    return 0;
}