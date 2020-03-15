/*
* author: pavveu
* task: Count all valid permutations where for given pairs (a,b), a is always after b
* time: O(n2^n)
* soltion: bitmask DP
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using graph = vector<vi>;

void go() {
	int n, m; cin >> n >> m;
	
	vll dp(1<<n, 0);
	dp[0] = 1;
	
	// binary set, for pair(v, u) bit u is set if u-th number cant go after v
	vi dontLike(n);
	for (int i = 0; i < m; i++) {
		int v, u; cin >> v >> u;
		v--, u--;
		dontLike[v] |= (1<<u);
	} 

	// Counts all permutations 
	for (int mask = 0; mask < (1<<n); mask++) {
		int hate = 0;
		// set whoom we dont like 
		// we dont count permutations if there is bit which we dont like
		for (int bit = 0; bit < n; bit++) 
			if ( (1<<bit) & mask ) 
				hate |= dontLike[bit]; 
				
		// only off bits
		for (int j = 0; j < n; j++) {
			if ( mask & (1 << j) ) continue;
			if ( hate & (1 << j) ) continue; 
			
			dp[mask | (1 << j)] += dp[mask];
		}
	}

	cout << dp[(1<<n) - 1]  << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	go();

	return 0;
}