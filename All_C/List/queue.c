#include<stdio.h>
#include<malloc.h>

/* gcc ./All_C/List/queue.c -fPIC -shared -o ./lib/libqueue.so */

typedef long int QElem;

// use the SqList to realize a simple and effective deque with fixed length

typedef struct{
   QElem *data;
   size_t front, rear;
   size_t maxsize;
} Queue;



Queue *newQueue(size_t maxsize){
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->maxsize = maxsize;
    queue->data = (QElem*)calloc(maxsize, sizeof(QElem));
    queue->front = queue->rear = 0;
    return queue;
}


int isEmpty(Queue *q){
    /* no elem, empty */
    return q->front == q->rear;
}

int isFull(Queue *q){
    // if the num of elem is maxsize - 1, full
    return (q->rear + 1) % q->maxsize == q->front;
}

int appendLeft(Queue *q, QElem elem){
    if(isFull(q)){
        // append fail
        return 0;
    }
    q->front = (q->front - 1) % q->maxsize;
    q->data[q->front] = elem;
    return 1;
}

int appendRight(Queue *q, QElem elem){
    if(isFull(q)){
        // append fail
        return 0;
    }
    
    q->data[q->rear] = elem;
    q->rear = (q->rear + 1) % q->maxsize;
    return 1;
}

int popLeft(Queue *q, QElem *buf){
    if(isEmpty(q)){
        // pop fail
        return 0;
    }
    *buf = q->data[q->front];
    q->front = (q->front + 1) % q->maxsize;
    return 1;
}

int popRight(Queue *q, QElem *buf){
    if(isEmpty(q)){
        // pop fail
        return 0;
    }
    q->rear = (q->rear - 1) % q->maxsize;
    *buf = q->data[q->rear];
    return 1;
}

int getLeft(Queue *q, size_t index, QElem *buf){
    // get elem from left 
    // index from 0 to (q->rear - q->front -1) % q->maxsize
    size_t get_index = (q->front + index) % q->maxsize;
    if(get_index >= q->rear){
        // get fail
        return 0;
    }
    *buf = q->data[get_index];
    return 1;
}

int getRight(Queue *q, size_t index, QElem *buf){
    // get elem from right
    // index from 0 to (q->rear - q->front -1) % q->maxsize
    size_t get_index = (q->rear - index - 1) % q->maxsize;
    if(get_index < q->front){
        //get fail
        return 0;
    }
    *buf = q->data[get_index];
    return 1;
}

void displayQueue(Queue *this){
    if(isEmpty(this)){
        printf("The queue is empty");
        return ;
    }
    printf("Left -> "); 
    size_t num = (this->rear - this->front) % this->maxsize;
    size_t cur = this->front, mod = this->maxsize;
    for(size_t i = 0; i < num; i++){
        // printf int
        printf("%ld -> ", this->data[(cur + i) % mod]);
    }
    printf("Right\n");
}

void destoryQueue(Queue *q){
    free(q->data);
    free(q);
}


int main(){
    Queue *q = newQueue(10), *p = newQueue(10);
    QElem x = 0;
    QElem *buf = &x;
    appendLeft(q, 1);
    appendLeft(q, 2);
    appendLeft(q, 10);
    appendRight(q, 3);
    popLeft(q, buf);
    appendLeft(p, *buf);
    popRight(q, buf);
    appendLeft(p, *buf);
    displayQueue(q);
    displayQueue(p);
    return 0;
}