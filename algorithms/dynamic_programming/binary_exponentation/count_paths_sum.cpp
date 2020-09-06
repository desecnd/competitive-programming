/*
* author: pavveu
* task: Count Number of <= k - paths ending at vertex 1 on a chessboard
* time: O(N^3logk)
* solution: DP + Matrix Exp Optimization
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
using graph = vector<vi>;

#define FOR(name__, upper__) for (int name__ = 0; name__ < (upper__); ++name__)
#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple

const int V = 64;
const int N = 65;
using T = uint32_t;
using matrix = array<array<T, N>, N>;

matrix operator*(const matrix& a, const matrix& b) {
	int n = a.size();
	matrix c{}; 

	FOR(i, n) FOR(j, n) FOR(k, n) {
		c[i][j] += a[i][k] * b[k][j];	
	}
	return c;
}

array<T, N> operator*(const matrix& a, const array<T,N>& x) {
	array<T,N> y{};
	FOR(i, N) FOR(k, N) {
		y[i] += a[i][k] * x[k];
	}
	return y;
}

matrix matrix_exponentation(matrix a, ll b) {
	matrix res{};
	FOR(i, N) res[i][i] = 1;

	while ( b > 0 ) {
		if ( b & 1 ) res = res * a;
		a = a * a;
		b /= 2;
	}
	return res;
}

graph build_chessboard_adj_list() {
	graph chessboard(V);

	vector<pii> dirs { {2, 1}, {-2, -1}, {-2, 1}, {2, -1}, 
				{1, 2}, {-1, -2}, {-1, 2}, {1, -2} };

	FOR(i, V) {
		int row = i / 8;
		int col = i % 8;

		for (auto p : dirs) {
			auto[r, c] = p;
			int row2 = row + r;
			int col2 = col + c;

			if ( row2 >= 0 && col2 >= 0 && row2 < 8 && col2 < 8 ) {
				int j = row2 * 8 + col2;
				chessboard[i].emplace_back(j);
			}
		}
	}

	return chessboard;
}

uint32_t solve_using_dp(uint32_t k) {
	graph adj { build_chessboard_adj_list() };

	// sum of zero paths = 1
	vector<uint32_t> dp(N, 1);
	dp[V] = 0;

	// dp[V] = sum of paths ending at 1 of lenght k-1

	FOR(ii, int(k)) {
		vector<uint32_t> new_dp(N, 0);

		FOR(u, V) {
			for (int v : adj[u]) {
				new_dp[v] += dp[u];
			}
		}
		// calculate sum of paths ending at v
		new_dp[V] += dp[V];
		new_dp[V] += dp[0];

		dp = new_dp;
	}


	return dp[V] + dp[0];
}

uint32_t solve_using_matrix(uint32_t k) {
	graph adj { build_chessboard_adj_list() };

	array<T,N> x{}; // k = 0
	FOR(i, N - 1) x[i] = 1;

	matrix A{};
	FOR(u, V) for (int v : adj[u]) A[v][u]++;
	A[V][V] = 1;
	A[V][0] = 1;

	matrix B = matrix_exponentation(A, k);
	auto y = B * x;
	return y[0] + y[V];
}


void go() {
	uint32_t k;
	cin >> k;
	cout << solve_using_matrix(k) << "\n";
}

void test() {
	vector<T> values { 9231, 123, 0, 1352, 1919, 9284, 12, 1111, 1342 };

	for (T k : values) {
		T matrix_ans { solve_using_matrix(k) };
		T dp_ans { solve_using_dp(k) };
		assert(dp_ans == matrix_ans);
	}
}


int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	test();
	go();

	return 0;
}
