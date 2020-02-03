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

struct PolynomialHash {
    // Inspired by dmkozyrev from Codeforces
    const static int p = 1e9 + 97; 
    static int base;
    static vector<int> x1;
    static vector<ull> x2;

    vector<int> pref1;
    vector<ull> pref2;

    PolynomialHash(const string & s) : pref1(s.size() + 1, 0), pref2(s.size() + 1, 0) {
        // polynomial hash = a0 * x^n-1 + a1 * x^n-2 + a2 * x^n-3 + .... an-1

        while ( x1.size() <= s.size() ) {
            // cout << x1.back() << " " << x2.back() << "\n"; 
            x1.push_back( ll(x1.back()) * base % p );
            x2.push_back( ll(x2.back()) * base );
        }

        for (int i = 0; i < s.size(); i++) {
            pref1[i + 1] = ( ll(pref1[i]) * base + s[i] ) % p;
            pref2[i + 1] = pref2[i] * base + s[i];
        }
    }

    // hash of substring [i, i + len - 1]
    inline pair<int, ull> operator()(int i, int len) const { 
        int h1 = pref1[i + len] - ll(pref1[i]) * x1[len] % p;
        ull h2 =  pref2[i + len] - pref2[i] * x2[len];
        return mp(h1 < 0 ? h1 + p : h1, h2);
    }
};

int PolynomialHash::base = 1e9 + 7;
vector<int> PolynomialHash::x1 { 1 };
vector<ull> PolynomialHash::x2 { 1 };

bool testLen(PolynomialHash& aHash, PolynomialHash& bHash, size_t n, size_t m, size_t k) {
    if ( k == 0 ) return true;
    else if ( k > n ) return false;

    vector<pair<int, ull>> hashes;
 
    for (size_t i = 0; i + k - 1 < n; i++) {
        auto hash { aHash(i, k) };
        // cerr << "hash[" << i << "-" << i + k - 1 << "] = " << hash.first << " " << hash.second << "\n";
        hashes.push_back(hash);
    }

    sort(all(hashes));

    for (size_t i = 0; i + k - 1 < m; i++) {
        auto hash { bHash(i, k) };
        // cerr << "hash[" << i << "-" << i + k - 1 << "] = " << hash.first << " " << hash.second << "\n";
        if ( binary_search(all(hashes), hash) ) {
            return true;
        }
    }
    return false;
}

int genBase(int module) {
    mt19937 gen( chrono::high_resolution_clock::now().time_since_epoch().count() ); 
    int base = uniform_int_distribution<int>(0.25 * module, 0.75 * module)(gen);

    // need to be coprime with 2^64 so, must be odd
    if ( base % 2 == 0 ) base--;
    return base;
}

void go() {
    PolynomialHash::base = genBase(PolynomialHash::p); 

    string a, b; cin >> a >> b;
    if ( a.size() > b.size() ) swap(a, b);
    int n = a.size(), m = b.size();

    PolynomialHash aHash(a), bHash(b);

    int lo = 0, hi = n + 1;
    while ( lo <= hi ) {
        int mid = lo + (hi - lo)/2;
        if ( testLen(aHash, bHash, n, m, mid) ) lo = mid + 1;
        else hi = mid - 1;
    }
    cout << hi << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    go();

    return 0;
}