#include "../include/queue.h"

void main(){
    Queue *queue = queue_new(10);
    queue_appendLeft(queue, (Elem)(long)1);
    queue_appendLeft(queue, (Elem)(long)2);
    queue_display(queue);
}