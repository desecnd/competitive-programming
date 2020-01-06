/*
* author: pavveu 
* task: Circular RMQ
* solution: Range Min, Range Update Segment Tree
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

struct SegmentTree {
    /// Inspired by Algorithms Live! Youtube tutorial
    int N;
    vi lo, hi;
    vll delta, minimum;

    SegmentTree(int n) : N(4*n + 1), lo(N, -1), hi(N, -1), delta(N, 0), minimum(N, 0) {
        init(0, n - 1);
    }

    void init(int a, int b, int i = 1) {
        lo[i] = a; hi[i] = b; 

        if ( a == b ) return;

        int m = (a+b)/2;
        init(a, m, 2*i);
        init(m + 1, b, 2*i + 1);
    }

    void propagate(int i) {
        delta[2*i] += delta[i];
        delta[2*i + 1] += delta[i]; 
        delta[i] = 0;
    }

    void update(int i) {
        minimum[i] = std::min(minimum[2*i] + delta[2*i], minimum[2*i + 1] + delta[2*i + 1]);
    }

    void updateRange(int a, int b, ll val, int i = 1) {
        if ( b < lo[i] || hi[i] < a ) return; 
        else if ( a <= lo[i] && hi[i] <= b ) {
            delta[i] += val;
            return;
        }

        propagate(i);
        updateRange(a, b, val, 2*i);
        updateRange(a, b, val, 2*i + 1);
        update(i);
    }

    ll query(int a, int b, int i = 1) {
        if ( b < lo[i] || hi[i] < a ) return numeric_limits<ll>::max();
        else if ( a <= lo[i] && hi[i] <= b ) {
            return delta[i] + minimum[i];
        }

        propagate(i);
        ll leftMin = query(a, b, 2*i);
        ll rightMin = query(a, b, 2*i + 1);
        update(i);

        return min(leftMin, rightMin);
    }
};

void go() {
    /// codeforces circular RMQ task
    int n; cin >> n;
    SegmentTree SegTree(n);

    for (int i = 0; i < n; i++) {
        ll temp; cin >> temp;
        SegTree.updateRange(i,i,temp);
    }

    int m; cin >> m; cin.get();
    while ( m-- ) {
        int a, b;
        ll c;
        string input;
        getline(cin, input);
        istringstream ss(input);

        ss >> a >> b;
        if ( ss.eof() ) {
            ll minVal = numeric_limits<ll>::max();
            if ( a > b ) minVal = min( SegTree.query(a, n - 1), SegTree.query(0, b));
            else minVal = SegTree.query(a,b);
            cout << minVal << "\n";
        }
        else {
            ss >> c;
            if ( a > b ) SegTree.updateRange(a, n-1, c), SegTree.updateRange(0, b, c);
            else SegTree.updateRange(a, b, c);
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    go();

    return 0;
}