/*
* author: pavveu
* task: find tree center
* time: O(n)
* solution: bfs  
*
* Tree Center(s - because there can be 2) 
* is a node with minimum eccentricity - distance to furtherst node
* its also in a half way of a derimeter - radius
* so if there is a center at node v, we now that 
* its eccentricity is radius of a tree
*
* there also can be 2 centers -> when derimeter is odd, it goes through 2 centers 
* connected by 1 edge, it this case radius is not derimeter/2 but (derimeter + 1) / 2
*
* to find center - node with minimum remoteness, we simply do BFS from all the leafs, and 
* vertices with max distance will be centers
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

using vi = vector<int>;
using graph = vector<vi>;
const int inf = 1e9;

#define all(x) begin(x), end(x)

// return pair of centers, if there is only one center, second == -1
pair<int,int> findCenters(graph& G, int V) {
    vi level(V, inf);
    vi deg(V, 0);
    queue<int> Q;

    // push all leafs, set level to 0
    for (int v = 0; v < V; v++) {
        deg[v] = G[v].size();
        if ( deg[v] == 1 ) {
            level[v] = 0; Q.push(v);
        }
    }

    // bfs, remove leafs at every step
    while ( Q.size() ) {
        int v = Q.front(); Q.pop();
        for (int u : G[v]) {
            deg[u]--;

            if ( deg[u] == 1 ) {
                level[u] = level[v] + 1;
                Q.push(u);
            }
        }
    }

    // max levle != min eccentricity 
    // when there are 2 centers max level = min eccentricity - 1 
    // otherwise its the same
    int maxLevel = *max_element(all(level));
    pair<int,int> centers {-1,-1};

    for (int v = 0; v < V; v++) {
        if ( level[v] == maxLevel ) {
            if ( centers.first == -1 ) centers.first = v;
            else centers.second = v;
        }
    }

    return centers;
}

void go() {
    int V, E;
    cin >> V; E = V - 1;

    graph T(V);
    for (int e = 0; e < E; e++) {
        int v, u; cin >> v >> u;
        v--, u--;

        T[v].push_back(u);
        T[u].push_back(v);
    }
    
    auto p = findCenters(T, V);
    if ( p.second != -1 ) cout << "Two Tree centers: " << p.first + 1 << " and " << p.second + 1 << "\n";
    else cout << "One Tree center: " << p.first + 1 << "\n";
}
    

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    go();
    return 0;
}