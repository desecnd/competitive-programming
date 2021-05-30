/*
* author: pavveu
* algorithm: Edmonds-Karp Maximum Flow
* time: O(V * |E|^2)  
* 
* Algorithm uses BFS to find augumenting path from sink to source
* as long as one exists.
* Every edge has to have it reverse counterpart in opposite direction
* by calculating flow going through the network, we can always take route 
* that normally would go coutn as "negative flow", so we can actually take edge with 
* negative flow and 0 capacity, which would count as positive flow by equation 
*   path_flow = capacity - flow
*/

#ifndef EDMONDS_KARP_0958637458229341
#define EDMONDS_KARP_0958637458229341

#include <cassert>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <vector>
#define FOR(iter__, upper__) for (int iter__ = 0; iter__ < (int)(upper__); ++iter__)
#define FORU(iter__, upper__) for (size_t iter__ = 0; iter__ < (upper__); ++iter__)

template<typename T>
void initialize_matrix(std::vector<std::vector<T>>& matrix, size_t rows, size_t cols, T val) {
    assert(matrix.empty());
    FORU (row, rows) matrix.emplace_back(cols, val);
}

template<typename T>
class edmonds_karp {

private:
    size_t n_nodes;
    std::vector<std::list<int>> adj;
    std::vector<std::vector<T>> flow_matrix;
    std::vector<std::vector<T>> capacity_matrix;

    T bfs(std::vector<int> &parent, int source, int sink) {
        std::vector<bool> visited(n_nodes, false);
        std::queue<std::pair<int, T>> q; // pair: [capacity left on path, vertex]

        std::fill(parent.begin(), parent.end(), -1);

        q.emplace(source, INFINITY);
        visited[source] = true;

        while (q.size()) {
            auto[u, path_capacity] = q.front(); q.pop(); 

            for (int v : adj[u]) {
                T flow_left = capacity_matrix[u][v] - flow_matrix[u][v];

                if (flow_left > 0 && !visited[v]) {
                    parent[v] = u;
                    visited[v] = true;
                    T current_path_cap = std::min(flow_left, path_capacity);

                    if (v == sink) {
                        return current_path_cap;
                    }
                    
                    q.emplace(v, current_path_cap);
                }
            }
        }
        return 0;
    }

public:
    constexpr static int INFINITY = std::numeric_limits<T>::max();

    edmonds_karp(size_t n) : n_nodes(n), adj(n) {
        initialize_matrix(flow_matrix, n, n, 0);
        initialize_matrix(capacity_matrix, n, n, 0);
    }

    T max_flow(int source, int sink) {
        T sum_flow {0};
        T path_flow {0};
        std::vector<int> parent(n_nodes);

        while ((path_flow = bfs(parent, source, sink)) > 0) {
            int u = sink;

            while (u != source) {
                flow_matrix[parent[u]][u] += path_flow;
                flow_matrix[u][parent[u]] -= path_flow;
                u = parent[u];
            }

            sum_flow += path_flow;
        }

        return sum_flow;
    }

    void add_edge(int u, int v, T c) {
        adj[u].push_back(v);
        // reverse edge
        adj[v].push_back(u);
        capacity_matrix[u][v] = c;
    }
};

void test() {
    edmonds_karp<int> max_flow_solver(6);
    max_flow_solver.add_edge(0, 1, 11);
    max_flow_solver.add_edge(0, 2, 12);
    max_flow_solver.add_edge(2, 1, 1);
    max_flow_solver.add_edge(1, 3, 12);
    max_flow_solver.add_edge(2, 4, 11);
    max_flow_solver.add_edge(4, 3, 7);
    max_flow_solver.add_edge(3, 5, 19);
    max_flow_solver.add_edge(4, 5, 4);
    assert(max_flow_solver.max_flow(0, 5) == 23);
}

#endif