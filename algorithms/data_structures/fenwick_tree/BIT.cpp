#include <iostream>
#include <vector>
using namespace std;

using vi = vector<int>;
using ll = long long;

struct FenwickTree {
    vector<ll> T;

    FenwickTree(int n) : T(n + 1, 0) {}

    inline int lowBit(int x) { return x & -x; }

    void update(int i, ll val) {
        /// i is 1-indexed 

        while ( i <= T.size() ) {
            T[i] += val;
            i += lowBit(i);
        }
    }

    ll prefSum(int i) {
        // sum in [1, i]
        ll sum = 0;
        while ( i > 0 ) {
            sum += T[i];
            i -= lowBit(i);
        }
        return sum;
    }

    ll query(int a, int b) {
        // sum in range [a,b], 1 indexed
        return prefSum(b) - prefSum(a - 1);
    }
};

void go() {
    cout << "Enter n of elements, and sequence of integers\n";
    int n; cin >> n;
    vi A(n);
    for (int &i : A) cin >> i;

    FenwickTree BIT(n);
    for (int i = 0; i < n; i++) BIT.update(i + 1, A[i]);

    cout << "Query for sum [a;b] 1 indexed:\n";
    int a, b;
    while ( cin >> a >> b ) {
        cout << BIT.query(a, b) << "\n";
    }

}

int main() {
    ios::sync_with_stdio(false);
    go();
    return 0;
}