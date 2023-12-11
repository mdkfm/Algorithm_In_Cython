#include <malloc.h>
#include "../include/tree.h"

#define GRAPHADJ_DEBUG 0
/* TODO: refactor three search function */

__malloc treeNode *tree_newNode(){
    /* use tree_newNode to create an empty node */
    treeNode *node;
    node = (treeNode *)malloc(sizeof(treeNode));
    if(node == NULL){
        /* malloc fail */
        return NULL;
    }
    node->pre = NULL;
    node->next = NULL;
    node->parent = NULL;
    node->firstchild = NULL;
    node->sibling = 0;
    return node;
}

__malloc Tree *tree_new(){
    /* create an empty tree */
    Tree *node = (Tree *)malloc(sizeof(Tree));
    if(node == NULL){
        /* malloc fail */
        return NULL;
    }
    node->root = NULL;
    node->size = 0;
    return node;
}

void tree_deleteNode(treeNode *node){
    /* delete a node */
    free(node);
}

void tree_delete(Tree* this){
    /* delete a tree */
    treeNode *node = this->root;
    while(node != NULL){
        treeNode *tmp = node->next;
        tree_deleteNode(node);
        node = tmp;
    }
    free(this);
}

void tree_raii(Tree **this){
    /* RAII for tree */
    tree_delete(*this);
    *this = NULL;
}

int tree_setLink(Tree *tree){
    /* set the pre and next between different subtrees */
    RAII(deque_raii) Deque *q = deque_new(tree->size + 1);
    if(q == NULL){
        return -1;
    }

#if GRAPHADJ_DEBUG
    printf("In setting link\n");
#endif

    deque_appendRight(q, (Elem)(void *) tree->root);
    while(! deque_isEmpty(q)){
        // get a node
        treeNode *node;
        deque_popLeft(q, (Elem*)&node);
        treeNode *child = node->firstchild;
        if(child != NULL){
            deque_appendRight(q, (Elem)(void *) child);
            while((child = child->next) != NULL){
                deque_appendRight(q, (Elem)(void *) child);
            }
        }

        // set pre and next link
        treeNode *next;
#if GRAPHADJ_DEBUG
        printf("Set link of %ld\n", node->data.num_int64);
#endif
        if(deque_get(q, (Elem *)&next, 0, 0)){
#if GRAPHADJ_DEBUG
            printf("next %ld\n", next->data.num_int64);
#endif
            node->next = next;
            next->pre = node;
        }
#if GRAPHADJ_DEBUG
        printf("Set link of %ld end\n", node->data.num_int64);
#endif
    }
    return 0;
}

// TODO: Graph struct
int tree_initFromAdj(Tree *tree, long **adj, Elem *value, int num){
    /* adj is an adj matrix of an undirected graph */
    /* num is the nodes num */

    /* error list:
     * no error: return 0
     * malloc error: return -1
     * tree error: return -2
     */

    /* check this undirected graph whether is ringed */
    // TODO: realize the isRigned
    // if(isRinged(adj, 0)){
    //     return -2;
    // }

    tree->size = num;

    RAII(list_raii) List *nodelist = list_new(num);
    if(unlikely(nodelist == NULL)){
        return -1;
    }
#if GRAPHADJ_DEBUG
    printf("Make nodes\n");
#endif
    for(int i = 0; i < num; i++){
        /* create all nodes and write value */
        treeNode *tmp = tree_newNode();
        if(unlikely(tmp == NULL)){
            goto fail;
        }
        tmp->data = value[i];
        list_set(nodelist, i, (Elem)(void *)tmp);
    }

    /* set the edges */
#if GRAPHADJ_DEBUG
    printf("Set edges\n");
#endif
    for(int i = 0; i < num; i++){
        treeNode *node;
        list_get(nodelist, i, (Elem*)&node);
        /* get the first child */
        treeNode *child;
        int j;
        for(j = i + 1; j < num; j++){
            if(unlikely(adj[i][j] == 1)){
                list_get(nodelist, j, (Elem *)&(node->firstchild));
                child = node->firstchild;
                break;
            }
        }
        /* set the next and sibling */
        for(; j < num; j++){
            if(unlikely(adj[i][j] == 1)){
                /* set pre and next link */
                list_get(nodelist, j, (Elem *)&(child->next));
                child->next->pre = child;

                /* set sibling */
                child->sibling = 1;
                child = child->next;
            }
        }
    }
#if GRAPHADJ_DEBUG
    printf("Set link\n");
#endif
    /* set root */
    list_get(nodelist, 0, (Elem *)&(tree->root));
    /* set the pre and next between different subtrees */
    if(unlikely(tree_setLink(tree) < 0)){
        goto fail;
    }
#if GRAPHADJ_DEBUG
    printf("Set link end\n");
    printf("Init end\n");
#endif
    return 0;

fail:
    /* manage the lifecycle of nodes separately */
    for(int i = 0; i < num; i++){
        treeNode *node;
        list_get(nodelist, i, (Elem *)&node);
        tree_deleteNode(node);
    }
    return -1;
}

void tree_preOrderSearch(treeNode const*const node, Stack *const q){
    if(node != NULL){
        stack_append(q, node->data);
        tree_preOrderSearch(node->firstchild, q);
        if(node->sibling){
            tree_preOrderSearch(node->next, q);
        }
    }
}

int tree_preOrder(Tree const*const tree, Stack *const buf){
    // the preorder of tree is corresponding to the preorder of bi-tree

    if(unlikely(stack_freeSize(buf) < tree->size)){
        return -1;
    }
    tree_preOrderSearch(tree->root, buf);
    return 0;
}

void tree_postOrderSearch(treeNode const*const node, Stack *const q){
    if(node != NULL){
        tree_postOrderSearch(node->firstchild, q);
        stack_append(q, node->data);
        // printf("%d\n", node->data);
        if(node->sibling){
            tree_postOrderSearch(node->next, q);
        }
    }
}

int tree_postOrder(Tree const*const tree, Stack *const buf){
    // the tree_postOrder of tree is corresponding to the inOrder of bi-tree

    if(unlikely(stack_freeSize(buf) < tree->size)){
        return -1;
    }
    tree_postOrderSearch(tree->root, buf);
    return 0;
}

void tree_rightPostOrderSearch(treeNode const*const node, Stack*const q){
    if(node != NULL){
        tree_rightPostOrderSearch(node->firstchild, q);
        if(node->sibling){
            tree_rightPostOrderSearch(node->next, q);
        }
        stack_append(q, node->data);
        // printf("%d\n", node->data);
    }
}

int tree_rightPostOrder(Tree const*const tree, Stack *const buf){
    // the right tree_postOrder of tree is corresponding to the tree_postOrder of bi-tree

    if(unlikely(stack_freeSize(buf) < tree->size)){
        return -1;
    }
    tree_rightPostOrderSearch(tree->root, buf);
    return 0;
}

int tree_levelOrder(Tree const*const tree, Stack *const buf){
    // return a result queue
    if(unlikely(stack_freeSize(buf) < tree->size)){
        return -1;
    }

    treeNode* node = tree->root;
    while(node != NULL){
        stack_append(buf, node->data);
        node = node->next;
    }
    return 0;
}
