#include<malloc.h>
#include<stdio.h>
#include "../include/data.h"
#include "../include/deque.h"

typedef struct BTNode{
    Elem data;
    struct BTNode *lchild;
    struct BTNode *rchild;
} BTNode;

typedef struct BiTree{
    BTNode *root;
    int size;
} BiTree;

BTNode *newBTNode(){
    BTNode *node;
    node = (BTNode *)malloc(sizeof(BTNode));
    if(node == NULL){
        /* malloc fail */
        return NULL;
    }
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

void deleteBTNode(BTNode *this){
    free(this);
}

BiTree *newBiTree(){
    BiTree *tree;
    tree = (BiTree *)malloc(sizeof(BiTree));
    if(tree == NULL){
        /* malloc fail */
        return NULL;
    }
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

int initBiTree(BiTree *tree, int length, Elem list[length], int adj[length][length]){
    /* init a tree with a Elem list and adj list */
    /* linked : adj[i][j] == 1, not linked : adj[i][j] == 0 */

    /* TODO: isRinged check */
    /* TODO: Invalid BiTree check */

    BTNode ** nodelist = (BTNode **)malloc(sizeof(BTNode *) * length);
    for(int i = 0; i < length; i++){
        BTNode *node = newBTNode();
        if(node == NULL){
            /* malloc fail */
            return 0;
        }
        nodelist[i] = node;
        node->data = list[i];
        node->lchild =NULL;
        node->rchild =NULL;
    }
    for(int i = 0; i < length; i++){
        for(int j = 0; j < length; j++){
            if(adj[i][j] == 1){
                BTNode *node = nodelist[i];
                if(node->lchild == NULL) node->lchild = nodelist[j];
                else if(node->rchild == NULL) node->rchild = nodelist[j];
                else return 0; // more than 2 child
            }
        }
    }
    tree->root = nodelist[0];
    tree->size = length;
    return 1;
}

Deque *preOrder(BiTree *this){
    /* return a queue of preOrder */
    Deque *visit = deque_new(this->size), *result= deque_new(this->size+1);
    BTNode *node = this->root;
    if(node == NULL){
        /* empty tree */
        deque_delete(result);
        deque_delete(visit);
        return NULL;
    }

    /* append root */
    deque_appendRight(visit, (Elem)(void *)node);

    while(!deque_isEmpty(visit)){
        /* pop a node */
        deque_popRight(visit, (Elem *)&node);
        /* get the data */
        deque_appendRight(result, node->data);

        /* append the child, right first */
        if(node->rchild != NULL){
            deque_appendRight(visit, (Elem)(void *)node->rchild);
        }
        if(node->lchild != NULL){
            deque_appendRight(visit, (Elem)(void *)node->lchild);
        }
    }
    deque_delete(visit);
    return result;
}

Deque *inOrder(BiTree *this){
    /* return a queue of inOrder */
    Deque *visit = deque_new(this->size), *result= deque_new(this->size);
    BTNode *node = this->root, *lchild, *rchild, *last=NULL;
    if(node == NULL){
        /* empty tree */
        deque_delete(result);
        deque_delete(visit);
        return NULL;
    }

    /* append root */
    deque_appendRight(visit, (Elem)(void *)node);

    while(!deque_isEmpty(visit) || node != NULL){
        deque_get(visit, (Elem *)&node, 0, 1);
        lchild = node->lchild;
        rchild = node->rchild;
        if(lchild == NULL || (last != NULL && last == lchild)){
            deque_popRight(visit, (Elem *)&node);
            deque_appendRight(result, node->data);
            deque_appendRight(visit, (Elem)(void *)rchild);
            continue;
        }
        deque_appendRight(visit, (Elem)(void *)lchild);
    }
    deque_delete(visit);
    return result;
}

Deque *postOrder(BiTree *this){
    /* return a queue of postOrder */
    Deque *visit = deque_new(this->size), *result= deque_new(this->size);
    BTNode *node = this->root, *rchild, *lchild, *last=NULL;
    if(node == NULL){
        /* empty tree */
        deque_delete(result);
        deque_delete(visit);
        return NULL;
    }

    /* append root */
    deque_appendRight(visit, (Elem)(void *)node);

    while(!deque_isEmpty(visit)){
        /* get a node */
        deque_get(visit, (Elem *)&node, 0, 1);
        rchild = node->rchild;
        lchild = node->lchild;
        if((lchild == NULL && rchild == NULL) || (last != NULL && (last == lchild || last == rchild))){
            deque_popRight(visit, (Elem *)&node);
            deque_appendRight(result, node->data);
            last = node;
            continue;
        }
        if(rchild != NULL) deque_appendRight(visit, (Elem)(void*)rchild);
        if(lchild != NULL) deque_appendRight(visit, (Elem)(void*)lchild);
    }
    deque_delete(visit);
    return result;
}

BTNode* mirror(BTNode *this){
    if(this == NULL) return NULL;
    BTNode *left, *right;
    left = mirror(this->lchild);
    right = mirror(this->rchild);
    this->lchild = right;
    this->rchild = left;
    return this;
}

Deque* q_mirror(BiTree *this){
    BTNode *node = this->root;
    this->root = mirror(node);
    return preOrder(this);
}


int main(){
    Deque *result;
    Elem list[5] = {3, 9, 20, 15, 7};
    int adj[5][5] = {
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    BiTree *tree = newBiTree();
    int err = initBiTree(tree, 5, list, adj);
    if(err == 1) printf("Init tree success!\n");
    
    result = preOrder(tree);
    deque_display(result);
    result = postOrder(tree);
    deque_display(result);

    Elem list1[5] = {1, 2, 3, 4, 5};
    int adj1[5][5] = {
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    tree = newBiTree();
    err = initBiTree(tree, 5, list1, adj1);
    result = preOrder(tree);
    deque_display(result);
    result = q_mirror(tree);
    deque_display(result);

    return 0;
}