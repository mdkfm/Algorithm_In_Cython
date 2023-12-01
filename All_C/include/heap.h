/* Created by skf on 23-12-1. */
#ifndef ALL_C_HEAP_H
#define ALL_C_HEAP_H
#include "../include/data.h"


typedef struct Heap{
    /* Complete Bi-Tree */
    Elem *data;
    int (*cmp)(Elem const e0, Elem const e1);
    /* compare function, if e0 > e1 return 1,
     * this max-heap is constructed according to cmp */
    long unsigned size;
    long unsigned maxsize;
} Heap;

Heap* heap_new(long unsigned const maxsize, int (*cmp)(Elem const, Elem const));
/* The first node is 0 */
void heap_heapify(Heap * const this, long unsigned const start);
void heap_display(Heap const * const this);
void heap_init(Heap * const this, Elem * const list, long unsigned const length);
void heap_display(Heap const * const this);
void heap_delete(Heap * const this);
Elem heap_top(Heap const * const this);
Elem heap_pop(Heap * const this);
int heap_insert(Heap * const this, Elem const key);
int heap_increase(Heap * const this, long unsigned const index, Elem const key);
#endif //ALL_C_HEAP_H
