#include<stdio.h>
#include<malloc.h>

/* gcc LinkList.c -fPIC -shared -o libLinkList.so */

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
    q->data[--q->front] = elem;
    return 1;
}

int appendRight(Queue *q, QElem elem){
    if(isFull(q)){
        // append fail
        return NULL;
    }
    q->data[q->rear++] = elem;
    return 1;
}

QElem popLeft(Queue *q){
    if(isEmpty(q)){
        // pop fail
        return NULL;
    }
    return q->data[q->front++];
}

QElem popRight(Queue *q){
    if(isEmpty(q)){
        // pop fail
        return NULL;
    }
    return q->data[--q->rear];
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