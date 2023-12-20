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
    Block *data;
} Deque;

Class(Deque)

__receive __malloc Deque*const deque_new(size_t const mem_num, size_t const mem_size);
void deque_display(Deque const * const this, void (*display)(void *));
void deque_delete(Deque * this);

/*
#define deque_appendLeft(this, type, elem) \
    do{ \
        if(unlikely(deque_isFull(this))){ \
            *//* append fail *//* \
            raise_error("deque_appendLeft: deque is full", __FILE__, __func__, __LINE__); \
        } \
        size_t maxsize = this->maxsize; \
        size_t index = (this->front + maxsize - 1) % maxsize; \
        block_set(this->data, index, 1, type, elem); \
        this->front = index; \
        this->size++; \
    }while(0)

#define deque_appendRight(this, type, elem) \
    do{ \
        if(unlikely(deque_isFull(this))){ \
            *//* append fail *//* \
            raise_error("deque_appendRight: deque is full", __FILE__, __func__, __LINE__); \
        } \
        size_t index = (this->rear + 1) % this->maxsize; \
        block_set(this->data, index, 1, type, elem); \
        this->rear = index; \
        this->size++; \
    }while(0)

#define deque_popLeft(this, type) ({ \
        if(unlikely(deque_isEmpty(this))){ \
            *//* pop fail *//* \
            raise_error("deque_popLeft: deque is empty", __FILE__, __func__, __LINE__); \
        } \
        size_t index = this->front; \
        this->front = (index + 1) % this->maxsize; \
        this->size--;\
        block_get(this->data, index, type);\
    })

#define deque_popRight(this, type) ({ \
        if(unlikely(deque_isEmpty(this))){ \
            *//* pop fail *//* \
            raise_error("deque_popRight: deque is empty", __FILE__, __func__, __LINE__); \
        } \
        size_t maxsize = this->maxsize; \
        size_t index = (this->rear + maxsize - 1) % maxsize; \
        this->rear = index; \
        this->size--;\
        block_get(this->data, index, type);\
    })

#define deque_get(this, index, type) ({ \
        if(unlikely(index >= this->size)){ \
            *//* index out of range *//* \
            raise_error("deque_get: index out of range", __FILE__, __func__, __LINE__);\
        } \
        size_t get_index = (this->front + index) % this->maxsize; \
        block_get(this->data, get_index, type); \
    })
*/

int deque_appendLeft(Deque *const this, void *const value);
int deque_appendRight(Deque *const this, void *const value);
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