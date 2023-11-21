#include<malloc.h>
#include "data.h"

// use the SqList to realize a simple and effective deque with fixed length

typedef struct{
    Elem *data;
    size_t front, rear;
    size_t maxsize;
} Queue;



Queue *newQueue(size_t maxsize);

int isEmpty(Queue const *this);

int isFull(Queue const *this);

int appendLeft(Queue *this, Elem elem);

int appendRight(Queue *this, Elem elem);

int popLeft(Queue *this, Elem *buf);

int popRight(Queue *this, Elem *buf);

int getLeft(Queue *this, size_t index, Elem *buf);

int getRight(Queue *this, size_t index, Elem *buf);

void displayQueue(Queue *this);

void deleteQueue(Queue *this);