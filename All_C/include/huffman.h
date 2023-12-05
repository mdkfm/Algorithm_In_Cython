/* Created by skf on 23-12-2. */

#ifndef ALL_C_HUFFMAN_H
#define ALL_C_HUFFMAN_H
#include "../include/data.h"

typedef struct HuffmanNode{
    Elem data;
    double weight;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
    int is_leaf;
} HuffmanNode;

typedef struct HuffmanTree{
    HuffmanNode *root;
} HuffmanTree;

void huffman_delete(HuffmanTree * const this);
HuffmanTree* huffman_new(Elem const * const list, double const * const weight, long unsigned const length);
void _huffman_display(HuffmanNode const * const node, int depth);
void huffman_display(HuffmanTree const * const this);

#endif /*ALL_C_HUFFMAN_H */
