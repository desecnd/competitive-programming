/*
* author: pavveu
* task: C - Cows and Stalls from Codeforces EDU
*       Given n points on the line and k cows
*       place k cows into n stalls such that
*       min distance between every 2 cows is maximum
*
* solution:
*       Binary Search MinMax:
*       Binary Search value t which is maximum possible distance
*       between cows and try to put them in stalls >= t units away 
*       it is always optimal to put first cow into first stall
* time: 
*       O(n * logn)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;

#define FOR(name__, upper__) for (int name__ = 0; name__ < (upper__); ++name__)
#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple

bool good(vi& stalls, int n_cows, int t) {
	int n { (int) stalls.size() };
	int last_cow = stalls[0];
	int cows = 1;

	for (int i = 1; i < n; i++) {
		if ( stalls[i] - last_cow >= t ) {
			cows++;
			last_cow = stalls[i];
		}
	}
	return (cows >= n_cows);
}

void go() {
	int n, k; cin >> n >> k;
	vi stalls(n);
	for (int& i : stalls) cin >> i;

    // invariants
	ll l = 0; // l is good 
	ll r = 1e9 + 10; // r is bad

    // open interval (l, r)
	while ( r - l > 1 ) {
		ll m = l + (r - l)/2;
		if ( good(stalls, k, m) ) l = m;
		else r = m;
	}
	cout << l << endl;
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);
	go();

	return 0;
}
