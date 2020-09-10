/*
* author: pavveu
* task: Find max L such that we can cut out k lines of lenght L from set of N lines
* time: O(nlogn)
* solution: Binary Search on double values
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

// max error for solution is 10^-6
const double eps { 1e-6 };

bool check(vi& a, int k, double x) { 
	int ans = 0;
	for (int l : a) {
		ans += int( floor(l / x) );
	}
	return (ans >= k);
}

double binsearch(vi& a, int k) {
	double lo { eps }, hi { 1e7 + 10 };

	while ( eps <  hi - lo  ) {
		double mid = ( lo + hi ) / 2.0;
		if ( check(a, k, mid) ) lo = mid; 
		else hi = mid; 
	}
	return hi; 
}

void go() {
	int n, k; cin >> n >> k;

	vi a(n); for(auto& i : a) cin >> i;
	cout << binsearch(a, k) << endl;
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	go();

	return 0;
}
