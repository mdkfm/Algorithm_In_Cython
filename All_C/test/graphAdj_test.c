//
// Created by skf on 23-12-8.
//
#include "../include/graphAdj.h"

int main(){
    auto_ptr(GraphAdj) graph = graphAdj_new(9, 1, 0);
    double source[9][9] = {
            {0, 0,  0,  0,  0,  0,  0,  0,  8},
            {0,   0, 9,  10, 11, 12, 13, 14, 15},
            {0,   9,   0, 16, 17, 18, 19, 20, 21},
            {0,   10,  16, 0, 22, 23, 24, 25, 26},
            {0,   11,  17, 22, 0, 27, 28, 29, 30},
            {0,   12,  18, 23, 27, 0, 31, 32, 33},
            {0,   13,  19, 24, 28, 31, 0, 34, 35},
            {0,   14,  20, 25, 29, 32, 34, 0, 36},
            {8,   15,  21, 26, 30, 33, 35, 36, 0}
    };

    graphAdj_initAdj(graph, source);
    printf("graphAdj_initAdj: \n");
    auto_ptr(Deque) buf = deque_new(10);

    graphAdj_DFS(graph, 0, buf);
    printf("DFS: ");
    deque_display(buf);
    printf("\n");

    deque_clear(buf);

    graphAdj_BFS(graph, 0, buf);
    printf("BFS: ");
    deque_display(buf);
    printf("\n");

    auto_ptr(GraphAdj) graph2 = graphAdj_Prim(graph);
    printf("Prim: \n");
    graphAdj_display(graph2);
    printf("degree: %ld\n", graph2->degree);
    printf("edge_num: %ld\n\n", graph2->edge_num);

    auto_ptr(GraphAdj) graph3 = graphAdj_Kruskal(graph);
    printf("Kruskal: \n");
    graphAdj_display(graph3);
    printf("degree: %ld\n", graph3->degree);
    printf("edge_num: %ld\n", graph3->edge_num);
    return 0;
}