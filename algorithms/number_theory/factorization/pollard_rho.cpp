/*
* author: pavveu
* task: Integer Factorization
* time: O( n^1/4 * log n)
* solution: Pollard's Rho algorithm
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
using graph = vector<vi>;

#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple

ll f(ll x, ll c, ll mod) {
    return (x * x  + c) % mod; 
}

ll gcd(ll a, ll b) {
    while ( b ) {
        a %= b; swap(a, b);
    }
    return a;
}

ll pollardRho(ll n, ll c = 1, ll x0 = 2) {
	ll x { x0 }, y { x0 };
    ll d { 1 };

    // Floyd Warshall cycle detection algorithm
    while ( d == 1 ) {
        x = f(x, c, n);
        y = f( f(y, c, n), c, n);
        d = gcd(llabs(x - y), n);
    }

    // Something went wrong
    if ( d == n ) return -1;
    else return d;
}

void factorize(ll n)  {
    ll p = pollardRho(n);
    // we may use brute force approach for n < 1000
    if ( p == -1 ) {
        cout << n << " * ";
        return;
    }
    factorize(p);
    factorize(n/p);
}

void go() {
	ll n; cin >> n;
    factorize(n);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	go();

	return 0;
}
