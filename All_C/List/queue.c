#include<stdio.h>
#include "../include/data.h"
#include "../include/queue.h"

/* circular queue */

Queue *queue_new(size_t const maxsize){
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->maxsize = maxsize;
    queue->data = (Elem*)calloc(maxsize + 1, sizeof(Elem));
    queue->front = queue->rear = 0;
    return queue;
}


int queue_isEmpty(Queue const *this){
    /* no elem, empty */
    return this->front == this->rear;
}

int queue_isFull(Queue const *this){
    // if the num of elem is maxsize, full
    return (this->rear + 1) % (this->maxsize + 1) == this->front;
}

int queue_appendLeft(Queue *this, Elem elem){
    if(queue_isFull(this)){
        // append fail
        return 0;
    }
    size_t front = this->front;
    size_t index = front == 0 ? this->maxsize : front - 1;
    this->data[index] = elem;
    this->front = index;
    return 1;
}

int queue_appendRight(Queue *this, Elem elem){
    if(queue_isFull(this)){
        // append fail
        return 0;
    }
    
    this->data[this->rear] = elem;
    this->rear = (this->rear + 1) % (this->maxsize + 1);
    return 1;
}

int queue_popLeft(Queue *this, Elem *buf){
    if(queue_isEmpty(this)){
        // pop fail
        return 0;
    }
    *buf = this->data[this->front];
    this->front = (this->front + 1) % (this->maxsize + 1);
    return 1;
}

int queue_popRight(Queue *this, Elem *buf){
    if(queue_isEmpty(this)){
        // pop fail
        return 0;
    }
    size_t rear = this->rear;
    size_t index = rear == 0 ? this->maxsize : rear - 1;
    *buf = this->data[index];
    this->rear = index;
    return 1;
}

int queue_getLeft(Queue const * const this, size_t index, Elem *buf){
    // get elem from left 
    // index from 0 to (rear - front -1) % maxsize
    size_t get_index = (this->front + index) % (this->maxsize + 1);
    if(get_index >= this->rear){
        // get fail
        return 0;
    }
    *buf = this->data[get_index];
    return 1;
}

int queue_getRight(Queue const * const this, size_t index, Elem *buf){
    // get elem from right
    // index from 0 to (q->rear - q->front -1) % q->maxsize
    size_t rear = this->rear;
    size_t get_index = rear - index == 0 ? this->maxsize : rear - index - 1;
    if(get_index < this->front){
        //get fail
        return 0;
    }
    *buf = this->data[get_index];
    return 1;
}

void queue_display(Queue const * const this){
    if(queue_isEmpty(this)){
        printf("The queue is empty");
        return ;
    }
    printf("Left -> "); 
    size_t rear = this->rear, mod = this->maxsize + 1;
    for(size_t i = this->front; i != rear; i = (i + 1) % mod){
        // printf int
        printf("%ld -> ", this->data[i].num_int64);
    }
    printf("Right\n");
}

void queue_delete(Queue * this){
    free(this->data);
    free(this);
}


//QueueT const queueT = {
//        newQueue,
//        isEmptyQueue,
//        isFullQueue,
//        appendLeftQueue,
//        appendRightQueue,
//        popLeftQueue,
//        popRightQueue,
//        getLeftQueue,
//        getRightQueue,
//        displayQueue,
//        deleteQueue
//};
