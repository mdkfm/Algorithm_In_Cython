#include <stdio.h>
#include <stdlib.h>
#include "../include/data.h"

/* gcc ./All_C/List/LinkList.c -fPIC -shared -o ./lib/libLinkList.so */

typedef struct LNode{
    Elem data;
    struct LNode *next;
} LinkNode;

void deleteList(LinkNode *this);

LinkNode * createFromArray(Elem const * list, int const length, int const reversed);

LinkNode * newListNode();

void deleteListNode(LinkNode *this);

void deleteList(LinkNode *this);

int isEmpty(LinkNode const *this);

int getLength(LinkNode const *this);

int toArray(LinkNode const * this, Elem *buf ,int length);

void displayList(LinkNode const *this);

LinkNode * getNode(LinkNode *this, int index);

int getElement(LinkNode *L, Elem *buf, int index);

int searchElement(LinkNode const *L, Elem element);

int deleteAll(LinkNode *L, Elem element);

int insert(LinkNode *L, int index, Elem element);

int pop(LinkNode *L, Elem *buf,int index);