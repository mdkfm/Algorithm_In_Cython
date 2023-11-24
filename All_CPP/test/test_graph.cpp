#include "../Graph/graph.cpp"

int main(){
    /* test */
    double adj[5][5] = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 1, 0},
            {1, 1, 0, 1, 1},
            {0, 1, 1, 0, 1},
            {0, 0, 1, 1, 0}
    };
    Graph<5> graph(adj, false, true);
    Queue<long unsigned> result = graph.topoSort();
    result.displayQueue();
    return 0;
}