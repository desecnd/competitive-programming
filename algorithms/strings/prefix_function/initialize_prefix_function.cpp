/*
* author: pavveu
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vu = vector<uint32_t>;
using vll = vector<ll>;

#define FOR(name__, upper__) for (int (name__) = 0; (name__) < (upper__); ++(name__))
#define all(x) begin(x), end(x)

void initialize_prefix_array(const string& s, vi& p) {
	p.assign(s.size() + 1, 0);
	int n = s.size();
	int k = 0;

	for (int i = 2; i <= n; i++) {
		while ( k > 0 && s[i - 1] != s[k] ) 
			k = p[k]; 
		if ( s[i - 1] == s[k] )   
			k++;
		p[i] = k;
	}
}

void go() {
	string s; cin >> s;
	vi p;
	initialize_prefix_array(s, p);

	for (int i : p) cout << i << " ";
	cout << "\n";
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	go();

	return 0;
}
