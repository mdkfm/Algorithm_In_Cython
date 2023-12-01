#include <stdio.h>
#include <malloc.h>
#include "../include/data.h"
#include "../include/link.h"

/* TODO: Refactor with link prefix and refactor other file */

Link* link_new(){
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

long unsigned link_initFromArray(Link * const this, Elem const * const list, long const length, int const reversed){
    /* construct a LinkList, based on list */
    /* length: the read length of list */
    /* reversed: 0 origin, 1 reversed */
    /* return the wrote length of list */
    if(length <= 0) return 0;

    LinkNode *s, *last = this->head; /* s tmp node */

    /* the start, end and step of the loop */
    long start = reversed ? length - 1 : 0;
    long end = reversed ? -1 : length;
    int step = reversed ? -1 : 1;

    long unsigned _length = 0;
    for (int i = start; i != end; i += step){
        s = (LinkNode *) malloc(sizeof(LinkNode));
        if(s == NULL) break;
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

int link_isEmpty(Link const * const this){
    return (this->head->next == this->tail);
}

long unsigned link_getLength(Link const * const this){
    return this->length;
}

long unsigned link_toArray(Link const * const this, Elem * const buf ,long unsigned const length){
    /* length: output the length */
    LinkNode const *p = this->head->next;
    long unsigned  max_length = link_getLength(this);
    max_length = max_length > length ? length : max_length;

    for(int i = 0; i < max_length; i++){
        buf[i] = p->data;
        p = p->next;
    }
    return max_length;
}

void link_display(Link const * const this){
    LinkNode const *p = this->head->next;
    long unsigned length = link_getLength(this);
    printf("Head");
    for(int i = 0; i < length; i++){
        /* where %ld is only used for int */
        printf(" -> %ld", p->data.num_int64);
        p = p->next;
    }
    printf("\n");
}

LinkNode *link_getNodeLeft(Link const * const this, long unsigned const index){
    /* The index begins from 0 */
    /* the 0 index is the head node */
    LinkNode *p = this->head;
    long unsigned length = link_getLength(this);
    if(index > length){
        return NULL;
    }
    for (int j = 0;j < index; j++){
        p = p->next;
    }
    return p;
}

LinkNode *link_getNodeRight(Link const * const this, long unsigned const index){
    /* The index begins from 0 */
    /* the 0 index is the tail node */
    LinkNode *p = this->tail;
    long unsigned length = link_getLength(this);
    if(index > length){
        return NULL;
    }
    for (int j = 0;j < index; j++){
        p = p->pre;
    }
    return p;
}

int link_getLeft(Link const * const this, long unsigned const index, Elem * const buf){
    /* The index begins from 0 */
    /* the 0 index is the head node */
    LinkNode *p = link_getNodeLeft(this, index);
    if(p == NULL){
        return 0;
    }
    *buf = p->data;
    return 1;
}

int link_getRight(Link const * const this, long unsigned const index, Elem * const buf){
    /* The index begins from 0 */
    /* the 0 index is the tail node */
    LinkNode *p = link_getNodeRight(this, index);
    if(p == NULL){
        return 0;
    }
    *buf = p->data;
    return 1;
}

int link_search(Link const * const this, Elem const element){
    int index = 1;
    LinkNode const *p = this->head->next;
    while( p != NULL && p->data.num_int64 != element.num_int64){
        p = p->next;
        index ++;
    }
    if(p->next == NULL){
        return 0;
    }
    return index;
}

long unsigned link_deleteAll(Link * const this, Elem const element){
    /* delete all the element */
    /* return the number of deleted element */
    LinkNode *p = this->head;
    long unsigned num = 0;
    while(p != NULL){
        LinkNode * target;
        while(p->next != NULL && p->next->data.num_int64 == element.num_int64){
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

int link_insertLeft(Link * const this, long unsigned const index, Elem const element){
    /* The index begins from 1 */
    LinkNode *p = link_getNodeLeft(this, index - 1);
    if(p == NULL){
        return 0;
    }
    LinkNode *s = link_newNode();
    if(s == NULL){
        return 0;
    }
    s->data = element;

    LinkNode *next = p->next;
    s->next = next;
    next->pre = s;
    p->next = s;
    s->pre = p;

    this->length ++;
    return 1;
}

int link_insertRight(Link * const this, long unsigned const index, Elem const element){
    /* The index begins from 1 */
    LinkNode *p = link_getNodeRight(this, index - 1);
    if(p == NULL){
        return 0;
    }
    LinkNode *s = link_newNode();
    if(s == NULL){
        return 0;
    }
    s->data = element;

    LinkNode *pre = p->pre;
    s->pre = pre;
    pre->next = s;
    p->pre = s;
    s->next = p;

    this->length ++;
    return 1;
}

int link_insertFirstLeft(Link * const this, Elem const element){
    LinkNode *s = link_newNode();
    if(s == NULL){
        return 0;
    }
    s->data = element;
    LinkNode *head = this->head, *next = head->next;
    s->next = next;
    next->pre = s;
    head->next = s;
    s->pre = head;

    this->length ++;
    return 1;
}

int link_insertFirstRight(Link * const this, Elem const element){
    LinkNode *s = link_newNode();
    if(s == NULL){
        return 0;
    }
    s->data = element;
    LinkNode *tail = this->tail, *pre = tail->pre;
    s->pre = pre;
    pre->next = s;
    tail->pre = s;
    s->next = tail;

    this->length ++;
    return 1;
}

int link_popLeft(Link * const this, Elem *const buf, long unsigned const index){
    /* The index begins from 1 */
    /* because the head node should not be pop */
    if(index < 1){
        return 0;
    }
    LinkNode *p = link_getNodeLeft(this, index - 1);
    if(p == NULL || p->next == NULL){
        return 0;
    }
    
    LinkNode *target = p->next, *next = target->next;
    *buf = target->data;
    p->next = next;
    next->pre = p;
    free(target);
    this->length --;
    return 1;
}

int link_popLeftFirst(Link * const this, Elem * const buf){
    if(link_isEmpty(this)){
        return 0;
    }
    LinkNode *head = this->head, *target = head->next, *next = target->next;
    *buf = target->data;
    head->next = next;
    next->pre = head;
    free(target);
    this->length --;
    return 1;
}

int link_popRight(Link * const this, Elem *const buf, long unsigned const index){
    /* The index begins from 1 */
    /* because the tail node should not be pop */
    if(index < 1){
        return 0;
    }
    LinkNode *p = link_getNodeRight(this, index - 1);
    if(p == NULL || p->pre == NULL){
        return 0;
    }

    LinkNode *target = p->pre, *pre = target->pre;
    *buf = target->data;
    p->pre = pre;
    pre->next = p;
    free(target);
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
    free(target);
    this->length --;
    return 1;
}

//LinkT const linkT = {
//    .new = newLink,
//    .initFromArray = initFromArrayLink,
//    .delete = deleteLink,
//    .isEmpty = isEmptyLink,
//    .getLength = getLengthLink,
//    .toArray = toArrayLink,
//    .display = displayLink,
//    .getLeft = getLeftLink,
//    .getRight = getRightLink,
//    .search = searchLink,
//    .deleteAll = deleteAllLink,
//    .insertLeft = insertLeftLink,
//    .insertRight = insertRightLink,
//    .insertFirstLeft = insertFirstLeftLink,
//    .insertFirstRight = insertFirstRightLink,
//    .popLeft = popLeftLink,
//    .popLeftFirst = popLeftFirstLink,
//    .popRight = popRightLink,
//    .popRightFirst = popRightFirstLink
//};