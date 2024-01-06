//
// Created by skf on 24-1-6.
//

#include <stdio.h>
#include "gnuc.h"


#define DType int
#include "stack.h"
#undef DType


#define DType double
#include "stack.h"
#undef DType


#define DType int
#include "deque.h"
#undef DType



int main(){
    auto_ptr(Stack) stack = stackT(int).new(10, NULL);
    stackT(int).append(stack, 1);
    stackT(int).append(stack, 2);
    stackT(int).append(stack, 3);
    stackT(int).append(stack, 4);

    stackT(int).display(stack);
    printf("\n");
    while(!stackT(int).isEmpty(stack)){
        printf("%d ", stackT(int).pop(stack));
    }
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
    return 0;
}