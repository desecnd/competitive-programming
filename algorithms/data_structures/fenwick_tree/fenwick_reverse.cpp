#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

struct FenwickTree {
    vector<ll> T;
    int N;

    FenwickTree(int n) {
        N = 1;
        while ( N < (n + 1) ) N *= 2;
        T.assign(N, 0);
    }

    inline int lowBit(int x) { return x & -x; }

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

    void updateRange(int a, int b, ll val) {
        update(a, val);
        if ( b < N ) update(b + 1, -val);
    }

    ll query(int i) {
        return prefSum(i);
    }
};

void go() {
    cout << "Enter n of elements and numbers sequence\n";

    int n; cin >> n;
    vector<ll> A(n);
    for (ll& i : A) cin >> i;

    FenwickTree BIT(n);

    cout << "0 [a, b, val] -> update range [a,b] with val\n";
    cout << "1 [i] -> query ith sequence item value\n";
    int q, a, b;
    ll val;

    while ( cin >> q ) {
        if ( q == 0 ) {
            cin >> a >> b >> val;
            BIT.updateRange(a, b, val);
        }
        else if ( q == 1 ) {
            cin >> a;
            cout << A[a - 1] + BIT.query(a) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    go();
    return 0;    
}