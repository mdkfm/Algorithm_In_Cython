typedef long int Elemtype;

typedef struct LNode{
    Elemtype data;
    struct LNode *next;
} LinkNode;

LinkNode * createFromArray(Elemtype * list, int length, int reversed);

LinkNode * newList();

void destroyList(LinkNode *L);

int isEmpty(LinkNode *L);

int getLength(LinkNode *L);

Elemtype * toArray(LinkNode * L, int length);

void displayList(LinkNode *L);

LinkNode * getNode(LinkNode *L, int index);

Elemtype getElement(LinkNode *L, int index);

int searchELement(LinkNode *L, Elemtype element);

void delete_or_Insert(LinkNode *L, Elemtype element);

void deleteAll(LinkNode *L, Elemtype element);

void insert(LinkNode *L, int index, Elemtype element);

Elemtype pop(LinkNode *L, int index);
