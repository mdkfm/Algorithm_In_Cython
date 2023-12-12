//
// Created by skf on 23-12-11.
//

#include "../CodeGen/listGen.h"

#ifndef listGen_int
#define listGen_int
listGen(int)
#endif

int main(){
    auto_ptr(List, int) list = listT(int).new(10);
    listT(int).write(list, (ListSlice){0, 10, 1}, (int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10);
    listT(int).display(list);

    auto_ptr(List, int) view = listT(int).view(list, (ListSlice){0, 10, 2});
    listT(int).display(view);
    return 0;
}