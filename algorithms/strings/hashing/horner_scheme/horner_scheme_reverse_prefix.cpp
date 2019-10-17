#include <bits/stdc++.h>
using namespace std;

using hash_t = long long;

inline hash_t code(char x) { return x - 'a' + 1; }

void go(const string& s) {
	int n = s.size();

	hash_t P = 10e9 + 7, x = 31;
	vector<hash_t> prefh(n + 1), powx(n + 1);
	prefh[0] = 0; powx[0] = 1;

	// h(s) = s0 * x^(n-1) + s1 * x^(n-2) + ... + sn-2 * x^(1) + sn-1  mod P
	for (int i = 0; i < n; i++) {
		powx[i + 1] = (powx[i] * x) % P;
		prefh[i + 1] = (prefh[i] * x + code(s[i])) % P;
	}
	
	cout << "s[i,i+len-1] -> string, h(s') = .... = hash\n";
	for (int len = 1; len <= n; len++)
	for (int i = 0; i + len <= n; i++) {
		cout << "s[" << setw(4) << i << "," << setw(4) << i + len - 1 << "] -> " << setw(n) << s.substr(i, len) << ", h(s') = ";
		
		hash_t h = (prefh[i + len] - prefh[i] * powx[len]) % P;
		h += h < 0 ? P : 0;

		printf("s[%3.d] * x^(%d) + .... + s[%d] = %lld\n", i, len - 1, i + len - 1, h); 
	}
	
		
}

int main(int argc, char ** argv) {
	if ( argc < 2 ) {
		cout << "Usage: program 'string'\n";
		return 0;
	}

	string s { argv[1] };
	go(s);

	return 0;
}
