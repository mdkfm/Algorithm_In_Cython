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

Queue *preOrder(BiTree *this){
    /* return a queue of preOrder */
    Queue *visit = newQueue(this->size), *result= newQueue(this->size+1);
    BTNode *node = this->root;
    if(node == NULL){
        /* empty tree */
        deleteQueue(result);
        deleteQueue(visit);
        return NULL;
    }

    /* append root */
    appendRight(visit, (Elem)(void *)node);

    while(!isEmpty(visit)){
        /* pop a node */
        popRight(visit, (Elem *)&node);
        /* get the data */
        appendRight(result, node->data);

        /* append the child, right first */
        if(node->rchild != NULL){
            appendRight(visit, (Elem)(void *)node->rchild);
        }
        if(node->lchild != NULL){
            appendRight(visit, (Elem)(void *)node->lchild);
        }
    }
    deleteQueue(visit);
    return result;
}

Queue *inOrder(BiTree *this){
    /* return a queue of inOrder */
    Queue *visit = newQueue(this->size), *result= newQueue(this->size);
    BTNode *node = this->root, *lchild, *rchild, *last=NULL;
    if(node == NULL){
        /* empty tree */
        deleteQueue(result);
        deleteQueue(visit);
        return NULL;
    }

    /* append root */
    appendRight(visit, (Elem)(void *)node);

    while(!isEmpty(visit) || node != NULL){
        getRight(visit, 0, (Elem *)&node);
        lchild = node->lchild;
        rchild = node->rchild;
        if(lchild == NULL || (last != NULL && last == lchild)){
            popRight(visit, (Elem *)&node);
            appendRight(result, node->data);
            appendRight(visit, (Elem)(void *)rchild);
            continue;
        }
        appendRight(visit, (Elem)(void *)lchild);
    }
    deleteQueue(visit);
    return result;
}

Queue *postOrder(BiTree *this){
    /* return a queue of postOrder */
    Queue *visit = newQueue(this->size), *result= newQueue(this->size);
    BTNode *node = this->root, *rchild, *lchild, *last=NULL;
    if(node == NULL){
        /* empty tree */
        deleteQueue(result);
        deleteQueue(visit);
        return NULL;
    }

    /* append root */
    appendRight(visit, (Elem)(void *)node);

    while(!isEmpty(visit)){
        /* get a node */
        getRight(visit, 0, (Elem *)&node);
        rchild = node->rchild;
        lchild = node->lchild;
        if((lchild == NULL && rchild == NULL) || (last != NULL && (last == lchild || last == rchild))){
            popRight(visit, (Elem *)&node);
            appendRight(result, node->data);
            last = node;
            continue;
        }
        if(rchild != NULL) appendRight(visit, (Elem)(void*)rchild);
        if(lchild != NULL) appendRight(visit, (Elem)(void*)lchild);
    }
    deleteQueue(visit);
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

Queue* q_mirror(BiTree *this){
    BTNode *node = this->root;
    this->root = mirror(node);
    return preOrder(this);
}


int main(){
    Queue *result;
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
    displayQueue(result);
    result = postOrder(tree);
    displayQueue(result);

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
    displayQueue(result);
    result = q_mirror(tree);
    displayQueue(result);

    return 0;
}