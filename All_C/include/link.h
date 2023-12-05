#ifndef ALL_C_LINK_LIST_H
#define ALL_C_LINK_LIST_H
#include "data.h"
#include "gnuc.h"

typedef struct LinkNode{
    struct LinkNode *pre;
    struct LinkNode *next;
    Elem data;
} LinkNode;

typedef struct Link{
    LinkNode *head;
    LinkNode *tail;
    size_t length;
} Link;

__malloc Link* link_new();
size_t link_appendList(Link * const this, Elem const * const list, size_t const length, int const reversed);
void link_delete(Link *this);

/* $Begin static inline */
static inline int link_isEmpty(Link const * const this){
    return (this->head->next == this->tail);
}
static inline size_t link_length(Link const * const this){
    return this->length;
}
/* $End static inline */

size_t link_toArray(Link const * const this, Elem * const buf ,size_t const length);
void link_display(Link const * const this);
int link_getLeft(Link const * const this, size_t const index, Elem * const buf);
int link_getRight(Link const * const this, size_t const index, Elem * const buf);
int link_search(Link const * const this, Elem const element);
size_t link_deleteAll(Link * const this, Elem const element);
int link_insertLeft(Link * const this, size_t const index, Elem const element);
int link_insertRight(Link * const this, size_t const index, Elem const element);
int link_insertFirstLeft(Link * const this, Elem const element);
int link_insertFirstRight(Link * const this, Elem const element);
int link_popLeft(Link * const this, Elem *const buf, size_t const index);
int link_popLeftFirst(Link * const this, Elem * const buf);
int link_popRight(Link * const this, Elem *const buf, size_t const index);
int link_popRightFirst(Link * const this, Elem * const buf);
#endif /* ALL_C_LINK_LIST_H */