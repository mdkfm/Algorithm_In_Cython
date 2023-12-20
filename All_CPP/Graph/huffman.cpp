//
// Created by skf on 23-12-1.
//

#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "../Container/heap.cpp"

template<typename Dtype>
class Huffman{
private:
    struct Node{
        Dtype data;
        double weight;
        Node *left, *right;
        Node(Dtype data, double weight, Node *left = nullptr, Node *right = nullptr):
        data(data), weight(weight), left(left), right(right){};
        int operator < (const Node &node) const{
            return weight < node.weight;
        };
        int operator > (const Node &node) const{
            return weight > node.weight;
        };
    };
    Node *root;
    void deleteNode(Node *node);
public:
    Huffman(Dtype data[], double weight[], long unsigned size);
    ~Huffman();
};

template<typename Dtype>
Huffman<Dtype>::Huffman(Dtype *data, double *weight, long unsigned size){
    Heap<Node *> heap(size);
    for(long unsigned i = 0; i < size; ++i){
        heap.append(new Node(data[i], weight[i]));
    }
    while(heap.getSize() > 1){
        Node *left = heap.pop();
        Node *right = heap.pop();
        Node *parent = new Node(0, left->weight + right->weight, left, right);
        heap.append(parent);
    }
    root = heap.pop();
}

template<typename Dtype>
void Huffman<Dtype>::deleteNode(Node *node){
    if(node == nullptr) return;
    Huffman::deleteNode(node->left);
    Huffman::deleteNode(node->right);
    delete node;
}

template<typename Dtype>
Huffman<Dtype>::~Huffman(){
    Huffman::deleteNode(root);
}
#endif
