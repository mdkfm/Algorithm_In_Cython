#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

/* gcc LinkList.c -fPIC -shared -o libLinkList.so */

typedef int Elemtype;

typedef struct LNode{
    Elemtype data;
    struct LNode *next;
} LinkNode;


LinkNode * createFromArray(Elemtype * list, int length, int reversed){
    // construct a LinkList, based on list
    // length the read length of list
    // reversed: 0 origin, 1 reversed
    LinkNode *L, *s; // L the head node, s tmp node
    L = (LinkNode *) malloc(sizeof(LinkNode));
    L->next = NULL;
    
    if(reversed){
        for (int i = 0; i < length; i ++){
                s = (LinkNode *) malloc(sizeof(LinkNode));
                s->data = list[i];
                s->next = L->next;
                L->next = s;
            }
    }
    else{
        for (int i = length - 1; i >= 0; i --){
                s = (LinkNode *) malloc(sizeof(LinkNode));
                s->data = list[i];
                s->next = L->next;
                L->next = s;
            }
    }
    
    return L;
}


LinkNode * newList(){
    LinkNode *L;
    L = (LinkNode *) malloc(sizeof(LinkNode));
    L->next = NULL;
    return L;
}

void destroyList(LinkNode *L){
    LinkNode *p = L->next;
    while(p != NULL){
        L->next = p->next;
        free(p);
        p = L->next;
    }
    free(L);
}

int isEmpty(LinkNode *L){
    return (L->next == NULL);
}

int getLength(LinkNode *L){
    int length = 0;
    LinkNode *p = L;
    while (p->next != NULL){
        length ++;
        p = p->next;
    }
    return length;
}

int * toArray(LinkNode * L, int length){
    /* length: output the length */
    LinkNode *p = L->next;
    int i = 0;
    int *list;
    int max_length;
    if(length > (max_length = getLength(L))){
        lenght = max_length;
    }
    list = (int *)malloc(length * sizeof(int));
    while(p != NULL){
        list[i] = p->data;
        p = p->next;
        i++;
    }
    return list;
}

void displayList(LinkNode *L){
    LinkNode *p = L->next;
    printf("Head");
    while(p != NULL){
        /* where %d is only used for int */
        printf(" -> %d", p->data);
        p = p->next;
    }
    printf("\n");
}

LinkNode * getNode(LinkNode *L, int index){
    /* The index begins from 0 */
    int j = 0;
    LinkNode *p = L;
    if (index < 0){
        return NULL;
    }
    while (j < index && p != NULL){
        j++;
        p = p->next;
    }
    return p;
}

Elemtype getElement(LinkNode *L, int index){
    LinkNode *node = getNode(L, index);
    if(node == NULL){
       return NULL;
    }
    return node->data;
}

int searchELement(LinkNode *L, Elemtype element){
    int index = 1;
    LinkNode *p = L->next;
    while( p != NULL && p->data != element){
        p = p->next;
        index ++;
    }
    if(p->next == NULL){
        return NULL;
    }
    return index;
}

void delete_or_Insert(LinkNode *L, Elemtype element){
    int index = 1;
    LinkNode *p = L->next, *target;
    while( p != NULL && p->data != element){
        p = p->next;
        index ++;
    }
    if(p->next == NULL){
        p->next = (LinkNode *)malloc(sizeof(LinkNode));
        p->next->data = element;
        printf("Not searched and inserted!");
    }
    else{
        /* free*/
        target = p->next;
        p->next = target->next;
        /* after deleted from List, we should free it */
        free(target);
        printf("Searched and deleted");
    }
}

void deleteAll(LinkNode *L, Elemtype element){
    LinkNode *p = L, *target;
    while(p != NULL){
        while(p->next != NULL && p->next->data == element){
            target = p->next
            p->next = target->next;
            free(target);
        }
        p = p->next;
    }
}

void insert(LinkNode *L, int index, Elemtype element){
    /* The index begins from 1 */
    LinkNode *p, *s;
    p = getNode(L, index - 1);
    s = (LinkNode *) malloc(sizeof(LinkNode));
    s->data = element;
    s->next = p->next;
    p->next = s;
}

Elemtype pop(LinkNode *L, int index){
    int output;
    LinkNode *p;
    p = getNode(L, index - 1);
    if(p == NULL || p->next == NULL){
        return NULL;
    }
    output = p->next->data;
    p->next = p->next->next;
    return output;
}


// int main(){
//     int a[10] = {0, 1, 2, 3, 4, 5, 5, 7, 8, 5}, length;
//     int *b;
//     LinkNode *L, *L2;
//     L = CreateList(a, 10, 0);
//     DisplayList(L);
//     b = ToArray(L, &length);
//     DestroyList(L);
//     L2 = CreateList(b, 10, 0);
//     DeleteAll(L2, 5);
//     DisplayList(L2);
// }