//
// Created by skf on 23-12-4.
//

#include <stdlib.h>

/* TODO : refactor orthList */

/* orthogonal list */
typedef struct edgeNode {
    long end0;
    long end1;
    double weight;
    struct edgeNode * tlink; /* same end0 */
    struct edgeNode * hlink; /* same end1 */
} edgeNode;

typedef struct dotNode{
    long data;
    edgeNode * in; /* end */
    edgeNode * out; /* source */
} dotNode;

typedef struct orthList {
    dotNode * list;
    size_t size;
    int weighted; /* tag */
    int directed; /* tag */
} orthList;

edgeNode * newEdgeNode(long end0, long end1, long weight){
    edgeNode * new = (edgeNode *) malloc(sizeof(edgeNode));
    if(new == NULL)
        return NULL;

    new->end0 = end0;
    new->end1 = end1;
    new->weight = weight;
    return new;
}

void deleteEdgeNode(edgeNode * node){
    free(node);
}

orthList* newOrthList(size_t size, int weighted, int directed){
    orthList * new = (orthList *) malloc(sizeof(orthList));
    if(new == NULL)
        return NULL;

    dotNode * list = (dotNode *) calloc(size, sizeof(dotNode));
    if(list == NULL){
        free(new);
        return NULL;
    }
    new->list = list;
    new->size = size;
    new->weighted = weighted;
    new->directed = directed;
    return new;
}

void deleteOrthList(orthList *orth){
    int size = orth->size, i;
    /* deleting orthList is equal to the all graph */
    /* so we should delete all edgeNodes at first */
    for(i = 0; i < size; i++){
        edgeNode * node = orth->list->out;
        while(node != NULL){
            edgeNode * tmp = node;
            node = node->hlink;
            deleteEdgeNode(tmp);
        }
    }

    free(orth->list);
    free(orth);
}