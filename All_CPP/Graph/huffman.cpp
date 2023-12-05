//
// Created by skf on 23-12-1.
//

#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <iostream>
#include "../List/queue.cpp"

template<typename Dtype>
class Huffman{
private:
    struct Node{
        Dtype data;
        double weight;
        Node *left, *right;
        Node(Dtype data, double weight, Node *left = nullptr, Node *right = nullptr):
        data(data), weight(weight), left(left), right(right){}
    };
    Node *root;
    void _destroy(Node *node);
    void _print(Node *node, int depth);
    void _encode(Node *node, std::string code, std::string *result);
    void _decode(Node *node, std::string code, int &index, std::string *result);
public:
    Huffman(Dtype data[], double weight[], long unsigned size);
    ~Huffman();
    void print();
    void encode(std::string *result);
    void decode(std::string code, std::string *result);
};

template<typename Dtype>
Huffman<Dtype>::Huffman(Dtype data[], double weight[], long unsigned size){
    if(size == 0) throw(std::invalid_argument("Empty data"));
    if(size == 1){
        root = new Node(data[0], weight[0]);
        return;
    }
    Queue<Node *> queue(size);
    for(long unsigned i = 0; i < size; i++){
        queue.appendLeft(new Node(data[i], weight[i]));
    }
    while(queue.size() > 1){
        Node *left = queue.popRight();
        Node *right = queue.popRight();
        Node *parent = new Node(Dtype(), left->weight + right->weight, left, right);
        queue.appendLeft(parent);
    }
    root = queue.popRight();
}

template<typename Dtype>
Huffman<Dtype>::~Huffman(){
    _destroy(root);
}

template<typename Dtype>
void Huffman<Dtype>::_destroy(Node *node){
    if(node == nullptr) return;
    _destroy(node->left);
    _destroy(node->right);
    delete node;
}

template<typename Dtype>
void Huffman<Dtype>::print(){
    _print(root, 0);
}

template<typename Dtype>
void Huffman<Dtype>::_print(Node *node, int depth){
    if(node == nullptr) return;
    _print(node->right, depth + 1);
    for(int i = 0; i < depth; i++) std::cout << "    ";
    std::cout << node->data << " " << node->weight << std::endl;
    _print(node->left, depth + 1);
}

template<typename Dtype>
void Huffman<Dtype>::encode(std::string *result){
    _encode(root, "", result);
}

template<typename Dtype>
void Huffman<Dtype>::_encode(Node *node, std::string code, std::string *result){
    if(node == nullptr) return;
    if(node->left == nullptr && node->right == nullptr){
        result[node->data] = code;
        return;
    }
    _encode(node->left, code + "0", result);
    _encode(node->right, code + "1", result);
}

template<typename Dtype>
void Huffman<Dtype>::decode(std::string code, std::string *result){
    int index = 0;
    _decode(root, code, index, result);
}

template<typename Dtype>
void Huffman<Dtype>::_decode(Node *node, std::string code, int &index, std::string *result){
    if(node == nullptr) return;
    if(node->left == nullptr && node->right == nullptr){
        result[index++] = node->data;
        return;
    }
    if(code[index++] == '0') _decode(node->left, code, index, result);
    else _decode(node->right, code, index, result);
}

int main(){
    char data[] = {'a', 'b', 'c', 'd'};
    double weight[] = {1, 3, 5, 7};
    Huffman<char> huffman(data, weight, 6);
    huffman.print();
    return 0;
}

#endif
