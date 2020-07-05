/*
* author: pavveu
* task: Longest Common Substring
* time: O(n logn^2)
* solution: Polynomial hash + Sorting + Binary Search
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<ll,ll>;

#define mp make_pair
#define mt make_tuple
#define all(x) begin(x), end(x)

class PolynomialHash {
    /// Inspired by dmkozyrev from Codeforces

private:
    static int p;
    static int base;
    static vector<int> x1;
    static vector<ull> x2;

	int len;
    vector<int> pref1;
    vector<ull> pref2;
public:
	using Hash = pair<int, ll>;

   	/// polynomial hash = a0*x^n-1 + a1*x^n-2 + a2*x^n-3 + ... + a(n-1) (mod p)
    PolynomialHash(const string& s) 
		: len(s.size()), pref1(len + 1, 0), pref2(len + 1, 0) 
	{

        while ( (int)x1.size() <= len ) {
            x1.push_back( ll(x1.back()) * base % p );
            x2.push_back( ll(x2.back()) * base );
        }

        for (int i = 0; i < len; i++) {
            pref1[i + 1] = ( ll(pref1[i]) * base + s[i] ) % p;
            pref2[i + 1] = pref2[i] * base + s[i];
        }
    }

	void static genBase(int module = 1e9 + 97) {
		p = module;

		x1.assign({1});
		x2.assign({1ll});

		mt19937 gen( chrono::high_resolution_clock::now().time_since_epoch().count() ); 
		base = uniform_int_distribution<int>(0.25 * module, 0.75 * module)(gen);

		// need to be coprime with 2^64 so, must be odd
		if ( base % 2 == 0 ) 
			base--;
	}

	inline int length() const { return len; }

    /// hash of substring [i, i + len - 1]
    inline Hash operator()(int i, int len) const { 
        int h1 = pref1[i + len] - ll(pref1[i]) * x1[len] % p;
        ull h2 =  pref2[i + len] - pref2[i] * x2[len];
        return {(h1 < 0 ? h1 + p : h1), h2};
    }
};

int PolynomialHash::p = 1e9 + 97;
int PolynomialHash::base = 1e9 + 7;
vector<int> PolynomialHash::x1 { 1 };
vector<ull> PolynomialHash::x2 { 1 };

bool checkLength(PolynomialHash& aHash, PolynomialHash& bHash, int k) {
	/// Check if there exist substring of length k in O(nlogn) time
    if ( k == 0 ) return true;
    else if ( k > aHash.length() ) return false;

    vector<PolynomialHash::Hash> hashes;
    for (int i = 0; i + k <= aHash.length(); i++) 
        hashes.push_back(aHash(i, k));
    sort(all(hashes));

    for (int i = 0; i + k <= bHash.length(); i++) 
        if ( binary_search(all(hashes), bHash(i, k)) ) 
            return true;
    return false;
}


void go() {
	PolynomialHash::genBase(1e9 + 97);

    string a, b; 
	cin >> a >> b;

    if ( a.size() > b.size() ) 
		swap(a, b);

    PolynomialHash aHash(a);
	PolynomialHash bHash(b);

    int lo = 0, hi = aHash.length() + 1;
    while ( lo <= hi ) {
        int mid = lo + (hi - lo)/2;
        if ( checkLength(aHash, bHash, mid) ) lo = mid + 1;
        else hi = mid - 1;
    }

    cout << hi << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    go();

    return 0;
}
