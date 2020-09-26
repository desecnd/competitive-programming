/*
* author: pavveu
* task: maintain decimal number s of size N, 
*           change digits in [l, r] to d per query
*           ask for value of s per query
* time: O(n log n)
* solution: Segment Tree with Lazy Propagation query / set operations
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
using graph = vector<vi>;

#define FOR(name__, upper__) for (int name__ = 0; name__ < (upper__); ++name__)
#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple

template<class T>
void initialize_matrix(vector<vector<T>>& matrix, int rows, int cols, T value) {
	assert(matrix.empty());
	FOR (row, rows) 
		matrix.emplace_back(cols, value);
}

struct segment_tree {
    int N; ll mod;
    vi lo, hi;
    vll delta, dec_sum;

    // base[i] = 111111... - i times mod m
    // pow10[i] = 10^i mod m
	vll pow10, base;

    segment_tree(int n, ll p) : N(4*n + 1), mod(p), lo(N, -1), hi(N, -1), 
            delta(N, -1), dec_sum(N, 0), pow10(N), base(N) 
    {
		pow10[0] = 1; base[0] = 0;
		for(int i = 1; i < N; i++) {
			pow10[i] = pow10[i - 1] * 10 % mod;
			base[i] = (pow10[i - 1] + base[i - 1]) % mod;
		}

        init(0, n - 1);
    }

    void init(int a, int b, int i = 1) {
        lo[i] = a; hi[i] = b; 

        if ( a == b ) return;

        int m = (a+b)/2;
        init(a, m, 2*i);
        init(m + 1, b, 2*i + 1);
    }

	int size(int i) {
		return (hi[i] - lo[i] + 1);
	}

    // propagate only if delta is set
    void propagate(int i) {
		if ( delta[i] != -1 ) {
			delta[2*i] = delta[i];
			delta[2*i + 1] = delta[i]; 
			delta[i] = -1;
		}
    }

    // take left decimal value and combine with right
    // by multiplication by power of 10
    void update(int i) {
		ll left = 0;
		if ( delta[2*i] == -1 ) {
			left = dec_sum[2*i];  
		}
		else {
			left = (base[ size(2*i) ] * delta[2*i]) % mod;
		}

		ll right = 0;
		if ( delta[2*i + 1] == -1 ) {
			right = dec_sum[2*i + 1];  
		}
		else {
			right = (base[ size(2*i + 1) ] * delta[2*i + 1]) % mod;
		}

		dec_sum[i] = (left * pow10[ size(2*i+1) ] + right) % mod;
    }

    void set_range(int a, int b, ll val, int i = 1) {
        if ( b < lo[i] || hi[i] < a ) {
			return; 
		}
        else if ( a <= lo[i] && hi[i] <= b ) {
            delta[i] = val;
            return;
        }

        propagate(i);
        set_range(a, b, val, 2*i);
        set_range(a, b, val, 2*i + 1);
        update(i);
    }

    ll query(int a, int b, int i = 1) {
        if ( b < lo[i] || hi[i] < a ) {
			return 0ll;
		}
        else if ( a <= lo[i] && hi[i] <= b ) {
			if ( delta[i] != -1) {
            	return delta[i] * base[ size(i) ] % mod;
			}
			else {
				return dec_sum[i];
			}
        }

        propagate(i);
        ll left_sum = query(a, b, 2*i);
        ll right_sum = query(a, b, 2*i + 1);
        update(i);

		return (left_sum * pow10[size(2*i + 1)] + right_sum) % mod;
    }
};


void go() {
	ll mod = 998'244'353ll;
	int n, q;
	cin >> n >> q;

	segment_tree st(n, mod);

	st.set_range(0, n - 1, 1);

	while (q--) {
		int a, b, d;
		cin >> a >> b >> d;
		st.set_range(a - 1, b - 1, d);
		cout << st.query(0, n - 1) << "\n";
	}
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	go();

	return 0;
}
