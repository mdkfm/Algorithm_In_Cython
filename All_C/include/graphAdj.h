//
// Created by skf on 23-12-8.
//

#ifndef ALL_C_GRAPHADJ_H
#define ALL_C_GRAPHADJ_H

#include "data.h"
#include "gnuc.h"
#include "deque.h"
#include "matrix.h"
#include "list.h"

typedef struct {
    Matrix *adj; /* a double matrix, 0.0 for not connected */
    size_t size;
    int weighted; /* only positive weight */
    int directed;
} GraphAdj;

__malloc GraphAdj *graphAdj_new(size_t size, int weighted, int directed);

int graphAdj_initAdj(GraphAdj * m, double source[m->size][m->size]);

void graphAdj_delete(GraphAdj * m);
void graphAdj_raii(GraphAdj ** m);

int graphAdj_DFS(GraphAdj *this, size_t start, Deque *buf);
int graphAdj_BFS(GraphAdj *this, size_t start, Deque *buf);
int graphAdj_DFS_All(GraphAdj *this, Deque *buf);
int graphAdj_BFS_All(GraphAdj *this, Deque *buf);
void deque_clear(Deque *const this);


#endif //ALL_C_GRAPHADJ_H
