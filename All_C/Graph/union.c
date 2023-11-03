#include<malloc.h>


typedef struct UFSNode{
    int rank; // the bound of num-layers
    int parent;
} UFSNode;

typedef struct UFSTree{
    UFSNode * set;
    int size;
} UFSTree;

UFSTree *newUnion(int size){
    UFSTree *tree = (UFSTree *)malloc(sizeof(UFSTree));
    if(tree == NULL){
        return NULL;
    }
    int i;
    tree->set = (UFSNode *)malloc(size * sizeof(UFSNode));
    if(tree->set == NULL){
        free(tree);
        return NULL;
    }
    for(i = 0; i < size; i++){
        tree->set[i]->rank = 0;
        tree->set[i]->parent = i;
    }
    return Tree;
}

int findRoot(UFSTree *tree, int x){
    UFSNode *node = tree->set[x];
    if(x != node->parent){
        // compresses paths
        node->parent = findRoot(tree, node->parent);
    }
    return node->parent;
}

void unoinTree(UFSTree *tree, int x, int y){
    int rx = findRoot(tree, x);
    int ry = findRoot(tree, y);
    if(rx == ry){
        return;
    }
    if(tree->set[rx]->rank > tree->set[ry]->rank){
        tree->set[ry]->parent = rx;
        return;
    }
    tree->set[rx]->parent = ry;
    if(tree->set[rx]->rank == tree->set[ry]->rank){
        tree->set[ry]->rank++;
    }
    
}