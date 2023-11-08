#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "queue.h"

// gcc All_C/Tree/tree.c -o excutable/tree -L./lib -lqueue

typedef long int Elemtype;

typedef struct treeNode{
    /* a combination of Bi-direct LinkList and Tree */
    /* we could delete some properties based on needs */

    Elemtype data;

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


treeNode *newNode(){
    /* use newNode to create a empty node */
    treeNode *node;
    node = (treeNode *)malloc(sizeof(treeNode));
    if(node == NULL){
        /* malloc fail */
        return NULL;
    }
    node->sibling = 0;
    return node;
}


Tree *newTree(){
    /* create a empty tree */
    Tree *node;
    node = (Tree *)malloc(sizeof(Tree));
    if(node == NULL){
        /* malloc fail */
        return NULL;
    }
    node->root = NULL;
    node->size = 0;
    return node;
}

int setLink(Tree *tree){
    /* set the pre and next between different subtrees */
    treeNode *node = tree->root, *child, *next;
    Queue *q = newQueue(tree->size + 1);
    if(q == NULL){
        return 0;
    }

    appendRight(q, (QElem) node);
    while(! isEmpty(q)){
        // get a node
        node = (treeNode*)popLeft(q);
        
        // push the child into queue
        child = node->firstchild;
        if(child != NULL){
            appendRight(q, (QElem) child);
            while((child = child->next) != NULL){
                appendRight(q, (QElem) child);
            }
        }

        // set pre and next link
        if((next = (treeNode*)getLeft(q, 0)) != NULL){
            node->next = next;
            next->pre = node;
        }
    }
    return 1;
}

// TODO: Graph struct
Tree *createTreeFromAdj(int **adj, Elemtype value[], int num){
    /* adj is an adj matrix of a undirected graph */
    /* num is the nodes num */
    /* check this undirected graph whether is ringed */
    // TODO: realize the isRigned
    // if(isRinged(adj, 0)){
    //     return NULL;
    // }

    Tree *tree = newTree();
    int i, j, begin;
    treeNode *node, *child;
    treeNode ** nodelist;
    
    tree->size = num;
    nodelist = (treeNode**)malloc(num * sizeof(treeNode*));
    if(nodelist == NULL){
        free(tree);
        printf("Make nodelist fail\n");
        exit(1);
    }

    for(i = 0; i < num; i++){
        /* create all nodes and write value */
        nodelist[i] = newNode();
        if(nodelist[i] == NULL){
            printf("Make node fail\n");
            goto fail;
        }
        nodelist[i]->data = value[i];
    }

    // set root
    tree->root = nodelist[0];

    /* set the edges */
    for(i = 0; i < num; i++){
        node = nodelist[i];
        /* get the first child */
        for(j = i + 1; j < num; j++){
            if(adj[i][j] == 1){
                node->firstchild = nodelist[j];
                child = node->firstchild;
                begin = j;
                break;
            }
        }
        /* set the next and sibling */
        for(j = begin + 1; j < num; j++){
            if(adj[i][j] == 1){
                // set pre and next link
                child->next = nodelist[j];
                nodelist[j]->pre = child;

                // set sibling
                child->sibling = 1;
                child = child->next;
            }
        }
    }
    /* set the pre and next between different subtrees */
    if(! setLink(tree)){
        printf("Set link fail\n");
        goto fail;
    }
    free(nodelist);
    return tree;

    fail:
        free(tree);
        for(j = 0; j < num; j++){
            free(nodelist[j]);
        }
        free(nodelist);
        exit(1);
}


Queue* preOrder(Tree *tree){
    // return a result queue
    // the preorder of tree is corresponding to the preorder of bi-tree
    Queue *q = newQueue(tree->size + 1);
    if(q == NULL){
        return NULL;
    }
    preOrderSearch(tree->root, q);
    return q;
}

void preOrderSearch(treeNode *node, Queue* q){
    if(node != NULL){
        appendRight(q, (QElem) node->data);
        // printf("%d\n", node->data);
        preOrderSearch(node->firstchild, q);
        if(node->sibling){
            preOrderSearch(node->next, q);
        }
    }
}

Queue* postOrder(Tree *tree){
    // return a result queue
    // the postorder of tree is corresponding to the inorder of bi-tree
    Queue *q = newQueue(tree->size + 1);
    if(q == NULL){
        return NULL;
    }
    postOrderSearch(tree->root, q);
    return q;
}

void postOrderSearch(treeNode *node, Queue* q){
    if(node != NULL){
        postOrderSearch(node->firstchild, q);
        appendRight(q, (QElem) node->data);
        // printf("%d\n", node->data);
        if(node->sibling){
            postOrderSearch(node->next, q);
        }
    }
}

Queue* rightPostOrder(Tree *tree){
    // return a result queue
    // the right postOrder of tree is corresponding to the postorder of bi-tree
    Queue *q = newQueue(tree->size + 1);
    if(q == NULL){
        return NULL;
    }
    rightPostOrderSearch(tree->root, q);
    return q;
}

void rightPostOrderSearch(treeNode *node, Queue* q){
    if(node != NULL){
        rightPostOrderSearch(node->firstchild, q);
        if(node->sibling){
            rightPostOrderSearch(node->next, q);
        }
        appendRight(q, (QElem) node->data);
        // printf("%d\n", node->data);
    }
}

Queue* levelOrder(Tree *tree){
    // return a result queue
    Queue *q = newQueue(tree->size + 1);
    if(q == NULL){
        return NULL;
    }
    treeNode* node = tree->root;
    while(node != NULL){
        appendRight(q, (QElem) node->data);
        node = node->next;
    }
    return q;
}

// void main(){
//     int i;
//     int adj[6][6] = {
//         {0, 1, 1, 1, 0, 0},
//         {0, 0, 0, 0, 1, 1},
//         {0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0}
//     };
//     int **test = (int **)malloc(6 * sizeof(int *));
//     for (i = 0; i < 6; i++) {
//         test[i] = adj[i];
//     }
//     int value[] = {0, 1, 2, 3, 4, 5};

//     Tree *tree = createTreeFromAdj(test, value, 6);
//     treeNode *node = tree->root;
//     while(node != NULL){
//         printf("%d -> ", node->data);
//         node = node->next;
//     }
//     printf("\n");

//     Queue* q1 = preOrder(tree);
//     displayQueue(q1);

//     Queue* q2 = postOrder(tree);
//     displayQueue(q2);

//     Queue* q3 = rightPostOrder(tree);
//     displayQueue(q3);
// }
