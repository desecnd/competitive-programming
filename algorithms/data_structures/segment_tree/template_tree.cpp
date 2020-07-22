/*
* author: pavveu
*
* my try at coding template friendly Segment Tree
* with associative operation functor and data type
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


template<typename T, typename Functor>
struct SegTree {
	#define LEFT(val__) 2*(val__)
	#define RIGHT(val__) 2*(val__) + 1

	int size;
	T NATURAL_ELEMENT;
	vi lo, hi;
	vector<T> nodes;
	Functor operation;

	int find_size(int n) {
		int size = 1;
		while ( size < n ) size *= 2; 
		return 2 * size;
	} 

	SegTree(int n, T natural_element) : 
		size(find_size(n)), NATURAL_ELEMENT(natural_element),
		lo(size, -1), hi(size, -1), 
		nodes(size, NATURAL_ELEMENT),
		operation()
	{
		init(0, n - 1);
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
		nodes[i] = operation(nodes[LEFT(i)], nodes[RIGHT(i)]);
	}

	T query(int a, int b, int i = 1) {
		if ( b < lo[i] || hi[i] < a ) return NATURAL_ELEMENT; 
		else if ( a <= lo[i] && hi[i] <= b ) {
			return nodes[i];
		} 
		else {
			T left = query(a, b, LEFT(i));
			T right = query(a, b, RIGHT(i));
			return operation(left, right); 
		}
	} 

	void set_val(int index, T new_node, int i = 1) {
		if ( index < lo[i] || hi[i] < index ) return; 
		else if ( lo[i] == hi[i] ) {
			if ( lo[i] == index )  {
				nodes[i] = new_node;
			}
			else return;
		} 
		else {
			set_val(index, new_node, LEFT(i));
			set_val(index, new_node, RIGHT(i));
			update(i);
		}
	}

	#undef LEFT
	#undef RIGHT
};

void go() {
	int n, m; cin >> n >> m;

	struct Node {
		int minimum;
		int cnt;
		Node(int a = 1e9+10, int b = 1) : minimum(a), cnt(b) {} 
	};

	struct Functor { 
		Functor() = default;
		Node operator()(Node a, Node b){
			if ( a.minimum < b.minimum ) return a;
			else if ( b.minimum < a.minimum ) return b;
			else return Node(a.minimum, a.cnt + b.cnt);
	   	} 
	};

	SegTree<Node, Functor> st(n, Node());

	FOR(i, n) {
		int val;
		cin >> val;
		st.set_val(i, val);
	}

	FOR(q, m) {
		int q_type, a, b;
		cin >> q_type >> a >> b;
		if ( q_type == 1 ) {
			st.set_val(a, b);
		}
		else if ( q_type == 2 ) {
			Node result = st.query(a, b - 1);
			cout << result.minimum << " " << result.cnt << "\n";
		}
	}
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);

	go();

	return 0;
}
