/* Created by skf on 23-12-2. */

#include <malloc.h>

#include "../include/data.h"
#include "../include/heap.h"
#include "../include/huffman.h"


void _huffman_delete(HuffmanNode * const node){
    if(node == NULL){
        return;
    }
    _huffman_delete(node->left);
    _huffman_delete(node->right);
    free(node);
}

void huffman_delete(HuffmanTree * const this){
    _huffman_delete(this->root);
    free(this);
}

int _cmp(Elem const e0, Elem const e1){
    HuffmanNode *node0 = (HuffmanNode *)e0.ptr;
    HuffmanNode *node1 = (HuffmanNode *)e1.ptr;
    return node0->weight < node1->weight;
}

#define NEW_DEBUG 0
HuffmanTree* huffman_new(
        Elem const * const list,
        double const * const weight,
        long unsigned const length){
    HuffmanTree *this = (HuffmanTree *)malloc(sizeof(HuffmanTree));
    if(this == NULL){
        return NULL;
    }
    this->root = NULL;
    HuffmanNode **node_list = (HuffmanNode **)malloc(sizeof(HuffmanNode *) * length);

    for(long unsigned i = 0; i < length; i++){
#if NEW_DEBUG
        printf("malloc node %ld\n", i);
#endif
        /* malloc all leaf nodes */
        HuffmanNode *node = (HuffmanNode *)malloc(sizeof(HuffmanNode));

        if(node == NULL){
            goto fail1;
        }
        node_list[i] = node;
        node->data = list[i];
#if NEW_DEBUG
        printf("node data %ld\n", list[i].num_int64);
#endif
        node->weight = weight[i];
        node->left = NULL;
        node->right = NULL;
        node->is_leaf = 1;
#if NEW_DEBUG
        printf("\n");
#endif
    }

    Heap *heap = heap_new(length, _cmp);
    /* heap of HuffmanNode */
    if(heap == NULL){
        goto fail1;
    }

    heap_init(heap, (Elem *)node_list, length);
    while(heap->size > 1){
        /* malloc a new non leaf node */
        HuffmanNode *node = (HuffmanNode *)malloc(sizeof(HuffmanNode));
        if(node == NULL){
            goto fail2;
        }
        node->is_leaf = 0;
        HuffmanNode *left, *right;

        heap_pop(heap, (Elem *)&left);
        heap_pop(heap, (Elem *)&right);
        node->left = left;
        node->right = right;
#if NEW_DEBUG
        printf("left %ld\n", left);
        printf("right %ld\n", right);
#endif
        node->data = (Elem)(long)0;
        node->weight = left->weight + right->weight;
        heap_append(heap, (Elem)(void *)node);
    }
    HuffmanNode *root;
    heap_pop(heap, (Elem *)&root);
    this->root = root;
    heap_delete(heap);
    return this;

    /* Hierarchical memory free */
    fail2:;
    long unsigned size = heap->size;
    while(size > 0){
        HuffmanNode *node;
        heap_pop(heap, (Elem *)&node);
        _huffman_delete(node);
        size--;
    }
    heap_delete(heap);
    fail1:;
    /* free all malloced memory */
    for(long unsigned j = 0; j < length; j++){
        if(node_list == NULL) break;
        free(node_list[j]);
    }
    free(node_list);
    free(this);
    return NULL;
}

void _huffman_display(HuffmanNode const * const node, int depth){
    if(node == NULL){
        return;
    }
    for(int i = 0; i < depth; i++){
        printf("  ");
    }
    if(node->is_leaf)
        printf("%c %lf\n", node->data.str, node->weight);
    else{
        printf("%lf\n", node->weight);
    }
    _huffman_display(node->left, depth + 1);
    _huffman_display(node->right, depth + 1);
}

void huffman_display(HuffmanTree const * const this){
    _huffman_display(this->root, 0);
}

