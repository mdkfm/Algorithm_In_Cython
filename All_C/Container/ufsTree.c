#include <malloc.h>
#include "../include/ufsTree.h"


__malloc UFSTree *ufsTree_new(size_t size){
    UFSTree *tree = (UFSTree *)malloc(sizeof(UFSTree));
    if(tree == NULL){
        return NULL;
    }

    tree->set = (UFSNode *)calloc(size, sizeof(UFSNode));
    if(tree->set == NULL){
        free(tree);
        return NULL;
    }
    for(size_t i = 0; i < size; i++){
        tree->set[i].rank = 0;
        tree->set[i].parent = i;
    }
    return tree;
}

void ufsTree_delete(UFSTree *tree){
    free(tree->set);
    free(tree);
}

size_t ufsTree_findRoot(UFSTree *tree, size_t x){
    UFSNode node = tree->set[x];
    if(x != node.parent){
        /* compresses paths */
        node.parent = ufsTree_findRoot(tree, node.parent);
    }
    return node.parent;
}

int ufsTree_union(UFSTree *tree, size_t x, size_t y){
    /* ufsTree x and y */
    /* union_result:
         * 1 : union success
         * 2 : union success, but the rank of root of from is increased
         * 3 : already union */
    size_t root_x = ufsTree_findRoot(tree, x);
    size_t root_y = ufsTree_findRoot(tree, y);
    size_t rank_x = tree->set[root_x].rank;
    size_t rank_y = tree->set[root_y].rank;
    UFSNode *set = tree->set;
    if(root_x == root_y){
        return 3;
    }
    if(rank_x > rank_y){
        set[root_y].parent = root_x;
        return 1;
    }
    set[root_x].parent = root_y;
    if(rank_x == rank_y){
        set[root_y].rank++;
    }
    return 2;
}