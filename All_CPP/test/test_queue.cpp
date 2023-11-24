#include "../List/queue.cpp"


int main(){
    Queue<int> q(10);
    Queue<int> &refq = q;
    refq.appendLeft(1);
    refq.appendLeft(2);
    refq.appendLeft(3);
    refq.displayQueue();
    return 0;
}
