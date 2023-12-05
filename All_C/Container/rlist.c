#include<stdio.h>

#include "../include/rlist.h"

__malloc RList *rlist_new(size_t const maxsize){
    RList *rlist = (RList*)malloc(sizeof(RList));
    rlist->maxsize = maxsize;
    rlist->data = (Elem*)calloc(maxsize, sizeof(Elem));
    rlist->front = rlist->rear = 0;
    return rlist;
}

__malloc RList *rlist_transFromList(List *list){
    /* transform a list to a rlist */
    /* the list will be free */
    RList *rlist = (RList*)malloc(sizeof(RList));
    rlist->size = list->index;
    rlist->front = 0;
    rlist->rear = list->index;
    rlist->maxsize = list->maxsize;
    rlist->data = list->data;

    free(list);
    return rlist;
}

int rlist_appendList(RList * const this, List const*const list){
    /* init a rlist from a list, shallow copy the data from list into this */
    /* the list will not be free */
    if(unlikely(list_size(list) > rlist_freeSize(this))){
        /* init fail */
        return -1;
    }
    Elem *data = this->data, *source = list->data;
    size_t index = list->index, rear = this->rear, maxsize = this->maxsize;
    for(int i = 0; i < index; i++){
        data[(rear + i + 1) % maxsize] = source[i];
    }
    this->rear = (rear + index) % maxsize;
    this->size += index;
    return 0;
}

int rlist_appendLeft(RList * const this, Elem const elem){
    if(unlikely(rlist_isFull(this))){
        // append fail
        return 0;
    }
    size_t maxsize = this->maxsize;
    size_t index = (this->front + maxsize - 1) % maxsize;
    this->data[index] = elem;
    this->front = index;
    this->size++;
    return 1;
}

int rlist_appendRight(RList * const this, Elem const elem){
    if(unlikely(rlist_isFull(this))){
        // append fail
        return 0;
    }
    
    this->data[this->rear] = elem;
    this->rear = (this->rear + 1) % (this->maxsize);
    this->size++;
    return 1;
}

int rlist_popLeft(RList * const this, Elem *const buf){
    if(unlikely(rlist_isEmpty(this))){
        // pop fail
        return 0;
    }
    *buf = this->data[this->front];
    this->front = (this->front + 1) % (this->maxsize);
    this->size--;
    return 1;
}

int rlist_popRight(RList *const this, Elem *const buf){
    if(unlikely(rlist_isEmpty(this))){
        // pop fail
        return 0;
    }
    size_t maxsize = this->maxsize;
    size_t index = (this->rear + maxsize - 1) % maxsize;
    *buf = this->data[index];
    this->rear = index;
    this->size--;
    return 1;
}

int rlist_get(RList const * const this, Elem *const buf, size_t const index, int const reversed){
    size_t size = this->size;
    if(unlikely(index > size)){
        // get fail
        return 0;
    }
    size_t get_index = (size + (reversed ? -index : index)) % size;
    get_index = (this->front + get_index) % this->maxsize;
    *buf = this->data[get_index];
    return 1;
}

//int rlist_getLeft(RList const * const this, size_t index, Elem *buf){
//    // get elem from left
//    // index from 0 to (rear - front -1) % maxsize
//    size_t get_index = (this->front + index) % (this->maxsize);
//    if(get_index >= this->rear){
//        // get fail
//        return 0;
//    }
//    *buf = this->data[get_index];
//    return 1;
//}
//
//int rlist_getRight(RList const * const this, size_t index, Elem *buf){
//    // get elem from right
//    // index from 0 to (q->rear - q->front -1) % q->maxsize
//    size_t maxsize = this->maxsize;
//    size_t get_index = (this->rear + maxsize - index - 1) % maxsize;
//    if(get_index < this->front){
//        //get fail
//        return 0;
//    }
//    *buf = this->data[get_index];
//    return 1;
//}

void rlist_display(RList const * const this){
    if(unlikely(rlist_isEmpty(this))){
        printf("The rlist is empty");
        return ;
    }
    printf("Left -> ");
    size_t size = this->size;
    for(size_t i = 0; i < size; i++){
        // printf long
        printf("%ld -> ", this->data[(this->front + i) % this->maxsize].num_int64);
    }
    printf("Right\n");
}

void rlist_delete(RList * this){
    free(this->data);
    free(this);
}

//int rlist_link(RList *this, RList *other){
//    /* link other after this */
//    if(this->rear < this->front){
//        /* the right end of this is filled */
//        return -1;
//    }
//
//    if(rlist_size(this) + rlist_size(other) > this->maxsize){
//        this->data = realloc(
//                this->data,
//                sizeof(Elem) * (this->maxsize + other->maxsize + 1)
//        );
//        this->maxsize += other->maxsize;
//    }
//
//    Elem *data = this->data, *other_data = other->data;
//    size_t maxsize = this->maxsize, other_maxsize = other->maxsize;
//
//    size_t rear = this->rear;
//    size_t cur = other->front;
//    size_t other_rear = other->rear;
//    while(cur != other_rear){
//        data[rear] = other_data[cur];
//        rear = (rear + 1) % (maxsize + 1);
//        cur = (cur + 1) % (other_maxsize + 1);
//    }
//    this->rear = rear;
//    return 0;
//}
