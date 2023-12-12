//
// Created by skf on 23-12-12.
//

#ifndef ALL_C_UNION_H
#define ALL_C_UNION_H

#include "data.h"
#include "gnuc.h"

typedef struct UFSNode{
    size_t rank; /* the bound of num-layers */
    size_t parent;
} UFSNode;

typedef struct UFSTree{
    UFSNode * set;
    int size;
} UFSTree;

typedef UFSTree * const UFSTree_class_ptr;

__malloc UFSTree *ufsTree_new(size_t size);
void ufsTree_delete(UFSTree *tree);
size_t ufsTree_findRoot(UFSTree *tree, size_t x);
int ufsTree_union(UFSTree *tree, size_t x, size_t y);

/* static inline */
static inline void UFSTree_raii(UFSTree_class_ptr *tree){
    ufsTree_delete(*tree);
}

#endif //ALL_C_UNION_H
