#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;

#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple

struct HashTable {
	using pa = pair<int,string>;
	
	ll P = 1e9+7;
	const int M;
	
	mt19937_64 rng;
	ll a, b; 
	vector<vector<pa>> buckets;
	
	HashTable(int n) : 
		M(n), 
		rng(chrono::high_resolution_clock::now().time_since_epoch().count()), 
		a(uniform_int_distribution<ll>(1ll, P)(rng)), 
		b(uniform_int_distribution<ll>(0ll, P)(rng)), 
		buckets(M) { 
	}
	
	// universal hash
	int hash(int key) {
		return (( key*a + b ) % P ) % M;
	}

	vector<pa>::iterator _lookup(int key) {
		int h { hash(key) };
	
		for ( auto it = buckets[h].begin(); it != buckets[h].end(); it++)
			if ( it->first == key ) return it; 

		else buckets[h].end();
	}

	bool insert(int key, string val) {
		int h { hash(key) };
		auto it = _lookup(key);

		if ( it != buckets[h].end() ) return false;
		buckets[h].emplace_back(key, val);
		return true;
	}
	void remove(int key) {
		int h { hash(key) };
		auto it = _lookup(key);
		
		if ( it == buckets[h].end() ) return;
		buckets[h].erase(it);
	}
	const string& lookup(int key) {
		auto it { _lookup(key) };
		return it->second;
	}
	
};

void go() {
	string name;
	int n, q, id;
	cin >> n;

	HashTable HT(n + 100);

	for (int i = 0; i < n; i++) {
		cin >> id >> name;
		HT.insert(id, name);
	}

	cin >> q;
	while (q--) {
		cin >> id;
		cout << HT.lookup(id) << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); 
	int t; cin >> t; 
	while(t--) go();
}
