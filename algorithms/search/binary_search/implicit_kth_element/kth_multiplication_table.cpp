/*
* author: pavveu
* task: find K-th value in multiplication table
* solution: Binary Search using calc()
* 		We assume k is 1-indexed and we hold following invariant:
*
* 			calc(l) < k 
* 			calc(r) >= k
*
* 		where calc(x) means number of items stricly < x 
*
* 					V-- k
* 		1 2 3 4 5 6 7 8 9 10 11 11 ...
* 		. . . . . . x x x >x
*
* 		Our solution relies on idea that calc() function can be 
* 		written in O(nlogn) or O(n) time.
*
* 		So we can binary search it to find proper x
*
* 		In this problem number of elements <x can be simply 
* 		computed by traversing every row of matrix table, and
* 		dividing x by row index 
*
* 			1 2 3 4 .... n 
* 		1 - multiples of 1
* 		2 - multiples of 2 -> floor( x/i ) = number of elements <x in current row 
* 		3 - multiples of 3
* 		.
* 		.
* 		n
*
*
* time: O(nlogn)
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

ll calc(ll n, ll x) {
	ll s = { 0 };
	for (ll i = 1; i <= n; i++ ) 
		s += min(n, x/i);
	return s;
}


void go() {
	ll n, k;
	cin >> n >> k;

	ll l = 0; 			// cnt(l) < k 
	ll r = n * n + 10; 	// calc(r) >= k

	while ( r - l > 1 ) {
		ll mid = l + (r - l)/2;
		if ( calc(n, mid) < k ) l = mid;
		else r = mid;
	}

	cout << r << endl;
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);
	go();

	return 0;
}
