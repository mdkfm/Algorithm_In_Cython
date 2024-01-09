//
// Created by skf on 24-1-6.
//

#ifndef STACK_DType
#error No STACK_DType defined
#else
#include <stdlib.h>


#define DType STACK_DType
#include "../basic/gnuc.h"
#include "../basic/template.h"
#include "../basic/error.h"

#define TClass Stack

#ifndef ALL_C_STACK_H
#define ALL_C_STACK_H
/* $Begin static template */
typedef struct Stack Stack;

struct Stack{
    size_t maxsize;
    size_t size;
    FPtr_t display;
    void * data;
};

DPtr(Stack);

void SF(delete)(Stack* this) {
    free(this->data);
    free(this);
}

void SF(clear)(Stack *const this) {
    this->size = 0;
}

static inline int SF(isFull)(Stack const* this) {
    /* if the num of elem is maxsize, full */
    return this->size == this->maxsize;
}

static inline int SF(isEmpty)(Stack const* this) {
    /* no elem, empty */
    return this->size == 0;
}

static inline size_t SF(freeSize)(Stack const* this) {
    return this->maxsize - this->size;
}

static inline void SF(raii)(Stack_class_ptr * this) {
    SF(delete)(*this);
}

/* $End static template */
#endif

#define Class C(Stack)

__receive __malloc  Stack*const
F(new)(size_t const maxsize, void (*display)(DType)) {
    Stack *list = (Stack *) malloc(sizeof(Stack));
    list->maxsize = maxsize;
    list->size = 0;
    list->display = display == NULL ? (FPtr_t)DISPLAY(DType) : (FPtr_t)display;
    list->data = malloc(maxsize * sizeof(DType));
    return list;
}


int F(init)(Stack* this, DType const * src, size_t length) {
    if(unlikely(length > this->maxsize)){
        /* init fail */
        return -1;
    }
    DType *data = this->data;
    for(int i = 0; i < length; i++){
        data[i] = src[i];
    }
    return 0;
}

DType F(get)(Stack const* this, size_t index, int reversed){
    size_t size = this->size;
    if unlikely(index > size) {
        /* size out of range */
        raise_error("Index out of range", __FILE__, __func__, __LINE__);
    }
    size_t get_size = reversed ? size - index - 1 : index;
    DType *data = this->data;
    return data[get_size];
}

int F(append)(Stack* this, DType elem) {
    if unlikely(SF(isFull(this))) {
        /* append fail */
        raise_error("Stack is full", __FILE__, __func__, __LINE__);
    }
    DType *data = this->data;
    data[this->size] = elem;
    this->size++;
    return 0;
}

DType F(pop)(Stack* this) {
    if unlikely(SF(isEmpty(this))) {
        /* pop fail */
        raise_error("Stack is empty", __FILE__, __func__, __LINE__);
    }
    this->size--;
    DType *data = this->data;
    return data[this->size];
}

void F(display)(Stack const* this) {
    void (*display)(DType) = (void (*)(DType))this->display;
    if unlikely(display == NULL){
        raise_error("Display function is NULL", __FILE__, __func__, __LINE__);
    }
    if unlikely(SF(isEmpty(this))) {
        printf("The stack is empty");
        return;
    }

    // display
    printf("Bottom -> ");
    size_t size = this->size;
    DType *data = this->data;
    for (int i = 0; i < size; i++) {
        display(data[i]);
        printf(" -> ");
    }
    printf("Top\n");
}

typedef struct FuncT_t FuncT_t;

struct FuncT_t{
    void (*delete)(Stack* this);
    void (*clear)(Stack* const this);
    int (*isFull)(Stack const* this);
    int (*isEmpty)(Stack const* this);
    size_t (*freeSize)(Stack const* this);
    Stack*const (*new)(size_t const maxsize, void (*display)(DType));
    int (*init)(Stack *const this, DType const *const data, size_t const length);
    DType (*get)(Stack const *const this, size_t const index, int const reversed);
    int (*append)(Stack *const this, DType const elem);
    DType (*pop)(Stack *const this);
    void (*display)(Stack const *const this);
};

static FuncT_t const F(funcT) = {
        .delete = SF(delete),
        .clear = SF(clear),
        .isFull = SF(isFull),
        .isEmpty = SF(isEmpty),
        .freeSize = SF(freeSize),
        .new = F(new),
        .init = F(init),
        .get = F(get),
        .append = F(append),
        .pop = F(pop),
        .display = F(display),
};

#define stackT(T) classFuncT(Stack, T)

#undef TClass
#undef Class
#undef DType

#endif //STACK_DType