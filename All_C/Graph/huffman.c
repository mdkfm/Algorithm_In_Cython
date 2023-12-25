/* Created by skf on 23-12-2. */

#include <malloc.h>

#include "../include/heap.h"
#include "../include/huffman.h"


void _huffman_delete(HuffmanNode *node){
    if(node == NULL){
        return;
    }
    _huffman_delete(node->left);
    _huffman_delete(node->right);
    free(node);
}

void huffman_delete(HuffmanTree *this){
    _huffman_delete(this->root);
    free(this);
}

int huffman_cmp(Block const*const block, size_t index0, size_t index1){
    HuffmanNode *node0 = read_mptr(HuffmanNode *, block_get(block, index0));
    HuffmanNode *node1 = read_mptr(HuffmanNode *, block_get(block, index1));
    return node1->weight - node0->weight;
}

#define NEW_DEBUG 0
HuffmanTree* huffman_new(
        char const * const list,
        double const * const weight,
        long unsigned const length){
    HuffmanTree *new = (HuffmanTree *)malloc(sizeof(HuffmanTree));
    if(new == NULL){
        return NULL;
    }
    new->root = NULL;
    auto_ptr(Heap) heap = heap_new(length, sizeof(HuffmanNode *), huffman_cmp, NULL);
    if(heap == NULL){
        goto fail0;
    }

    for(long unsigned i = 0; i < length; i++){
        HuffmanNode *tmp = (HuffmanNode *)malloc(sizeof(HuffmanNode));
        if(tmp == NULL){
            goto fail1;
        }
        heap_append(heap, tmp_mptr(tmp));
#if NEW_DEBUG
        printf("\n");
#endif
    }

    while(heap->size > 1){
        /* malloc a new non leaf node */
        HuffmanNode *node = (HuffmanNode *)malloc(sizeof(HuffmanNode));
        if(node == NULL){
            goto fail1;
        }
        node->is_leaf = 0;

        HuffmanNode *left = read_mptr(HuffmanNode *, heap_pop(heap));
        HuffmanNode *right = read_mptr(HuffmanNode *, heap_pop(heap));
        node->left = left;
        node->right = right;
#if NEW_DEBUG
        printf("left %ld\n", left);
        printf("right %ld\n", right);
#endif
        node->data = 0;
        node->weight = left->weight + right->weight;
        heap_append(heap, tmp_mptr(node));
    }
    HuffmanNode *root = read_mptr(HuffmanNode *, heap_pop(heap));
    new->root = root;

    return new;

    /* Hierarchical memory free */
    fail1:;
    /* free all malloced memory */
    Block *block = heap->data;
    size_t size = heap->size;
    for(long unsigned i = 0; i < size; i++){
        HuffmanNode *tmp = read_mptr(HuffmanNode *, block_get(block, i));
        _huffman_delete(tmp);
    }
    fail0:;
    free(new);
    return NULL;
}

void _huffman_display(HuffmanNode const * const node, int depth){
    if(node == NULL){
        return;
    }
    for(int i = 0; i < depth - 1; i++){
        printf("| ");
    }
    printf("- ");
    if(node->is_leaf)
        printf("%c %lf\n", node->data, node->weight);
    else{
        printf("%lf\n", node->weight);
    }
    _huffman_display(node->left, depth + 1);
    _huffman_display(node->right, depth + 1);
}

void huffman_display(HuffmanTree const * const this){
    _huffman_display(this->root, 0);
}

