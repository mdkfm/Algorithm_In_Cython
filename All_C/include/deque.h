#ifndef ALL_C_Deque_H
#define ALL_C_Deque_H

#include<malloc.h>
#include "block.h"
#include "stack.h"
#include "gnuc.h"

typedef struct{
    size_t front, rear;
    size_t maxsize;
    size_t size;
    void (*display)(void *);
    Block *data;
} Deque;

Class(Deque)

__receive __malloc Deque*const
deque_new(size_t const mem_num, size_t const mem_size, void (*display)(void *));
void deque_display(Deque const * const this);
void deque_delete(Deque * this);
int deque_appendLeft(Deque * const this, Monad const*const value);
int deque_appendRight(Deque * const this, Monad const*const value);
Monad *deque_popLeft(Deque *const this);
Monad *deque_popRight(Deque *const this);
Monad *deque_getLeft(Deque const * const this, size_t index);
Monad *deque_getRight(Deque const * const this, size_t index);


/* $Begin static inline */
__receive static inline int deque_isEmpty(Deque const * const this){
    /* no elem, empty */
    return this->size == 0;
}

__receive static inline int deque_isFull(Deque const * const this){
    // if the num of elem is maxsize, full
    return this->size == this->maxsize;
}

__receive static inline size_t deque_size(Deque const * const this){
    return this->size;
}

__receive static inline size_t deque_freeSize(Deque const * const this){
    return this->maxsize - this->size;
}

static inline void deque_clear(Deque *const this){
    this->front = this->rear = 0;
    this->size = 0;
}

static inline void Deque_raii(Deque_class_ptr * ptr){
    deque_delete(*ptr);
}
/* $End static inline */

#endif