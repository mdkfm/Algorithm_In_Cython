#include <stdexcept>
#include "../List/queue.cpp"

template<long unsigned _node_num>
class Graph{
private:
    double _adj_matrix[_node_num][_node_num];
    bool isRinged_directed() const;
    bool isRinged_undirected() const;
    bool invalid_check();
public:
    long unsigned const node_num;
    bool const weighted;
    bool const directed;
    Graph(double adj_matrix[_node_num][_node_num], bool weighted, bool directed);
    double get_edge(long unsigned a, long unsigned b) const;
    void set_edge(long unsigned a, long unsigned b, double weight = 1.0);
    Queue<long unsigned> DFS(long unsigned start) const;
    Queue<long unsigned> BFS(long unsigned start) const;
    Queue<long unsigned> topoSort() const;
    bool isRinged() const;
};

template<long unsigned _node_num>
Graph<_node_num>::Graph(double adj_matrix[_node_num][_node_num], bool weighted, bool directed):
node_num(_node_num), weighted(weighted), directed(directed){
    for(long unsigned i = 0; i < _node_num; i++){
        for(long unsigned j = 0; j < _node_num; j++){
            this->_adj_matrix[i][j] = adj_matrix[i][j];
        }
    }
    if(!invalid_check()) {
        throw(std::invalid_argument("Invalid graph"));
    }
}

template<long unsigned _node_num>
bool Graph<_node_num>::invalid_check(){
    for(long unsigned i = 0; i < _node_num; i++){
        for(long unsigned j = 0; j < _node_num; j++){
            double weight = _adj_matrix[i][j];
            if(weight < 0) return false;
            if(i == j && weight != 0.0) return false;
            if(!weighted && weight != 1.0 && weight != 0.0) return false;
        }
    }
    return true;
}

template<long unsigned _node_num>
double Graph<_node_num>::get_edge(long unsigned a, long unsigned b) const{
    return _adj_matrix[a][b];
}

template<long unsigned _node_num>
void Graph<_node_num>::set_edge(long unsigned a, long unsigned b, double weight){
    /* set edge from a to b, with weight, if weight is not given, set to 1.0 */
    /* if weight = 0, delete the edge */
    if(a == b) throw(std::invalid_argument("self-self edge is not allowed"));
    if(weight < 0) throw(std::domain_error("negative or zero weight is not allowed"));
    if(!weighted && weight != 1.0) throw(std::domain_error("weight is not allowed"));
    _adj_matrix[a][b] = weight;
    _adj_matrix[b][a] = directed ? _adj_matrix[b][a] : weight;
}

template<long unsigned _node_num>
Queue<long unsigned> Graph<_node_num>::DFS(long unsigned start) const{
    /* DFS from start */
    Queue<long unsigned> result(_node_num), stack(_node_num);
    bool visited[_node_num] = {false};
    stack.appendRight(start);
    visited[start] = true;
    while(!stack.isEmpty()){
        long unsigned node = stack.popRight();
        result.appendRight(node);
        for(long unsigned i = 0; i < _node_num; i++){
            if(_adj_matrix[node][i] != 0.0 && !visited[i]){
                stack.appendRight(i);
                visited[i] = true;
            }
        }
    }
    return result;
}

template<long unsigned _node_num>
Queue<long unsigned> Graph<_node_num>::BFS(long unsigned start) const{
    /* BFS from start */
    Queue<long unsigned> result(_node_num), queue(_node_num);
    bool visited[_node_num] = {false};
    queue.appendRight(start);
    visited[start] = true;
    while(!queue.isEmpty()){
        long unsigned node = queue.popLeft();
        result.appendRight(node);
        for(long unsigned i = 0; i < _node_num; i++){
            if(_adj_matrix[node][i] != 0.0 && !visited[i]){
                queue.appendRight(i);
                visited[i] = true;
            }
        }
    }
    return result;
}

template<long unsigned _node_num>
Queue<long unsigned> Graph<_node_num>::topoSort() const{
    /* Topological sort */
    if(!directed) throw std::domain_error("TopoSort is only for directed graph");

    Queue<long unsigned> result(_node_num), queue(_node_num);
    long unsigned in_degree[_node_num] = {0};
    /* calculate in degree */
    for(long unsigned i = 0; i < _node_num; i++){
        for(long unsigned j = 0; j < _node_num; j++){
            if(_adj_matrix[i][j] != 0.0) in_degree[j]++;
        }
    }
    /* push node with in degree 0 into queue */
    for(long unsigned i = 0; i < _node_num; i++){
        if(in_degree[i] == 0) queue.appendRight(i);
    }
    /* pop node from queue, push into result, and decrease in degree of its child */
    while(!queue.isEmpty()){
        long unsigned node = queue.popLeft();
        result.appendRight(node);
        for(long unsigned i = 0; i < _node_num; i++){
            if(_adj_matrix[node][i] != 0.0){
                long unsigned degree = --in_degree[i];
                if(degree == 0) queue.appendRight(i);
            }
        }
    }
    if(!result.isFull()) throw std::domain_error("Graph has a cycle");
    return result;
}

template<long unsigned _node_num>
bool Graph<_node_num>::isRinged_undirected() const{
    /* In DFS, if a node is visited twice, then the graph is ringed */
    bool visited[_node_num] = {false};
    /* for not directed, we need to save the parent */
    struct _node{
        long unsigned node;
        long unsigned parent;
    };
    Queue<_node> stack(_node_num);
    stack.appendRight(_node{0, 0});
    visited[0] = true;
    while(!stack.isEmpty()){
        _node node = stack.popRight();
        for(long unsigned i = 0; i < _node_num; i++){
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

template<long unsigned _node_num>
bool Graph<_node_num>::isRinged_directed() const{
    /* In DFS, if a node is visited twice, then the graph is ringed */
    bool visited[_node_num] = {false};
    Queue<long unsigned> stack(_node_num);
    stack.appendRight(0);
    visited[0] = true;
    while(!stack.isEmpty()){
        long unsigned node = stack.popRight();
        for(long unsigned i = 0; i < _node_num; i++) {
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

template<long unsigned _node_num>
bool Graph<_node_num>::isRinged() const{
    /* check whether the graph is ringed */
    /* In DFS, if a node is visited twice, then the graph is ringed */
    if(directed) return isRinged_directed();
    else return isRinged_undirected();
}