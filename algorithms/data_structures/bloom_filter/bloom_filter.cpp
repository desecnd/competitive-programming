/*
* author: pavveu
* abstract: Bloom Filter 
* Probabilistic data structure (bitset)
* contains 1 bit of information (or k if more hash functions are used) 
* for every element, if x exist in Bloom filter
* i-th bit for every of k hash function must be set
*/

#include <iostream>
#include <vector>
#include <bitset>
#include <chrono>
#include <random>

using namespace std;
using ll = long long;

#define mp make_pair

struct BloomFilter {
    static const size_t N { size_t(1e9 + 7) }; 
    mt19937_64 rng;

    int K;
    vector<bitset<N>> buckets; 
    vector<pair<ll,ll>> hashes;

    BloomFilter(int k) : rng(chrono::high_resolution_clock::now().time_since_epoch().count()),
        K(k), buckets(k), hashes(k) {

        for ( auto& p : hashes) {
            p = mp( uniform_int_distribution<ll>(1ll, N)(rng), 
                uniform_int_distribution<ll>(0ll, N)(rng));
        }
    }

    int hash(int i, ll key) {
        /// universal hash ax + b mod N
        return ((key * hashes[i].first + hashes[i].second) % N );
    }

    void insert(ll key) {
        /// set all hash[i](key) bits 
        for (int i = 0; i < K; i++) buckets[i].set(hash(i, key));
    }

    bool exist(ll key) {
        /// check hash[i](key) bit for every hash function 
        bool allOn = true;
        for (int i = 0; i < K; i++)
            if ( !buckets[i].test(hash(i, key)) ) allOn = false;

        // if all bits set, element probably exist in data structure
        return allOn;
    }
};

void go() {
    // n of hash functions
    BloomFilter BF(10);

    cout << "0 [a] - insert a into Bloom filter\n";
    cout << "1 [a] - check if a is in Bloom filter\n";

    int q; ll a;
    while ( cin >> q >> a ) {
        if ( q == 0 ) BF.insert(a);
        else if ( q == 1 ) {
            if ( BF.exist(a) ) cout << "maybe\n";
            else cout << "no\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    go();

    return 0;
}