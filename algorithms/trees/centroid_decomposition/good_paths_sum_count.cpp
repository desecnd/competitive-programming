/*
* author: pavveu
* task: beautiful(vertex) = {1,0}, beautiful path has more or equal beautiful vertecies
	* Calculate sum distance of all beautiful paths
* time: O(nlog^2n)
* solution: Centroid Decomposition
*/

#include <bits/stdc++.h>
using namespace std;


#define FOR(name__, val__) for (int name__ = 0; name__ < (val__); name__++)
#define ALL(x) begin(x), end(x)

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using graph = vector<vi>;

// 0 indexed for queries
struct fenwick_tree {
	int n;
	vll t;
	
	fenwick_tree(int N) : n(N + 1), t(n, 0ll) {}

	inline int lowbit(int x) { return x & -x; }

	void update(int i, ll val) {
		i++;
		while ( i < n ) {
			t[i] += val;
			i += lowbit(i);
		}
	}

	ll prefsum(int i) {
		i++;

		ll val = 0;
		while ( i > 0 ) {
			val += t[i];
			i -= lowbit(i);
		}
		return val;
	}
};

struct dnc_trees {
	int V;

	graph adj;

	vi blocked;
	vi parent;
	vi subsize;

	vi beautiful;

	struct path {
		int good, bad;
		path(int g, int b) : good(g), bad(b) {}
	};

	dnc_trees(const graph& g, const vi& beauty) : V(g.size()), adj(g), blocked(V, 0), parent(V), subsize(V), beautiful(beauty) {}

	void calc_subtree_info(int u, int p) {
		parent[u] = p;
		subsize[u] = 1;

		for ( int v : adj[u] ) {
			if ( p != v && !blocked[v] ) {
				calc_subtree_info(v, u);
				subsize[u] += subsize[v];
			}
		}
	}

	void find_paths(vector<path>& paths, int u, int p, int good, int bad) {
		good += beautiful[u];
		bad += 1 - beautiful[u];
		paths.emplace_back(good, bad);

		for (int v : adj[u]) {
			if ( p != v && !blocked[v] ) {
				find_paths(paths, v, u, good, bad);
			}
		}	
	}

	ll solve_tree(int centroid, int comp_size) {
		// offset calculations:
		// centroid -> each subtree >= n/2 size
		// max_path = n/2 + centroid = n/2 + 1
		// so, max good - bad = n/2 + 1
		// we need range of [-n/2+1; n/2+1]
		// offset = n/2+1
		// range + offset = [0; (n/2 + 1)*2] = [0;n+2] = n+3 elements
		int offset = comp_size/2 + 1;
		fenwick_tree paths_sum(comp_size + 3);
		fenwick_tree paths_cnt(comp_size + 3);

		int default_good = beautiful[centroid];
		int default_bad = 1 - beautiful[centroid];

		ll res = default_good; 

		for (int v : adj[centroid]) {
			if ( blocked[v] ) continue; 

			vector<path> paths;
			find_paths(paths, v, centroid, default_good, default_bad);
			// query for past subtrees
			for ( path p : paths ) {
				if ( p.good >= p.bad ) res += p.good + p.bad;

				// get all for which p1.good + p2.good >= p1.bad + p2.bad
				// sum: p2.bad - p2.good <= p1.good - p1.bad
				// sum: p2.bad + p1.bad <= p1.good + p2.good

				ll paths_dist_sum = paths_sum.prefsum(offset + p.good - p.bad);
				ll paths_count = paths_cnt.prefsum(offset + p.good - p.bad);

				res += paths_dist_sum;
				res += paths_count * (p.good + p.bad);
			}

			// add subtree to data structure
			for ( path p : paths ) {
				// we delete centroid node from path, so we dont overcount it
				p.good -= default_good;
				p.bad -= default_bad;

				paths_sum.update(offset + p.bad - p.good, p.good + p.bad);
				paths_cnt.update(offset + p.bad - p.good, 1);
			}
		}

		return res;
	}

	// find centroid and divide to forest of trees
	ll dnc(int new_root) {
		calc_subtree_info(new_root, new_root);

		int comp_size = 0;
		int centroid = new_root;
		int best_size = subsize[new_root];

		queue<int> q;
		q.push(new_root);

		while ( q.size() ) {
			int u = q.front(); q.pop();
			comp_size++;

			int max_size = subsize[new_root] - subsize[u];
			for (int v : adj[u]) {
				if ( v != parent[u] && !blocked[v] ) {
					max_size = std::max(max_size, subsize[v]);
					q.push(v);
				}	
			}

			if ( max_size < best_size ) {
				best_size = max_size;
				centroid = u; 
			}
		}	

		// solve for current tree
		ll ways = solve_tree(centroid, comp_size);

		// delete centroid and split into forest of trees
		blocked[centroid] = 1;
		for (int v : adj[centroid]) {
			if ( !blocked[v] ) ways += dnc(v); 
		}
		return ways;
	}
};

void go() {
	int V, E;
	cin >> V;
	E = V - 1;

	graph adj(V);
	FOR(e, E) {
		int u, v;
		cin >> u >> v;
		u--, v--;

		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}

	vi beautiful(V);
	for (auto& i : beautiful) cin >> i;

	dnc_trees dnct(adj, beautiful); 
	cout << dnct.dnc(0) << endl;
}

void test() {
	int V = 8;
	vll ans_dnc(V, 59);
	vll ans_solve { 17, 24, 46, 8 , 8 , 54, 26, 26 };

	graph adj {
		{ 1 },
		{ 0, 2 },
		{ 1, 3, 4, 5 },
		{ 2 },
		{ 2 },
		{ 2, 6, 7 },
		{ 5 },
		{ 5 }
	};

	vi beautiful { 1, 0, 0, 0, 0, 1, 1, 1 };
	FOR(u, V) 
	{
		dnc_trees dnct(adj, beautiful); 
		assert(ans_solve[u] == dnct.solve_tree(u, V));
		assert(ans_dnc[u] == dnct.dnc(u));
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	test();
	go();

	return 0;
}
