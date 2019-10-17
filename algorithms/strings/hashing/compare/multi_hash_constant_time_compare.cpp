#include <bits/stdc++.h>
using namespace std;

struct shash {
	using hash_t = long long;
	using mod = array<hash_t, 4>;

	mod P { hash_t(1e9+7) , hash_t(1e9+9), hash_t(1e9+21), hash_t(1e9+33) };
	string s; int n;
	vector<mod> prefh, powx;
	hash_t x { 31 };
	
	shash(const string &s) : s(s), n(s.size()), prefh(n+1), powx(n+1) {
		prefh[0] = {0, 0, 0, 0};	
		powx[0] = {1, 1, 1, 1};

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
	
	void output() {
		for (int len = 1; len < n; len++) 
		for (int i = 0; i + len <= n; i++) {
			mod h { hash(i, len) };
			printf("s[%6.d,%6.d] = { ", i, i+len-1);
			for (hash_t p : h) printf("%10.lld, ", p);
			printf("}\n");
		}
	}

};

int main() {
	string a,b; cin >> a >> b;
	int n { a.size() }, m { b.size() };

	shash ah(a), bh(b);

	for (int len = 1; len < n; len++) 
	for (int i = 0; i + len <= n; i++) 
	for (int j = 0; j + len <= m; j++) {
		bool hash_equal = ah.equal(bh,i,j,len);
		bool string_equal = equal(a.begin() + i, a.begin()+i + len, b.begin() + j);
		
		assert(hash_equal == string_equal);
	}

	cout << "All comparisons OK.\n";
	return 0;
}

