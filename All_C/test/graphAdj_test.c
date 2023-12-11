//
// Created by skf on 23-12-8.
//
#include "../include/graphAdj.h"

int main(){
    RAII(graphAdj_raii) GraphAdj *graph = graphAdj_new(5, 0, 0);
    double source[5][5] = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 1, 1},
            {1, 1, 0, 0, 1},
            {0, 1, 0, 0, 1},
            {0, 1, 1, 1, 0}
    };

    graphAdj_initAdj(graph, source);
    printf("graphAdj_initAdj: \n");
    RAII(deque_raii) Deque *buf = deque_new(10);

    graphAdj_DFS(graph, 0, buf);
    printf("DFS: ");
    deque_display(buf);

    deque_clear(buf);

    graphAdj_BFS(graph, 0, buf);
    printf("BFS: ");
    deque_display(buf);
    return 0;
}