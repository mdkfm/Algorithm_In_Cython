/* Created by skf on 23-12-1. */
#ifndef ALL_C_HEAP_H
#define ALL_C_HEAP_H
#include "block.h"
#include "gnuc.h"

typedef int (*Heap_cmp)(Block const*const this, size_t const index0, size_t const index1);
typedef void (*Heap_display)(void const*const);


typedef struct Heap{
    /* Complete Bi-Tree */
    Block *data;
    Heap_cmp cmp;
    Heap_display display;
    /* compare function, if e0 > e1 return 1, e0 == e1 return 0, e0 < e1 return -1 */
    /* this max-heap is constructed according to cmp */
    size_t size;
    size_t maxsize;
} Heap;

typedef Heap *const Heap_class_ptr;

__receive __malloc Heap*const
heap_new(size_t mem_num, size_t mem_size, Heap_cmp cmp, Heap_display display);
void heap_display(Heap const * const this);
void heap_delete(Heap * const this);

Monad *heap_top(Heap const * const this);
Monad *heap_pop(Heap * const this);
int heap_append(Heap * const this, Monad const*const key);
int heap_increase(Heap * const this, size_t index, Monad const*const key);


/* $Begin static inline */
static inline size_t heap_PARENT(size_t const i){
    return (i) >> 1;
}

static inline size_t heap_LEFT(size_t const i){
    return (i) << 1;
}

static inline size_t heap_RIGHT(size_t const i){
    return ((i) << 1) + 1;
}

static inline size_t heap_LAST_PARENT(Heap const * const this){
    return heap_PARENT(this->size);
}

static inline size_t heap_LAST(Heap const * const this){
    return this->size;
}

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

static inline void Heap_raii(Heap_class_ptr *ptr){
    heap_delete(*ptr);
}
/* $End static inline */

#endif /*ALL_C_HEAP_H */
