//
// Created by skf on 23-12-11.
//
#ifndef CSTL_LISTGEN_H
#define CSTL_LISTGEN_H
#include <stdlib.h>
#include <stdio.h>
#include "gen.h"
#define listGen(Elem) \
typedef struct List_##Elem{ \
    Elem *data; \
    size_t length; \
\
    /* read mode */ \
    long step; \
\
    /* view chain */ \
    struct List_##Elem *pre; \
    struct List_##Elem *next; \
} List_##Elem;        \
typedef List_##Elem* const List_##Elem##_class_ptr; \
\
__malloc List_##Elem *const _list_##Elem##_new(size_t const length){ \
    List_##Elem *new = (List_##Elem *)malloc(sizeof(List_##Elem)); \
    if(unlikely(new == NULL)){ \
        /* malloc fail */ \
        return NULL; \
    } \
    Elem *data = (Elem *)calloc(length, sizeof(Elem)); \
    if(unlikely(data == NULL)){ \
        /* malloc fail */ \
        return NULL; \
    } \
    new->data = data; \
    new->length = length; \
    new->step = 1; \
    new->pre = NULL; \
    new->next = NULL; \
    \
    return new; \
} \
\
void _list_##Elem##_delete(List_##Elem * this){ \
    if(this == NULL){ \
        return; \
    } \
    if(this->pre != NULL){ \
        /* printf("free view\n"); */ \
        List_##Elem *next = this->next; \
        this->pre->next = next; \
        if(next != NULL){ \
            next->pre = this->pre; \
        } \
        free(this); \
        return; \
    } \
    \
    List_##Elem* next = this->next; \
    while(next != NULL){ \
        List_##Elem* tmp = next->next; \
        free(next); \
        next = tmp; \
    } \
    /* printf("free list\n"); */ \
    free(this->data); \
    free(this); \
} \
\
void _List_##Elem##_raii(List_##Elem##_class_ptr * this){ \
    /* printf("list raii\n"); */ \
    _list_##Elem##_delete(*this); \
}\
\
int _list_##Elem##_set(List_##Elem *const this, size_t const index, Elem const elem){\
    /* set this->data[index] = elem */\
    /* return 0 if success, -1 if fail */\
    if(unlikely(index >= this->length)){\
        /* index out of range */\
        return -1;\
    }\
    Elem *data = this->data + index * this->step;\
    *data = elem;\
    return 0;\
}\
\
int _list_##Elem##_get(List_##Elem const*const this, size_t const index, Elem *const buf){\
    /* get this->data[index] */\
    /* return 0 if success, -1 if fail */\
    if(unlikely(index >= this->length)){\
        /* index out of range */\
        return -1;\
    }\
    Elem *data = this->data + index * this->step;\
    *buf = *data;\
    return 0;\
}\
\
int _list_##Elem##_write(List_##Elem *const this, ListSlice const slice, Elem *const array, size_t const length){\
    /* write list to this->data[start:end] */\
    /* return 0 if success, -1 if fail */\
\
    /* normalize slice */\
    size_t len = slice_normalize((ListSlice *const)&slice, this->length);\
    if(len == 0){\
        /* slice error */\
        return -1;\
    }\
    if(len > length){\
        /* array is too small */\
        return -2;\
    }\
    size_t start = slice.start * this->step;\
    long step = slice.step * this->step;\
    for(size_t i = 0, index = start; i < len; i++){\
        this->data[index] = array[i];\
        index += step;\
    }\
    return 0;\
}\
\
List_##Elem* _list_##Elem##_view(List_##Elem *const this, ListSlice slice){\
    /* view this->data[start:end] */\
    /* return NULL if fail */\
    size_t len = slice_normalize((ListSlice *const)&slice, this->length);\
    if(len == 0){\
        /* slice error */\
        return NULL;\
    }\
    List_##Elem *new = (List_##Elem *)malloc(sizeof(List_##Elem));\
    if(new == NULL){\
        /* malloc fail */\
        return NULL;\
    }\
    new->data = this->data + slice.start * this->step;\
    new->length = len;\
    new->step = slice.step * this->step;\
\
    this->next = new;\
    new->pre = this;\
    new->next = NULL;\
    return new;\
\
}\
\
void _list_##Elem##_display(List_##Elem const*const this){\
    /* display this list */\
    if(this == NULL){\
        printf("List: NULL\n\n");\
        return;\
    }\
    size_t length = this->length;\
    long step = this->step;\
    Elem *data = this->data;\
    printf("List: len: %lu\n", length);\
    for(size_t i = 0; i < length; i++, data += step){\
        printf("%ld ", (long)(*data));\
    }\
    printf("\n\n");\
}\
\
typedef struct List_##Elem##_Table{\
    List_##Elem * const (*new)(const size_t);\
    void (*delete)(List_##Elem * this);\
    int (*set)(List_##Elem *const this, size_t const index, Elem const elem);\
    int (*get)(List_##Elem const*const this, size_t const index, Elem *const buf);\
    int (*write)(List_##Elem *const this, ListSlice const slice, Elem *const array, size_t const length);\
    List_##Elem* (*view)(List_##Elem *const this, ListSlice slice); \
    void (*display)(List_##Elem const*const this);\
}List_##Elem##_Table;\
\
List_##Elem##_Table _list_##Elem##_table = {\
    .new = _list_##Elem##_new,\
    .delete = _list_##Elem##_delete,\
    .set = _list_##Elem##_set, \
    .get = _list_##Elem##_get,\
    .write = _list_##Elem##_write,\
    .view = _list_##Elem##_view,\
    .display = _list_##Elem##_display\
};\

#define List(Elem) List_##Elem
#define listT(Elem) _list_##Elem##_table


typedef struct ListSlice{
    size_t start;
    size_t end;
    int step;
} ListSlice;

static inline size_t slice_normalize(ListSlice *const slice, size_t const bound){
    size_t start = slice->start, end = slice->end;
    long step = slice->step;

    if(unlikely(step == 0)){
        /* step can not be 0 */
        return 0;
    }
    if(unlikely(start == 0 && end == 0)){
        /* default slice */
        slice->start = step < 0 ? bound - 1 : 0;
        slice->end = step < 0 ? -1 : bound;
        step = step < 0 ? -step : step;
        return (bound - 1)/ step + 1;
    }
    if(unlikely(end > bound || start > bound)){
        /* index error */
        return 0;
    }
    if(unlikely((step < 0) ^ (start > end))){
        /* direct error */
        return 0;
    }
    end = step < 0 ? end + 1 : end - 1;
    size_t len = (end - start) / step + 1;
    slice->end = start + len * step;
    return len;
}

#endif //CSTL_LISTGEN_H