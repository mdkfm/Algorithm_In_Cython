#include<stdio.h>
#include<malloc.h>
#include "../include/data.h"

// use the SqList to realize a simple and effective deque with fixed length

typedef struct{
   Elem *data;
   long front, rear;
   long maxsize;
} Queue;



Queue *newQueue(size_t const maxsize){
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->maxsize = maxsize;
    queue->data = (Elem*)calloc(maxsize + 1, sizeof(Elem));
    queue->front = queue->rear = 0;
    return queue;
}


int isEmpty(Queue const *this){
    /* no elem, empty */
    return this->front == this->rear;
}

int isFull(Queue const *this){
    // if the num of elem is maxsize - 1, full
    return (this->rear + 1) % (this->maxsize + 1) == this->front;
}

int appendLeft(Queue *this, Elem elem){
    if(isFull(this)){
        // append fail
        return 0;
    }
    this->front = (this->front - 1) % (this->maxsize + 1);
    this->data[this->front] = elem;
    return 1;
}

int appendRight(Queue *this, Elem elem){
    if(isFull(this)){
        // append fail
        return 0;
    }
    
    this->data[this->rear] = elem;
    this->rear = (this->rear + 1) % (this->maxsize + 1);
    return 1;
}

int popLeft(Queue *this, Elem *buf){
    if(isEmpty(this)){
        // pop fail
        return 0;
    }
    *buf = this->data[this->front];
    this->front = (this->front + 1) % (this->maxsize + 1);
    return 1;
}

int popRight(Queue *this, Elem *buf){
    if(isEmpty(this)){
        // pop fail
        return 0;
    }
    this->rear = (this->rear - 1) % (this->maxsize + 1);
    *buf = this->data[this->rear];
    return 1;
}

int getLeft(Queue *this, size_t index, Elem *buf){
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

int getRight(Queue *this, size_t index, Elem *buf){
    // get elem from right
    // index from 0 to (q->rear - q->front -1) % q->maxsize
    size_t get_index = (this->rear - index - 1) % (this->maxsize + 1);
    if(get_index < this->front){
        //get fail
        return 0;
    }
    *buf = this->data[get_index];
    return 1;
}

void displayQueue(Queue *this){
    if(isEmpty(this)){
        printf("The queue is empty");
        return ;
    }
    printf("Left -> "); 
    size_t num = (this->rear - this->front) % (this->maxsize + 1);
    size_t cur = this->front, mod = this->maxsize + 1;
    for(size_t i = 0; i < num; i++){
        // printf int
        printf("%ld -> ", this->data[(cur + i) % mod].num_int64);
    }
    printf("Right\n");
}

void deleteQueue(Queue *this){
    free(this->data);
    free(this);
}


int main(){
   Queue *q = newQueue(10), *p = newQueue(10);
   long x = 1;
   printf("%ld\n", (q->front - 1) % 10);
   appendLeft(q, (Elem) x);
   appendLeft(q, (Elem) x);
   appendLeft(q, (Elem) x);
   appendLeft(q, (Elem) x);
   printf("%u %u\n", q->front, q->rear);
   appendRight(q, (Elem) x);
   
//    popLeft(q, &x);
//    popRight(q, &x);
   displayQueue(q);
   return 0;
}