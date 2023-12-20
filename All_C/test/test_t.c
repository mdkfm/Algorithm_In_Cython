//
// Created by skf on 23-12-18.
//
#include <stdio.h>
#include "../Container/block.c"
#include <stdlib.h>

typedef struct A{
    int a;
    int b;
} A;

A *func(){
    return tmp_ptr((A){1, 2});
}

int main(){
    A* a = func();
    printf("%p %d %d\n", a, a->a, a->b);
    a->a = 3;
    a->b = 4;
    printf("%p %d %d\n", a, a->a, a->b);
}