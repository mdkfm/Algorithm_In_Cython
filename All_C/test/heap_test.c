/* Created by skf on 23-12-1. */
#include <malloc.h>

//#include "../include/heap.h"
#include "../Container/block.c"
#include "../Container/heap.c"

int cmp(void const*const e0, void const*const e1){
    return (*(long *)e0 - *(long *)e1);
}

void display(void const*const e){
    printf("%ld ", *(long *)e);
}

int main(){
    /* test */
    long a[12] = {0, 1, 2, 3, 4, 5, 5, 5, 7, 8, 9, 11};
    Heap*const H1 = heap_new(50, sizeof(long), cmp);
    heap_init(H1, (void *)a, 12);
    heap_display(H1, display);
    heap_append(H1, long, 10);
    heap_append(H1, long, -1);

    heap_display(H1, display);
    long unsigned length = H1->size;
    for(int i = 0; i < length; i++){
        long buf = heap_pop(H1, long);
        printf("%ld ", buf);
    }
    printf("\n");
}