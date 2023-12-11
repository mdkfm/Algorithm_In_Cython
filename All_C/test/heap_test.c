/* Created by skf on 23-12-1. */
#include <malloc.h>

#include "../include/heap.h"

int cmp(Elem const e0, Elem const e1){
    return (e0.num_int64 - e1.num_int64) > 0;
}

int main(){
    /* test */
    long a[12] = {0, 1, 2, 3, 4, 5, 5, 5, 7, 8, 9, 11};
    Heap*const H1 = heap_new(50, cmp);
    heap_init(H1, (Elem *)a, 12);
    heap_append(H1, (Elem)(long)10);
    heap_append(H1, (Elem)(long)-1);

    heap_display(H1);
    long unsigned length = H1->size;
    Elem buf;
    for(int i = 0; i < length; i++){
        heap_pop(H1, &buf);
        printf("%ld ", buf.num_int64);
    }
    printf("\n");
}