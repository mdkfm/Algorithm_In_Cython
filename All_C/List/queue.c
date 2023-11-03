#include<stdio.h>
#include<malloc.h>

/* gcc ./All_C/List/queue.c -fPIC -shared -o ./lib/libqueue.so */

typedef long int QElem;

// use the SqList to realize a simple and effective deque with fixed length

typedef struct{
   QElem *data;
   int dtype;
   int front, rear;
   int maxsize;
} Queue;



Queue *newQueue(int maxsize){
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->maxsize = maxsize;
    queue->data = (QElem*)malloc(maxsize * sizeof(QElem));
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
        return NULL;
    }
    q->front = (q->front - 1) % q->maxsize;
    q->data[q->front] = elem;
    return 1;
}

int appendRight(Queue *q, QElem elem){
    if(isFull(q)){
        // append fail
        return NULL;
    }
    
    q->data[q->rear] = elem;
    q->rear = (q->rear + 1) % q->maxsize;
    return 1;
}

QElem popLeft(Queue *q){
    if(isEmpty(q)){
        // pop fail
        return NULL;
    }
    long output = q->data[q->front];
    q->front = (q->front + 1) % q->maxsize;
    return output;
}

QElem popRight(Queue *q){
    if(isEmpty(q)){
        // pop fail
        return NULL;
    }
    q->rear = (q->rear - 1) % q->maxsize;
    return q->data[q->rear];
}

QElem getLeft(Queue *q, int index){
    // get elem from left 
    // index from 0 to (q->rear - q->front -1) % q->maxsize
    int get_index = (q->front + index) % q->maxsize;
    if(index < 0 || get_index >= q->rear){
        // get fail
        return NULL;
    }
    return q->data[get_index];
}

QElem getRight(Queue *q, int index){
    // get elem from right
    // index from 0 to (q->rear - q->front -1) % q->maxsize
    int get_index = (q->rear - index - 1) % q->maxsize;
    if(index < 0 || get_index < q->front){
        //get fail
        return NULL;
    }
    return q->data[get_index];
}

void displayQueue(Queue *q){
    if(isEmpty(q)){
        printf("The queue is empty");
        return ;
    }
    printf("Left -> ");
    int i, num = (q->rear - q->front) % q->maxsize;
    for(i = 0; i < num; i++){
        // printf int
        printf("%ld -> ", q->data[q->front + i]);
    }
    printf("Right\n");
}

void destoryQueue(Queue *q){
    free(q->data);
    free(q);
}


// void main(){
//     Queue *q = newQueue(10), *p = newQueue(10);
//     appendLeft(q, 1);
//     appendLeft(q, 2);
//     appendLeft(q, 10);
//     appendRight(q, 3);
//     appendLeft(p, popLeft(q));
//     appendLeft(p, popRight(q));
//     displayQueue(q);
//     displayQueue(p);
// }