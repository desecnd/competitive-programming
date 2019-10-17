#include <bits/stdc++.h>
using namespace std;
using hash_t = long long;
using mod = array<hash_t, 2>;

#define all(x) begin(x), end(x)

struct shash {

	mod P { hash_t(1e9+7) , hash_t(1e9+9) };
	string s; int n;
	vector<mod> prefh, powx;
	hash_t x { 31 };
	
	shash(const string &s) : s(s), n(s.size()), prefh(n+1), powx(n+1) {
		prefh[0] = {0, 0};	
		powx[0] = {1, 1};

		for (int i = 0; i < n; i++) for (int p = 0; p < P.size(); p++) {
			prefh[i + 1][p] = ( prefh[i][p] * x + s[i] + 1 - 'a' ) % P[p];
			powx[i + 1][p] = ( powx[i][p] * x ) % P[p];
		}	
	}

	bool equal(const shash &b, int i, int j, int len) {
		return (this->hash(i,len) == b.hash(j, len));
	}

	// hash for substring [i, i + len - 1];
	mod hash(int i, int len) const {
		mod CRT;	
		for (int p = 0; p < P.size(); p++) {
			CRT[p] = (prefh[i + len][p] - prefh[i][p] * powx[len][p]) % P[p];
			CRT[p] += CRT[p] < 0 ? P[p] : 0;
		}
		return CRT;
	}
};

bool checkLen(const shash & sh, int n, int len) {
	vector<pair<mod, int>> A;
	
	for (int i = 0; i + len <= n; i++) {
		mod h { sh.hash(i, len) };
		
		A.emplace_back(h, i);
	}

	sort (all(A));

	for (int i = 0; i + 1 < A.size(); i++) 
		if ( A[i].first == A[i + 1].first) return true;
	return false;
}

// calculate hash for string s	
void go(const string & s) {
	shash sh(s);
	
	int lo = 0, hi = s.size();	
	while ( lo <= hi ) {
		int mid = lo + (hi - lo)/2;
		
		if ( checkLen(sh, s.size(), mid) ) lo = mid + 1;	
		else hi = mid - 1;
	}

	cout << hi << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	string s; cin >> s;
	go(s);
	
	return 0;
}

