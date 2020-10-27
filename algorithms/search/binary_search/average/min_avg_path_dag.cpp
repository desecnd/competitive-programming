/*
* author: pavveu
* task: Find Minimum Average Path on DAG
* solution: 
* 		Fix Average and treat it as constant
* 		we get following equation:
*
* 		(w1 + w2 + w3 + ... + wk)/k = avg
*
* 		Now we want to Binary Search trough this value
* 		so in our check function we hold invariant:
*
* 		(w1 + w2 + w3 + ... + wk)/k <= avg   <--> check() = true
*
* 		K is a positive number so we multiply both sides by k
* 		w1 + w2 + w3 + ... + wk <= k * avg
*
* 		On both sides we have k elements:
*
* 		w1 + w2 + w3 + ... + wk <= avg + avg + avg ... + avg
*
* 		We can substract right side from this equation, and 
* 		group elements together
*
* 		(w1 - avg) + (w2 - avg) + (w3 - avg) + ... + (wk - avg) <= 0
*
* 		So we reduced our problem from finding minimum average to
* 		finding shortest Path on modified DAG:
*
* 		w --> w - avg
*
* 		In summary, we binary search on value avg, use it as a constant
* 		To find a shortest path on modified DAG. 
* 		We check if shortest path from 1 do V is <= 0, if so,
* 		we can for sure obtain <= current average
*
* time: O( (V + E) * log( |W| * eps^-1 ) )
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

#define FOR(name__, upper__) for (int name__ = 0; name__ < (upper__); ++name__)
#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple

struct edge {
	int w, dst;
	edge(int weight, int destination) : w(weight), dst(destination) {}
};

using graph = vector<vector<edge>>;

// Check if we can obtain average path <= avg
bool check(graph& adj, vi& parent, double avg) {
	int V = adj.size();

	vector<double> dist(V, 2e10);
	dist[0] = 0.0;
	parent[0] = -1;

	FOR(u, V) {
		for (edge e : adj[u]) {
			// MODIFIED DAG, w --> w - avg
			double new_weight = e.w - avg;
			int v = e.dst;

			if ( dist[v] > dist[u] + new_weight ) {
				dist[v] = dist[u] + new_weight;
				parent[v] = u;
			}
		}
	}

	return (dist[V - 1] <= 0);
}

void go() {
	int V, E;
	cin >> V >> E;
	graph adj(V);

	FOR(e, E) {
		int u, v, w; 
		cin >> u >> v >> w;
		u--, v--;
		// Build Dag, u -> v iff u < v 
		if ( u < v ) adj[u].emplace_back(w, v);
		else adj[v].emplace_back(w, u);
	}

	vi parent(V);
	double lo { 0 }; 	// lo is impossible
	double hi { 110 };	// hi is possible

	// 0 is risky, lets check it first, 
	// its lower bound on this task
	if ( check(adj, parent, 0)) {
		hi = 0;
	} 
	else {
		FOR(iter, 100) {
			double mid { (lo + hi)/2.0 };
			if ( check(adj, parent, mid) ) hi = mid;
			else lo = mid;
		}
	}

	check(adj, parent, hi);

	// Print Solution:
	vi ans;
	int x = V - 1;

	while ( x != -1 ) {
		ans.push_back(x);
		x = parent[x];
	}
	reverse(all(ans));

	cout << ans.size() - 1 << endl;

	for (int u : ans) cout << u + 1 << " ";

	cout <<endl;
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	go();

	return 0;
}
