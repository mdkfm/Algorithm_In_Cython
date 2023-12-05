/* Created by skf on 23-12-5. */
#include <stdlib.h>
#include "../include/list.h"

__malloc List *list_new(size_t const maxsize) {
    List *list = (List *) malloc(sizeof(List));
    list->maxsize = maxsize;
    list->index = 0;
    list->data = (Elem *) calloc(maxsize, sizeof(Elem));
    return list;
}

void list_delete(List * this) {
    free(this->data);
    free(this);
}

int list_init(List *const this, Elem const *const data, size_t const length) {
    if(unlikely(length > this->maxsize)){
        /* init fail */
        return -1;
    }

    for(int i = 0; i < length; i++){
        this->data[i] = data[i];
    }
    return 0;
}

int list_get(List const *const this, Elem *const buf, size_t const index, int const reversed){
    size_t size = this->index;
    if (unlikely(index > size)) {
        /* index out of range */
        return -1;
    }
    size_t get_index = reversed ? size - index - 1 : index;
    *buf = this->data[get_index];
    return 0;
}

int list_append(List *const this, Elem const elem) {
    if (unlikely(list_isFull(this))) {
        /* append fail */
        return -1;
    }
    this->data[this->index] = elem;
    this->index++;
    return 0;
}

int list_pop(List *const this, Elem *const buf) {
    if (unlikely(list_isEmpty(this))) {
        /* pop fail */
        return -1;
    }
    this->index--;
    *buf = this->data[this->index];
    return 0;
}