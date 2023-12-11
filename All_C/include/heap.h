/* Created by skf on 23-12-1. */
#ifndef ALL_C_HEAP_H
#define ALL_C_HEAP_H
#include "data.h"
#include "gnuc.h"

typedef struct Heap{
    /* Complete Bi-Tree */
    Elem *data;
    int (*cmp)(Elem const e0, Elem const e1);
    /* compare function, if e0 > e1 return 1,
     * this max-heap is constructed according to cmp */
    size_t size;
    size_t maxsize;
} Heap;

__receive __malloc Heap*const heap_new(size_t const maxsize, int (*cmp)(Elem const, Elem const));

/* $Begin static inline */
__receive static inline int heap_isEmpty(Heap const * const this){
    return this->size == 0;
}

__receive static inline int heap_isFull(Heap const * const this){
    return this->size == this->maxsize;
}

__receive static inline size_t heap_size(Heap const * const this){
    return this->size;
}

__receive static inline size_t heap_freeSize(Heap const * const this){
    return this->maxsize - this->size;
}
/* $End static inline */

int heap_init(Heap * const this, Elem * const list, size_t const length);
void heap_display(Heap const * const this);
void heap_delete(Heap * const this);
int heap_top(Heap const * const this, Elem * const buf);
int heap_pop(Heap * const this, Elem * const buf);
int heap_append(Heap * const this, Elem const key);
int heap_increase(Heap * const this, size_t const index, Elem const key);
#endif /*ALL_C_HEAP_H */
