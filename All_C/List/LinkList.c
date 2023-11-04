#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

/* gcc ./All_C/List/LinkList.c -fPIC -shared -o ./lib/libLinkList.so */

typedef long int Elemtype;

typedef struct LNode{
    Elemtype data;
    struct LNode *next;
} LinkNode;


LinkNode * createFromArray(Elemtype * list, int length, int reversed){
    // construct a LinkList, based on list
    // length the read length of list
    // reversed: 0 origin, 1 reversed
    LinkNode *L, *s; // L the head node, s tmp node
    int i;
    L = (LinkNode *) malloc(sizeof(LinkNode));
    L->next = NULL;
    
    if(reversed){
        for (i = 0; i < length; i ++){
                s = (LinkNode *) malloc(sizeof(LinkNode));
                s->data = list[i];
                s->next = L->next;
                L->next = s;
            }
    }
    else{
        for (i = length - 1; i >= 0; i --){
                s = (LinkNode *) malloc(sizeof(LinkNode));
                s->data = list[i];
                s->next = L->next;
                L->next = s;
            }
    }
    
    return L;
}


LinkNode * newListNode(){
    LinkNode *L;
    L = (LinkNode *) malloc(sizeof(LinkNode));
    L->next = NULL;
    return L;
}

void * deleteListNode(LinkNode *L){
    free(L);
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

Elemtype * toArray(LinkNode * L, int length){
    /* length: output the length */
    LinkNode *p = L->next;
    int i = 0;
    Elemtype *list;
    int max_length;
    if(length > (max_length = getLength(L))){
        length = max_length;
    }
    list = (Elemtype*)malloc(length * sizeof(Elemtype));
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
        /* where %ld is only used for int */
        printf(" -> %ld", p->data);
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
       return 0;
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
        return 0;
    }
    return index;
}

void delete_or_Insert(LinkNode *L, Elemtype element){

    LinkNode *p = L, *target;
    while( p->next != NULL && p->next->data != element){
        p = p->next;
    }
    if(p->next == NULL){
        p->next = (LinkNode *)malloc(sizeof(LinkNode));
        p->next->data = element;
        p->next->next = NULL;
        printf("Not searched and inserted!\n");
    }
    else{
        target = p->next;
        p->next = target->next;
        /* after deleted from List, we should free it */
        free(target);
        printf("Searched and deleted\n");
    }
}

void deleteAll(LinkNode *L, Elemtype element){
    LinkNode *p = L, *target;
    while(p != NULL){
        while(p->next != NULL && p->next->data == element){
            target = p->next;
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
    LinkNode *p, *target;
    p = getNode(L, index - 1);
    if(p == NULL || p->next == NULL){
        return 0;
    }
    
    target = p->next;
    output = target->data;
    p->next = target->next;
    free(target);
    return output;
}

// int main(){
//     Elemtype a[10] = {0, 1, 2, 3, 4, 5, 5, 5, 7, 8};
//     LinkNode *L;
//     L = createFromArray(a, 10, 0);
//     delete_or_Insert(L, 8);
//     delete_or_Insert(L, 10);
//     displayList(L);
// }
