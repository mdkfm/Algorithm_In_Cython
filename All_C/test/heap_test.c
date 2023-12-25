/* Created by skf on 23-12-1. */
#include <malloc.h>

#include "../include/heap.h"
#include "../Container/block.c"

int cmp(Block const*const this, size_t const index0,size_t const e1){
    return *(long *)block_getPtr(this, index0) - *(long *)block_getPtr(this, e1);
}

void display(void const*const e){
    printf("%ld ", *(long *)e);
}

int main(){
    /* test */
    long a[12] = {0, 1, 2, 3, 4, 5, 5, 5, 7, 8, 9, 11};
    Heap*const H1 = heap_new(50, sizeof(long), cmp, display);
    heap_init(H1, (void *)a, 12);
    heap_display(H1);
    heap_append(H1, tmp_mptr((long)10));
    heap_append(H1, tmp_mptr((long)6));

    heap_display(H1);
    long unsigned length = H1->size;
    for(int i = 0; i < length; i++){
        auto_ptr(Monad) buf = heap_pop(H1);
        printf("%ld ", *(long *)buf->data);
    }
    printf("\n");
}