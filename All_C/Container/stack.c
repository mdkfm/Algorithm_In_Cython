/* Created by skf on 23-12-5. */
#include <stdlib.h>
#include <stdio.h>

#include "../include/stack.h"

__malloc Stack*const stack_new(size_t const maxsize) {
    Stack *list = (Stack *) malloc(sizeof(Stack));
    list->maxsize = maxsize;
    list->size = 0;
    list->data = (Elem *) calloc(maxsize, sizeof(Elem));
    return list;
}

void stack_delete(Stack * this) {
    free(this->data);
    free(this);
}

void stack_clear(Stack *const this) {
    this->size = 0;
}

int stack_init(Stack *const this, Elem const *const data, size_t const length) {
    if(unlikely(length > this->maxsize)){
        /* init fail */
        return -1;
    }

    for(int i = 0; i < length; i++){
        this->data[i] = data[i];
    }
    return 0;
}

int stack_get(Stack const *const this, Elem *const buf, size_t const index, int const reversed){
    size_t size = this->size;
    if (unlikely(index > size)) {
        /* size out of range */
        return -1;
    }
    size_t get_size = reversed ? size - index - 1 : index;
    *buf = this->data[get_size];
    return 0;
}

int stack_append(Stack *const this, Elem const elem) {
    if (unlikely(stack_isFull(this))) {
        /* append fail */
        return -1;
    }
    this->data[this->size] = elem;
    this->size++;
    return 0;
}

int stack_pop(Stack *const this, Elem *const buf) {
    if (unlikely(stack_isEmpty(this))) {
        /* pop fail */
        return -1;
    }
    this->size--;
    *buf = this->data[this->size];
    return 0;
}

void stack_display(Stack const *const this) {
    size_t size = this->size;
    for (int i = 0; i < size; i++) {
        printf("%ld ", this->data[i].num_int64);
    }
    printf("\n");
}