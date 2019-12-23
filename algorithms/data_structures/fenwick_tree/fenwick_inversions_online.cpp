#include <iostream>
#include <vector>

using namespace std;
using vi = vector<int>;
using ll = long long;

struct FenwickTree {
    int N;
    vector<ll> T;

    FenwickTree(int n) : N(n + 1), T(n + 1, 0) {} 

    inline int lowBit(int i) { return i & -i; }

    void update(int i, ll val) {
        while ( i <= N ) {
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
        return sum;
    }

    ll query(int a, int b) {
        return prefSum(b) - prefSum(a - 1);
    }
};

void go() {
    cout << "Enter n of elements and permutation: \n";
    int n; cin >> n; 
    vi perm(n); for (int& i : perm) cin >> i;

    FenwickTree BIT(n);
    ll inversionsCnt = 0;

    for (int i = 0; i < n; i++) {
        int x = perm[i];
        inversionsCnt += BIT.query(x, n);
        BIT.update(x, 1);

        cout << "Current inversions: " << inversionsCnt << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    go();
    return 0;
}