/* Created by skf on 23-12-1. */
#include <stdio.h>
#include <stdlib.h>

#include "../include/heap.h"

#define HEAP_DEBUG 0

#define HEAP_ROOT 1
#define HEAP_FREE 0

__receive __malloc Heap*const
heap_new(size_t mem_num, size_t mem_size, Heap_cmp cmp, Heap_display display){
    if(cmp == NULL){
        return NULL;
    }

    Heap *this = (Heap *)malloc(sizeof(Heap));
    if(this == NULL){
        return NULL;
    }
    /* The first node is 1 */
    Block *data = block_new(mem_num + 1, mem_size);
    if(data == NULL){
        free(this);
        return NULL;
    }
    this->data = data;
    this->size = 0;
    this->maxsize = mem_num;
    this->cmp = cmp;
    this->display = display;
    return this;
}

void heap_heapifyFrom(Heap * const this, size_t start){
    /* heapify the heap from start */
    Block *const list = this->data;
    size_t const end = heap_LAST(this);
    Heap_cmp cmp = this->cmp;

    size_t node = start;
    void* key = block_getPtr(list, node); /* *key will be cover */
    auto_ptr(Monad) buf = monad_new(list->mem_size, key);
    while(1){
        size_t index = node;

        /* use cmv instead if */
        /* get the max between key, left and right */
        size_t l = heap_LEFT(node) <= end ? heap_LEFT(node) : node;
        size_t r = heap_RIGHT(node) <= end ? heap_RIGHT(node) : node;

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
    /* heapify the heap */
    long end = HEAP_ROOT;
    for(long i = heap_LAST_PARENT(this); i >= end; i--){
        heap_heapifyFrom(this, i);
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

    Block* const list = this->data;
    Heap_display display = this->display;
    printf("Heap: ");
    size_t end = heap_LAST(this);
    for (size_t i = HEAP_ROOT; i <= end; ++i) {
        display(block_getPtr(list, i));
        printf(" ");
    }
    printf("\n");
}

int heap_init(Heap * const this, void * const list, size_t length){
    if(length > this->maxsize){
        return -1;
    }

    block_write(this->data, HEAP_ROOT, length, list);
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
    Monad *top = monad_new(this->data->mem_size, block_getPtr(this->data, HEAP_ROOT));
    return top;
}

Monad *heap_pop(Heap * const this){
    if(unlikely(heap_isEmpty(this))){
        raise_error("Heap is empty", __FILE__, __func__, __LINE__);
    }

    Block * const list = this->data;

    /* get the top element */
    Monad *result = monad_new(list->mem_size, block_getPtr(list, HEAP_ROOT));

    /* move the last element to the top */
    block_write(list, HEAP_ROOT, 1, block_getPtr(list, heap_LAST(this)));
    this->size --;

    /* heapify the heap */
    heap_heapifyFrom(this, HEAP_ROOT);
    return result;
}

void heap_float(Heap *const this, size_t index){
    /* float from index to the top */
    /* the element should be at HEAP_FREE */
    Block * const list = this->data;
    Heap_cmp cmp = this->cmp;

    size_t i = index, parent = heap_PARENT(index);
    while(index > HEAP_ROOT && cmp(this->data, parent, HEAP_FREE) < 0){
        /* from bottom to top, time complexity O(lg(n)) */
        block_write(list, i, 1, block_getPtr(list, parent));
        i = parent;
        parent = heap_PARENT(i);
    }
    block_write(list, i, 1, block_getPtr(list, HEAP_FREE));
}

int heap_append(Heap * const this, Monad const*const key){
    /* Insert an element into the heap */

    if(unlikely(heap_isFull(this))){
        return -1;
    }
    this->size++;

    Block * const list = this->data;
    /* write it to the free space */
    block_set(list, HEAP_FREE, key);

    /* float it to the top */
    heap_float(this, heap_LAST(this));
    return 0;
}

int heap_increase(Heap * const this, size_t index, Monad const*const key){
    /* index from 1 to size */
    /* increase the index element to key */

    /* similar with heap_insert */
    if(index >= this->size){
        return 0;
    }
    Block * const list = this->data;
    block_set(list, HEAP_FREE, key);

    /* float it to the top */
    heap_float(this, index);
    return 1;
}
