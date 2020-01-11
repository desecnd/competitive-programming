/*
* author: pavveu
* task: find tree diameter
* time: O(n)
* solution: greedy
*
* tree diameter is longest path in a tree
* in order to find it, we can use one tricky greedy aproach
*
* first of all lets see that after doing bfs from any node
* in the three, the furthest away is always diameter end
* 
* otherwise, we could find distance larger then diameter 
* which cannot occure
* 
* doing bfs from that end we will find diameter length 
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
#define mp make_pair

pair<int,int> bfs(graph& G, int V, int s) {
    vi dist(V, inf);
    dist[s] = 0;
    queue<int> Q;
    Q.push(s);

    while (Q.size()) {
        int v = Q.front(); Q.pop();
        for (int u : G[v]) {
            if ( dist[u] == inf ) {
                Q.push(u);
                dist[u] = dist[v] + 1;
            }
        }
    }

    auto it = max_element(all(dist));
    return mp(std::distance(dist.begin(), it), *it);
}

void go() {
    int V, E;
    cin >> V; E = V - 1;

    graph T(V);
    for (int e = 0; e < E; e++) {
        int v,u;
        cin >> v >> u;
        v--,u--;

        T[v].push_back(u);
        T[u].push_back(v);
    }

    // p.first is end of diameter for sure
    auto p = bfs(T, V, 0);
    // so max distance is another end of diameter
    p = bfs(T, V, p.first);
    cout << "Diameter: " << p.second << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    go();
     
    return 0;
}