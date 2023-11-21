#include <stdio.h>
#include <stdlib.h>
#include "../include/data.h"

/* gcc ./All_C/List/LinkList.c -fPIC -shared -o ./lib/libLinkList.so */

typedef struct LNode{
    Elem data;
    struct LNode *next;
} LinkNode;

void deleteList(LinkNode *this);

LinkNode * createFromArray(Elem const * list, int const length, int const reversed){
    // construct a LinkList, based on list
    // length the read length of list
    // reversed: 0 origin, 1 reversed
    LinkNode *L, *s; // L the head node, s tmp node
    int i;
    L = (LinkNode *) malloc(sizeof(LinkNode));
    if(L == NULL){
        return NULL;
    }
    L->next = NULL;
    int begin = reversed ? 0 : length - 1;
    int end = reversed ? length : -1;
    int step = reversed ? 1 : -1;
    for (i = begin; i != end; i += step){
        s = (LinkNode *) malloc(sizeof(LinkNode));
        if(s == NULL)goto fail;
        s->data = list[i];
        s->next = L->next;
        L->next = s;
    }
    
    return L;
    fail:
        deleteList(L);
        return NULL;
}


LinkNode * newListNode(){
    LinkNode *L;
    L = (LinkNode *) malloc(sizeof(LinkNode));
    L->next = NULL;
    return L;
}

void deleteListNode(LinkNode *this){
    free(this);
}

void deleteList(LinkNode *this){
    LinkNode *p = this->next;
    while(p != NULL){
        this->next = p->next;
        free(p);
        p = this->next;
    }
    free(this);
}

int isEmpty(LinkNode const *this){
    return (this->next == NULL);
}

int getLength(LinkNode const *this){
    int length = 0;
    LinkNode const *p = this;
    while (p->next != NULL){
        length ++;
        p = p->next;
    }
    return length;
}

int toArray(LinkNode const * this, Elem *buf ,int length){
    /* length: output the length */
    LinkNode const *p = this->next;
    int  max_length = getLength(this);
    max_length = max_length > length ? length : max_length;

    for(int i = 0; i < max_length && p != NULL; i++){
        buf[i] = p->data;
        p = p->next;
    }
    return max_length;
}

void displayList(LinkNode const *this){
    LinkNode const *p = this->next;
    printf("Head");
    while(p != NULL){
        /* where %ld is only used for int */
        printf(" -> %ld", p->data.num_int64);
        p = p->next;
    }
    printf("\n");
}

LinkNode * getNode(LinkNode *this, int index){
    /* The index begins from 0 */
    /* the 0 index is the head node */
    LinkNode *p = this;
    if (index < 0){
        return NULL;
    }
    for (int j = 0;j < index && p != NULL; j++){
        p = p->next;
    }
    return p;
}

int getElement(LinkNode *L, Elem *buf, int index){
    LinkNode *node = getNode(L, index);
    if(node == NULL){
       return 0;
    }
    *buf = node->data;
    return 1;
}

int searchElement(LinkNode const *L, Elem element){
    int index = 1;
    LinkNode const *p = L->next;
    while( p != NULL && p->data.num_int64 != element.num_int64){
        p = p->next;
        index ++;
    }
    if(p->next == NULL){
        return 0;
    }
    return index;
}

int deleteAll(LinkNode *L, Elem element){
    LinkNode *p = L, *target;
    int num = 0;
    while(p != NULL){
        while(p->next != NULL && p->next->data.num_int64 == element.num_int64){
            target = p->next;
            p->next = target->next;
            free(target);
            num++;
        }
        p = p->next;
    }
    return num;
}

int insert(LinkNode *L, int index, Elem element){
    /* The index begins from 1 */
    LinkNode *p, *s;
    p = getNode(L, index - 1);
    if(p == NULL){
        return 0;
    }
    s = (LinkNode *) malloc(sizeof(LinkNode));
    if(s == NULL){
        return 0;
    }
    s->data = element;
    s->next = p->next;
    p->next = s;
    return 1;
}

int pop(LinkNode *L, Elem *buf,int index){
    /* The index begins from 1 */
    /* because the head node should not be pop */
    if(index < 1){
        return 0;
    }
    LinkNode *p, *target;
    p = getNode(L, index - 1);
    if(p == NULL || p->next == NULL){
        return 0;
    }
    
    target = p->next;
    *buf = target->data;
    p->next = target->next;
    free(target);
    return 1;
}