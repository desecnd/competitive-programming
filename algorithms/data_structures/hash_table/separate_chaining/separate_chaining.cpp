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
	const ll M = 10007; // prime size
	const size_t maxLen = 1e6 + 10;
	ll alfa;
	vll preBase;
	vector<vector<T>> table;

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

	HashTable(int A = 26) : alfa(A + 1), preBase(maxLen), table(M) {
		preBase[0] = 1;
		for (size_t i = 1; i < maxLen; i++) {
			preBase[i] = (preBase[i - 1] * alfa) % M;
		}
	}

	void Add(const T & x) {
		if ( Find(x) ) { 
			return;
		}				
	
		ll h = hash(x);
		table[h].push_back(x);

		cout << "Adding Element " << x 
			<< " to the set with hash: " << h << '\n';
	}
	void Delete(const T & x) {
		if ( !Find(x) ) { 
			return;
		}

		ll h = hash(x);
		table[h].erase(find(all(table[h]), x));
		
		cout << "Deleted element " << x << " with hash: " << h << '\n';
	}
	bool Find(const T & x) {
		ll h = hash(x);

		for (const auto & y : table[h]) {
			if ( y == x ) { 
				cout << "Found element " << x << " with hash: " << h << '\n';
				return true;
			}
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
			HT.Add(s);
		} 
		else if ( query == "del" ) {
			HT.Delete(s);
		} 
		else if ( query == "find" ) {
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
