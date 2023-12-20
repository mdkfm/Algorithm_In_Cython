/* Created by skf on 23-12-1. */
#include <stdio.h>
#include <stdlib.h>

#include "../include/heap.h"

#define HEAP_DEBUG 0


__receive __malloc Heap*const
heap_new(size_t const mem_num, size_t const mem_size, Heap_cmp cmp){
    if(cmp == NULL){
        return NULL;
    }

    Heap *this = (Heap *)malloc(sizeof(Heap));
    if(this == NULL){
        return NULL;
    }
    /* The first node is 0 */
    Block *data = block_new(mem_num, mem_size);
    if(data == NULL){
        free(this);
        return NULL;
    }
    this->data = data;
    this->size = 0;
    this->maxsize = mem_num;
    this->cmp = cmp;
    return this;
}

void heap_heapifyFrom(Heap * const this, size_t const start){
    /* heapify the heap from start */
    Block *const list = this->data;
    size_t const length = this->size;
    Heap_cmp cmp = this->cmp;

    size_t node = start;
    void* key = block_getPtr(list, node); /* *key will be cover */
    auto_ptr(Monad) buf = monad_new(list->mem_size, key);
    while(1){
        size_t index = node;

        /* use cmv instead if */
        /* get the max between key, left and right */
        size_t l = heap_LEFT(node) < length ? heap_LEFT(node) : node;
        size_t r = heap_RIGHT(node) < length ? heap_RIGHT(node) : node;

        index = cmp(this->data, l, index) > 0 ? l : index;
        index = cmp(this->data, r, index) > 0 ? r : index;

        if(unlikely(index == node)){
            break;
        }

        /* only write */
        block_write(list, node, 1, block_getPtr(list, index));
        node = index;
    }
    /* the last write */
    block_set(list, node, buf);
}

void heap_heapify(Heap * const this){
    size_t length = this->size;
    for(size_t i = length / 2; i > 0 ; i--){
        heap_heapifyFrom(this, i - 1);
#if HEAP_DEBUG
        heap_display(this);
#endif
    }
}

void heap_display(Heap const * const this, void (*display)(void const*const)){
    if(unlikely(heap_isEmpty(this))){
        printf("Empty heap\n");
        return;
    }

    size_t length = heap_size(this);
    Block* const list = this->data;
    printf("Heap: ");
    for (size_t i = 0; i < length; ++i) {
        display(block_getPtr(list, i));
        printf(" ");
    }
    printf("\n");
}

int heap_init(Heap * const this, void * const list, size_t const length){
    if(length > this->maxsize){
        return -1;
    }

    block_write(this->data, 0, length, list);
    this->size = length;

    heap_heapify(this);
    return 0;
}


void heap_delete(Heap * const this){
    free(this->data);
    free(this);
}


Monad *heap_top(Heap const * const this){
    if(unlikely(heap_isEmpty(this))){
        raise_error("Heap is empty", __FILE__, __func__, __LINE__);
    }
    Monad *top = monad_new(this->data->mem_size, block_getPtr(this->data, 0));
    return top;
}

Monad *heap_pop(Heap * const this){
    if(unlikely(heap_isEmpty(this))){
        raise_error("Heap is empty", __FILE__, __func__, __LINE__);
    }

    Block * const list = this->data;
    size_t length = this->size;

    /* get the top element */
    Monad *result = monad_new(list->mem_size, block_getPtr(list, 0));

    /* move the last element to the top
     * and heapify the heap*/
    block_write(list, 0, 1, block_getPtr(list, --length));
    this->size = length;
    heap_heapifyFrom(this, 0);

    return result;
}

int heap_append(Heap * const this, Monad const*const key){
    /* Insert an element into the heap */

    if(unlikely(heap_isFull(this))){
        return -1;
    }
    size_t index = this->size;
    this->size = index + 1;

    Block * const list = this->data;
    block_set(list, index, key);

    Heap_cmp cmp = this->cmp;

    size_t parent = heap_PARENT(index);
    while(index != 0 && cmp(this, parent, index) < 0){
        /* from bottom to top, time complexity O(lg(n)) */
        block_write(list, index, 1, block_getPtr(list, parent));
        index = parent;
        parent = heap_PARENT(index);
    }
    block_set(list, index, key);
    return 0;
}

int heap_increase(Heap * const this, size_t const index, Monad const*const key){
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
         same as heap_insert

        size_t parent = heap_PARENT(i);
        list[i] = list[parent];
        i = parent;
    }
    list[i] = key;
    return 1;
}
