/*
* author: pavveu
* task: Solve Linear Recurrences with constant factors
* time: O(n^3logk)
* solution: Constant Dynamic Programing - Matrix Optimalization
* 	
* 	Solve Linear Recurrence in form:
* 		ai = FOR(j, n) cj * a(i - j) + p + q*(i + n) + r*(i + n)^2
*
* 		x = ( ai, a(i + 1), a(i + 2), ..., a(i + n - 1), 1, (i + n), (1 + n)^2 ) 
*
* 		using linear algebra order of multiply
* 			x - input column vector of size N - dp
* 			A - transformation matrix N x N 
* 				new_dp[i] += aij * dp[j]
* 			y - result column vector of size N - new_dp
*
* 			B = A^k
* 			y = Bx
*
* 			y[0] stores solution - ak
*
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

using T = ll;
using matrix = vector<vector<T>>;
const ll mod = 1e9 + 7;

void initialize_matrix(matrix& m, int rows, int cols, T value) {
	assert(m.size() == 0);
	FOR (row, rows) 
		m.emplace_back(cols, value);
}

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

vector<T> operator*(const matrix& a, const vector<T>& x) {
	int n = a.size();
	vector<T> y(n, 0);

	FOR(i, n) FOR(k, n) {
		y[i] += a[i][k] * x[k];
		y[i] %= mod;
	}
	return y;
}

matrix matrix_exponentation(matrix a, ll b) {
	int n = a.size();
	matrix res;
	initialize_matrix(res, n, n, 0ll);
	FOR(i, n) res[i][i] = 1;

	while ( b ) {
		if ( b & 1 ) res = res * a;
		a = a * a;
		b /= 2;
	}
	return res;	
}

ll solve_using_matrix(vi& a, vi& c, int p, int q, int r, int n, ll k) {
	int m = n + 3;

	// x - column vector 
	// x(i) = (ai, ai+1, ... , ai+n-1, 1, n + i, (n+i)^2), i = 0
	vector<T> x(m);
	FOR(i, n) x[i] = a[i];
	x[n] = 1;
	x[n + 1] = n;
	x[n + 2] = n * n;

	// A - matrix of transition from x to x + 1
	matrix A;
	initialize_matrix(A, m, m, 0ll);

	// Matrix is build like in linear algebra
	// A[i][j] = aij = i <- j   
	// yi = aij * xj 
	FOR(j, n - 1) A[j][j + 1] = 1;

	FOR(j, n) A[n - 1][j] = c[n - 1 - j];
	A[n - 1][n] = p;
	A[n - 1][n + 1] = q;
	A[n - 1][n + 2] = r;

	A[n][n] = 1; 

	A[n + 1][n] = 1;
	A[n + 1][n + 1] = 1;

	A[n + 2][n + 2] = 1;
	A[n + 2][n + 1] = 2;
	A[n + 2][n] = 1;
	

	// B = A^k+1
	matrix B  = matrix_exponentation(A, k);

	// y - column vector
	// Bx = y
	auto y = B * x;
	return y[0];
}

ll solve_using_dp(vi& a, vi& c, int p, int q, int r, int n, ll k) {
	int m = n + 3;
	vll dp(m, 0);

	FOR(i, n) dp[i] = a[i];
	dp[n] = 1; // 1
	dp[n + 1] = n; // i
	dp[n + 2] = n * n; // i^2

	FOR(i, k) {
		vll new_dp(m, 0);

		// new_dp[0]
		FOR(j, n) new_dp[n - 1] += c[j] * dp[n - j - 1];
		new_dp[n - 1] += p * dp[n];
		new_dp[n - 1] += q * dp[n + 1];
		new_dp[n - 1] += r * dp[n + 2];

		// new_dp[1:n-1]
		FOR(j, n - 1) 
			new_dp[j] += 1 * dp[j + 1];

		new_dp[n] += 1 * dp[n]; // 1

		new_dp[n + 1] += 1 * dp[n]; // 1
		new_dp[n + 1] += 1 * dp[n + 1]; // i

		new_dp[n + 2] += dp[n + 2];
		new_dp[n + 2] += 2 * dp[n + 1];
		new_dp[n + 2] += dp[n];

		dp = new_dp;
	}

	return dp[0];
}

void go() {
	int n;
	ll k;
	cin >> n >> k;

	vi a(n); for (auto& i : a) cin >> i;
	vi c(n); for (auto& i : c) cin >> i; int p, q, r;
	cin >> p >> q >> r;

	ll matrix_ans { solve_using_matrix(a, c, p, q, r, n, k) };
	// ll dp_ans { solve_using_dp(a, c, p, q, r, n, k) };
	// assert(dp_ans == matrix_ans);
	cout << matrix_ans << "\n";
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);
	go();
	return 0;
}
