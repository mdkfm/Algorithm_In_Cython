/* Created by skf on 23-12-1. */
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include "../include/data.h"
#include "../include/heap.h"
#include "../include/error.h"

#define HEAP_DEBUG 0


__receive __malloc Heap*const heap_new(size_t const maxsize, int (*cmp)(Elem const, Elem const)){
    if(cmp == NULL){
        return NULL;
    }

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

static inline size_t heap_PARENT(size_t const i){
    return ((i) - 1) >> 1;
}

static inline size_t heap_LEFT(size_t const i){
    return ((i) << 1) + 1;
}

static inline size_t heap_RIGHT(size_t const i){
    return ((i) << 1) + 2;
}

void heap_heapifyFrom(Heap * const this, size_t const start){
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

        int cond1 = cmp(left, max) > 0;
        index = cond1 ? l : index;
        max = cond1 ? left : max;

        int cond2 = cmp(right, max) > 0;
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

void heap_heapify(Heap * const this){
    size_t length = this->size;
    for(size_t i = length / 2 - 1; ; i--){
        heap_heapifyFrom(this, i);
        if(unlikely(i == 0)) break;
#if HEAP_DEBUG
        heap_display(this);
#endif
    }
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

int heap_initFromList(Heap * const this, Elem * const list, size_t const length){
    if(length > this->maxsize){
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        this->data[i] = list[i];
    }
    this->size = length;

    heap_heapify(this);
    return 0;
}

int heap_initFromStart(Heap * const this, void * const start, size_t const size, size_t const mem_num){
    /* write a lot of increasing ptr into heap */
    /* start: the start value */
    /* size: the size of each element */
    /* mem_num: the number of elements */
    if(mem_num > this->maxsize){
        return -1;
    }

    Elem *data = this->data;
    void *p = start; /* GNU C support void ptr calculation */
    for(size_t i = 0; i < mem_num; i++, data++, p += size){
        *data = (Elem){.ptr= p};
    }
    this->size = mem_num;

    heap_heapify(this);
    return 0;
}

void heap_delete(Heap * const this){
    free(this->data);
    free(this);
}

void Heap_raii(Heap_class_ptr *ptr){
    heap_delete(*ptr);
}

Elem heap_top(Heap const * const this){
    if(unlikely(heap_isEmpty(this))){
        raise_error("Heap is empty");
    }
    return this->data[0];
}

Elem heap_pop(Heap * const this){
    if(unlikely(heap_isEmpty(this))){
        raise_error("Heap is empty");
    }

    Elem * const list = this->data;
    size_t length = this->size;

    Elem result = list[0]; /* get the top element */

    /* move the last element to the top
     * and heapify the heap */
    list[0] = list[length - 1];
    this->size --;
    heap_heapifyFrom(this, 0);

    return result;
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