#include <string.h>

#include "../include/graphAdj.h"

__malloc GraphAdj *graphAdj_new(size_t size, int weighted, int directed){
    if(size * size < size)
        // size_t overflow
        return NULL;

    GraphAdj *new = (GraphAdj *) malloc(sizeof(GraphAdj));
    if(new == NULL)
        return NULL;

    Matrix *adj = matrix_new(size, size);
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

int graphAdj_invalidCheck(GraphAdj * m, double source[m->size][m->size]){
    /* check if the matrix is valid */
    /* valid: 1, invalid: 0 */
    size_t size = m->size;
    int weighted = m->weighted, directed = m->directed;
    for(int i = 0; i < size; i++){
        if(source[i][i] != 0.0) return -1;
        for(int j = 0; j < size; j++){
            if(source[i][j] < 0.0) return -1;
            if(!weighted && source[i][j] != 0.0 && source[i][j] != 1.0) return -1;
        }
    }
    if(!directed){
        /* this test has a bad spatial locality */
        for(int i = 0; i < size; i++){
            for(int j = i; j < size; j++){
                if(source[i][j] != source[j][i]) return -1;
            }
        }
    }
    return 0;
}

int graphAdj_initAdj(GraphAdj * m, double source[m->size][m->size]){
    int i, j;
    if(graphAdj_invalidCheck(m, source) < 0) return -1; /* if invalid, return -1 */
    for(i = 0; i < m->size; i++){
        for(j = 0; j < m->size; j++){
            matrix_set(m->adj, i, j, (Elem)source[i][j]);
        }
    }
    return 0;
}

void graphAdj_delete(GraphAdj * m){
    matrix_delete(m->adj);
    free(m);
}

void graphAdj_raii(GraphAdj **this){
//    printf("graphAdj_raii\n");
    graphAdj_delete(*this);
    *this = NULL;
}

/* TODO: Realize some graph algorithm */

int graphAdj_DFS(GraphAdj *this, size_t start, Deque *buf){
    /* graphAdj_DFS from start */
    /* buf store the result */

    /* error list:
     * no error: 0,
     * start out of range: -1,
     * malloc fail: -2
     * buf is too small: -3 */

    if(start >= this->size) {
        /* start is out of range */
        return -1;
    }

    size_t size = this->size;
    if(size > deque_freeSize(buf)){
        /* buf is too small */
        return -3;
    }

    Matrix *adj = this->adj;

    RAII(deque_raii) Deque *stack = deque_new(size);
    if(stack == NULL) {
        return -2;
    }

    RAII(list_raii) List * visited = list_new(size);
    if(visited == NULL){
        return -2;
    }

    deque_appendRight(stack, (Elem)start);
    list_set(visited, start, (Elem){.num_int64 = 1});
    while(!deque_isEmpty(stack)){
        size_t node;
        deque_popRight(stack, (Elem *)&node);
        deque_appendRight(buf, (Elem)node);
        for(size_t i = 0; i < size; i++){
            int linked = matrix_get(adj, node, i).num_float64 > 0.0;
            Elem visited_i;
            list_get(visited, i, &visited_i);
            if(linked && visited_i.num_int64 != 1){
                deque_appendRight(stack, (Elem)i);
                list_set(visited, i, (Elem){.num_int64 = 1});
            }
        }
    }
    return 0;
}

int graphAdj_BFS(GraphAdj *this, size_t start, Deque *buf){
    /* graphAdj_BFS from start */
    /* buf store the result */

    /* error list:
     * no error: 0,
     * start out of range: -1,
     * malloc fail: -2
     * buf is too small: -3 */

    if(start >= this->size)
        return -1;

    size_t size = this->size;
    if(size > buf->maxsize - deque_size(buf)){
        /* buf is too small */
        return -3;
    }

    Matrix *adj = this->adj;

    RAII(deque_raii) Deque *queue = deque_new(size);
    if(queue == NULL) {
        return -2;
    }

    RAII(list_raii) List * visited = list_new(size);
    if(visited == NULL){
        return -2;
    }

    deque_appendRight(queue, (Elem)start);
    list_set(visited, start, (Elem){.num_int64 = 1});
    while(!deque_isEmpty(queue)){
        size_t node;
        deque_popLeft(queue, (Elem *)&node);
        deque_appendRight(buf, (Elem)node);

        for(size_t i = 0; i < size; i++){
            int linked = matrix_get(adj, node, i).num_float64 > 0.0;
            Elem visited_i;
            list_get(visited, i, &visited_i);
            if(linked && visited_i.num_int64 != 1){
                deque_appendRight(queue, (Elem)i);
                list_set(visited, i, (Elem){.num_int64 = 1});
            }
        }
    }

    return 0;
}

int graphAdj_DFS_All(GraphAdj *this, Deque *buf){
    /* graphAdj_DFS all nodes */

    /* error list:
     * no error: 0,
     * malloc fail: -1
     * buf is too small: -2 */

    size_t size = this->size;
    if(size > deque_freeSize(buf)){
        /* buf is too small */
        return -2;
    }

    RAII(list_raii) List * visited = list_new(size);
    if(visited == NULL){
        return -1;
    }

    for(size_t start = 0; start < size; start++){
        Elem visited_start;
        list_get(visited, start, &visited_start);
        if(visited_start.num_int64 == 1){
            continue;
        }
        graphAdj_DFS(this, start, buf);
    }

    return 0;
}

int graphAdj_BFS_All(GraphAdj *this, Deque *buf){
    /* graphAdj_BFS all nodes */

    /* error list:
     * no error: 0,
     * malloc fail: -1
     * buf is too small: -2 */

    size_t size = this->size;
    if(size > deque_freeSize(buf)){
        /* buf is too small */
        return -2;
    }

    RAII(list_raii) List * visited = list_new(size);
    if(visited == NULL){
        return -1;
    }

    for(size_t start = 0; start < size; start++){
        Elem visited_start;
        list_get(visited, start, &visited_start);
        if(visited_start.num_int64 == 1){
            continue;
        }
        graphAdj_BFS(this, start, buf);
    }

    return 0;
}