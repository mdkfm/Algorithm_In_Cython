//
// Created by skf on 24-1-6.
//
#include <stdlib.h>
#include <stdio.h>
#include "gnuc.h"
#include "template.h"
#include "error.h"

#define TClass Deque
#ifndef ALL_C_DEQUE_H
#define ALL_C_DEQUE_H

typedef struct Deque Deque;

struct Deque{
    size_t front, rear;
    size_t maxsize;
    size_t size;
    FPtr display;
    DType *data;
};

DPtr(Deque);

void SF(delete)(Deque* this) {
    free(this->data);
    free(this);
}

void SF(clear)(Deque *const this) {
    this->size = 0;
}

static inline int SF(isFull)(Deque const* this) {
    /* if the num of elem is maxsize, full */
    return this->size == this->maxsize;
}

static inline int SF(isEmpty)(Deque const* this) {
    /* no elem, empty */
    return this->size == 0;
}

static inline size_t SF(size)(Deque const* this) {
    return this->size;
}

static inline size_t SF(freeSize)(Deque const* this) {
    return this->maxsize - this->size;
}

static inline void SF(raii)(Deque_class_ptr * this) {
    SF(delete)(*this);
}

static inline size_t SF(realSize)(Deque const * const this){
    return this->maxsize + 1;
}

static inline size_t SF(leftEnd)(Deque const * const this){
    return this->front;
}

static inline size_t SF(rightEnd)(Deque const * const this){
    return (this->rear + SF(realSize)(this) - 1) % SF(realSize)(this);
}

#endif //ALL_C_DEQUE_H

#define Class C(Deque)

__receive __malloc Deque*const
F(new)(size_t maxsize, void (*display)(DType)){
    Deque *new = (Deque*)malloc(sizeof(Deque));
    if unlikely(new == NULL){
        /* malloc fail */
        return NULL;
    }

    DType *data = malloc(maxsize * sizeof(DType));
    if unlikely(data == NULL){
        /* malloc fail */
        free(new);
        return NULL;
    }

    new->data = data;
    new->display =  display == NULL ? (FPtr)DISPLAY(DType) : (FPtr)display;
    new->maxsize = maxsize;
    new->size = 0;
    new->front = new->rear = 0;
    return new;
}

void F(display)(Deque *this){
    void (*display)(DType) = (void (*)(DType))this->display;
    if unlikely(display == NULL){
        raise_error("Display function is NULL", __FILE__, __func__, __LINE__);
    }
    if unlikely(SF(isEmpty)(this)){
        printf("The deque is empty");
        return ;
    }

    // display
    printf("Left -> ");
    DType *data = this->data;
    size_t first = SF(leftEnd)(this), size = SF(size)(this), realSize = SF(realSize)(this);
    for(size_t i = 0; i < size; i++){
        display(data[(first + i) % realSize]);
        printf(" -> ");
    }
    printf("Right\n");
}

int F(appendLeft)(Deque *this, DType elem){
    if unlikely(SF(isFull)(this)){
        return -1;
    }
    size_t realSize = SF(realSize)(this);
    size_t index = (this->front + realSize - 1) % realSize;
    DType *data = this->data;
    data[index] = elem;
    this->front = index;
    this->size++;
    return 0;
}

int F(appendRight)(Deque *this, DType elem){
    if unlikely(SF(isFull)(this)){
        return -1;
    }
    DType *data = this->data;
    data[this->rear] = elem;
    this->rear = (this->rear + 1) % SF(realSize)(this);
    this->size++;
    return 0;
}

DType F(popLeft)(Deque * this){
    if unlikely(SF(isEmpty)(this)){
        // pop fail
        raise_error("The deque is empty", __FILE__, __func__, __LINE__);
    }
    size_t index = SF(leftEnd)(this);
    this->front = (index + 1) % SF(realSize)(this);
    this->size--;
    DType *data = this->data;
    return data[index];
}

DType F(popRight)(Deque * this){
    if unlikely(SF(isEmpty)(this)){
        // pop fail
        raise_error("The deque is empty", __FILE__, __func__, __LINE__);
    }
    size_t realSize = SF(realSize)(this);
    size_t index = SF(rightEnd)(this);
    this->rear = index;
    this->size--;
    DType *data = this->data;
    return data[index];
}

DType F(getLeft)(Deque const* this, size_t index){
    // get elem from left
    // index from 0 to size
    if(index >= this->size){
        // get fail
        raise_error("Index error", __FILE__, __func__, __LINE__);
    }
    index = (SF(leftEnd)(this) + index) % SF(realSize)(this);
    DType *data = this->data;
    return data[index];
}

DType F(getRight)(Deque const* this, size_t index){
    // get elem from right
    // index from 0 to size
    if(index >= this->size){
        // get fail
        raise_error("Index error", __FILE__, __func__, __LINE__);
    }
    size_t realSize = SF(realSize)(this);
    index = (SF(rightEnd)(this) + realSize - index) % realSize;
    DType *data = this->data;
    return data[index];
}

typedef struct F(Func_T) {
    void (*delete)(Deque *this);
    void (*clear)(Deque *const this);
    int (*isFull)(Deque const *this);
    int (*isEmpty)(Deque const *this);
    size_t (*size)(Deque const *this);
    size_t (*freeSize)(Deque const *this);
    Deque *const (*new)(size_t const maxsize, void (*display)(DType));
    int (*appendLeft)(Deque *const this, DType const elem);
    int (*appendRight)(Deque *const this, DType const elem);
    DType (*popLeft)(Deque *const this);
    DType (*popRight)(Deque *const this);
    DType (*getLeft)(Deque const *const this, size_t const index);
    DType (*getRight)(Deque const *const this, size_t const index);
    void (*display)(Deque *const this);
} F(FuncT);

static F(FuncT) const F(funcT) = {
        .delete = SF(delete),
        .clear = SF(clear),
        .isFull = SF(isFull),
        .isEmpty = SF(isEmpty),
        .size = SF(size),
        .freeSize = SF(freeSize),
        .new = F(new),
        .appendLeft = F(appendLeft),
        .appendRight = F(appendRight),
        .popLeft = F(popLeft),
        .popRight = F(popRight),
        .getLeft = F(getLeft),
        .getRight = F(getRight),
        .display = F(display),
};

#define Deque(T) CCAT(Deque, T)
#define dequeT(T) Deque_##T##_funcT

#undef TClass