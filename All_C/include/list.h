//
// Created by skf on 23-12-5.
//

#ifndef ALL_C_LIST_H
#define ALL_C_LIST_H
#include "data.h"
#include "gnuc.h"

typedef struct List{
    size_t maxsize;
    size_t index;
    Elem *data;
} List;

__malloc List *list_new(size_t const maxsize);
void list_delete(List * this);
int list_init(List *const this, Elem const *const data, size_t const length);

/* $Begin static inline */
static inline int list_isFull(List const *const this) {
    /* if the num of elem is maxsize, full */
    return this->index == this->maxsize;
}

static inline int list_isEmpty(List const *const this) {
    /* no elem, empty */
    return this->index == 0;
}

static inline size_t list_size(List const *const this) {
    return this->index;
}

static inline size_t list_freeSize(List const *const this) {
    return this->maxsize - this->index;
}
/* $End static inline */

int list_get(List const *const this, Elem *const buf, size_t const index, int const reversed);
int list_append(List *const this, Elem const elem);
int list_pop(List *const this, Elem *const buf);

#endif //ALL_C_LIST_H
