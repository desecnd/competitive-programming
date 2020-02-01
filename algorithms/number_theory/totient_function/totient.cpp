/*
* author: pavveu
* task: Find Value of Euler totient function
* time: O(n ^ 1/2)
* solution: Prime Factorization
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

ll totient(ll n) {
    ll totient = n;
    for (ll i = 2; i * i <= n; i++ ) {
        if ( n % i == 0 ) {
            while ( n % i == 0 ) 
                n /= i;
            totient -= totient/i; 
        }
    }

    // prime divisor > sqrt
    if ( n > 1 )  totient -= totient/n;
    return totient;
}

void go(ll n) {
    cout << "phi(" << n << ") = " << totient(n) << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
    ll n; 
    while ( cin >> n ) 
        go(n);

	return 0;
}
