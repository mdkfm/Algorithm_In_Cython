//
// Created by skf on 24-1-7.
//

#ifndef HEAP_DType
#error No HEAP_DType defined
#else
#include <stdlib.h>

#define DType HEAP_DType
#include "../basic/template.h"
#include "../basic/gnuc.h"
#include "../basic/error.h"

#define TClass Heap

#ifndef ALL_C_HEAP_H
#define ALL_C_HEAP_H

typedef struct Heap{
    /* Complete Bi-Tree */
    size_t size;
    size_t maxsize;
    FPtr_t cmp;
    FPtr_t display;
    /* compare function, if e0 > e1 return 1, e0 == e1 return 0, e0 < e1 return -1 */
    /* this max-heap is constructed according to cmp */

    void* data;

} Heap;

DPtr(Heap);

void SF(delete)(Heap*const this) {
    free(this->data);
    free(this);
}

static inline void SF(raii)(Ptr(Heap) *this) {
    SF(delete)(*this);
}

static inline size_t SF(root)() {
    /* return the root node */
    return 1;
}

static inline size_t SF(end)(Heap const* this) {
    /* return the last node */
    return SF(root)() + this->size - 1;
}

static inline size_t SF(parent)(size_t const i) {
    return i >> 1;
}

static inline size_t SF(left)(size_t const i) {
    return i << 1;
}

static inline size_t SF(right)(size_t const i) {
    return (i << 1) + 1;
}

static inline int SF(isEmpty)(Heap const* this) {
    return this->size == 0;
}

static inline int SF(isFull)(Heap const* this) {
    return this->size == this->maxsize;
}

static inline size_t SF(freeSize)(Heap const* this) {
    return this->maxsize - this->size;
}

static inline void SF(clear)(Heap *const this) {
    this->size = 0;
}
#endif //ALL_C_HEAP_H


#define Class C(Heap)

typedef int(* F(cmp_t))(DType e0, DType e1);
typedef void(* F(display_t))(DType e);

__receive __malloc Heap*const
F(new)(size_t maxsize, F(cmp_t) cmp, F(display_t) display) {
    Heap* this = (Heap *) malloc(sizeof(Heap));

    this->cmp = (FPtr_t) (cmp == NULL ? CMP(DType) : cmp);
    if unlikely(this->cmp == NULL) {
        free(this);
        raise_error("compare function is not defined", __FILE__, __func__, __LINE__);
        return NULL;
    }

    this->data = malloc(sizeof(DType) * maxsize);
    if(this->data == NULL){
        free(this);
        return NULL;
    }

    this->display = (FPtr_t) (display == NULL ? DISPLAY(DType) : display);
    this->maxsize = maxsize;
    this->size = 0;
    return this;
}

void F(display)(Heap const* this) {
    F(display_t) display = (F(display_t)) this->display;
    if unlikely(display == NULL) {
        raise_error("display function is not defined", __FILE__, __func__, __LINE__);
    }
    if unlikely(this->size == 0) {
        printf("Empty heap\n");
        return;
    }
    printf("Heap: ");
    DType *data = (DType *) this->data;
    size_t end = SF(end)(this) + 1;
    for (size_t i = SF(root)(); i < end; i++) {
        display(data[i]);
        printf(" ");
    }
    printf("\n");
}

void F(heapifyFrom)(Heap * const this, size_t start){
    /* heapify the heap from start */
    if unlikely(start > SF(end)(this)){
        raise_error("index out of range", __FILE__, __func__, __LINE__);
    }

    DType *data = this->data;
    size_t const end = SF(end)(this);
    F(cmp_t) cmp = (F(cmp_t)) this->cmp;

    size_t node = start;
    DType key = data[start];
    while(1){
        size_t max_index = node;

        /* use cmv instead if */
        /* get the max between key, left and right */
        size_t l = SF(left)(node);
        l = l <= end ? l : node;
        size_t r = SF(left)(node);
        r = r <= end ? r : node;

        max_index = cmp(data[l], data[max_index]) > 0 ? l : max_index;
        max_index = cmp(data[r], data[max_index]) > 0 ? r : max_index;

        if(unlikely(max_index == node)){
            break;
        }

        /* only write */
        data[node] = data[max_index];
        node = max_index;
    }
    /* the last write */
    data[node] = key;
}

void F(heapify)(Heap * const this){
    /* heapify the heap */
    long end = SF(root)();
    long start = SF(parent)(SF(end)(this));
    for(long i = start; i >= end; i--){
        F(heapifyFrom)(this, i);
    }
}

int F(init)(Heap * const this, DType const* list, size_t length){
    if(length > this->maxsize){
        return -1;
    }

    DType *data = this->data;
    size_t end = SF(root)() + length;
    for(size_t i = SF(root)(); i < end; i++){
        data[i] = list[i];
    }
    this->size = length;

    F(heapify)(this);
    return 0;
}

DType F(top)(Heap const * const this){
    if unlikely(SF(isEmpty)(this)){
        raise_error("heap is empty", __FILE__, __func__, __LINE__);
    }
    DType *data = this->data;
    return data[SF(root)()];
}

DType F(pop)(Heap * this){
    if unlikely(SF(isEmpty)(this)){
        raise_error("heap is empty", __FILE__, __func__, __LINE__);
    }
    DType *data = this->data;
    size_t root = SF(root)(), end = SF(end)(this);
    DType top = data[root];
    data[root] = data[end];
    this->size--;
    F(heapifyFrom)(this, root);
    return top;
}

void F(float)(Heap * this, size_t index){
    /* float from index to the top */
    if unlikely(index > SF(end)(this)){
        raise_error("index out of range", __FILE__, __func__, __LINE__);
    }

    DType *data = this->data;
    F(cmp_t) cmp = (F(cmp_t)) this->cmp;

    DType key = data[index];
    while(1){
        size_t parent = SF(parent)(index);
        if unlikely(parent == 0){
            break;
        }
        if (cmp(data[parent], key) >= 0){
            break;
        }
        data[index] = data[parent];
        index = parent;
    }
    data[index] = key;
}

int F(push)(Heap * this, DType elem){
    if unlikely(SF(isFull)(this)){
        return -1;
    }
    size_t index = SF(end)(this) + 1;
    this->size++;
    DType *data = this->data;
    data[index] = elem;
    F(float)(this, index);
    return 0;
}

int F(increase)(Heap * this, size_t index, DType elem){
    if unlikely(index > SF(end)(this)){
        return -1;
    }
    DType *data = this->data;
    F(cmp_t) cmp = (F(cmp_t)) this->cmp;
    if(cmp(data[index], elem) >= 0){
        return -1;
    }
    data[index] = elem;
    F(float)(this, index);
    return 0;
}

typedef struct FuncT_t FuncT_t;

struct FuncT_t {
    void (*delete)(Heap *this);
    void (*clear)(Heap *const this);
    int (*isFull)(Heap const *this);
    int (*isEmpty)(Heap const *this);
    size_t (*freeSize)(Heap const *this);
    Heap*const (*new)(size_t const maxsize, F(cmp_t) cmp, F(display_t) display);
    void (*display)(Heap const *this);
    int (*init)(Heap * const this, DType const* list, size_t length);
    DType (*top)(Heap const * const this);
    DType (*pop)(Heap * this);
    int (*push)(Heap * this, DType elem);
    int (*increase)(Heap * this, size_t index, DType elem);
};

static FuncT_t FuncT = {
    .delete = SF(delete),
    .clear = SF(clear),
    .isFull = SF(isFull),
    .isEmpty = SF(isEmpty),
    .freeSize = SF(freeSize),
    .new = F(new),
    .display = F(display),
    .init = F(init),
    .top = F(top),
    .pop = F(pop),
    .push = F(push),
    .increase = F(increase),
};

#define heapT(T) classFuncT(Heap, T)

#undef Class
#undef TClass
#undef DType
#endif