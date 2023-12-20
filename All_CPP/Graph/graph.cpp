#include <stdexcept>
#include "../Container/deque.cpp"

/* TODO: refactor to delete the template */

template<size_t _node_num>
class Graph{
private:
    double _adj_matrix[_node_num][_node_num];
    bool isRinged_directed() const;
    bool isRinged_undirected() const;
    bool invalid_check();
public:
    size_t const node_num;
    bool const weighted;
    bool const directed;
    Graph(double adj_matrix[_node_num][_node_num], bool weighted, bool directed);
    double get_edge(size_t a, size_t b) const;
    void set_edge(size_t a, size_t b, double weight = 1.0);
    Deque<size_t> DFS(size_t start) const;
    Deque<size_t> DFS_All() const;
    Deque<size_t> BFS(size_t start) const;
    Deque<size_t> BFS_All() const;
    Deque<size_t> topoSort() const;
    bool isRinged() const;
};

template<size_t _node_num>
Graph<_node_num>::Graph(double adj_matrix[_node_num][_node_num], bool weighted, bool directed):
node_num(_node_num), weighted(weighted), directed(directed){
    for(size_t i = 0; i < _node_num; i++){
        for(size_t j = 0; j < _node_num; j++){
            this->_adj_matrix[i][j] = adj_matrix[i][j];
        }
    }
    if(!invalid_check()) {
        throw(std::invalid_argument("Invalid graph"));
    }
}

template<size_t _node_num>
bool Graph<_node_num>::invalid_check(){
    for(size_t i = 0; i < _node_num; i++){
        for(size_t j = 0; j < _node_num; j++){
            double weight = _adj_matrix[i][j];
            if(weight < 0) return false;
            if(i == j && weight != 0.0) return false;
            if(!weighted && weight != 1.0 && weight != 0.0) return false;
        }
    }
    return true;
}

template<size_t _node_num>
double Graph<_node_num>::get_edge(size_t a, size_t b) const{
    return _adj_matrix[a][b];
}

template<size_t _node_num>
void Graph<_node_num>::set_edge(size_t a, size_t b, double weight){
    /* set edge from a to b, with weight, if weight is not given, set to 1.0 */
    /* if weight = 0, delete the edge */
    if(a == b) throw(std::invalid_argument("self-self edge is not allowed"));
    if(weight < 0) throw(std::domain_error("negative or zero weight is not allowed"));
    if(!weighted && weight != 1.0) throw(std::domain_error("weight is not allowed"));
    _adj_matrix[a][b] = weight;
    _adj_matrix[b][a] = directed ? _adj_matrix[b][a] : weight;
}

template<size_t _node_num>
Deque<size_t> Graph<_node_num>::DFS(size_t start) const{
    /* DFS from start */
    Deque<size_t> result(_node_num), stack(_node_num);
    bool visited[_node_num] = {false};
    stack.appendRight(start);
    visited[start] = true;
    while(!stack.isEmpty()){
        size_t node = stack.popRight();
        result.appendRight(node);
        for(size_t i = 0; i < _node_num; i++){
            if(_adj_matrix[node][i] != 0.0 && !visited[i]){
                stack.appendRight(i);
                visited[i] = true;
            }
        }
    }
    return result;
}

template<size_t _node_num>
Deque<size_t> Graph<_node_num>::DFS_All() const{
    /* DFS all nodes, also for not linked graph */
    Deque<size_t> result(_node_num), stack(_node_num);
    bool visited[_node_num] = {false};
    for(size_t i = 0; i < _node_num; i++){
        if(visited[i]) continue;
        stack.appendRight(i);
        visited[i] = true;
        while(!stack.isEmpty()){
            size_t node = stack.popRight();
            result.appendRight(node);
            for(size_t j = 0; j < _node_num; j++){
                if(_adj_matrix[node][j] != 0.0 && !visited[j]){
                    stack.appendRight(j);
                    visited[j] = true;
                }
            }
        }
    }
    return result;
}

template<size_t _node_num>
Deque<size_t> Graph<_node_num>::BFS(size_t start) const{
    /* BFS from start */
    Deque<size_t> result(_node_num), queue(_node_num);
    bool visited[_node_num] = {false};
    queue.appendRight(start);
    visited[start] = true;
    while(!queue.isEmpty()){
        size_t node = queue.popLeft();
        result.appendRight(node);
        for(size_t i = 0; i < _node_num; i++){
            if(_adj_matrix[node][i] != 0.0 && !visited[i]){
                queue.appendRight(i);
                visited[i] = true;
            }
        }
    }
    return result;
}

template<size_t _node_num>
Deque<size_t> Graph<_node_num>::BFS_All() const{
    /* BFS all nodes, also for not linked graph */
    Deque<size_t> result(_node_num), queue(_node_num);
    bool visited[_node_num] = {false};
    for(size_t i = 0; i < _node_num; i++){
        if(visited[i]) continue;
        queue.appendRight(i);
        visited[i] = true;
        while(!queue.isEmpty()){
            size_t node = queue.popLeft();
            result.appendRight(node);
            for(size_t j = 0; j < _node_num; j++){
                if(_adj_matrix[node][j] != 0.0 && !visited[j]){
                    queue.appendRight(j);
                    visited[j] = true;
                }
            }
        }

    }
    return result;
}

template<size_t _node_num>
Deque<size_t> Graph<_node_num>::topoSort() const{
    /* Topological sort */
    if(!directed) throw std::domain_error("TopoSort is only for directed graph");

    Deque<size_t> result(_node_num), queue(_node_num);
    size_t in_degree[_node_num] = {0};
    /* calculate in degree */
    for(size_t i = 0; i < _node_num; i++){
        for(size_t j = 0; j < _node_num; j++){
            if(_adj_matrix[i][j] != 0.0) in_degree[j]++;
        }
    }
    /* push node with in degree 0 into queue */
    for(size_t i = 0; i < _node_num; i++){
        if(in_degree[i] == 0) queue.appendRight(i);
    }
    /* pop node from queue, push into result, and decrease in degree of its child */
    while(!queue.isEmpty()){
        size_t node = queue.popLeft();
        result.appendRight(node);
        for(size_t i = 0; i < _node_num; i++){
            if(_adj_matrix[node][i] != 0.0){
                size_t degree = --in_degree[i];
                if(degree == 0) queue.appendRight(i);
            }
        }
    }
    if(!result.isFull()) throw std::domain_error("Graph has a cycle");
    return result;
}

template<size_t _node_num>
bool Graph<_node_num>::isRinged_undirected() const{
    /* In DFS, if a node is visited twice, then the graph is ringed */
    bool visited[_node_num] = {false};
    /* for not directed, we need to save the parent */
    struct _node{
        size_t node;
        size_t parent;
    };
    Deque<_node> stack(_node_num);
    stack.appendRight(_node{0, 0});
    visited[0] = true;
    while(!stack.isEmpty()){
        _node node = stack.popRight();
        for(size_t i = 0; i < _node_num; i++){
            if(_adj_matrix[node.node][i] != 0.0){
                if(visited[i]){
                    /* if there is an edge with visited node but not its parent, then it is ringed */
                    if(i != node.parent) return true;
                }else{
                    /* else push into stack, and set the parent */
                    stack.appendRight(_node{i, node.node});
                    visited[i] = true;
                }
            }
        }
    }
    return false;
}

template<size_t _node_num>
bool Graph<_node_num>::isRinged_directed() const{
    /* In DFS, if a node is visited twice, then the graph is ringed */
    bool visited[_node_num] = {false};
    Deque<size_t> stack(_node_num);
    stack.appendRight(0);
    visited[0] = true;
    while(!stack.isEmpty()){
        size_t node = stack.popRight();
        for(size_t i = 0; i < _node_num; i++) {
            if (_adj_matrix[node][i] != 0.0) {
                if (visited[i]) return true;
                /* else push into stack, and set the parent */
                stack.appendRight(i);
                visited[i] = true;
            }
        }
    }
    return false;
}

template<size_t _node_num>
bool Graph<_node_num>::isRinged() const{
    /* check whether the graph is ringed */
    /* In DFS, if a node is visited twice, then the graph is ringed */
    return directed ? isRinged_directed() : isRinged_undirected();
}


int main(){
    double adj_matrix[5][5] = {
        {0, 1, 0, 0, 0},
        {1, 0, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1},
        {0, 1, 0, 1, 0}
    };
    Graph<5> graph(adj_matrix, false, false);
    Deque<size_t> result = graph.DFS_All();
    for(size_t i = 0; i < 5; i++){
        std::cout << result.popLeft() << " ";
    }
    std::cout << std::endl;
    return 0;
}