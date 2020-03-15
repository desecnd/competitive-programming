/*
* author: pavveu
* task: Calculate Most scored Path between Source and Sink (node with out deg = 0)
* time: O(V + ElogN)
* solution: 
* solution: DP on SCC DAG
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
using edge = tuple<int, int, int>; // id, w, from
using graph = vector<vector<edge>>;

#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple

void dfs1(graph& G, vi& vis, vi& order, int v) {
	vis[v] = 1;
	for (edge& e : G[v]) {
		int w, i, u;
		tie(w, i, u) = e;
		if ( !vis[u] ) dfs1(G, vis, order, u);
	}
	order.push_back(v);
}

void dfs2(graph& G, vi& vis, vi& scc, int n, int v) {
	vis[v] = 1;
	scc[v] = n;
	for (edge& e : G[v] ) {
		int w, i, u;
		tie(w, i, u) = e;
		if ( !vis[u] ) dfs2(G, vis, scc, n, u);
	}
}

void go() {
	int V, E; cin >> V >> E;

	graph G(V), T(V);
	for (int e = 0; e < E; e++) {
		int v, u, w; cin >> v >> u >> w;
		v--, u--;	

		G[v].emplace_back(w, e, u);
		T[u].emplace_back(w, e, v);
	}

	vi score(V);
	for (int &i : score) 
		cin >> i;

	int s; cin >> s; s--;
	
	// init all arrays
	vi vis(V, 0), scc(V, -1), order;

	// get all sccs on stack
	for (int i = 0; i < V; i++) 
		if ( !vis[i] ) dfs1(G, vis, order, i); 

	// reverse stack -> queue
	reverse(all(order));

	int sccs = 0;
	vis.assign(V, 0);

	// get SCC's in topological order
	for (int v : order) {
		if ( vis[v] ) continue;

		dfs2(T, vis, scc, sccs, v);
		sccs++;
	}

	int startingScc = scc[s]; 
	vll sccScore(sccs, 0);
	graph meta(sccs); 

	// create meta DAG
	for (int v = 0; v < V; v++) {
		sccScore[scc[v]] += score[v];
		for ( edge& e : G[v] ) {
			int w, i, u;	
			tie(w, i, u) = e;
			int su = scc[u], sv = scc[v];
			if ( su == sv ) sccScore[sv] += w;
			else meta[sv].emplace_back(w, i, su);
		}
	}

	// Store SCC DAG DP
	const ll ninf = numeric_limits<ll>::min();
	vll dp(sccs, ninf);
	dp[startingScc] = sccScore[startingScc];

	// for all strongly connected components
	for ( int c = 0; c < sccs; c++ ) { 
		if ( dp[c] == ninf ) continue; 

		for ( edge& e : meta[c] ) {
			int w, i, u;	
			tie(w, i, u) = e;
			dp[u] = max(dp[u], dp[c] + w + sccScore[u]);
		}
	}

	cout << *max_element(all(dp)) << "\n";
}		

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	go();

	return 0;
}