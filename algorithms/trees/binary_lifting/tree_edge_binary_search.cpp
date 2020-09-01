/*
 * author: pavveu
 * task: Binary Search value on path from u to v
 * time: 
	*	O(log n) per query
 	*	O(nlogn) preproces
 * solution: 
 	* 	Binary Lifting LCA + binary search
 */ 

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vi>;
using vvll = vector<vll>;
using graph = vector<vector<pair<int,int>>>;

#define FOR(name__, val__) for(int name__ = 0; name__ < (val__); name__++)

template<typename T>
void initialize_matrix(vector<vector<T>>& matrix, int rows, int cols, T val) {
	assert(matrix.size() == 0);
	FOR(row, rows) 
		matrix.emplace_back(cols, val);
}

struct binary_lifting {
	static constexpr ll id = 0ll;
	int V, root, dep;
	vi depth;

	vvi parent;
	vvll path_sum;

	binary_lifting(const graph& g, int root) : V(g.size()), root(root), dep(log2(V) + 1), depth(V, -1) {
		initialize_matrix(parent, dep, V, -1);
		initialize_matrix(path_sum, dep, V, id);

		dfs(g, root, -1, id);

		FOR(j, dep - 1) FOR(u, V) {
			int p = parent[j][u];
			if ( p != -1 ) {
				parent[j + 1][u] = parent[j][p];
				path_sum[j + 1][u] = path_sum[j][u] + path_sum[j][p];
			}
		}
	}	

	void dfs(const graph& g, int u, int p, int w) {
		if ( p == -1 ) depth[u] = 0;  
		else depth[u] = depth[p] + 1;

		path_sum[0][u] = w;
		parent[0][u] = p;

		for (auto edge : g[u]) {
			auto[weight, v] = edge;
			if ( depth[v] == -1 ) dfs(g, v, u, weight);
		}
	}

	pair<ll, int> jump(int u, int k) {
		ll sum = id;
		FOR(j, dep) {
			if ( u == -1 ) break;
			if ( k & (1<<j) ) { 
				sum += path_sum[j][u];
				u = parent[j][u];
			}
		}
		return {sum, u};
	}


	int lca(int u, int v) {
		if ( depth[v] < depth[u] ) swap(u, v);
		auto[temp, new_v] = jump(v, depth[v] - depth[u]);
		v = new_v;
		if ( u == v ) return u;

		for (int j = dep - 1; j >= 0; j--) {
			if ( parent[j][u] != parent[j][v] ) {
				u = parent[j][u];
				v = parent[j][v];
			}
		}

		return parent[0][u];
	}

	// binary_search up the tree, 
	// find first ancestor which is <=sum distance from u
	template<class Comparator>
	int binary_search(int u, ll sum, Comparator comp ) {
		for (int j = dep - 1; j >= 0; j-- ) {
			if ( parent[j][u] != -1 && comp(path_sum[j][u], sum) ) {
				sum -= path_sum[j][u];
				u = parent[j][u];
			}
		}
		return u;
	}

	// Find where someone with x energy will end, going from u -> v
	// if to traverse edge with weight w, equal amount of energy is needed
	int where_stops(int u, int v, ll energy) {
		int w = lca(u, v);
		auto[uwdist, temp1] = jump(u, depth[u] - depth[w]);
		auto[vwdist, temp2] = jump(v, depth[v] - depth[w]);

		if ( energy >= uwdist + vwdist ) return v; 
		else if ( energy > uwdist ) {
			return parent[0][binary_search(v, vwdist + uwdist - energy, less<ll>())];
		}
		else {
			return binary_search(u, energy, less_equal<ll>());
		}
	}
};	



void go() {
	int V; cin >> V;

	int E = V - 1;

	graph g(V);

	FOR(e, E) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;

		g[u].emplace_back(w, v);
		g[v].emplace_back(w, u);
	}

	binary_lifting bl(g, 0);

	int queries; cin >> queries;

	while ( queries-- ) {
		int a, b; ll x;
		cin >> a >> b >> x;
		a--, b--;

		cout << bl.where_stops(a, b, x) + 1 << "\n";
	}
}

void test(int root = 0) {
	using query = tuple<int, int, ll, int>;
	vector<query> queries;


	int V = 5;
	graph g(V);

	g[0].emplace_back(20, 1);
	g[1].emplace_back(20, 0);

	g[2].emplace_back(15, 1);
	g[1].emplace_back(15, 2);

	g[0].emplace_back(15, 3);
	g[3].emplace_back(15, 0);

	g[4].emplace_back(10, 3);
	g[3].emplace_back(10, 4);

	binary_lifting bl(g, root);

	queries.emplace_back(2,4,0ll,2);
	queries.emplace_back(2,4,7ll,2);
	queries.emplace_back(2,4,14ll,2);
	queries.emplace_back(2,4,15ll,1);
	queries.emplace_back(2,4,16ll,1);
	queries.emplace_back(2,4,35ll,0);
	queries.emplace_back(2,4,36ll,0);
	queries.emplace_back(2,4,49ll,0);
	queries.emplace_back(2,4,50ll,3);
	queries.emplace_back(2,4,51ll,3);
	queries.emplace_back(2,4,59ll,3);
	queries.emplace_back(2,4,60ll,4);
	queries.emplace_back(2,4,1000000000000000000ll,4);
	queries.emplace_back(0,2,20ll,1);
	queries.emplace_back(0,2,5ll,0);
	queries.emplace_back(0,2,21ll,1);
	queries.emplace_back(0,2,19ll,0);
	queries.emplace_back(0,2,1000000000000000000ll,2);
	queries.emplace_back(0,2,35ll,2);

	for (query q : queries) {
		auto[a, b, energy, answer] = q;
		assert( bl.where_stops(a, b, energy) == answer );
	}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

	FOR(i, 5) test(i);

    go();
    return 0;
}
