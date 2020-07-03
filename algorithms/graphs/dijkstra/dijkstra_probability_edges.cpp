/*
* author: pavveu
* task: CHICAGO - 106 Miles to Chicago from SPOJ 
* time: O(E log V)
* solution: Dijkstra shortest path
*
* to find solution we have to find path from 1 to N, where p1 * p2 * .. * pn 
* on edges is maximal, where p0 is 1.0 other is weight / 100 
* 
* We could use Dijkstra only if we would accumulate distance on every edge
* so, every edge should be positive -> or above 1 if we multiply weight 
* here we got another situation, every edge is in (0, 1] interval
* so what we can do is simply inverse every probability
* calculate shortest path, and then reverse the answer
*/
 
#include <bits/stdc++.h>
using namespace std;
 
using vi = vector<int>;
using edge = tuple<double,int>;
using graph = vector<vector<edge>>;
 
#define all(x) begin(x), end(x)
#define mt make_tuple
 
const double inf = numeric_limits<double>::max();
 
void dijkstra(graph& G, int V, int s, int e ) {
    vector<double> dist(V, inf);
 
    // start probabiliy = 1.0
    dist[s] = 1.0;
 
    set<tuple<double,int>> Q;
    Q.emplace(dist[s], s);
 
    // Dijkstra with set and Decrease Key
    while ( Q.size() ) {
        double d; int v;
        tie(d, v) = *Q.begin(); Q.erase(Q.begin());
 
        for (edge& e : G[v]) {
            double w; int u;
            tie(w, u) = e;
 
            if ( dist[u] > dist[v] * w ) {
                // DECREASE KEY
                if ( dist[u] != inf ) 
                    Q.erase(Q.find(mt(dist[u], u)));
 
                dist[u] = dist[v] * w;
                Q.emplace(dist[u], u);
            }
        }
    }
 
    // we Reversed probability on every edge, so now we have to come back
    double ans = 100.0 / dist[e];
    cout << fixed << setprecision(6) << ans << " percent\n";
}
 
bool go(int n) {
    if ( !n ) return false;
    int V = n, E;
    cin >> E;
 
    graph G(V);
    for (int e = 0; e < E; e++) {
        int v, u, p;
        cin >> v >> u >> p;
        v--, u--;
 
        // reverse probability for dijkstra
        double w = 100.0 / p;
        G[v].emplace_back(w, u);
        G[u].emplace_back(w, v);
    }
 
    dijkstra(G, V, 0, V - 1);
    return true;
}
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
 
    int n;
    do {
        cin >> n;
    } while(go(n));
 
    return 0;
} 