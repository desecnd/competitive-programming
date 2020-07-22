/*
* author: pavveu
* task: Find min i: a[i] >= x 
* time: O(log n)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vu = vector<uint32_t>;
using vll = vector<ll>;
using pii = pair<int,int>;
using vpii = vector<pii>;
using matrix = vector<vu>;
using graph = matrix;

#define FOR(name__, upper__) for (int (name__) = 0; (name__) < (upper__); ++(name__))
#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple

template<class T>
void initialize_matrix(vector<vector<T>>& matrix, int rows, int cols, T value) {
	assert(matrix.empty());
	FOR (row, rows) 
		matrix.emplace_back(cols, value);
}

class SegTree {
private:
	#define LEFT(val__) 2*(val__)
	#define RIGHT(val__) 2*(val__) + 1

	const int natural_element = -(1e9 + 1000);
	int size;
	vi lo, hi;
	vi maxim;

	int find_size(int n) {
		int size = 1;
		while ( size < n ) size *= 2; 
		return 2 * size;
	} 

	void init(int a, int b, int i = 1) {
		lo[i] = a;
	   	hi[i] = b;

		if ( a == b ) return;

		int m = (a + b)/2;
		init(a, m, LEFT(i));
		init(m + 1, b, RIGHT(i));
	}

	void update(int i) {
		assert(lo[i] != hi[i]);
		maxim[i] = std::max(maxim[LEFT(i)], maxim[RIGHT(i)]);
	}

	int find_(int x, int i) {
		if ( lo[i] == hi[i] ) return lo[i];
		else {
			if ( maxim[LEFT(i)] < x ) {
				return find_(x, RIGHT(i));
			}
			else {
				return find_(x, LEFT(i));
			}
		}
	}

	void set_value_(int index, int new_val, int i) {
		if ( index < lo[i] || hi[i] < index ) return; 
		else if ( lo[i] == hi[i] ) {
			if ( lo[i] == index )  {
				maxim[i] = new_val;
			}
			else return;
		} 
		else {
			set_value_(index, new_val, LEFT(i));
			set_value_(index, new_val, RIGHT(i));
			update(i);
		}
	}

	#undef LEFT
	#undef RIGHT

public:

	SegTree(int n) : 
		size(find_size(n)),
		lo(size, -1), hi(size, -1), 
		maxim(size, natural_element)
	{
		init(0, n - 1);
	}

	int find(int x) {
		if ( maxim[1] < x ) return -1;
		else return find_(x, 1);
	}

	void set_value(int index, int new_val) {
		set_value_(index, new_val, 1);
	}
};

void go() {
	int n, m; cin >> n >> m;

	SegTree st(n);

	FOR(i, n) {
		int val;
		cin >> val;
		st.set_value(i, val);
	}

	FOR(q, m) {
		int q_type, a;
		cin >> q_type >> a;
		if ( q_type == 1 ) { 
			int val; 
			cin >> val;
			st.set_value(a, val);
		}
		else if ( q_type == 2 ){ 
		   	cout << st.find(a) << "\n";
		}

	}
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	go();

	return 0;
}
