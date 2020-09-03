/* The code was inspired by Algorihms Live! problem solution
* author: pavveu
* task: USACO 2013 US Open, Gold - Problem 2 Yin and Yang
	* in tree with weights w c {-1, 1 }, count all paths
	* that are balanced (sum == 0) and path got a spliting point 
	* which splits path into 2 balanced paths
* time: O(n log n) 
* solution: Centroid Decomposition 
*/ 

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vi>;
using vvll = vector<vll>;

#define FOR(name__, val__) for(int name__ = 0; name__ < (val__); name__++)
#define all(x) begin(x), end(x)

struct edge {
	int w, dst;
	edge(int a, int b) : w(a), dst(b) {}
};

using graph = vector<vector<edge>>;

struct divide_and_conquer_trees {
	int V;
	graph adj;

	vi blocked;
	vi parent;
	vi subsize;

	struct path {
		int balance, good;
		path(int b, int g) : balance(b), good(g) {}
	};

	struct offset_map {
		int lo, hi;
		int n, offset;
		vi table;
		offset_map(int from_inc, int to_inc) : 
			lo(from_inc), hi(to_inc), n(to_inc - from_inc + 1), offset(-from_inc), table(n, 0) { }

		void clear() { fill(all(table), 0); } 
		void operator+=(const offset_map& om) { FOR(i, n) { table[i] += om.table[i]; } };
		int operator()(int i) const { assert(i >= lo && i <= hi); return table[i + offset]; } 
		int& operator()(int i) { assert(i >= lo && i <= hi); return table[i + offset]; }
	};

	vector<path> paths;

	divide_and_conquer_trees(const graph& g) : V(g.size()), adj(g), blocked(V, 0), parent(V), subsize(V), paths() {}

	// calculate parents and subtree sums
	void calc_tree_info(int u, int p) {
		parent[u] = p;
		subsize[u] = 1;

		for ( edge e : adj[u]) {
			int v = e.dst;
			if ( v != p && !blocked[v] ) {
				calc_tree_info(v, u);
				subsize[u] += subsize[v];
			}
		}
	}

	void find_paths(offset_map& seen, vector<path>&paths, int u, int p, int sum) {
		paths.emplace_back(sum, int(seen(sum) > 0));
		seen(sum)++;

		for ( edge e : adj[u] ) {
			if ( e.dst != p && !blocked[e.dst] ) 
				find_paths(seen, paths, e.dst, u, sum + e.w);
		}

		seen(sum)--;
	}
	

	// cnt number of paths that go through centroid
	ll solve_tree(int root, int comp_size) {

		// Care for max O(comp_size) !
		offset_map 
			good_all(-comp_size, comp_size), 
			bad_all(-comp_size, comp_size), 
			seen(-comp_size, comp_size);

		ll res = 0;

		for ( edge e : adj[root] ) {
			if ( blocked[e.dst] ) continue;

			vector<path> paths;
			find_paths(seen, paths, e.dst, root, e.w);

			for ( path p : paths ) {
				res += good_all(-p.balance);

				// its already yinyang path from root
				if ( p.good && p.balance == 0 ) {
					res++;
				}

				// its yinyaing split point is at root
				if ( p.good || p.balance == 0 ) res += bad_all(-p.balance);
			}

			for ( path p : paths ) {
				if ( p.good ) good_all(p.balance)++;
				else bad_all(p.balance)++;
			}
		}

		return res;
	}

	ll divide_and_conquer(int new_root) {

		calc_tree_info(new_root, new_root);
		int centroid = new_root;
		int best_size = subsize[centroid];
		int comp_size = 0;

		queue<int> q;
		q.push(new_root);

		while ( q.size() ) {
			int u = q.front(); q.pop();
			comp_size++;

			int max_size_left = subsize[new_root] - subsize[u];

			for ( edge e : adj[u] ) {
				if ( e.dst != parent[u] && !blocked[e.dst] ) {
					max_size_left = std::max(max_size_left, subsize[e.dst]);
					q.push(e.dst);
				}
			}

			if ( max_size_left < best_size ) {
				centroid = u;
				best_size = max_size_left;
			}
		}

		ll ways = solve_tree(centroid, comp_size);

		blocked[centroid] = 1;
		for (edge e : adj[centroid] ) 
			if ( !blocked[e.dst] ) ways += divide_and_conquer(e.dst);

		return ways;
	}
};


void go() {
	int V, E;
	cin >> V;
	E = V - 1;

	graph g(V);
	FOR(e, E) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		w = 2 * w - 1;
		g[u].emplace_back(w, v);
		g[v].emplace_back(w, u);
	}

	divide_and_conquer_trees dnct(g);
	cout << dnct.divide_and_conquer(0) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

	go();

    return 0;
}
