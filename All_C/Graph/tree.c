#include <malloc.h>
#include "../include/tree.h"

/* TODO: refactor three search function */

__malloc treeNode *tree_newNode(){
    /* use tree_newNode to create an empty node */
    treeNode *node;
    node = (treeNode *)malloc(sizeof(treeNode));
    if(node == NULL){
        /* malloc fail */
        return NULL;
    }
    node->sibling = 0;
    return node;
}


__malloc Tree *tree_new(){
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

int tree_setLink(Tree *tree){
    /* set the pre and next between different subtrees */
    treeNode *node = tree->root, *child, *next;
    RList *q = rlist_new(tree->size + 1);
    if(q == NULL){
        return 0;
    }

    rlist_appendRight(q, (Elem)(void *) node);
    while(! rlist_isEmpty(q)){
        // get a node
        Elem buf;
        rlist_popLeft(q, &buf);
        node = (treeNode *)buf.ptr;
        
        // push the child into queue
        child = node->firstchild;
        if(child != NULL){
            rlist_appendRight(q, (Elem)(void *) child);
            while((child = child->next) != NULL){
                rlist_appendRight(q, (Elem)(void *) child);
            }
        }

        // set pre and next link

        if(rlist_get(q, &buf, 0, 0)){
            next = (treeNode *)buf.ptr;
            node->next = next;
            next->pre = node;
        }
    }
    return 1;
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


    treeNode *node, *child;
    treeNode ** nodelist;
    
    tree->size = num;
    nodelist = (treeNode**)malloc(num * sizeof(treeNode*));
    if(nodelist == NULL){
        return -1;
    }

    for(int i = 0; i < num; i++){
        /* create all nodes and write value */
        nodelist[i] = tree_newNode();
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
    if(! tree_setLink(tree)){
        printf("Set link fail\n");
        goto fail;
    }
    free(nodelist);
    return 0;

    fail:
        free(tree);
        for(int i = 0; i < num; i++){
            free(nodelist[i]);
        }
        free(nodelist);
        return -1;
}

void tree_preOrderSearch(treeNode const*const node, List *const q){
    if(node != NULL){
        list_append(q, node->data);
        tree_preOrderSearch(node->firstchild, q);
        if(node->sibling){
            tree_preOrderSearch(node->next, q);
        }
    }
}

int tree_preOrder(Tree const*const tree, List *const buf){
    // the preorder of tree is corresponding to the preorder of bi-tree

    if(unlikely(rlist_freeSize(buf) < tree->size)){
        return -1;
    }
    tree_preOrderSearch(tree->root, buf);
    return 0;
}

void tree_postOrderSearch(treeNode const*const node, List *const q){
    if(node != NULL){
        tree_postOrderSearch(node->firstchild, q);
        list_append(q, node->data);
        // printf("%d\n", node->data);
        if(node->sibling){
            tree_postOrderSearch(node->next, q);
        }
    }
}

int tree_postOrder(Tree const*const tree, List *const buf){
    // the tree_postOrder of tree is corresponding to the inOrder of bi-tree

    if(unlikely(rlist_freeSize(buf) < tree->size)){
        return -1;
    }
    tree_postOrderSearch(tree->root, buf);
    return 0;
}

void tree_rightPostOrderSearch(treeNode const*const node, List*const q){
    if(node != NULL){
        tree_rightPostOrderSearch(node->firstchild, q);
        if(node->sibling){
            tree_rightPostOrderSearch(node->next, q);
        }
        list_append(q, node->data);
        // printf("%d\n", node->data);
    }
}

int tree_rightPostOrder(Tree const*const tree, List *const buf){
    // the right tree_postOrder of tree is corresponding to the tree_postOrder of bi-tree

    if(unlikely(rlist_freeSize(buf) < tree->size)){
        return -1;
    }
    tree_rightPostOrderSearch(tree->root, buf);
    return 0;
}

int tree_levelOrder(Tree const*const tree, List *const buf){
    // return a result queue
    if(unlikely(rlist_freeSize(buf) < tree->size)){
        return -1;
    }

    treeNode* node = tree->root;
    while(node != NULL){
        list_append(buf, node->data);
        node = node->next;
    }
    return 0;
}
