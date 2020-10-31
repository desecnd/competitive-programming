/*
* author: pavveu
* task: find K-th sum of pairs from 2 arrays a and b 
* solution: Binary Search using calc()
* 		We assume k is 0-indexed and we hold following invariant:
*
* 			calc(l) <= k 
* 			calc(r) > k
*
* 		where calc(x) means number of items stricly < x 
*
* 		Our solution relies on idea that calc() function can be 
* 		written in O(nlogn) or O(n) time.
*
* 		So we can binary search it to find proper x
*
* 		In this problem number of elements < x can be calculated 
* 		by first sorting both arrays, and while traversing the second one
* 		checking using 2 pointers how far we can get in the first array
*
* time: O(n log|A|) + O(n log n)
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

ll calc(vll& a, vll& b, ll x) {
	ll s = { 0 };

	int i = a.size();
	// b is non-decreasing 
	// so every next val is >= previous one
	for (ll val : b) {
		while ( i > 0 && a[i - 1] + val >= x ) i--;
		s += i;
	}
	return s;
}

void go() {
	ll n, k;
	cin >> n >> k;
	k--;

	vll a(n), b(n);
	for (ll& i : a) cin >> i;
	for (ll& i : b) cin >> i;

	sort(all(a));
	sort(all(b));

	ll l = 0; 			// cnt(l) <= k 
	ll r = 2e9 + 100; 	// calc(r) > k
	while ( r - l > 1 ) {
		ll mid = l + (r - l)/2;
		if ( calc(a, b, mid) <= k ) l = mid;
		else r = mid;
	}

	cout << l << endl;
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);
	go();

	return 0;
}
