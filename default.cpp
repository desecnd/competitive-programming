/*
* author: pavveu
* task:
* time:
* solution:
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
using graph = vector<vi>;

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

void go() {

}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	go();

	return 0;
}
