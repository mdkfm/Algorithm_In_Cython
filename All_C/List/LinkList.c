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


LinkNode* mergeOrder(LinkNode *L1, LinkNode *L2){
    LinkNode *p1 = L1->next;
    LinkNode *p2 = L2->next;
    LinkNode *mergedList = newListNode();
    LinkNode *p = mergedList;
    
    while(p1 != NULL && p2 != NULL){
        if(p1->data <= p2->data){
            p->next = p1;
            p1 = p1->next;
        }
        else{
            p->next = p2;
            p2 = p2->next;
        }
        p = p->next;
    }
    
    if(p1 != NULL){
        p->next = p1;
    }
    else{
        p->next = p2;
    }
    
    return mergedList;
}

LinkNode* deleteLastN(LinkNode *L, int n){
    LinkNode *p = L;
    LinkNode *q = L;
    int count = 0;
    
    while(count < n && q->next != NULL){
        q = q->next;
        count++;
    }
    
    if(count < n){
        return L;
    }
    
    while(q->next != NULL){
        p = p->next;
        q = q->next;
    }
    
    LinkNode *temp = p->next;
    p->next = p->next->next;
    deleteListNode(temp);
    return L;
}

LinkNode* _reversedK(LinkNode *L, int k){
    LinkNode *current = L;
    LinkNode *end = getNode(L, k-1);
    if(end == NULL){
        return L;
    }
    LinkNode *prev = NULL;
    LinkNode *next = NULL;
    int count = 0;
        
    // Reverse the next k nodes excluding L
    while(current != NULL && count < k){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }
        
    // Connect the reversed part with the remaining list
    if(next != NULL){
        L->next = _reversedK(next, k);
    }
        
    // Return the new head of the reversed list
    return prev;
}

void reversedK(LinkNode *L, int k){
    // reverse k nodes by k nodes
    L->next = _reversedK(L->next, k);
}

// int main(){
//     Elemtype a[12] = {0, 1, 2, 3, 4, 5, 5, 5, 7, 8, 9, 11};
//     LinkNode *L1;
//     L1 = createFromArray(a, 12, 0);
//     printf("L1: ");
//     displayList(L1);

//     Elemtype b[8] = {3, 4, 6, 7, 8, 10, 11, 45};
//     LinkNode *L2;
//     L2 = createFromArray(b, 8, 0);
//     printf("L2: ");
//     displayList(L2);

//     LinkNode *merged = mergeOrder(L1, L2);
//     printf("Merged: ");
//     displayList(merged);

//     reversedK(L1, 4);
//     printf("Reversed L1: ");
//     displayList(L1);

//     deleteLastN(L1, 4);
//     printf("Deleted last 4th node: \n");
//     displayList(L1);

//     deleteLastN(L1, 33);
//     printf("Deleted last 33th node: \n");
//     displayList(L1);
// }
