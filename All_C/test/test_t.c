//
// Created by skf on 23-12-4.
//

#include <stdio.h>
#include <stdlib.h>
#include "../include/gnuc.h"


int main(){
    size_t a = 10;
    size_t b = 20;
    int c[a];
    printf("%ld\n", sizeof(c));
    return 0;
}