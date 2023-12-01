/* Created by skf on 23-11-21. */

#include "../include/data.h"
#include "../include/queue.h"

#ifndef ALL_C_TREE_H
#define ALL_C_TREE_H

typedef struct treeNode{
    /* a combination of Bi-direct LinkList and Tree */
    /* we could delete some properties based on needs */

    Elem data;

    /* pre and next is the parts of LinkList */
    /* the order is the level order */

    struct treeNode *pre;
    struct treeNode *next;

    /* this tree could be converted to bi-tree simply */
    /* firstchild -> leftchild */
    /* if sibling, next -> rightchild */
    struct treeNode * parent;
    struct treeNode * firstchild;
    unsigned sibling : 1; /* if sibling == 1, the next is a sibling node */

} treeNode;

typedef struct Tree{
    treeNode * root;
    int size;
} Tree;


treeNode *newNode();

Tree *newTree();

int setLink(Tree *tree);

Tree *createTreeFromAdj(int **adj, Elem *value, int num);

void preOrderSearch(treeNode *node, Queue* q);

Queue* preOrder(Tree *tree);

void postOrderSearch(treeNode *node, Queue* q);

Queue* postOrder(Tree *tree);

void rightPostOrderSearch(treeNode *node, Queue* q);

Queue* rightPostOrder(Tree *tree);

Queue* levelOrder(Tree *tree);

#endif /* ALL_C_TREE_H */
