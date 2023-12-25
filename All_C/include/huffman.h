/* Created by skf on 23-12-2. */

#ifndef ALL_C_HUFFMAN_H
#define ALL_C_HUFFMAN_H
#include "block.h"
#include "gnuc.h"


typedef struct HuffmanNode{
    char data;
    double weight;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
    int is_leaf;
} HuffmanNode;

typedef struct HuffmanTree{
    HuffmanNode *root;
    Block *nodeList;
} HuffmanTree;

void huffman_delete(HuffmanTree * const this);
__malloc HuffmanTree* huffman_new(char const * const list, double const * const weight, size_t length);
void _huffman_display(HuffmanNode const * const node, int depth);
void huffman_display(HuffmanTree const * const this);

#endif /*ALL_C_HUFFMAN_H */
