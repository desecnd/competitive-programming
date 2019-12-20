#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

using vi = vector<int>;

// RMQ inspired by KTH implementation
// https://github.com/kth-competitive-programming/kactl
template <typename T>
struct RMQ {
    using ll = long long;

    vector<vector<T>> sparse;

    RMQ(vector<T>& A) {
        int dep = 1, m = 1, n = A.size();

        // m >= n and m = 2^(dep - 1)
        while ( m < n ) dep++, m *= 2;
        sparse.assign(dep, A);

        for (int j = 0; j < dep - 1; j++)
        for (int i = 0; i < n; i++) {
            sparse[j + 1][i] = min( sparse[j][i], sparse[j][min(n - 1, i + (1<<j))]);
        }
    }

    // half open interval - [a, b)
    T query(int a, int b) { 
        unsigned int size = b - a;
        int dep = 32 - __builtin_clz(size) - 1;
        return min(sparse[dep][a], sparse[dep][b - (1<<dep)]);
    }
};

void go() {
    cout << "Enter array size and all n elements\n";

    int n; cin >> n;
    vi A(n);
    for (int &i : A) cin >> i;

    RMQ<int> rmq(A);
    cout << "Pass 2 values: (a, b) meaning query for minimum value in range [a, b] (1- indexed)\n";

    int a, b;
    while ( cin >> a >> b ) {
        cout << rmq.query(a - 1, b) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);

    go();

    return 0;
}