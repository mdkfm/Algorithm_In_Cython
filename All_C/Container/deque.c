#include<stdio.h>

#include "../include/deque.h"

__receive __malloc Deque*const deque_new(size_t const mem_num, size_t const mem_size){
    Deque *new = (Deque*)malloc(sizeof(Deque));
    if(unlikely(new == NULL)){
        /* malloc fail */
        return NULL;
    }

    Block *data = block_new(mem_num, mem_size);
    if(unlikely(data == NULL)){
        /* malloc fail */
        free(new);
        return NULL;
    }

    new->data = data;
    new->maxsize = mem_num;
    new->size = 0;
    new->front = new->rear = 0;
    return new;
}

void deque_display(Deque const * const this, void (*display)(void *)){
    if(unlikely(deque_isEmpty(this))){
        printf("The deque is empty");
        return ;
    }
    printf("Left -> ");
    size_t size = this->size;
    for(size_t i = 0; i < size; i++){
        display(block_getPtr(this->data, (this->front + i) % this->maxsize));
        printf(" -> ");
    }
    printf("Right\n");
}

void deque_delete(Deque * this){
    block_delete(this->data);
    free(this);
}

int deque_appendLeft(Deque * const this, void *const value){
    if(unlikely(deque_isFull(this))){
        // append fail
        return 0;
    }
    size_t maxsize = this->maxsize;
    size_t index = (this->front + maxsize - 1) % maxsize;
    block_write(this->data, index, 1, value);
    this->front = index;
    this->size++;
    return 1;
}

int deque_appendRight(Deque * const this, void *const value){
    if(unlikely(deque_isFull(this))){
        // append fail
        return 0;
    }

    block_write(this->data, this->rear, 1, value);
    this->rear = (this->rear + 1) % (this->maxsize);
    this->size++;
    return 1;
}

Monad *deque_popLeft(Deque * const this){
    if(unlikely(deque_isEmpty(this))){
        // pop fail
        return NULL;
    }
    Monad *value = monad_new(this->data->mem_size);
    block_read(this->data, this->front, 1, value->data);

    this->front = (this->front + 1) % (this->maxsize);
    this->size--;
    return value;
}

Monad *deque_popRight(Deque *const this){
    if(unlikely(deque_isEmpty(this))){
        // pop fail
        return NULL;
    }
    size_t maxsize = this->maxsize;
    size_t index = (this->rear + maxsize - 1) % maxsize;

    Monad *value = monad_new(this->data->mem_size);
    block_read(this->data, index, 1, value->data);

    this->rear = index;
    this->size--;
    return value;
}

Monad *deque_getLeft(Deque const * const this, size_t index){
    // get elem from left
    // index from 0 to (rear - front -1) % maxsize
    size_t get_index = (this->front + index) % (this->maxsize);
    if(get_index >= this->rear){
        // get fail
        return NULL;
    }
    Monad *value = monad_new(this->data->mem_size);
    block_read(this->data, get_index, 1, value->data);
    return value;
}

Monad *deque_getRight(Deque const * const this, size_t index){
    // get elem from right
    // index from 0 to (q->rear - q->front -1) % q->maxsize
    size_t maxsize = this->maxsize;
    size_t get_index = (this->rear + maxsize - index - 1) % maxsize;
    if(get_index < this->front){
        //get fail
        return NULL;
    }
    Monad *value = monad_new(this->data->mem_size);
    block_read(this->data, get_index, 1, value->data);
    return value;
}
