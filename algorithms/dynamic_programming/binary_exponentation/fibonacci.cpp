/*
* author: pavveu
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
	matrix c; 
	initialize_matrix(c, 2, 2, 0ll);
	FOR(i, 2) FOR(j, 2) FOR(k, 2) {
		c[i][j] += a[i][k] * b[k][j];	
		c[i][j] %= mod;
	}
	return c;
}


void go() {
	ll n; cin >> n;
	matrix fib, cost;
	 
	n += 1;

	initialize_matrix(fib, 2, 2, 0ll);
	initialize_matrix(cost, 2, 2, 0ll);

	FOR(i, 2) fib[i][i] = 1ll;

	cost[0][0] = 0ll;
	cost[0][1] = 1ll;
	cost[1][0] = 1ll;
	cost[1][1] = 1ll;

	while ( n > 0 ) {
		if ( n % 2 ) fib = cost * fib;
		cost = cost * cost;
		n /= 2;
	}

	cout << fib[0][0] << "\n";
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	go();

	return 0;
}
