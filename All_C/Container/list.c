/* Created by skf on 23-12-6. */

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../include/list.h"


__malloc List *const list_new(size_t const length){
    List *new = (List *)malloc(sizeof(List));
    if(unlikely(new == NULL)){
        /* malloc fail */
        return NULL;
    }
    Elem *data = (Elem *)calloc(length, sizeof(Elem));
    if(unlikely(data == NULL)){
        /* malloc fail */
        return NULL;
    }
    memset(data, 0, length * sizeof(Elem));
    new->data = data;
    new->length = length;
    new->step = 1;
    new->pre = NULL;
    new->next = NULL;
    return new;
}

void list_delete(List * this){
    if(this == NULL){
        return;
    }
    if(this->pre != NULL){
        /* printf("free view\n"); */
        List *next = this->next;
        this->pre->next = next;
        if(next != NULL){
            next->pre = this->pre;
        }
        free(this);
        return;
    }

    List* next = this->next;
    while(next != NULL){
        List* tmp = next->next;
        free(next);
        next = tmp;
    }
    /* printf("free list\n"); */
    free(this->data);
    free(this);
}

void list_raii(List **this){
//    printf("list_raii\n");
    list_delete(*this);
    *this = NULL;
}

int list_set(List *const this, size_t const index, Elem const elem){
    /* set this->data[index] = elem */
    /* return 0 if success, -1 if fail */
    if(unlikely(index >= this->length)){
        /* index out of range */
        return -1;
    }
    Elem *data = this->data + index * this->step;
    *data = elem;
    return 0;
}

int list_get(List const*const this, size_t const index, Elem *const buf){
    /* get this->data[index] */
    /* return 0 if success, -1 if fail */
    if(unlikely(index >= this->length)){
        /* index out of range */
        return -1;
    }
    Elem *data = this->data + index * this->step;
    *buf = *data;
    return 0;
}

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

int list_write(List *const this, ListSlice const slice, Elem *const array, size_t const length){
    /* write list to this->data[start:end] */
    /* return 0 if success, -1 if fail */

    /* normalize slice */
    size_t len = slice_normalize((ListSlice *const)&slice, this->length);
    if(len == 0){
        /* slice error */
        return -1;
    }
    if(len > length){
        /* array is too small */
        return -2;
    }
    size_t start = slice.start * this->step;
    long step = slice.step * this->step;
    for(size_t i = 0, index = start; i < len; i++){
        this->data[index] = array[i];
        index += step;
    }
    return 0;
}

List* list_view(List *const this, ListSlice slice){
    /* view this->data[start:end] */
    /* return NULL if fail */
    size_t len = slice_normalize((ListSlice *const)&slice, this->length);
    if(len == 0){
        /* slice error */
        return NULL;
    }
    List *new = (List *)malloc(sizeof(List));
    if(new == NULL){
        /* malloc fail */
        return NULL;
    }
    new->data = this->data + slice.start * this->step;
    new->length = len;
    new->step = slice.step * this->step;

    this->next = new;
    new->pre = this;
    new->next = NULL;
    return new;

}

void list_display(List const*const this){
    /* display this list */
    if(this == NULL){
        printf("List: NULL\n\n");
        return;
    }
    size_t length = this->length;
    long step = this->step;
    Elem *data = this->data;
    printf("List: len: %lu\n", length);
    for(size_t i = 0; i < length; i++, data += step){
        printf("%ld ", (*data).num_int64);
    }
    printf("\n\n");
}
