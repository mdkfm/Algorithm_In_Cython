/* Created by skf on 23-12-1. */
#include <malloc.h>

#include "../include/data.h"
#include "../include/heap.h"

#define HEAP_DEBUG 0


__receive __malloc Heap*const heap_new(size_t const maxsize, int (*cmp)(Elem const, Elem const)){
    if(cmp == NULL){
        return NULL;
    }

    Heap *this = (Heap *)malloc(sizeof(Heap));
    if(this == NULL){
        return NULL;
    }
    if(cmp == NULL){
        free(this);
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

static inline size_t heap_PARENT(size_t const i){
    return ((i) - 1) >> 1;
}

static inline size_t heap_LEFT(size_t const i){
    return ((i) << 1) + 1;
}

static inline size_t heap_RIGHT(size_t const i){
    return ((i) << 1) + 2;
}

void heap_heapify(Heap * const this, size_t const start){
    /* heapify the heap from start */
    Elem * const list = this->data;
    size_t const length = this->size;
    int (*cmp)(Elem const, Elem const) = this->cmp;

    size_t node = start;
    Elem key = list[start];
    while(1){
        size_t index = node;
        Elem max = key;

        /* use cmv instead if */
        /* get the max between key, left and right */
        size_t l = heap_LEFT(node);
        l = l < length ? l : node;
        Elem left = list[l];

        size_t r = heap_RIGHT(node);
        r = r < length ? r : node;
        Elem right = list[r];

        int cond1 = cmp(left, max);
        index = cond1 ? l : index;
        max = cond1 ? left : max;

        int cond2 = cmp(right, max);
        index = cond2 ? r : index;
        max = cond2 ? right : max;

        if(unlikely(index == node)){
            break;
        }

        /* only write */
        list[node] = max;
        node = index;
    }
    /* the last write */
    list[node] = key;
}

void heap_display(Heap const * const this){
    if(unlikely(heap_isEmpty(this))){
        printf("Empty heap\n");
        return;
    }

    size_t length = heap_size(this);
    Elem * const list = this->data;
    for (size_t i = 0; i < length; ++i) {
        printf("%ld ", list[i].num_int64);
    }
    printf("\n");
}

int heap_init(Heap * const this, Elem * const list, size_t const length){
    if(length > this->maxsize){
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        this->data[i] = list[i];
    }
    this->size = length;

    for(size_t i = length / 2 - 1; ; i--){
        heap_heapify(this, i);
        if(unlikely(i == 0)) break;
#if HEAP_DEBUG
        heap_display(this);
#endif
    }
    return 0;
}

void heap_delete(Heap * const this){
    free(this->data);
    free(this);
}

int heap_top(Heap const * const this, Elem * const buf){
    if(unlikely(heap_isEmpty(this))){
        return -1;
    }
    *buf = this->data[0];
    return 0;
}

int heap_pop(Heap * const this, Elem * const buf){
    if(unlikely(heap_isEmpty(this))){
        return -1;
    }

    Elem * const list = this->data;
    size_t length = this->size;

    *buf = list[0]; /* get the top element */

    /* move the last element to the top
     * and heapify the heap */
    list[0] = list[length - 1];
    this->size --;
    heap_heapify(this, 0);

    return 0;
}

int heap_append(Heap * const this, Elem const key){
    /* Insert an element into the heap */
    if(unlikely(heap_isFull(this))){
        return -1;
    }
    size_t i = this->size;
    this->size ++;
    this->data[i] = key;

    Elem * const list = this->data;
    int (*cmp)(Elem const, Elem const) = this->cmp;

    while(i != 0 && cmp(list[heap_PARENT(i)], key) < 0){
        /* from bottom to top, time complexity O(lg(n)) */
        size_t parent = heap_PARENT(i);
        list[i] = list[parent];
        i = parent;
    }
    list[i] = key;
    return 0;
}

int heap_increase(Heap * const this, size_t const index, Elem const key){
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
    size_t i = index;
    while(i != 0 && cmp(list[heap_PARENT(i)], key) < 0){
        /* same as heap_insert */
        size_t parent = heap_PARENT(i);
        list[i] = list[parent];
        i = parent;
    }
    list[i] = key;
    return 1;
}