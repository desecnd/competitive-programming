/* Calculate Prefix Sums for 2-Dimensional Array
// 
// We simply build ROWS-times prefix sum array
// for every row of Array A
// then, we add up every column downwards
//
// PrefSum[row][col] += PrefSum[row - 1][col]
// so we build our array in O(nm) time
// 
// Next step is to answer queries in O(1)   
// we can observe that for to points a = (a1, a2), b = (b1, b2)
//
// PS:
//         a2        b2
//    A A A B B B B B B 
//    A A A B B B B B B
// a1 C C C D D D D D D 
// b1 C C C D D D D D D 
//
// our goal is to calculate sector D 
// we can only get sum of 
// -> A + B + C + D -> prefSum[b1][b2]
// -> A + B         -> prefSum[b1][a2 - 1]
// -> A + C         -> prefSum[a1 - 1][b2]
// -> A             -> prefSum[a1 - 1][a2 - 1]
//
// So D will be equal = (A + B + C + D) - (A + B) - (A + C) + (A)
// = D + B - B + C - C + 2A - 2A = D
// 
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define FOR(name__, upper__) for (int name__ = 0; name__ < (upper__); ++name__)
#define all(x) begin(x), end(x)

template<typename T>
void initialize_matrix(vector<vector<T>>& matrix, int rows, int cols, T val) {
    assert(matrix.empty());
    FOR(row, rows) matrix.emplace_back(cols, val);
}

using rectangle = tuple<int, int, int, int>;

template<typename T>
class prefix_sums_2d {
public:
    int rows, cols;
    vector<vector<T>> prefix_sum;

    prefix_sums_2d(vector<vector<T>>& A) : rows(A.size()), cols(A[0].size()), prefix_sum(A) 
    {
        FOR(row, rows) for (int col = 1; col < cols; col++) 
            prefix_sum[row][col] += prefix_sum[row][col - 1];

        FOR(col, cols) for (int row = 1; row < rows; row++) 
            prefix_sum[row][col] += prefix_sum[row - 1][col];
    } 
    
    T query(rectangle coords) {
        auto[ur, lc, dr, rc] = coords;
        T result = prefix_sum[dr][rc];
        if ( ur > 0 && lc > 0 ) result += prefix_sum[ur - 1][lc - 1];
        if ( ur > 0 ) result -= prefix_sum[ur - 1][rc];
        if ( lc > 0 ) result -= prefix_sum[dr][lc - 1];
        return result;
    }
};

void go() {
    int rows, cols;
    cin >> rows >> cols;
    
    vector<vector<int>> value_matrix;
    initialize_matrix(value_matrix, rows, cols, 0);
    
    FOR(row, rows) FOR(col, cols) 
        cin >> value_matrix[row][col];
    
    prefix_sums_2d<int> value_sum(value_matrix);
	
	// Sum from (0,5) to (3, 6)
	cout << value_sum.query({0, 5, 3, 6}) << endl;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	go();
}
