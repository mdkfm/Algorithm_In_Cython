typedef long int QElem;

// use the SqList to realize a simple and effective deque with fixed length

typedef struct{
   QElem *data;
   int front, rear;
   int maxsize;
} Queue;

Queue *newQueue(int maxsize);

int isEmpty(Queue *q);

int isFull(Queue *q);

int appendLeft(Queue *q, QElem elem);

int appendRight(Queue *q, QElem elem);

QElem popLeft(Queue *q);

QElem popRight(Queue *q);

QElem getLeft(Queue *q, int index);

QElem getRight(Queue *q, int index);

void displayQueue(Queue *q);