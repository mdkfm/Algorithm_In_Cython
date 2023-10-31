#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

// void exit(int status);

/* gcc LinkList.c -fPIC -shared -o libLinkList.so */

typedef struct LNode{
    int data;
    struct LNode *next;
}LinkNode;


LinkNode * CreateList(int * list, int length, int reversed){
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


LinkNode * InitList(){
    LinkNode *L;
    L = (LinkNode *) malloc(sizeof(LinkNode));
    L->next = NULL;
    return L;
}

void DestroyList(LinkNode *L){
    LinkNode *p = L->next;
    while(p != NULL){
        L->next = p->next;
        free(p);
        p = L->next;
    }
    free(L);
}

int IsEmpty(LinkNode *L){
    return (L->next == NULL);
}

int GetLength(LinkNode *L){
    int length = 0;
    LinkNode *p = L;
    while (p->next != NULL){
        length ++;
        p = p->next;
    }
    return length;
}

int * ToArray(LinkNode * L, int *length){
    /* length: output the length */
    LinkNode *p = L->next;
    int i = 0;
    int *list;
    list = (int *)malloc(*length * sizeof(int));
    *length = GetLength(L);
    while(p != NULL){
        list[i] = p->data;
        p = p->next;
        i++;
    }
    return list;
}

void DisplayList(LinkNode *L){
    LinkNode *p = L->next;
    printf("Head");
    while(p != NULL){
        printf(" -> %d", p->data);
        p = p->next;
    }
    printf("\n");
}

LinkNode * GetNode(LinkNode *L, int index){
    /* The index begins from 0 */
    int j = 0;
    LinkNode *p = L;
    if (index < 0){
        printf("IndexError: The index must >= 0, but the passed value is %d \n", index);
        exit(1);
    }
    while (j < index && p != NULL){
        j++;
        p = p->next;
    }
    if (p == NULL){
        printf("IndexError: The index exceeds the linked list. ");
        printf("The length of list is %d, but the index is %d. \n", j, index);
        exit(1);
    }
    else{
        return p;
    }
}

int GetElement(LinkNode *L, int index){
    if(index == 0){
        printf("IndexError: The head node has not data. \n");
        exit(1);
    }
    return (GetNode(L, index)->data);
}

int SearchELement(LinkNode *L, int element){
    int index = 1;
    LinkNode *p = L->next;
    while( p != NULL && p->data != element){
        p = p->next;
        index ++;
    }
    if(p->next == NULL){
        printf("SearchError: The element is not in list. \n");
        exit(1);
    }
    else{
        return index;
    }
}

int Delete_or_Insert(LinkNode *L, int element){
    int index = 1;
    LinkNode *p = L->next;
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
        p->next = p->next->next;
        printf("Searched and deleted");
    }
}

void DeleteAll(LinkNode *L, int element){
    LinkNode *p = L;
    while(p != NULL){
        while(p->next != NULL && p->next->data == element){
            p->next = p->next->next;
        }
        p = p->next;
    }
}

void Insert(LinkNode *L, int index, int element){
    /* The index begins from 1 */
    LinkNode *p, *s;
    p = GetNode(L, index - 1);
    s = (LinkNode *) malloc(sizeof(LinkNode));
    s->data = element;
    s->next = p->next;
    p->next = s;
}

int ListPop(LinkNode *L, int index){
    int output;
    LinkNode *p;
    p = GetNode(L, index - 1);
    if(p->next == NULL){
        printf("IndexError: The index exceeds the linked list. \n");
        exit(1);
    }
    else{
        output = p->next->data;
        p->next = p->next->next;
        return output;
    }
}

int * CharToInt(char * s, int length){
    int * list;
    int i;
    list = (int *)malloc((length + 10) * sizeof(int));
    for(i = 0; i < length; i++){
        list[i] = s[i];
    }
    return list;
}

char * IntToChar(int *list, int length){
    char * s;
    int i;
    s = (char *)malloc((length + 10) * sizeof(char));
    for(i = 0; i < length; i++){
        s[i] = list[i];
    }
    s[length] = '\0';
    return s;
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