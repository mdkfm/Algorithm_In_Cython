#include <stdio.h>
#include "../include/data.h"
#include "../include/queue.h"


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
    /* create an empty tree */
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

    appendRight(q, (Elem)(void *) node);
    while(! isEmpty(q)){
        // get a node
        Elem buf;
        popLeft(q, &buf);
        node = (treeNode *)buf.ptr;
        
        // push the child into queue
        child = node->firstchild;
        if(child != NULL){
            appendRight(q, (Elem)(void *) child);
            while((child = child->next) != NULL){
                appendRight(q, (Elem)(void *) child);
            }
        }

        // set pre and next link

        if(getLeft(q, 0, &buf)){
            next = (treeNode *)buf.ptr;
            node->next = next;
            next->pre = node;
        }
    }
    return 1;
}

// TODO: Graph struct
Tree *createTreeFromAdj(int **adj, Elem *value, int num){
    /* adj is an adj matrix of an undirected graph */
    /* num is the nodes num */
    /* check this undirected graph whether is ringed */
    // TODO: realize the isRigned
    // if(isRinged(adj, 0)){
    //     return NULL;
    // }

    Tree *tree = newTree();
    treeNode *node, *child;
    treeNode ** nodelist;
    
    tree->size = num;
    nodelist = (treeNode**)malloc(num * sizeof(treeNode*));
    if(nodelist == NULL){
        free(tree);
        return NULL;
    }

    for(int i = 0; i < num; i++){
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
    for(int i = 0; i < num; i++){
        node = nodelist[i];
        /* get the first child */
        int j;
        for(j = i + 1; j < num; j++){
            if(adj[i][j] == 1){
                node->firstchild = nodelist[j];
                child = node->firstchild;
                break;
            }
        }
        /* set the next and sibling */
        for(; j < num; j++){
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
        for(int i = 0; i < num; i++){
            free(nodelist[i]);
        }
        free(nodelist);
        return NULL;
}

void preOrderSearch(treeNode *node, Queue* q){
    if(node != NULL){
        appendRight(q, node->data);
        // printf("%d\n", node->data);
        preOrderSearch(node->firstchild, q);
        if(node->sibling){
            preOrderSearch(node->next, q);
        }
    }
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

void postOrderSearch(treeNode *node, Queue* q){
    if(node != NULL){
        postOrderSearch(node->firstchild, q);
        appendRight(q, node->data);
        // printf("%d\n", node->data);
        if(node->sibling){
            postOrderSearch(node->next, q);
        }
    }
}

Queue* postOrder(Tree *tree){
    // return a result queue
    // the postOrder of tree is corresponding to the inOrder of bi-tree
    Queue *q = newQueue(tree->size + 1);
    if(q == NULL){
        return NULL;
    }
    postOrderSearch(tree->root, q);
    return q;
}

void rightPostOrderSearch(treeNode *node, Queue* q){
    if(node != NULL){
        rightPostOrderSearch(node->firstchild, q);
        if(node->sibling){
            rightPostOrderSearch(node->next, q);
        }
        appendRight(q, node->data);
        // printf("%d\n", node->data);
    }
}

Queue* rightPostOrder(Tree *tree){
    // return a result queue
    // the right postOrder of tree is corresponding to the postOrder of bi-tree
    Queue *q = newQueue(tree->size + 1);
    if(q == NULL){
        return NULL;
    }
    rightPostOrderSearch(tree->root, q);
    return q;
}

Queue* levelOrder(Tree *tree){
    // return a result queue
    Queue *q = newQueue(tree->size + 1);
    if(q == NULL){
        return NULL;
    }
    treeNode* node = tree->root;
    while(node != NULL){
        appendRight(q, node->data);
        node = node->next;
    }
    return q;
}


