#include<malloc.h>
#include "data.h"

#ifndef ALL_C_QUEUE_H
#define ALL_C_QUEUE_H
typedef struct{
    Elem *data;
    size_t front, rear;
    size_t maxsize;
} Queue;

Queue *queue_new(size_t const maxsize);
int queue_isEmpty(Queue const *this);
int queue_isFull(Queue const *this);
int queue_appendLeft(Queue *this, Elem elem);
int queue_appendRight(Queue *this, Elem elem);
int queue_popLeft(Queue *this, Elem *buf);
int queue_popRight(Queue *this, Elem *buf);
int queue_getLeft(Queue const * const this, size_t index, Elem *buf);
int queue_getRight(Queue const * const this, size_t index, Elem *buf);
void queue_display(Queue const * const this);
void queue_delete(Queue * this);

//typedef struct{
//    Queue* (*new)(size_t maxsize);
//    int (*isEmpty)(Queue const * const this);
//    int (*isFull)(Queue const * const this);
//    int (*appendLeft)(Queue * const this, Elem elem);
//    int (*appendRight)(Queue * const this, Elem elem);
//    int (*popLeft)(Queue * const this, Elem *buf);
//    int (*popRight)(Queue * const this, Elem *buf);
//    int (*getLeft)(Queue const * const this, size_t index, Elem *buf);
//    int (*getRight)(Queue const  * const this, size_t index, Elem *buf);
//    void (*display)(Queue const * const this);
//    void (*delete)(Queue * this);
//} QueueT;
//
//extern QueueT const queueT;
#endif