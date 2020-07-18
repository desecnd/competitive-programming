/*
* author: pavveu
* task: Count Distinct K-length paths 
* time: O(n^3 log k)
* solution: DP with Binary Exponent optimalization
*
* explanation:
*
* if linear iterative dp can be written in O(1) space, we surely can use Binary Exp
*
* couting paths in O(m * k) 
*
* FOR(i, k)	FOR(v, V) FOR(u, G[v])
*	dp[u][i + 1] += dp[v][i];
*
* which can be written in O(1) space
*
* FOR(i, k) FOR(v, V) FOR(u, G[v]) 
* 	new_dp[u] += 1 * dp[v]
*
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
using matrix = vector<vll>;
using graph = matrix;

#define FOR(name__, upper__) for (int (name__) = 0; (name__) < (upper__); ++(name__))
#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple

template<class T>
void initialize_matrix(vector<vector<T>>& matrix, int rows, int cols, T value) {
	assert(matrix.empty());
	FOR (row, rows) 
		matrix.emplace_back(cols, value);
}

ll mod = 1e9 + 7;

matrix operator*(const matrix& a, const matrix& b) {
	int n = a.size();
	matrix c; 
	initialize_matrix(c, n, n, 0ll);
	FOR(i, n) FOR(j, n) FOR(k, n) {
		c[i][j] += a[i][k] * b[k][j];	
		c[i][j] %= mod;
	}
	return c;
}


void go() {
	int V, E, k; 
	cin >> V >> E >> k;

	matrix G, paths;
	initialize_matrix(G, V, V, 0ll);
	initialize_matrix(paths, V, V, 0ll);

	// k == 0
	FOR(i, V) paths[i][i] = 1;

	FOR(e, E) {
		int v, u; 
		cin >> v >> u;
		v--, u--;
		G[u][v] = 1ll;
	}

	while ( k > 0 ) {
		if ( k % 2 ) paths = G * paths;
		G = G * G;
		k /= 2;
	}

	ll ans = 0;
	FOR(i, V) 
		FOR(j, V)
			ans = ( ans + paths[i][j] ) % mod;

	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	go();

	return 0;
}
