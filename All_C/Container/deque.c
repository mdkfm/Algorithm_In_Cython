#include<stdio.h>
#include "../include/deque.h"

/* $Begin static inline */
static inline size_t deque_realSize(Deque const * const this){
    return this->maxsize + 1;
}

static inline size_t deque_leftEnd(Deque const * const this){
    return this->front;
}

static inline size_t deque_rightEnd(Deque const * const this){
    return (this->rear + deque_realSize(this) - 1) % deque_realSize(this);
}
/* $End static inline */

__receive __malloc Deque*const
deque_new(size_t const mem_num, size_t const mem_size, void (*display)(void *)){
    Deque *new = (Deque*)malloc(sizeof(Deque));
    if(unlikely(new == NULL)){
        /* malloc fail */
        return NULL;
    }

    Block *data = block_new(mem_num + 1, mem_size);
    if(unlikely(data == NULL)){
        /* malloc fail */
        free(new);
        return NULL;
    }

    new->data = data;
    new->display = display;
    new->maxsize = mem_num;
    new->size = 0;
    new->front = new->rear = 0;
    return new;
}

void deque_display(Deque const * const this){
    if(unlikely(deque_isEmpty(this))){
        printf("The deque is empty");
        return ;
    }
    printf("Left -> ");
    size_t size = deque_size(this), front = this->front, realSize = deque_realSize(this);
    void (*display)(void *) = this->display;
    for(size_t i = 0; i < size; i++){
        display(block_getPtr(this->data, (front + i) % realSize));
        printf(" -> ");
    }
    printf("Right\n");
}

void deque_delete(Deque * this){
    block_delete(this->data);
    free(this);
}

int deque_appendLeft(Deque * const this, Monad const*const value){
    if(unlikely(deque_isFull(this))){
        // append fail
        return 0;
    }
    size_t realSize = deque_realSize(this);
    size_t index = (this->front + realSize - 1) % realSize;
    block_set(this->data, index, value);
    this->front = index;
    this->size++;
    return 1;
}

int deque_appendRight(Deque * const this, Monad const*const value){
    if(unlikely(deque_isFull(this))){
        // append fail
        return 0;
    }

    block_set(this->data, this->rear, value);
    this->rear = (this->rear + 1) % deque_realSize(this);
    this->size++;
    return 1;
}

Monad *deque_popLeft(Deque * const this){
    if(unlikely(deque_isEmpty(this))){
        // pop fail
        return NULL;
    }
    Monad *value = block_get(this->data, this->front);

    this->front = (this->front + 1) % deque_realSize(this);
    this->size--;
    return value;
}

Monad *deque_popRight(Deque *const this){
    if(unlikely(deque_isEmpty(this))){
        // pop fail
        return NULL;
    }
    size_t realSize = deque_realSize(this);
    size_t index = (this->rear + realSize - 1) % realSize;

    Monad *value = block_get(this->data, index);
    this->rear = index;
    this->size--;
    return value;
}

Monad *deque_getLeft(Deque const * const this, size_t index){
    // get elem from left
    // index from 0 to size
    if(index >= this->size){
        // get fail
        return NULL;
    }
    size_t get_index = (this->front + index) % deque_realSize(this);
    return block_get(this->data, get_index);
}

Monad *deque_getRight(Deque const * const this, size_t index){
    // get elem from right
    // index from 0 to size
    if(index >= this->size){
        // get fail
        return NULL;
    }
    size_t realSize = deque_realSize(this);
    size_t get_index = (this->rear + realSize - index - 1) % realSize;
    return block_get(this->data, get_index);
}
