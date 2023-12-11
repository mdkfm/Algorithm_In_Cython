/* Created by skf on 23-11-21. */

#ifndef ALL_C_TREE_H
#define ALL_C_TREE_H
#include "data.h"
#include "gnuc.h"
#include "deque.h"
#include "stack.h"
#include "list.h"

typedef struct treeNode{
    /* a combination of Bi-direct LinkStack and Tree */
    /* we could delete some properties based on needs */

    Elem data;

    /* pre and next is the parts of LinkStack */
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

__malloc Tree *tree_new();

void tree_deleteNode(treeNode *node);
void tree_delete(Tree* this);
void tree_raii(Tree **this);

int tree_initFromAdj(Tree *this, long **adj, Elem *value, int num);

void tree_preOrderSearch(treeNode const*const node, Stack *const q);
int tree_preOrder(Tree const*const tree, Stack *const buf);

void tree_postOrderSearch(treeNode const*const node, Stack *const q);
int tree_postOrder(Tree const*const tree, Stack *const buf);

void tree_rightPostOrderSearch(treeNode const*const node, Stack *const q);
int tree_rightPostOrder(Tree const*const tree, Stack *const buf);

int tree_levelOrder(Tree const*const tree, Stack *const buf);

#endif /* ALL_C_TREE_H */
