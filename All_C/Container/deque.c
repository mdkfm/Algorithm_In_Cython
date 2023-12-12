#include<stdio.h>

#include "../include/deque.h"
#include "../include/error.h"

__receive __malloc Deque*const deque_new(size_t const maxsize){
    Deque *new = (Deque*)malloc(sizeof(Deque));
    new->maxsize = maxsize;
    new->size = 0;
    new->data = (Elem*)calloc(maxsize, sizeof(Elem));
    new->front = new->rear = 0;
    return new;
}

__receive Deque*const deque_transFromStack(Stack *stack){
    /* transform a stack to a deque */
    /* the stack will be free */
    Deque *deque = (Deque*)malloc(sizeof(Deque));
    deque->size = stack->size;
    deque->front = 0;
    deque->rear = stack->size;
    deque->maxsize = stack->maxsize;
    deque->data = stack->data;

    free(stack);
    return deque;
}

int deque_appendStack(Deque * const this, Stack const*const stack){
    /* init a deque from a stack, shallow copy the data from stack into this */
    /* the stack will not be free */
    if(unlikely(stack_size(stack) > deque_freeSize(this))){
        /* init fail */
        return -1;
    }
    Elem *data = this->data, *source = stack->data;
    size_t index = stack->size, rear = this->rear, maxsize = this->maxsize;
    for(int i = 0; i < index; i++){
        data[(rear + i + 1) % maxsize] = source[i];
    }
    this->rear = (rear + index) % maxsize;
    this->size += index;
    return 0;
}

int deque_appendLeft(Deque * const this, Elem const elem){
    if(unlikely(deque_isFull(this))){
        // append fail
        return 0;
    }
    size_t maxsize = this->maxsize;
    size_t index = (this->front + maxsize - 1) % maxsize;
    this->data[index] = elem;
    this->front = index;
    this->size++;
    return 1;
}

int deque_appendRight(Deque * const this, Elem const elem){
    if(unlikely(deque_isFull(this))){
        // append fail
        return 0;
    }
    
    this->data[this->rear] = elem;
    this->rear = (this->rear + 1) % (this->maxsize);
    this->size++;
    return 1;
}

int deque_popLeft(Deque * const this, Elem *const buf){
    if(unlikely(deque_isEmpty(this))){
        // pop fail
        return 0;
    }
    *buf = this->data[this->front];
    this->front = (this->front + 1) % (this->maxsize);
    this->size--;
    return 1;
}

int deque_popRight(Deque *const this, Elem *const buf){
    if(unlikely(deque_isEmpty(this))){
        // pop fail
        return 0;
    }
    size_t maxsize = this->maxsize;
    size_t index = (this->rear + maxsize - 1) % maxsize;
    *buf = this->data[index];
    this->rear = index;
    this->size--;
    return 1;
}

Elem deque_get(Deque const * const this, size_t const index){
    if(unlikely(index >= this->size)){
        raise_error("deque_get: index out of range");
    }
    size_t get_index = index;
    get_index = (this->front + get_index) % this->maxsize;
    return this->data[get_index];
}

//int deque_getLeft(Deque const * const this, size_t index, Elem *buf){
//    // get elem from left
//    // index from 0 to (rear - front -1) % maxsize
//    size_t get_index = (this->front + index) % (this->maxsize);
//    if(get_index >= this->rear){
//        // get fail
//        return 0;
//    }
//    *buf = this->data[get_index];
//    return 1;
//}
//
//int deque_getRight(Deque const * const this, size_t index, Elem *buf){
//    // get elem from right
//    // index from 0 to (q->rear - q->front -1) % q->maxsize
//    size_t maxsize = this->maxsize;
//    size_t get_index = (this->rear + maxsize - index - 1) % maxsize;
//    if(get_index < this->front){
//        //get fail
//        return 0;
//    }
//    *buf = this->data[get_index];
//    return 1;
//}

void deque_display(Deque const * const this){
    if(unlikely(deque_isEmpty(this))){
        printf("The deque is empty");
        return ;
    }
    printf("Left -> ");
    size_t size = this->size;
    for(size_t i = 0; i < size; i++){
        // printf long
        printf("%ld -> ", this->data[(this->front + i) % this->maxsize].num_int64);
    }
    printf("Right\n");
}

void deque_delete(Deque * this){
    free(this->data);
    free(this);
}

void Deque_raii(Deque_class_ptr * ptr){
//    printf("deque_raii\n");
    deque_delete(*ptr);
}

//int deque_link(Deque *this, Deque *other){
//    /* link other after this */
//    if(this->rear < this->front){
//        /* the right end of this is filled */
//        return -1;
//    }
//
//    if(deque_size(this) + deque_size(other) > this->maxsize){
//        this->data = realloc(
//                this->data,
//                sizeof(Elem) * (this->maxsize + other->maxsize + 1)
//        );
//        this->maxsize += other->maxsize;
//    }
//
//    Elem *data = this->data, *other_data = other->data;
//    size_t maxsize = this->maxsize, other_maxsize = other->maxsize;
//
//    size_t rear = this->rear;
//    size_t cur = other->front;
//    size_t other_rear = other->rear;
//    while(cur != other_rear){
//        data[rear] = other_data[cur];
//        rear = (rear + 1) % (maxsize + 1);
//        cur = (cur + 1) % (other_maxsize + 1);
//    }
//    this->rear = rear;
//    return 0;
//}
