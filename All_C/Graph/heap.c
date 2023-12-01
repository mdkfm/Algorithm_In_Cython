/* Created by skf on 23-12-1. */
#include <malloc.h>

#include "../include/data.h"
#include "../include/heap.h"

#define PARENT(i) ((i) - 1) >> 1
#define LEFT(i) ((i) << 1) + 1
#define RIGHT(i) ((i) << 1) + 2

#define HEAP_DEBUG 0


Heap* heap_new(long unsigned const maxsize, int (*cmp)(Elem const, Elem const)){
    Heap *this = (Heap *)malloc(sizeof(Heap));
    if(this == NULL){
        return NULL;
    }

    /* The first node is 0 */
    this->data = (Elem *)malloc(sizeof(Elem) * maxsize);
    if(this->data == NULL){
        free(this);
        return NULL;
    }
    this->size = 0;
    this->maxsize = maxsize;
    this->cmp = cmp;
    return this;
}


void heap_heapify(Heap * const this, long unsigned const start){
    Elem * const list = this->data;
    long unsigned const length = this->size;
    int (*cmp)(Elem const, Elem const) = this->cmp;

    long unsigned node = start;
    Elem key = list[start];
    while(1){
        long unsigned index = node;
        Elem max = key;

        /* use cmv instead if */
        /* get the max between key, left and right */
        long unsigned l = LEFT(node);
        l = l < length ? l : node;
        Elem left = list[l];

        long unsigned r = RIGHT(node);
        r = r < length ? r : node;
        Elem right = list[r];

        int cond1 = cmp(left, max);
        index = cond1 ? l : index;
        max = cond1 ? left : max;

        int cond2 = cmp(right, max);
        index = cond2 ? r : index;
        max = cond2 ? right : max;

        if(index == node){
            break;
        }

        /* only write */
        list[node] = max;
        node = index;
    }
    /* the last write */
    list[node] = key;
}

void heap_display(Heap const * const this);

void heap_init(Heap * const this, Elem * const list, long unsigned const length){
    for (long unsigned i = 0; i < length; ++i) {
        this->data[i] = list[i];
    }
    this->size = length;

    for(long unsigned i = length / 2 - 1; ; i--){
        heap_heapify(this, i);
        if(i == 0) break;
#if HEAP_DEBUG
        heap_display(this);
#endif
    }
}

void heap_display(Heap const * const this){
    long unsigned length = this->size;
    Elem * const list = this->data;
    for (long unsigned i = 0; i < length; ++i) {
        printf("%ld ", list[i].num_int64);
    }
    printf("\n");
}

void heap_delete(Heap * const this){
    free(this->data);
    free(this);
}

Elem heap_top(Heap const * const this){
    return this->data[0];
}

Elem heap_pop(Heap * const this){
    Elem * const list = this->data;
    long unsigned length = this->size;
    Elem top = list[0];
    list[0] = list[length - 1];
    this->size --;
    heap_heapify(this, 0);
    return top;
}

int heap_insert(Heap * const this, Elem const key){
    /* Insert an element into the heap */
    if(this->size >= this->maxsize){
        return 0;
    }
    long unsigned i = this->size;
    this->size ++;
    this->data[i] = key;

    Elem * const list = this->data;
    int (*cmp)(Elem const, Elem const) = this->cmp;

    while(i != 0 && cmp(list[PARENT(i)], key) < 0){
        /* from bottom to top, time complexity O(lg(n)) */
        long unsigned parent = PARENT(i);
        list[i] = list[parent];
        i = parent;
    }
    list[i] = key;
    return 1;
}

int heap_increase(Heap * const this, long unsigned const index, Elem const key){
    /* increase the index element to key */
    /* similar with heap_insert */
    if(index >= this->size){
        return 0;
    }
    Elem * const list = this->data;
    int (*cmp)(Elem const, Elem const) = this->cmp;
    if(cmp(list[index], key) > 0){
        return 0;
    }
    list[index] = key;
    long unsigned i = index;
    while(i != 0 && cmp(list[PARENT(i)], key) < 0){
        /* same as heap_insert */
        long unsigned parent = PARENT(i);
        list[i] = list[parent];
        i = parent;
    }
    list[i] = key;
    return 1;
}