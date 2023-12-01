#include<malloc.h>

typedef struct adjMatrix{
    double * adj; // 0.0 for not connected
    size_t size;
    int weighted; // only positive weight
    int directed;
} adjMatrix;

adjMatrix *newAdjMatrix(size_t size, int weighted, int directed){
    if(size * size < size)
        // size_t overflow
        return NULL;

    adjMatrix *new = (adjMatrix *) malloc(sizeof(adjMatrix));
    if(new == NULL)
        return NULL;

    double *adj =  (double *) calloc(size * size, sizeof(double));
    if(adj == NULL){
        free(new);
        return NULL;
    }

    new->adj = adj;
    new->size = size;
    new->weighted = weighted;
    new->directed = directed;
    return new;
}

int invalid_check(adjMatrix * m, double source[m->size][m->size]){
    /* check if the matrix is valid */
    /* valid: 1, invalid: 0 */
    size_t size = m->size;
    int weighted = m->weighted, directed = m->directed;
    for(int i = 0; i < size; i++){
        if(source[i][i] != 0.0) return 0;
        for(int j = 0; j < size; j++){
            if(source[i][j] < 0.0) return 0;
            if(!weighted && source[i][j] != 0.0 && source[i][j] != 1.0) return 0;
        }
    }
    if(!directed){
        /* this test has a bad spatial locality */
        for(int i = 0; i < size; i++){
            for(int j = i; j < size; j++){
                if(source[i][j] != source[j][i]) return 1;
            }
        }
    }
    return 1;
}

int initAdjMatrix(adjMatrix * m, double source[m->size][m->size]){
    int i, j;
    if(invalid_check(m, source) == 0) return 0; /* if invalid, return 0 */
    for(i = 0; i < m->size; i++){
        for(j = 0; j < m->size; j++){
            m->adj[i * m->size + j] = source[i][j];
        }
    }
    return 1;
}

void deleteAdjMatrix(adjMatrix * m){
    free(m->adj);
    free(m);
}

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

/* TODO: Realize some graph algorithm */