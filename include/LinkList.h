#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

// void exit(int status);

typedef struct LNode{
    int data;
    struct LNode *next;
}LinkNode;

LinkNode * CreateList(int * list, int length, int reversed);

LinkNode * InitList();

void DestroyList(LinkNode *L);

int IsEmpty(LinkNode *L);

int GetLength(LinkNode *L);

int * ToArray(LinkNode *L, int *length);

void DisplayList(LinkNode *L);

LinkNode * GetNode(LinkNode *L, int index);

int GetElement(LinkNode *L, int index);

int SearchELement(LinkNode *L, int element);

void DeleteAll(LinkNode *L, int element);

void Insert(LinkNode *L, int index, int element);

int ListPop(LinkNode *L, int index);

int * CharToInt(char * s, int length);

char * IntToChar(int *list, int length);
