//
// Created by skf on 23-12-15.
//

#ifndef ALL_C_BLOCK_H
#define ALL_C_BLOCK_H
#include <stdlib.h>
#include <string.h>
#include "../include/gnuc.h"
#include "../include/error.h"

#define RAII(func) __attribute__((cleanup(func)))
#define auto_ptr(class) RAII(class##_raii) class##_class_ptr
#define Class(class) typedef class * class##_class_ptr;

#define tmp_ptr(x) (typeof(x) *)(&(typeof(x)[]){(x)})
#define tmp_pptr(x) tmp_ptr(tmp_ptr(x))
#define tmp_monad(x) (Monad){.data = tmp_ptr(x), .mem_size = sizeof(x), .shared_num = 1}
#define tmp_mptr(x) tmp_ptr(tmp_monad(x))
#define read_mptr(type, x) (*(type *)x->data)

typedef struct Block{
    void * data;
    size_t mem_num;
    size_t mem_size;
    size_t shared_num;
} Block;

Class(Block)

/* monad is not a part of block */
/* monad should not share memory with block */
typedef struct Monad{
    void * data;
    size_t mem_size;
    size_t shared_num;
} Monad;

Class(Monad)


__malloc Block *const block_new(size_t const mem_num, size_t const mem_size);
void block_delete(Block * this);
void block_share(Block *const this, Block **that);
Monad *block_get(Block const*const this, size_t const index);
void block_set(Block *const this, size_t const index, Monad const*const monad);
int block_read(Block *const this, size_t const index, size_t const num, void *const buf);
int block_write(Block *const this, size_t const index, size_t const num, void const*const buf);


/* monad_new create a new monad in HEAP */
/* tmp_mptr create a new monad in STACK */
__malloc Monad *const monad_new(size_t const mem_size, void *const src);
void monad_delete(Monad * this);
void monad_share(Monad *const this, Monad **const that);
void monad_set(Monad *const this, Monad const*const that);


/* $Begin static inline */
static inline void *block_getPtr(Block const*const this, size_t const index){
    if(unlikely(index >= this->mem_num)){
        /* index out of range */
        return NULL;
    }
    return this->data + index * this->mem_size;
}

static inline size_t block_size(Block const *const this){
    return this->mem_num;
}

static inline size_t block_memSize(Block const *const this){
    return this->mem_size;
}

static inline void Block_raii(Block_class_ptr *ptr){
    block_delete(*ptr);
}

static inline void Monad_raii(Monad_class_ptr *ptr){
    monad_delete(*ptr);
    *ptr = NULL;
}

#endif //ALL_C_BLOCK_H
