#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
using edge = tuple<int,int,int,int>; // weight, id, from, to
using graph = vector<vector<edge>>;

#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple

struct HashTable {
	using pa = pair<int, string>;
	
	const pa EMPTY { -1, "" };
	const pa DELETED { -2, "" };

	const ll M = 1e5 + 19; // prime size
	const ll P = 1e5 + 3; // Prime for second hash
	
	vector<pa> buckets;

	HashTable() : buckets(M, EMPTY) {}

	int hash1(int key) { return key % M; }

	// values [1, P] where P < M
	int hash2(int key) { return P - (key % P); }

	pa& _lookup(int key) {
		int h1{ hash1(key) }, h2{ hash2(key) };
		int i = h1;
		
		while ( buckets[i] != EMPTY && buckets[i].first != key ) 
			i = ( i + h2 ) % M;
		
		return buckets[i];
	}

	const string& lookup(int key) {
		return _lookup(key).second;
	}

	bool insert(int key, string val) {
		if ( _lookup(key) == EMPTY ) return false;

		int h1 { hash1(key) }, h2 { hash2(key) };
		int i = h1;
	
		while ( buckets[i] != EMPTY && buckets[i] != DELETED ) 
			i = ( i + h2 ) % M;

		buckets[i] = mp(key, val);
		return true;
	}

	// If no element in Hash Table, inserts pair (key, newVal)
	void reassing(int key, string newVal) {
		pa& x = _lookup(key);
		x = mp(key, newVal);	
	}

	bool remove(int key) {
		pa& x = _lookup(key);

		if ( x == EMPTY ) return false;
		
		x = DELETED;
		return true;
	}

};

void go() {
	// add queries	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	go();
}
