#include "../include/data.h"

#ifndef ALL_C_LINK_LIST_H
#define ALL_C_LINK_LIST_H

typedef struct LNode{
    Elem data;
    struct LNode *pre;
    struct LNode *next;
} LinkNode;

typedef struct Link{
    LinkNode *head;
    LinkNode *tail;
    long unsigned length;
} Link;

Link* link_new();
long unsigned link_initFromArray(Link * const this, Elem const * const list, long const length, int const reversed);
void link_delete(Link *this);
int link_isEmpty(Link const * const this);
long unsigned link_getLength(Link const * const this);
long unsigned link_toArray(Link const * const this, Elem * const buf ,long unsigned const length);
void link_display(Link const * const this);
LinkNode *link_getNodeLeft(Link const * const this, long unsigned const index);
LinkNode *link_getNodeRight(Link const * const this, long unsigned const index);
int link_getLeft(Link const * const this, long unsigned const index, Elem * const buf);
int link_getRight(Link const * const this, long unsigned const index, Elem * const buf);
int link_search(Link const * const this, Elem const element);
long unsigned link_deleteAll(Link * const this, Elem const element);
int link_insertLeft(Link * const this, long unsigned const index, Elem const element);
int link_insertRight(Link * const this, long unsigned const index, Elem const element);
int link_insertFirstLeft(Link * const this, Elem const element);
int link_insertFirstRight(Link * const this, Elem const element);
int link_popLeft(Link * const this, Elem *const buf, long unsigned const index);
int link_popLeftFirst(Link * const this, Elem * const buf);
int link_popRight(Link * const this, Elem *const buf, long unsigned const index);
int link_popRightFirst(Link * const this, Elem * const buf);

//typedef struct{
//    Link* (*new)();
//    long unsigned (*initFromArray)(Link * const this, Elem const * const list, long const length, int const reversed);
//    void (*delete)(Link *this);
//    int (*isEmpty)(Link const * const this);
//    long unsigned (*getLength)(Link const * const this);
//    long unsigned (*toArray)(Link const * const this, Elem * const buf ,long unsigned const length);
//    void (*display)(Link const * const this);
//    int (*getLeft)(Link const * const this, long unsigned const index, Elem * const buf);
//    int (*getRight)(Link const * const this, long unsigned const index, Elem * const buf);
//    int (*search)(Link const * const this, Elem const element);
//    long unsigned (*deleteAll)(Link * const this, Elem const element);
//    int (*insertLeft)(Link * const this, long unsigned const index, Elem const element);
//    int (*insertRight)(Link * const this, long unsigned const index, Elem const element);
//    int (*insertFirstLeft)(Link * const this, Elem const element);
//    int (*insertFirstRight)(Link * const this, Elem const element);
//    int (*popLeft)(Link * const this, Elem *const buf, long unsigned const index);
//    int (*popLeftFirst)(Link * const this, Elem * const buf);
//    int (*popRight)(Link * const this, Elem *const buf, long unsigned const index);
//    int (*popRightFirst)(Link * const this, Elem * const buf);
//} LinkT;
//
//extern LinkT const linkT;

#endif /* ALL_C_LINK_LIST_H */