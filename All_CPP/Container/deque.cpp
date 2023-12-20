#include<iostream>
#include<stdexcept>

template<typename Dtype>
class Deque{
private:
    Dtype *data; /* one more space for judging full */
    size_t front, rear;
    size_t const realSize;
public:
    size_t size;
    size_t const maxsize;
    explicit Deque(size_t maxsize);
    ~Deque(){delete[] data;}
    [[nodiscard]] inline bool isEmpty() const;
    [[nodiscard]] inline bool isFull() const;
    void appendLeft(Dtype elem);
    void appendRight(Dtype elem);
    [[nodiscard]] Dtype popLeft();
    [[nodiscard]] Dtype popRight();
    [[nodiscard]] Dtype getLeft(size_t const index) const;
    [[nodiscard]] Dtype getRight(size_t const index) const;
    void display() const;
};

template<typename Dtype>
Deque<Dtype>::Deque(size_t maxsize): maxsize(maxsize), realSize(maxsize + 1){
    if(maxsize == 0) throw std::invalid_argument("maxsize should be positive");
    data = new Dtype[maxsize + 1];
    front = rear = 0;
    size = 0;
}

template<typename Dtype>
inline bool Deque<Dtype>::isEmpty() const{
    return size == 0;
}

template<typename Dtype>
inline bool Deque<Dtype>::isFull() const{
    return size == maxsize;
}

template<typename Dtype>
void Deque<Dtype>::appendLeft(Dtype elem){
    if(this->isFull()){
        /* append fail */
        throw std::overflow_error("Deque is full");
    }

    size_t index = (front + realSize - 1) % realSize;
    data[index] = elem;
    front = index;
    size++;
}

template<typename Dtype>
void Deque<Dtype>::appendRight(Dtype elem){
    if(this->isFull()){
        // append fail
        throw std::overflow_error("Deque is full");
    }
    size_t index = rear;
    data[index] = elem;
    rear = (index + 1) % realSize;
    size++;
}

template<typename Dtype>
Dtype Deque<Dtype>::popLeft(){
    if(this->isEmpty()){
        // pop fail
        throw std::underflow_error("Deque is empty");
    }
    size_t index = front;
    front = (index + 1) % realSize;
    size--;
    return data[index];
}

template<typename Dtype>
Dtype Deque<Dtype>::popRight(){
    if(this->isEmpty()){
        // pop fail
        throw std::underflow_error("Deque is empty");
    }
    size_t index = (rear + realSize - 1) % realSize;
    rear = index;
    size--;
    return data[index];
}

template<typename Dtype>
Dtype Deque<Dtype>::getLeft(size_t index) const{
    /* get elem from left */
    /* index from 0 to size - 1 */
    if(index >= size){
        // get fail
        throw std::invalid_argument("Invalid index");
    }

    return data[(front + index) % realSize];
}

template<typename Dtype>
Dtype Deque<Dtype>::getRight(size_t index) const{
    /* get elem from right */
    /* index from 0 to size - 1 */
    if(index >= size){
        // get fail
        throw std::invalid_argument("Invalid index");
    }

    return data[(rear + realSize - index - 1) % realSize];
}

template<typename Dtype>
void Deque<Dtype>::display() const{
    if(this->isEmpty()){
        throw std::underflow_error("Deque is empty");
    }
    std::cout<<"Left -> ";
    size_t end = size, mod = realSize;
    for(size_t i = 0, index = front; i < end; i++, index = (index + 1) % mod){
        std::cout << data[index] << " -> ";
    }
    std::cout<<"Right"<<std::endl;
}



/*int main() {
    Deque<int> deque(10);
    deque.appendLeft(1);
    deque.appendLeft(2);
    deque.appendLeft(3);
    deque.appendLeft(4);
    deque.appendLeft(5);
    deque.appendRight(6);
    deque.display();
    std::cout << deque.getRight(0) << std::endl;
    std::cout << deque.getLeft(0) << std::endl;
    std::cout << deque.popLeft() << std::endl;
    std::cout << deque.popRight() << std::endl;
}*/
