/*
* author: pavveu
* task: Find Shortest Path from s to t
* time: O(V log E)
* solution: Dijkstra with DECREASE KEY
*/
 
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using edge = tuple<int,int>; // edge weight, vertex
using graph = vector<vector<edge>>;
 
#define mp make_pair
#define mt make_tuple
#define all(x) begin(x), end(x)
 
const int inf = 1e9;
 
int dijkstra(graph& G, int s, int t) {
    int V = G.size();

    vi dist(V, inf);
    dist[s] = 0;
 
    set<tuple<int,int>> Q;
    Q.emplace(dist[s], s);
 
    while ( Q.size() ) {
        int d, v; 
        tie(d, v) = *Q.begin(); Q.erase(Q.begin());
 
        for ( edge& e : G[v] ) {
            int w, u; 
            tie(w, u) = e;
 
            if ( dist[u] > dist[v] + w ) {
                if ( dist[u] != inf ) 
                    Q.erase(Q.find(mt(dist[u], u)));
 
                dist[u] = dist[v] + w;
                Q.emplace(dist[u], u);
            } 
        }
    }
 
    return dist[t];
}
 
void go() {
    int V, E; cin >> V >> E;
 
    graph G(V);
    for (int e = 0; e < E; e++) {
        int v, u, w; cin >> v >> u >> w;
        v--, u--;
        G[v].emplace_back(w, u);
    }

    int s, t;
    cin >> s >> t;
    s--, t--;
 
    cout << dijkstra(G, s, t) << "\n";
}
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    go();
 
    return 0;
} 