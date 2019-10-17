/*
* Author: pavveu	
* Task: Find Maximum Length of repeated substring in a string
* Time: O(nlog^2n)
*/

#include <bits/stdc++.h>
using namespace std;

// UNSIGNED - take care
using hash_t = uint64_t;
using vi = vector<int>;
#define all(x) begin(x), end(x)

// Randomization based on time - not fixed seed, for anti-hashes attack on codeforces ;)
mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MAXLEN = 1e6 + 2;
const int HASH_CNT = 4;
// P = 2**32 - 13337 -> (P-1)/2 is prime 
// Less P-1 dividors - better!
const hash_t P = (uint32_t) - 13337;
hash_t powx [HASH_CNT][MAXLEN];
hash_t hashes[HASH_CNT][MAXLEN];
uniform_int_distribution<hash_t> DIST( 0.25 * P, 0.75 * P);
const hash_t MULT[HASH_CNT] = { DIST(rng), DIST(rng), DIST(rng), DIST(rng) };
// 4-base hash propability of collision near n^2 / P^4 ~ 2.93e-27 

// calculate base power mod P for every base
void preprocess(int n) {
	for (int h = 0; h < HASH_CNT; h++) {
		powx[h][0] = 1;
	
		for (int i = 0; i <= n; i++) {
			powx[h][i + 1] = (powx[h][i] * MULT[h] ) % P;
		}
	}
}


// Checks if there exist repeated substring of length len
bool checkLen(const string & s,int len) {
	if ( len == 0 ) return true;

	hash_t Q[HASH_CNT] = {0, 0, 0, 0};
	int m = s.size() - len + 1;
	
	// Create first sliding window of lenght len - 1
	for (int h = 0; h < HASH_CNT; h++) {
		
		for (int i = 0; i < len - 1; i++) 
		Q[h] = (Q[h] * MULT[h] + s[i] + 1 -'a') % P;
	}

	for (int i = len - 1; i < s.size(); i++) 
	for (int h = 0; h < HASH_CNT; h++) {
		// push front - now sliding window width is len
		Q[h] = (Q[h] * MULT[h] + s[i] + 1 - 'a') % P;

		hashes[h][i - len + 1] = Q[h];

		// pop back - now sliding window width is len - 1
		Q[h] = Q[h] + P - powx[h][len - 1] * (s[i - len + 1] - 'a' + 1) % P ;
		if (Q[h] >= P) Q[h] -= P;
	}

	// stable sort ~ C(n,2) comparisons
	vi perm(m); iota(all(perm), 0);
	stable_sort(all(perm), [&](int a, int b) {
		for (int i = 0; i < HASH_CNT; i++) 
			if ( hashes[i][a] != hashes[i][b] ) return hashes[i][a] < hashes[i][b] ;
		return false;
	});

	// Compare adjacent sorted hashes ~ n comparisons
	for (int i = 0; i + 1 < m; i++) {
		bool eq = true;
		for (int h =0; h < HASH_CNT; h++) {
			if ( hashes[h][perm[i]] != hashes[h][perm[i + 1]] ) 
				eq = false;
		}

		if (eq) return true;
	}
	return false;
}

// Binary Search for finding max length of repeated substring
void go(const string & s) {
	int lo = 0, hi = s.size();	
	while ( lo <= hi ) {
		
		int mid = lo + (hi - lo)/2;
		if ( checkLen(s, mid) ) lo = mid + 1;
		else hi = mid - 1;
	}

	cout << hi << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	string s; cin >> s;
	preprocess(s.size());
	go(s);
	
	return 0;
}

