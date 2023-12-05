#include <stdio.h>
#include <malloc.h>

#include "../include/link.h"

__malloc Link* link_new(){
    Link *link = (Link*)malloc(sizeof(Link));
    if(link == NULL) return NULL;

    link->head = (LinkNode*)malloc(sizeof(LinkNode));
    if(link->head == NULL){
        free(link);
        return NULL;
    }

    link->tail = (LinkNode*)malloc(sizeof(LinkNode));
    if(link->tail == NULL){
        free(link->head);
        free(link);
        return NULL;
    }
    link->head->next = link->tail;
    link->tail->pre = link->head;
    link->length = 0;
    return link;
}

size_t link_appendList(Link * const this, Elem const * const list, size_t const length, int const reversed){
    /* construct a LinkList, based on list */
    /* length: the read length of list */
    /* reversed: 0 origin, 1 reversed */

    /* no error: return the wrote length of list
     * length error: return 0 */

    if(length == 0) return 0;

    /* the start, end and step of the loop */
    long start = reversed ? length - 1 : 0;
    long end = reversed ? -1 : length;
    int step = reversed ? -1 : 1;

    size_t _length = 0;
    LinkNode *last = this->tail->pre;
    for (int i = start; i != end; i += step){
        LinkNode *s = (LinkNode *) malloc(sizeof(LinkNode));
        if(unlikely(s == NULL)) break;
        _length ++;
        s->data = list[i];
        last->next = s;
        s->pre = last;
        last = s;
    }

    LinkNode *tail = this->tail;
    last->next = tail;
    tail->pre = last;
    this->length = _length;
    return _length;
}

LinkNode * link_newNode(){
    LinkNode *new = (LinkNode *) malloc(sizeof(LinkNode));
    if(new == NULL) return NULL;
    new->data.num_int64 = 0;
    new->pre = NULL;
    new->next = NULL;
    return new;
}

void link_deleteNode(LinkNode *this){
    free(this);
}

void link_delete(Link *this){
    LinkNode *head = this->head,*p = head->next;
    while(p != NULL){
        head->next = p->next;
        free(p);
        p = head->next;
    }
    free(head);
    free(this);
}


size_t link_toArray(Link const * const this, Elem * const buf ,size_t const length){
    /* length: output the length */
    LinkNode const *p = this->head->next;
    size_t  max_length = link_length(this);
    max_length = max_length > length ? length : max_length;

    for(int i = 0; i < max_length; i++){
        buf[i] = p->data;
        p = p->next;
    }
    return max_length;
}

void link_display(Link const * const this){
    LinkNode const *p = this->head->next;
    size_t length = link_length(this);
    printf("Head");
    for(int i = 0; i < length; i++){
        /* where %ld is only used for int */
        printf(" -> %ld", p->data.num_int64);
        p = p->next;
    }
    printf("\n");
}

LinkNode *link_getNodeLeft(Link const * const this, size_t const index){
    /* The index begins from 0 */
    /* the 0 index is the head node */
    LinkNode *p = this->head;
    size_t length = link_length(this);
    if(index > length){
        return NULL;
    }
    for (int j = 0;j < index; j++){
        p = p->next;
    }
    return p;
}

LinkNode *link_getNodeRight(Link const * const this, size_t const index){
    /* The index begins from 0 */
    /* the 0 index is the tail node */
    LinkNode *p = this->tail;
    size_t length = link_length(this);
    if(index > length){
        return NULL;
    }
    for (int j = 0;j < index; j++){
        p = p->pre;
    }
    return p;
}

int link_getLeft(Link const * const this, size_t const index, Elem * const buf){
    /* The index begins from 0 */
    /* the 0 index is the head node */

    /* no error: return 0
     * index error: return -1 */

    LinkNode *p = link_getNodeLeft(this, index);
    if(p == NULL){
        return -1;
    }
    *buf = p->data;
    return 0;
}

int link_getRight(Link const * const this, size_t const index, Elem * const buf){
    /* The index begins from 0 */
    /* the 0 index is the tail node */

    /* no error: return 0
     * index error: return -1 */
    LinkNode *p = link_getNodeRight(this, index);
    if(p == NULL){
        return -1;
    }
    *buf = p->data;
    return 0;
}

int link_search(Link const * const this, Elem const element){
    int index = 1;
    LinkNode const * p = this->head->next;
    LinkNode const*const end = this->tail;
    while(p != end && p->data.num_int64 != element.num_int64){
        p = p->next;
        index ++;
    }
    if(p->next == NULL){
        return -1;
    }
    return index;
}

size_t link_deleteAll(Link * const this, Elem const element){
    /* delete all the element */
    /* return the number of deleted element */
    LinkNode *p = this->head;
    LinkNode const*const end = this->tail;
    size_t num = 0;
    while(p != end){
        LinkNode * target;
        while(p->next != end && p->next->data.num_int64 == element.num_int64){
            target = p->next;
            p->next = target->next;
            free(target);
            num++;
        }
        p = p->next;
    }
    this->length -= num;
    return num;
}

int link_insertLeft(Link * const this, size_t const index, Elem const element){
    /* The index begins from 1 */

    /* no error: return 0
     * index error: return -1
     * malloc fail: return -2 */

    LinkNode *p = link_getNodeLeft(this, index - 1);
    if(p == NULL){
        return -1;
    }
    LinkNode *s = link_newNode();
    if(s == NULL){
        return -2;
    }
    s->data = element;

    LinkNode *next = p->next;
    s->next = next;
    next->pre = s;
    p->next = s;
    s->pre = p;

    this->length++;
    return 0;
}

int link_insertRight(Link * const this, size_t const index, Elem const element){
    /* The index begins from 1 */

    /* no error: return 0
     * index error: return -1
     * malloc fail: return -2 */

    LinkNode *p = link_getNodeRight(this, index - 1);
    if(p == NULL){
        return -1;
    }
    LinkNode *s = link_newNode();
    if(s == NULL){
        return -2;
    }
    s->data = element;

    LinkNode *pre = p->pre;
    s->pre = pre;
    pre->next = s;
    p->pre = s;
    s->next = p;

    this->length ++;
    return 0;
}

int link_insertFirstLeft(Link * const this, Elem const element){
    /* no error: return 0
     * malloc fail: return -1 */

    LinkNode *s = link_newNode();
    if(s == NULL){
        return -1;
    }
    s->data = element;
    LinkNode *head = this->head, *next = head->next;
    s->next = next;
    next->pre = s;
    head->next = s;
    s->pre = head;

    this->length ++;
    return 0;
}

int link_insertFirstRight(Link * const this, Elem const element){
    /* no error: return 0
     * malloc fail: return -1 */

    LinkNode *s = link_newNode();
    if(s == NULL){
        return -1;
    }
    s->data = element;
    LinkNode *tail = this->tail, *pre = tail->pre;
    s->pre = pre;
    pre->next = s;
    tail->pre = s;
    s->next = tail;

    this->length ++;
    return 0;
}


int link_popLeft(Link * const this, Elem *const buf, size_t const index){
    /* The index begins from 1 */
    /* because the head node should not be pop */

    /* no error: return 0
     * index error: return -1 */

    size_t length = link_length(this);
    if(index < 1 || index > length){
        return -1;
    }

    LinkNode *p = link_getNodeLeft(this, index);
    *buf = p->data;

    LinkNode *pre = p->pre, *next = p->next;
    pre->next = next;
    next->pre = pre;
    link_deleteNode(p);
    this->length --;
    return 0;
}

int link_popLeftFirst(Link * const this, Elem * const buf){
    /* no error: return 0
     * link empty: return -1 */
    if(link_isEmpty(this)){
        return -1;
    }
    LinkNode *head = this->head, *target = head->next, *next = target->next;
    *buf = target->data;

    head->next = next;
    next->pre = head;
    link_deleteNode(target);
    this->length --;
    return 0;
}

int link_popRight(Link * const this, Elem *const buf, size_t const index){
    /* The index begins from 1 */
    /* because the tail node should not be pop */

    /* no error: return 0
     * index error: return -1 */
    size_t length = link_length(this);
    if(index < 1 || index > length){
        return -1;
    }

    LinkNode *p = link_getNodeRight(this, index);
    *buf = p->data;

    LinkNode *pre = p->pre, *next = p->next;
    pre->next = next;
    next->pre = pre;
    link_deleteNode(p);
    this->length --;
    return 1;
}

int link_popRightFirst(Link * const this, Elem * const buf){
    if(link_isEmpty(this)){
        return 0;
    }
    LinkNode *tail = this->tail, *target = tail->pre, *pre = target->pre;
    *buf = target->data;

    tail->pre = pre;
    pre->next = tail;
    link_deleteNode(target);
    this->length --;
    return 1;
}