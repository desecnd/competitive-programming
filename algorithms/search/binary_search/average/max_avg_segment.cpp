/*
* author: pavveu
* task:
* 		Find segment of lenght >= D, with maximum average
* solution:
* 		We fix average and treat it as constant
*
* 		(a[l] + a[l + 1] + a[l + 2] ... a[r - 1])/(r - l) >= avg
*
* 		a[l] + a[l + 1] + a[l + 2] .... a[r - 1] >= avg(r - l)
*
* 		a[l] - avg + a[l + 1] - avg + ... a[r - 1] - avg >= 0
*
* 		We can use prefix sums for O(1) check
*
* 			pref[i] = a[0] -avg  + a[1] -avg  + ... + a[i - 1] - avg
* 			sum[l, r) = pref[r] - pref[l] 
*
* 			pref[r] - pref[l] >= 0
* 			pref[r] >= pref[l]
*
* 		If for every r, we can find l such that prefix is minimum quickly, we got answer
* 		- We can precalculate minimum on prefix function
*
* 		minpref[i] = min ( minpref[i - 1], pref[ i ] )
*
* 		So for every r, we check if minpref[r - D] is <= pref[r]
* 			if so, we can return true, it is possible to obtain >= fixed average
*
* time: O(n log(|a| * eps^-1) )
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

template<class T>
void initialize_matrix(vector<vector<T>>& matrix, int rows, int cols, T value) {
	assert(matrix.empty());
	FOR (row, rows) 
		matrix.emplace_back(cols, value);
}

tuple<bool, int, int> check(vi& a, int d, double avg) {
	vector<double> p(a.size() + 1);
	vector<double> m(a.size() + 1);
	vector<int> l(a.size() + 1);

	m[0] = 0;
	l[0] = 0;
	p[0] = 0.0;

	for (int i = 1; i <= a.size(); i++) {
		p[i] = p[i - 1] + a[i - 1] - avg;
		if ( m[i - 1] > p[i] ) {
			m[i] = p[i];
			l[i] = i;
		}
		else {
			l[i] = l[i - 1];
			m[i] = m[i - 1];
		}
	}

	// [l, r)
	for (int r = d; r <= a.size(); r++) {
		if ( p[r] >= m[r - d] ) {
			return make_tuple(true, l[r - d], r - 1);
		}
	}
	return make_tuple(false, -1, -1);
}

void go() {
	int n, d;
	cin >> n >> d;
	vi a(n); for (int& i : a) cin >> i;

	double lo { -1.0 }; // lo = true
	double hi { 101.0 }; // hi = false

	int ansL = -1, ansR = -1;
	FOR(i, 80) {
		double mid { (lo + hi) / 2.0 };
		auto[poss, l, r] = check(a, d, mid);

		if ( poss ) {
			lo = mid;
			ansL = l;
			ansR = r;
		}
		else {
			hi = mid;
		}
	}

	cout << ansL + 1 << " " << ansR + 1 << endl;
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);
	go();

	return 0;
}
