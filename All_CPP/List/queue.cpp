#include<iostream>
#include<stdexcept>

template<class QElem>
class Queue{
private:
    QElem *data; /* one more space for judging full */
    long unsigned front, rear;
public:
    long unsigned const maxsize;
    Queue(long unsigned maxsize);
    bool isEmpty() const;
    bool isFull() const;
    long unsigned size() const;
    void appendLeft(QElem elem);
    void appendRight(QElem elem);
    QElem popLeft();
    QElem popRight();
    QElem getLeft(long unsigned index) const;
    QElem getRight(long unsigned index) const;
    void displayQueue() const;
};

template<class QElem>
Queue<QElem>::Queue(long unsigned maxsize): maxsize(maxsize){
    if(maxsize <= 0) throw std::invalid_argument("maxsize should be positive");
    data = new QElem[maxsize + 1];
    front = rear = 0;
}

template<class QElem>
bool Queue<QElem>::isEmpty() const{
    /* no elem, empty */
    return front == rear;
}

template<class QElem>
long unsigned Queue<QElem>::size() const{
    /* size = (rear - front + maxsize + 1) % maxsize */
    return (rear + maxsize + 1 - front) % (maxsize + 1);
}

template<class QElem>
bool Queue<QElem>::isFull() const{
    /* if the num of elem using namespace std;is maxsize - 1, full */
    return ((rear + 1) % (maxsize + 1)) == front;
}

template<class QElem>
void Queue<QElem>::appendLeft(QElem elem){
    if(this->isFull()){
        /* append fail */
        throw std::overflow_error("Queue is full");
    }
    long unsigned index = front == 0 ? maxsize : front - 1;
    data[index] = elem;
    front = index;
}

template<class QElem>
void Queue<QElem>::appendRight(QElem elem){
    if(this->isFull()){
        // append fail
        throw std::overflow_error("Queue is full");
    }

    data[rear] = elem;
    rear = (rear + 1) % (maxsize + 1);
}

template<class QElem>
QElem Queue<QElem>::popLeft(){
    if(this->isEmpty()){
        // pop fail
        throw std::underflow_error("Queue is empty");
    }
    QElem output = data[front];
    front = (front + 1) % (maxsize + 1);
    return output;
}

template<class QElem>
QElem Queue<QElem>::popRight(){
    if(this->isEmpty()){
        // pop fail
        throw std::underflow_error("Queue is empty");
    }
    long unsigned index = rear == 0 ? maxsize : rear - 1;
    rear = index;
    return data[index];
}

template<class QElem>
QElem Queue<QElem>::getLeft(long unsigned index) const{
    /* get elem from left */
    /* index from 0 to (q->rear - q->front -1) % q->maxsize */
    int get_index = (front + index) % (maxsize + 1);
    if(get_index >= rear){
        // get fail
        throw std::invalid_argument("Invalid index");
    }
    return data[get_index];
}

template<class QElem>
QElem Queue<QElem>::getRight(long unsigned index) const{
    /* get elem from right */
    /* index from 0 to (q->rear - q->front -1) % q->maxsize */
    long unsigned get_index = rear > index ? rear - index - 1 : (maxsize + rear) - index;
    if(get_index < front){
        /* get fail */
        throw std::invalid_argument("Invalid index");
    }
    return data[get_index];
}

template<class QElem>
void Queue<QElem>::displayQueue() const{
    if(this->isEmpty()){
        throw std::underflow_error("Queue is empty");
    }
    std::cout<<"Left -> ";
    long unsigned end = rear, mod = maxsize + 1;
    for(long unsigned i = front; i != end; i = (i + 1) % mod){
        std::cout << data[i] << " -> ";
    }
    std::cout<<"Right"<<std::endl;
}
