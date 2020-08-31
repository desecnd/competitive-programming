/*
* author: pavveu
* task: Find Lowest Common Ancestor of u in v per query
* time: O(logV) per query
* solution: LCA Binary Lifting  
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
using graph = vector<vi>;
using vvi = vector<vi>;

#define FOR(name__, upper__) for (int name__ = 0; name__ < (upper__); ++name__)
#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple

template<class T>
void initialize_matrix(vector<vector<T>>& matrix, int rows, int cols, T value) {
    assert(matrix.empty());
    FOR (row, rows) 
        matrix.emplace_back(cols, value);
}

struct binary_lifting {
    int V, root, dep;
    vi depth;
    vvi parent;

    binary_lifting(const graph& g) : V(g.size()), root(0), dep(0), depth(V, -1) {
        int n = 1;
        while ( n <= V ) n *= 2, dep++;

        initialize_matrix(parent, dep, V, -1);

        dfs(g, root, -1);

        FOR(j, dep - 1) FOR(u, V) 
            if ( parent[j][u] != -1 ) parent[j + 1][u] = parent[j][parent[j][u]];
    }

    void dfs(const graph& g, int u, int p) {
        if ( p == -1 ) depth[u] = 0; 
        else depth[u] = depth[p] + 1; 

        parent[0][u] = p;

        for (int v : g[u]) {
            if ( depth[v] == -1 ) {
				dfs(g, v, u);
			}
        }
    }

    int jump(int u, int k) {
        for (int j = 0; u != -1 && j < dep; j++) {
            if ( k & (1<<j) ) u = parent[j][u];
        }
        return u;
    }


    int lca(int u, int v) {
        if ( depth[u] > depth[v] ) swap(u,v);
        v = jump(v, depth[v] - depth[u]);
        if ( v == u ) return u;

        for (int j = dep - 1; j >= 0; j--) {
            if ( parent[j][u] != parent[j][v] ) {
                u = parent[j][u];
                v = parent[j][v];
            }
        }
        return parent[0][u];
    }
};

void go() {
    int V, E;
    cin >> V;
    E = V - 1;

    graph g(V);
    FOR(e, E) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    binary_lifting bl(g);

	int queries;
	cin >> queries;

	while ( queries-- ) {
		int a, b; cin >> a >> b;
		a--, b--;


		cout << bl.lca(a, b) + 1 << "\n";
	}
}


int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);

    go();

    return 0;
}