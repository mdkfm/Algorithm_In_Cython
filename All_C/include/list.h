//
// Created by skf on 23-12-10.
//

#ifndef ALL_C_LIST_H
#define ALL_C_LIST_H
#include "../include/data.h"
#include "../include/gnuc.h"

typedef struct List{
    Elem *data;
    size_t length;

    /* read mode */
    long step;

    /* view chain */
    struct List *pre;
    struct List *next;
} List;

typedef List * const List_class_ptr;

typedef struct ListSlice{
    size_t start;
    size_t end;
    int step;
} ListSlice;

__used __malloc List *const list_new(size_t const length);
void list_delete(List * this);

void list_set(List *const this, size_t const index, Elem const elem);
Elem list_get(List const*const this, size_t const index);
int list_write(List *const this, ListSlice const slice, Elem *const array, size_t const length);
List* list_view(List *const this, ListSlice slice);
void list_display(List const*const this);

/* static inline */
static inline void List_raii(List_class_ptr *this){
    list_delete(*this);
}

#endif //ALL_C_LIST_H
