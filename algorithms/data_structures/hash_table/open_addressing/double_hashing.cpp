/* Double Hashing - Open Adressing Hash Table Implementation
//
// Double Hashing is improvement for Linear Probing 
// to resolve hash collisions between different objects 
//
// It works same as linear probing, but instead of walking
// every time by 1 step, every key got its own "walk distance"
// by which it iterates through every bucket
// 
// We choose Prime Number M as our buckets quantity 
// because if population of keys and number of buckets
// share common factor, every key will get to bucket that
// is a multiple of that factor
//
// If keys are Uniformly Distributed i.e. chance of 
// getting every number is the same, choice of M 
// 
// But in many cases numbers are not uniformly distributed, 
// so its better to use prime number
// 
// Second Hash fuction has to map values {1, M-1}
// so we can use formula 1 + (key mod M-1) -> [1, M)
// only one requirement is that H2 value is coprime with M
// and every number < P is coprime with it 
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;
using pii = pair<int,int>;

#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple

struct HashTable {
	// special id + name for that id
	using pa = pair<int, string>;
	
	const pa EMPTY { -1, "" };
	const pa DELETED { -2, "$" };

	const ll M = 1e5 + 19; // prime size
	
	vector<pa> buckets;

	HashTable() : buckets(M, EMPTY) {}

	int hash1(int key) { return key % M; }

	// Values [1, M) -> has to be coprime with size so its cool
	int hash2(int key) { return 1 + (key % (M - 1)); }

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
		if ( _lookup(key) != EMPTY ) return false;

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

// T tescases:
// n - number of id's
// (id, name) < id of worker and his name 
// q - number of queries
// id < id of worker who's name we want to know
void go() {
	string name;
	int n, q, id;
	cin >> n;

	HashTable HT;
	assert(n <= HT.M);

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
	while (t--) go();
}
