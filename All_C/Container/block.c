//
// Created by skf on 23-12-14.
//
#include "../include/block.h"

#define CHECK_SIZE(this, that) (this->mem_size != that->mem_size)


__malloc Block *const block_new(size_t const mem_num, size_t const mem_size){
    Block *new = (Block *)malloc(sizeof(Block));

    if(unlikely(new == NULL)){
        /* malloc fail */
        raise_error("block_new: malloc fail", __FILE__, __func__, __LINE__)
    }
    void *data = calloc(mem_num, mem_size);
    if(unlikely(data == NULL)){
        /* malloc fail */
        free(new);
        raise_error("block_new: malloc fail", __FILE__, __func__, __LINE__)
    }

    new->data = data;
    new->mem_num = mem_num;
    new->mem_size = mem_size;
    new->shared_num = 1;
    return new;
}

void block_delete(Block * this){
    if(this == NULL || --this->shared_num > 0){
        return;
    }
    free(this->data);
    free(this);
}

void block_share(Block *const this, Block **that){
    if(unlikely(this == NULL)){
        return;
    }
    if(likely(*that != NULL)){
        block_delete(*that);
    }
    *that = this;
    this->shared_num++;
}

Monad *block_get(Block const*const this, size_t const index){
    /* create a new Monad, and move the value into it */
    if(unlikely(index >= this->mem_num)){
        /* index out of range */
        raise_error("Block get: index out of range", __FILE__, "block_get", __LINE__)
    }
    Monad *result = monad_new(this->mem_size, this->data + index * this->mem_size);
    return result;
}

void block_set(Block *const this, size_t const index, Monad const*const monad){
    /* move the value into the block */
    if(unlikely(index >= this->mem_num)){
        /* index out of range */
        raise_error("Block set: index out of range", __FILE__, "block_set", __LINE__)
    }
    if(unlikely(CHECK_SIZE(this, monad))){
        /* size not match */
        raise_error("Block set: size not match", __FILE__, "block_set", __LINE__)
    }
    memcpy(this->data + index * this->mem_size, monad->data, this->mem_size);
    return;
}

int block_read(Block *const this, size_t const index, size_t const num, void *const buf){
    if(unlikely(index >= this->mem_num || index + num > this->mem_num)){
        /* index out of range */
        return -1;
    }
    memcpy(buf, this->data + index * this->mem_size, num * this->mem_size);
    return 0;
}

int block_write(Block *const this, size_t const index, size_t const num, void const*const buf){
    if(unlikely(index >= this->mem_num || index + num > this->mem_num)){
        /* index out of range */
        return -1;
    }
    memcpy(this->data + index * this->mem_size, buf, num * this->mem_size);
    return 0;
}

__malloc Monad *const monad_new(size_t const mem_size, void *const src){
    Monad *new = (Monad *)malloc(sizeof(Monad));
    if(unlikely(new == NULL)){
        /* malloc fail */
        raise_error("monad_new: malloc fail", __FILE__, __func__, __LINE__)
    }
    void *data = malloc(mem_size);
    if(unlikely(data == NULL)){
        /* malloc fail */
        free(new);
        raise_error("monad_new: malloc fail", __FILE__, __func__, __LINE__)
    }

    memcpy(data, src, mem_size);
    new->data = data;
    new->mem_size = mem_size;
    new->shared_num = 1;
    return new;
}

void monad_delete(Monad * this){
    if(this == NULL || --this->shared_num > 0){
        return;
    }
    free(this->data);
    free(this);
}

void monad_share(Monad *const this, Monad **const that){
    if(unlikely(this == NULL)){
        return;
    }

    /* if that is not NULL, delete it */
    if(likely(*that != NULL)){
        monad_delete(*that);
    }

    *that = this;
    this->shared_num++;
}

void monad_set(Monad *const this, Monad const*const that){
    if(unlikely(this == NULL || that == NULL || CHECK_SIZE(this, that))){
        return;
    }
    memcpy(this->data, that->data, this->mem_size);
    return;
}