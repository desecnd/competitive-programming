/*
* author: pavveu
* task: TRAFFICN fro SPOJ 
* time: O(E log V)
* solution: Dijkstra with DECREASE KEY
*
* Problem is to find shortest path in Graph
* with possibility of building one additional road
* from given set 
*
* We can use Dijkstra algorithm with state distance meaning
* whats the shortest distance at state 0 or 1 
* where 0 stands for not building additional road (yet)
* and 1 stands for path with addtional road already built
*/
 
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using edge = tuple<int, int, int>; // weight, isItSpecial, target
using graph = vector<vector<edge>>;
 
#define mp make_pair
#define mt make_tuple
#define all(x) begin(x), end(x)
 
const int inf = 2e9;
 
int dijkstra(graph& G, int V, int s, int t) {
    vector<vi> dist(2, vi(V, inf));
    dist[0][s] = 0;
 
    set<tuple<int, int,int>> Q;
    Q.emplace(dist[0][s], 0, s);
 
    while ( Q.size() ) {
        int d, used, v; 
        tie(d, used, v) = *Q.begin(); Q.erase(Q.begin());
        // cout << "Now in " << v + 1 << " with distance: " << d << " used: " << used << endl;
 
        for ( edge& e : G[v] ) {
            int w, special, u; 
            tie(w, special, u) = e;
 
            int state = special + used;
            if ( state <= 1 && dist[state][u] > dist[used][v] + w ) {
                if ( dist[state][u] != inf )
                    Q.erase(Q.find(mt(dist[state][u], state, u)));
 
                dist[state][u] = dist[used][v] + w;
                // cout << "Updating: " << u + 1 << " with distance: " << dist[state][u] << " on state: " << state << "\n";
                Q.emplace(dist[state][u], state, u);
            } 
        }
    }
 
    int d = min(dist[0][t], dist[1][t]);
    return ( d == inf ? -1 : d );
}
 
void go() {
    int V, E, k, s, t; 
    cin >> V >> E >> k >> s >> t;
    s--, t--;
    graph G(V);
 
    for (int e = 0; e < E; e++) {
        int v, u, w; cin >> v >> u >> w;
        v--, u--;
        G[v].emplace_back(w, 0, u);
    }
    
    for (int e = 0; e < k; e++) {
        int v, u, w; cin >> v >> u >> w;
        v--, u--;
        G[v].emplace_back(w, 1, u);
        G[u].emplace_back(w, 1, v);
    }
 
    cout << dijkstra(G, V, s, t) << "\n";
}
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while ( t-- ) go();
 
    return 0;
} 