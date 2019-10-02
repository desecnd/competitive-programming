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

template <typename T>
struct HashTable {
	const ll M = 1<<10; // 2^m size
	const size_t maxLen = 1e6 + 10;
	int currSize;
	ll alfa;
	vll preBase;
	vector<T> table;

	// lowercase string s
	ll hash(const string & s) {
		ll polyHash = 0; 
		size_t power = s.size() - 1;
		for (auto x : s) {
			ll digit = x - 'a' + 1;
			digit = ( digit * preBase[power--] ) % M;
			polyHash = ( polyHash + digit ) % M;
		}
		return polyHash;
	}

	HashTable(int A = 26) : currSize(0), alfa(A + 1), preBase(maxLen), table(M, "") {
		preBase[0] = 1;
		for (size_t i = 1; i < maxLen; i++) {
			preBase[i] = (preBase[i - 1] * alfa) % M;
		}
	}

	void Add(const T & x) {
		if ( Find(x) ) { 
			return;
		} else if ( currSize >= M ) {
			return;
		}
	
		// we are using triangle numbers, because 
		// triangle numbers modulo 2^m always give full
		// permuation, which means, we will traverse every element
		ll h = hash(x), i = 0;
		ll tri = h;
		while ( table[tri] != "" && table[tri] != "*" ) {	 	  
			i++;
			tri = ( h + (i * (i + 1))/2 ) % M;
		}
		table[tri] = x;

		cout << "Adding Element " << x 
			<< " to the set with hash: " << h 
			<< " on position " << tri << '\n';
			
		currSize++;
	}

	void Delete(const T & x) {
		if ( !Find(x) ) { 
			return;
		}

		ll h = hash(x), i = 0;
		ll tri = h;
		
		while ( table[tri] != x ) { 
			i++;
			tri  = (h + (i * (i + 1))/2) % M;
		}

		table[tri] = "*";

		cout << "Deleted element " << x 
				<< " with hash: " << h
				<< ", located on position " << tri << '\n'; 
		currSize--;
	}
	bool Find(const T & x) {
		ll h = hash(x);
		ll i = 0, tri = h;
		
		while ( table[tri] != "" && table[tri] != x ) {
			i++;
			tri = ( h + (i + (i + 1))/2 ) % M;	
		}
		
		if ( table[tri] == x ) {	
				cout << "Found element " << x << " with hash: " << h << '\n';
				return true;
		}
		cout << "There are no element " << x << " in the set\n";
		return false;	
	}
};

void go() {
	HashTable<string> HT;

	string query, s;
	while ( cin >> query >> s ) {
		if ( query == "add" ) {
			cerr << "Adding----------\n";
			HT.Add(s);
		} 
		else if ( query == "del" ) {
			cerr << "Deleting----------\n";
			HT.Delete(s);
		} 
		else if ( query == "find" ) {
			cerr << "Finding----------\n";
			HT.Find(s);
		} 
		else {
			cout << "BAD QUERY\n";
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	go();
}
