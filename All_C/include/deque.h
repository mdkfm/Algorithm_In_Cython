#ifndef ALL_C_Deque_H
#define ALL_C_Deque_H

#include<malloc.h>
#include "data.h"
#include "stack.h"
#include "gnuc.h"

typedef struct{
    size_t front, rear;
    size_t maxsize;
    size_t size;
    Elem *data;
} Deque;

typedef Deque * const Deque_class_ptr;

__receive __malloc Deque*const deque_new(size_t const maxsize);

__receive Deque*const deque_transFromStack(Stack *list);

int deque_appendStack(Deque * const this, Stack const*const list);

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
/* $End static inline */

int deque_appendLeft(Deque *const this, Elem const elem);
int deque_appendRight(Deque *const this, Elem const elem);
int deque_popLeft(Deque *const this, Elem *const buf);
int deque_popRight(Deque *const this, Elem *const buf);

Elem  deque_get(Deque const * const this, size_t index);
//int deque_getLeft(Deque const * const this, size_t index, Elem *buf);
//int deque_getRight(Deque const * const this, size_t index, Elem *buf);

void deque_display(Deque const * const this);
void deque_delete(Deque * this);
void Deque_raii(Deque_class_ptr *ptr);
//int deque_link(Deque *this, Deque *other);

#endif