/*
* author: pavveu
* task: Find bottleneck edge between 2 graph nodes per query 
* time: O (VlogV + E)
* solution: MST + Binary Lifting
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
using vvi = vector<vi>;
using edge = pair<int,int>;
using graph = vector<vector<edge>>;

#define FOR(name__, upper__) for (int name__ = 0; name__ < (upper__); ++name__)
#define DEBUG(name__, val__)  "( " << (name__) << ": " << (val__) << " )"
#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple

template<class T>
void initialize_matrix(vector<vector<T>>& matrix, int rows, int cols, T value) {
	assert(matrix.empty());
	FOR (row, rows) 
		matrix.emplace_back(cols, value);
}

const int inf = 1e9 + 100;

struct tree_jumps {
	const edge id = {inf, -1};
	int V, root, dep;
	vi depth;

	vvi parent;
	vvi min_weight;

	tree_jumps(const graph& g, int root = 0) : V(g.size()), root(root), dep(0), depth(V, -1)  {
		int n = 1;
		while ( n <= V ) n *= 2, dep++; 

		initialize_matrix(parent, dep, V, -1);
		initialize_matrix(min_weight, dep, V, inf);
		dfs(g, root, id);

		FOR(j, dep - 1) FOR(u, V) {
			int p = parent[j][u];
			if ( p != -1 ) {
			   	parent[j + 1][u] = parent[j][p]; 
				min_weight[j + 1][u] = std::min(min_weight[j][u], min_weight[j][p]);
			}
		}
	}

	void dfs(const graph& g, int u, edge e) {
		auto[w, p] = e;

		min_weight[0][u] = w;
		parent[0][u] = p;

		if ( p == -1 ) depth[u] = 0; 
		else  depth[u] = depth[p] + 1;

		for (edge e : g[u] ) {
			auto[w2, v] = e;
			if ( depth[v] == -1 ) dfs(g, v, {w2, u}); 
		}
	}

	edge jump(int u, int k) {
		int minw = inf;
		for (int j = dep - 1; u != -1 && j >= 0; j-- ) {
			if ( k & (1<<j) ) {
				minw = std::min(minw, min_weight[j][u]);
			   	u = parent[j][u];
			}
		}
		return { minw, u };
	}

	int lca(int u, int v) {

		if ( depth[u] > depth[v] ) swap(u, v);

		auto[dump, new_v] = jump(v, depth[v] - depth[u]);
		v = new_v;

		if ( v == u ) return v;

		for (int j = dep - 1; j >= 0; j--) {
			if ( parent[j][u] != parent[j][v] ) {
				u = parent[j][u];
				v = parent[j][v];
			}
		}

		return parent[0][u];
	}	

	int query(int u, int v) {
		int w = lca(u, v);
		int duw = depth[u] - depth[w];
		int dvw = depth[v] - depth[w];

		auto [flow1, dump1] = jump(u, duw);
		auto [flow2, dump2] = jump(v, dvw);

		return std::min(flow1, flow2);
	}
};

struct find_union {
	vi e;
	find_union(int n) : e(n, -1) {}

	int find(int x) { return e[x] < 0? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a);
		b = find(b);
		if ( a == b ) return false;

		if ( e[a] > e[b] ) swap(a, b);
		e[a] += e[b];
		e[b] = a;
		return true;
	}
};

graph mst(vector<tuple<int,int,int>>& edges, int V) {
	sort(all(edges));
    reverse(all(edges));

	find_union dsu(V);

	graph g(V);

	for (tuple<int,int,int> &e : edges) {
		auto[w, u, v] = e;

		if ( dsu.join(u, v) ) {
			g[u].emplace_back(w, v);
			g[v].emplace_back(w, u);
		}
	}

	return g;
}

void go() {
	int V, E;
	cin >> V >> E;

	vector<tuple<int,int,int>> edges;
	FOR(e, E) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;

		edges.emplace_back(w, u, v);
	}

	graph g( mst(edges, V) );
	tree_jumps tj(g, 0);

	int queries;
	cin >> queries;
	while ( queries-- ) {
		int a, b;
		cin >> a >> b;
		a--, b--;

		cout << tj.query(a, b) << "\n";
	}
}


int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	go();

	return 0;
}