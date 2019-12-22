#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

struct FenwickTree {
    vector<ll> T;
    int N;

    FenwickTree(int n) {
        // Size is power of 2 for easier kth implementation 
        N = 1; 
        while ( N < (n + 1) ) N *= 2;
        T.assign(N, 0);
    }

    inline int lowBit(int x) { return x & -x; }

    void update(int i, ll val) {
        while (i <= N) {
            T[i] += val;
            i += lowBit(i);
        }
    }

    ll prefSum(int i) {
        ll sum = 0;
        while ( i > 0 ) {
            sum += T[i];
            i -= lowBit(i);
        }
    }

    ll query(int a, int b) {
        return prefSum(b) - prefSum(a - 1);
    }

    int kth(ll x) {
        /// Binary search on tree O(logn)
        int i = N/2;

        while ( !(i & 1)) {
            if ( x > T[i] ) {
                x -= T[i];
                i += lowBit(i)/2;
            }
            else {
                int lb = lowBit(i);
                i -= lb;
                i += lb/2;
            }
        }

        if ( x > T[i] ) i++;
        return i;
    }
};

void go() {
    /// water level at certain days
    vector<ll> water { 120, 100, 50, 95, 20, 90, 110, 5, 0, 95 };

    for (int i = 0; i < water.size(); i++)
        cout << "Day " << i + 1 << " - " << water[i] << " ml\n";

    FenwickTree BIT(water.size());

    for (int i = 0; i < water.size(); i++)
        BIT.update(i + 1, water[i]);

    ll x;
    cout << "Which day n-th ml of water fell down?\nEnter n of ml to check:\n";
    while ( cin >> x ) {
        cout << BIT.kth(x) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    go();

    return 0;
}