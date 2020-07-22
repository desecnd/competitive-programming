/*
* author: pavveu
* task: Count Distinct [0..K]-length paths
* time: O(8n^3 log k)  
* solution: DP with Binary Exponent optimalization
*
* explanation:
*   if you know how to calculate K-length paths, we need to store sum somehow
* 	sum_and_dp = 2x2 matrix of matrices (2 states, sum and dp) 
*  
* 	new_sum[i] += sum[i]
* 	new_sum[i] += dp[j]
* 	new_dp[i]  += dp[j]
*
* 	sum_and_dp =
* 				sum , 			dp 
* 		sum [ [ Identity  ] [ Zero  ] ]
*	 	dp  [ [ Graph     ] [ Graph ] ]
*
*	solution is sum_and_dp[0 and 1][0]
*
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vu = vector<uint32_t>;
using vll = vector<ll>;
using pii = pair<int,int>;
using vpii = vector<pii>;
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

	matrix adjency_matrix, paths_cnt, sum_and_dp;
	initialize_matrix(adjency_matrix, V, V, 0ll);

	FOR(e, E) {
		int v, u;
		cin >> v >> u;
		v--, u--;
		adjency_matrix[v][u] = 1;
	}

	initialize_matrix(sum_and_dp, 2*V, 2*V, 0ll);
	FOR(i, V) sum_and_dp[i][i] = 1ll; 

	FOR(i, V) FOR(j, V) {
		sum_and_dp[i + V][j] = sum_and_dp[V + i][V + j] = adjency_matrix[i][j];  
	}

	initialize_matrix(paths_cnt, 2*V, 2*V, 0ll);
	FOR(i, 2*V) paths_cnt[i][i] = 1ll; 

	while ( k > 0 ) {
		if ( k % 2 ) paths_cnt = sum_and_dp * paths_cnt;
		sum_and_dp = sum_and_dp * sum_and_dp;
		k /= 2;
	}

	uint32_t ans = 0u; 
	FOR (i, 2*V) FOR(j, V) ans = (ans +  paths_cnt[i][j]) % mod;
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	go();

	return 0;
}
