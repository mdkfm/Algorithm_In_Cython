#include<malloc.h>
#include<stdio.h>

#define INF 1e400

typedef enum Dtype {INT64, FLOAT64} Dtype;

/* adjacent matrix */
typedef union MElem{
    double num_float64;
    long num_int64;
} MElem;

/* realize my matrix */
typedef struct Matrix{
    MElem * data;
    size_t row;
    size_t column;
    Dtype dtype;
} Matrix;


Matrix * newMatrix(size_t row, size_t column, Dtype dtype){
    if(row * column < row){
        // size_t overflow 
        return NULL;
    }

    Matrix * new = (Matrix *) malloc(sizeof(Matrix));
    if(new == NULL)
        return NULL;
    
    MElem * data = (MElem *) calloc(row * column, sizeof(MElem));
    if(data == NULL){
        free(new);
        return NULL;
    }

    new->data = data;
    new->row = row;
    new->column = column;
    new->dtype = dtype;
    return new;
}

void deleteMatrix(Matrix *m){
    free(m->data);
    free(m);
}

void initMatrix(Matrix * m, MElem source[m->row][m->column]){
    int i, j, row = m->row, column = m->column;
    for(i = 0; i < row; i++){
        for(j = 0; j < column; j++){
            m->data[i * column + j] = source[i][j];
        }
    }
}

MElem getMElem(Matrix *m, size_t row, size_t column){
    row %= m->row;
    column %= m->column;
    return m->data[row * m->column + column];
}

void setMElem(Matrix *m, size_t row, size_t column, MElem value){
    row %= m->row;
    column %= m->column;
    m->data[row * m->column + column] = value;
}

typedef struct adjMatrix{
    Matrix * adj;
    size_t size;
    int weighted;
    int directed;
} adjMatrix;

adjMatrix *newAdjMatrix(size_t size, int weighted, int directed){
    if(size * size < size)
        // size_t overflow
        return NULL;

    adjMatrix *new = (adjMatrix *) malloc(sizeof(adjMatrix));
    if(new == NULL)
        return NULL;

    Matrix *adj =  weighted ? newMatrix(size, size, FLOAT64) : newMatrix(size, size, INT64);
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

void initAdjMatrix(adjMatrix * m, MElem source[m->size][m->size]){
    initMatrix(m->adj, source);
}

void deleteAdjMatrix(adjMatrix * m){
    deleteMatrix(m->adj);
    free(m);
}

typedef union Weight{
    double num_float64; /* num_float64 for directed */ 
    long num_int64; /* num_int64 for not directed */
} Weight;

/* orthogonal list */
typedef struct edgeNode {
    long end0;
    long end1;
    Weight weight;
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





void main(){
    MElem a[2][2] = {
        {0, 1},
        {1, 0}
    };
    Matrix *m = newMatrix(2, 2);
    initMatrix(m, a);
    printf("%ld %ld %ld %ld\n", m->data[0], m->data[1], m->data[2], m->data[3]);
}