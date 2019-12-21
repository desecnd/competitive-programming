#include <iostream>
#include <vector>

using namespace std;
using ll = long long;


vector<ll> sieve(int N) {
    /// Basic eratosthenees sieve for finding primes in given interval
    /// O(n log log n )
    /// works abount 6 seconds for N = 1e8

    vector<bool> isPrime(N + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (ll i = 2; i <= N; i++) {
        if ( !isPrime[i] ) continue;

        // cross out every multiple of prime
        for (ll j = i * i; j <= N; j+=i) 
            isPrime[j] = false;
    }

    vector<ll> primes;
    for (ll i = 0; i <= N; i++)
        if ( isPrime[i] ) primes.push_back(i);

    return primes;
}

void go() {
    cout << "Sieve algorithm for prime finding, enter maxVal: ";
    int n; cin >> n;  

    vector<ll> primes { sieve(n) };
    // for ( ll p : primes ) cout << p << " ";
    cout << "\nFound " << primes.size() << " primes in [0; " << n << "]\n";
}

int main() {
    ios::sync_with_stdio(0);
    go(); 

    return 0;
}