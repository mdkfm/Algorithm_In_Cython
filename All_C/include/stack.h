//
// Created by skf on 23-12-5.
//

#ifndef ALL_C_STACK_H
#define ALL_C_STACK_H
#include "data.h"
#include "gnuc.h"

typedef struct Stack{
    size_t maxsize;
    size_t size;
    Elem *data;
} Stack;

typedef Stack *const Stack_class_ptr;

__malloc Stack*const stack_new(size_t const maxsize);
void stack_delete(Stack * this);
void stack_clear(Stack *const this);

int stack_init(Stack *const this, Elem const *const data, size_t const length);

int stack_get(Stack const *const this, Elem *const buf, size_t const size, int const reversed);
int stack_append(Stack *const this, Elem const elem);
int stack_pop(Stack *const this, Elem *const buf);
void stack_display(Stack const *const this);

/* $Begin static inline */
static inline int stack_isFull(Stack const *const this) {
    /* if the num of elem is maxsize, full */
    return this->size == this->maxsize;
}

static inline int stack_isEmpty(Stack const *const this) {
    /* no elem, empty */
    return this->size == 0;
}

static inline size_t stack_size(Stack const *const this) {
    return this->size;
}

static inline size_t stack_freeSize(Stack const *const this) {
    return this->maxsize - this->size;
}

static inline void Stack_raii(Stack_class_ptr * this) {
    stack_delete(*this);
}

/* $End static inline */

#endif //ALL_C_LIST_H
