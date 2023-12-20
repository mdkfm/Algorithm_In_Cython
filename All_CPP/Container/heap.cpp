//
// Created by skf on 23-12-18.
//
#include <stdexcept>
#include <iostream>

template<typename Dtype>
class Heap{
private:
    Dtype *data;
    size_t size;
    static inline size_t Parent(size_t const index);
    static inline size_t Left(size_t const index);
    static inline size_t Right(size_t const index);
    void heapifyFrom(size_t const start);
    void heapify();
public:
    size_t getSize();
    size_t const maxsize;
    Heap(size_t const maxsize);
    ~Heap(){delete[] data;}
    [[nodiscard]] inline bool isEmpty() const;
    [[nodiscard]] inline bool isFull() const;
    void init(Dtype * const list, size_t const length);
    void display() const;
    [[nodiscard]] Dtype top() const;
    [[nodiscard]] Dtype pop();
    void append(Dtype elem);
};

template<typename Dtype>
Heap<Dtype>::Heap(size_t const maxsize): maxsize(maxsize){
    if(maxsize == 0) throw std::invalid_argument("maxsize should be positive");
    data = new Dtype[maxsize];
    size = 0;
}

template<typename Dtype>
inline size_t Heap<Dtype>::getSize(){
    return size;
}

template<typename Dtype>
inline size_t Heap<Dtype>::Parent(size_t const index){
    if(index == 0) throw std::invalid_argument("Root node has no parent");
    return (index - 1) >> 1;
}

template<typename Dtype>
inline size_t Heap<Dtype>::Left(size_t const index){
    size_t result = (index << 1) + 1;
    return result;
}

template<typename Dtype>
inline size_t Heap<Dtype>::Right(size_t const index){
    size_t result = (index << 1) + 2;
    return result;
}

template<typename Dtype>
inline bool Heap<Dtype>::isEmpty() const{
    return size == 0;
}

template<typename Dtype>
inline bool Heap<Dtype>::isFull() const{
    return size == maxsize;
}

template<typename Dtype>
void Heap<Dtype>::heapifyFrom(size_t const start){
    size_t node = start;
    Dtype key = data[node];
    while(1){
        size_t index = node;
        Dtype max = key;

        /* use cmv instead if */
        /* get the max between key, left and right */
        size_t l = Heap::Left(node);
        l = l < size ? l : node;
        int cond1 = data[l] > max;
        index = cond1 ? l : index;
        max = cond1 ? data[l] : max;

        size_t r = Heap::Right(node);
        r = r < size ? r : node;
        int cond2 = data[r] > max;
        index = cond2 ? r : index;
        max = cond2 ? data[r] : max;

        if(index == node){
            /* heapify end */
            break;
        }

        /* only one write */
        data[node] = max;
        node = index;
    }
    /* the last write */
    data[node] = key;
}

template<typename Dtype>
void Heap<Dtype>::heapify(){
    size_t length = size;
    for(size_t i = length / 2; i > 0; i--){
        Heap::heapifyFrom(i - 1);
    }
}

template<typename Dtype>
void Heap<Dtype>::init(Dtype * const list, size_t const length){
    if(length > maxsize) throw std::invalid_argument("length should be less than maxsize");
    for(size_t i = 0; i < length; i++){
        data[i] = list[i];
    }
    size = length;
    Heap::heapify();
}

template<typename Dtype>
Dtype Heap<Dtype>::top() const{
    if(Heap::isEmpty()){
        throw std::underflow_error("Heap is empty");
    }
    return data[0];
}

template<typename Dtype>
void Heap<Dtype>::append(Dtype elem){
    if(Heap::isFull()){
        throw std::overflow_error("Heap is full");
    }
    size_t index = size;
    data[index] = elem;
    size++;

    while(index > 0 && data[Heap::Parent(index)] < elem){
        size_t parent = Heap::Parent(index);
        data[index] = data[parent];
        index = parent;
    }
    data[index] = elem;
}

template<typename Dtype>
Dtype Heap<Dtype>::pop(){
    if(Heap::isEmpty()){
        throw std::underflow_error("Heap is empty");
    }
    Dtype result = data[0];
    size--;
    data[0] = data[size];
    Heap::heapifyFrom(0);
    return result;
}

template<typename Dtype>
void Heap<Dtype>::display() const{
    if(Heap::isEmpty()){
        throw std::underflow_error("Heap is empty");
    }
    std::cout<<"Heap -> ";
    size_t end = size;
    for(size_t i = 0; i < end; i++){
        std::cout << data[i] << " -> ";
    }
    std::cout<<"End"<<std::endl;
}
