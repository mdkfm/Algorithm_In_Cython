#ifndef ALL_C_RList_H
#define ALL_C_RList_H

#include<malloc.h>
#include "data.h"
#include "list.h"
#include "gnuc.h"

typedef struct{
    size_t front, rear;
    size_t maxsize;
    size_t size;
    Elem *data;
} RList;

__malloc RList *rlist_new(size_t const maxsize);

__malloc RList *rlist_transFromList(List *list);

int rlist_appendList(RList * const this, List const*const list);

/* $Begin static inline */
static inline int rlist_isEmpty(RList const * const this){
    /* no elem, empty */
    return this->size == 0;
}

static inline int rlist_isFull(RList const * const this){
    // if the num of elem is maxsize, full
    return this->size == this->maxsize;
}

static inline size_t rlist_size(RList const * const this){
    return this->size;
}

static inline size_t rlist_freeSize(RList const * const this){
    return this->maxsize - this->size;
}
/* $End static inline */

int rlist_appendLeft(RList *const this, Elem const elem);
int rlist_appendRight(RList *const this, Elem const elem);
int rlist_popLeft(RList *const this, Elem *const buf);
int rlist_popRight(RList *const this, Elem *const buf);

int rlist_get(RList const * const this, Elem *const buf, size_t const index, int const reversed);
//int rlist_getLeft(RList const * const this, size_t index, Elem *buf);
//int rlist_getRight(RList const * const this, size_t index, Elem *buf);

void rlist_display(RList const * const this);
void rlist_delete(RList * this);
//int rlist_link(RList *this, RList *other);

#endif