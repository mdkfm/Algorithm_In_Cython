#include <string.h>

#include "../include/graphAdj.h"
#include "../include/heap.h"
#include "../include/ufsTree.h"

#define GRAPHADJ_NOLINK 0.0
#define GRAPHADJ_ISLINK(x) ((x) > 0.0)

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
    size_t max_degree = 0;
    size_t edge_num = 0;
    for(i = 0; i < m->size; i++){
        size_t degree = 0;
        for(j = 0; j < m->size; j++){
            matrix_set(m->adj, i, j, (Elem)source[i][j]);
            degree += source[i][j] > 0.0;
            edge_num += source[i][j] > 0.0;
        }
        max_degree = degree > max_degree ? degree : max_degree;
    }
    m->degree = max_degree;
    m->edge_num = edge_num;
    return 0;
}

void graphAdj_delete(GraphAdj * m){
    matrix_delete(m->adj);
    free(m);
}

void graphAdj_display(GraphAdj const*const this){
    matrix_display(this->adj);
}

int graphAdj_add(GraphAdj *this, size_t i, size_t j, double weight, int method){
    /* add an edge from i to j */
    /* method:
     * 0 : if edge (i, j) exists, do not change
     * 1 : change */

    if(unlikely(i >= this->size || j >= this->size))
        return -1;
    if(unlikely(i == j))
        return -2;
    if(unlikely(weight <= 0.0))
        return -3;
    if(unlikely(matrix_get(this->adj, i, j).num_float64 != 0.0 && !method))
        return -4;
    weight = this->weighted ? weight : 1.0;
    matrix_set(this->adj, i, j, (Elem)weight);
    if(!this->directed)
        matrix_set(this->adj, j, i, (Elem)weight);
    return 0;
}

int graphAdj_set(GraphAdj *this, size_t i, size_t j, double weight, int method){
    /* set the weight of edge (i, j) */
    /* method:
     * 0 : if edge (i, j) does not exist, do not add
     * 1 : add */

    if(unlikely(i >= this->size || j >= this->size))
        return -1;
    if(unlikely(i == j))
        return -2;
    if(unlikely(weight <= 0.0))
        return -3;
    if(unlikely(matrix_get(this->adj, i, j).num_float64 == 0.0 && !method))
        return -4;

    weight = this->weighted ? weight : 1.0;
    matrix_set(this->adj, i, j, (Elem)weight);
    if(!this->directed)
        matrix_set(this->adj, j, i, (Elem)weight);
    return 0;
}

int graphAdj_remove(GraphAdj *this, size_t i, size_t j){
    /* remove the edge (i, j) */

    if(unlikely(i >= this->size || j >= this->size))
        return -1;

    matrix_set(this->adj, i, j, (Elem)0.0);
    if(!this->directed)
        matrix_set(this->adj, j, i, (Elem)0.0);
    return 0;
}

/* TODO: Realize some graph algorithm */

#define GRAPHADJ_DFS_DEBUG 0

int graphAdj_DFS(GraphAdj *this, size_t start, Deque *buf){
    /* graphAdj_DFS from start */
    /* buf store the result */

    /* error list:
     * no error: 0,
     * start out of range: -1,
     * malloc fail: -2
     * buf is too small: -3 */

    if(unlikely(start >= this->size)) {
        /* start is out of range */
        return -1;
    }

    size_t size = this->size;
    if(unlikely(size > deque_freeSize(buf))){
        /* buf is too small */
        return -3;
    }

    Matrix *adj = this->adj;

    auto_ptr(Deque) stack = deque_new(size);
    auto_ptr(List) visited = list_new(size);
    if(unlikely(stack == NULL || visited == NULL)) {
        return -2;
    }

    deque_appendRight(stack, (Elem)start);
    list_set(visited, start, (Elem){.num_int64 = 1});

    while(!deque_isEmpty(stack)){
        size_t node;
        deque_popRight(stack, (Elem *)&node);
#if GRAPHADJ_DFS_DEBUG
        printf("%ld ", node);
#endif
        deque_appendRight(buf, (Elem)node);
        for(size_t i = 0; i < size; i++){
            int linked = matrix_get(adj, node, i).num_float64 > 0.0;
            long visited_i = list_get(visited, i).num_int64;
            if(linked && visited_i != 1){
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

    if(unlikely(start >= this->size))
        return -1;

    size_t size = this->size;
    if(unlikely(size > deque_freeSize(buf))){
        /* buf is too small */
        return -3;
    }

    Matrix *adj = this->adj;

    auto_ptr(Deque) queue = deque_new(size);
    if(unlikely(queue == NULL)) {
        return -2;
    }

    auto_ptr(List) visited = list_new(size);
    if(unlikely(visited == NULL)){
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
            long visited_i = list_get(visited, i).num_int64;
            if(linked && visited_i != 1){
                deque_appendRight(queue, (Elem)i);
                list_set(visited, i, (Elem){.num_int64 = 1});
            }
        }
    }

    return 0;
}

int graphAdj_DFSVisited(GraphAdj *this, size_t start, Deque *buf, List *visited){
    /* graphAdj_DFS from start */
    /* buf store the result */

    /* error list:
     * no error: 0,
     * start out of range: -1,
     * malloc fail: -2
     * buf is too small: -3 */

    if(unlikely(start >= this->size)) {
        /* start is out of range */
        return -1;
    }

    size_t size = this->size;
    if(unlikely(size > deque_freeSize(buf))){
        /* buf is too small */
        return -3;
    }

    Matrix *adj = this->adj;

    auto_ptr(Deque) stack = deque_new(size);
    if(unlikely(stack == NULL)) {
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
            long visited_i = list_get(visited, i).num_int64;
            if(linked && visited_i != 1){
                deque_appendRight(stack, (Elem)i);
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

    auto_ptr(List) visited = list_new(size);
    if(visited == NULL){
        return -1;
    }

    if(!this->directed){
        for(size_t start = 0; start < size; start++){
            long visited_start = list_get(visited, start).num_int64;
            if(visited_start == 1){
                continue;
            }
            if(unlikely(graphAdj_DFS(this, start, buf) < 0))
                return -1;
        }
        return 0;
    }
    for(size_t start = 0; start < size; start++){
        long visited_start = list_get(visited, start).num_int64;
        if(visited_start == 1){
            continue;
        }
        if(unlikely(graphAdj_DFSVisited(this, start, buf, visited) < 0))
            return -1;
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

    auto_ptr(List) visited = list_new(size);
    if(visited == NULL){
        return -1;
    }

    for(size_t start = 0; start < size; start++){
        long visited_start = list_get(visited, start).num_int64;
        if(visited_start == 1){
            continue;
        }
        graphAdj_BFS(this, start, buf);
    }

    return 0;
}

int graphAdj_isConnected(GraphAdj *this){
    /* check if the graph is connected */
    /* connected: 1, not connected: 0 */

    /* error list:
     * no error: 0,
     * malloc fail: -1 */

    if(this->directed){
        return -2;
    }
    size_t size = this->size;
    auto_ptr(Deque) buf = deque_new(size);
    if(buf == NULL){
        return -1;
    }

    if(unlikely(graphAdj_DFS(this, 0, buf) < 0)){
        return -1;
    }

    return deque_size(buf) == size;
}

#define GRAPHADJ_PRIM_DEBUG 0
__malloc GraphAdj * graphAdj_Prim(GraphAdj const*const this){
    /* Prim algorithm */
    /* return a new GraphAdj */

    /* error list:
     * no error: return a new GraphAdj
     * malloc fail: return NULL */

    if(this->directed || !this->weighted){
        return NULL;
    }

    /* create new GraphAdj */
#if GRAPHADJ_PRIM_DEBUG
    printf("create new GraphAdj\n\n");
#endif
    size_t size = this->size;
    GraphAdj * new = graphAdj_new(size, this->weighted, 0);
    if(new == NULL){
        return NULL;
    }

    Matrix *adj = this->adj;
    Matrix *new_adj = new->adj;

    /* init tmp List : closest, lowcost, degrees */
#if GRAPHADJ_PRIM_DEBUG
    printf("init tmp List : closest, lowcost, degrees\n\n");
#endif
    /* closest[i] store the closest node to i */
    /* lowcost[i] store the weight of edge (i, closest[i]) */
    auto_ptr(List) closest = list_new(size), lowcost = list_new(size);
    auto_ptr(List) degrees = list_new(size);
    if(closest == NULL || lowcost == NULL || degrees == NULL){
        return NULL;
    }

#if GRAPHADJ_PRIM_DEBUG
    printf("start from node 0\n\n");
#endif
    /* start from node 0 */
    list_set(lowcost, 0, (Elem){.num_int64 = 0});
    for(size_t i = 1; i < size; i++){
//        list_set(closest, i, (Elem){.num_int64 = 0});
        double cost = matrix_get(adj, 0, i).num_float64;
        cost = GRAPHADJ_ISLINK(cost) ? cost : INF;
        list_set(lowcost, i, (Elem){.num_float64 = cost});
    }

    /* add size - 1 edges */
#if GRAPHADJ_PRIM_DEBUG
    printf("add size - 1 edges\n\n");
#endif
    for(size_t i = 1; i < size; i++){
        double min = INF;
        size_t candidate = 0;
        for(size_t j = 0; j < size; j++){
            double lowcost_j = list_get(lowcost, j).num_float64;
            int cond = (GRAPHADJ_ISLINK(lowcost_j) && lowcost_j < min);
            min = cond ? lowcost_j : min;
            candidate = cond ? j : candidate;
        }
#if GRAPHADJ_PRIM_DEBUG
        printf("candidate: %ld\n", candidate);
#endif
        size_t closest_candidate = list_get(closest, candidate).num_int64;

        list_set(degrees, candidate, (Elem){list_get(degrees, candidate).num_int64 + 1});
        list_set(degrees, closest_candidate, (Elem){list_get(degrees, closest_candidate).num_int64 + 1});
        matrix_set(new_adj, candidate, closest_candidate, (Elem)min);
        matrix_set(new_adj, closest_candidate, candidate, (Elem)min);

        list_set(lowcost, candidate, (Elem){.num_float64 = 0.0});
        for(size_t j = 0; j < size; j++){
            double adj_candidate_j = matrix_get(adj, candidate, j).num_float64;
            double lowcost_j = list_get(lowcost, j).num_float64;
            int cond = (GRAPHADJ_ISLINK(adj_candidate_j) && adj_candidate_j < lowcost_j);
            list_set(lowcost, j, (Elem){.num_float64 = cond ? adj_candidate_j : lowcost_j});
            list_set(closest, j, (Elem){.num_int64 = cond ? candidate : list_get(closest, j).num_int64});
        }
    }

#if GRAPHADJ_PRIM_DEBUG
    printf("set edge num and degree\n\n");
#endif
    /* set edge num and degree */
    new->edge_num = size - 1;
    size_t max_degree = 0;
    for(size_t i = 0; i < size; i++){
        size_t degree = list_get(degrees, i).num_int64;
        max_degree = degree > max_degree ? degree : max_degree;
    }
    new->degree = max_degree;
    return new;
}

typedef struct _GraphAdj_edge{
    size_t from, to;
    double weight;
} GraphAdj_edge;

int _graphAdj_cmp(Elem e0, Elem e1){
    GraphAdj_edge *n0 = (GraphAdj_edge *)e0.ptr;
    GraphAdj_edge *n1 = (GraphAdj_edge *)e1.ptr;
    return n0->weight < n1->weight ? 1 : (n0->weight > n1->weight ? -1 : 0);
}

__malloc  GraphAdj * graphAdj_Kruskal(GraphAdj const*const this){
    /* Kruskal algorithm */
    /* return a new GraphAdj */

    /* error list:
     * no error: return a new GraphAdj
     * malloc fail: return NULL */

    if(this->directed || !this->weighted){
        return NULL;
    }
    size_t size = this->size;
    GraphAdj * new = graphAdj_new(size, this->weighted, 0);
    if(new == NULL){
        return NULL;
    }

    Matrix * adj = this->adj;
    Matrix * new_adj = new->adj;

    auto_ptr(UFSTree) tree = ufsTree_new(size);
    auto_ptr(Heap) heap = heap_new(size * size, _graphAdj_cmp);
    auto_ptr(List) degrees = list_new(size);

    size_t edge_num = this->edge_num;
    GraphAdj_edge *const edges = (GraphAdj_edge *)calloc(edge_num, sizeof(GraphAdj_edge));

    if(tree == NULL || heap == NULL || degrees == NULL || edges == NULL){
        return NULL;
    }

    /* init edges */
    GraphAdj_edge *start = edges;
    for(size_t i = 0; i < size; i++){
        for(size_t j = i + 1; j < size; j++){
            double weight = matrix_get(adj, i, j).num_float64;
            if(GRAPHADJ_ISLINK(weight)){
                *start = (GraphAdj_edge){.from = i, .to = j, .weight = weight};
                start ++;
            }
        }
    }

    /* init heap */
    heap_initFromStart(heap, edges, sizeof(GraphAdj_edge), edge_num);

    /* init tree */
    size_t new_edge_num = 0;
    while(new_edge_num < size - 1){
        GraphAdj_edge *edge = heap_pop(heap).ptr;
        size_t from = edge->from, to = edge->to;
        int union_result = ufsTree_union(tree, from, to);

        if(union_result == 3){
            /* already union before */
            continue;
        }

        double weight = edge->weight;
        new_edge_num ++;
        list_set(degrees, from, (Elem){list_get(degrees, from).num_int64 + 1});
        list_set(degrees, to, (Elem){list_get(degrees, to).num_int64 + 1});
        matrix_set(new_adj, from, to, (Elem)weight);
        matrix_set(new_adj, to, from, (Elem)weight);

    }

    /* set edge num and degree */
    new->edge_num = size - 1;
    size_t max_degree = 0;
    for(size_t i = 0; i < size; i++){
        size_t degree = list_get(degrees, i).num_int64;
        max_degree = degree > max_degree ? degree : max_degree;
    }
    new->degree = max_degree;

    /* free edges */
    free(edges);
    return new;
}