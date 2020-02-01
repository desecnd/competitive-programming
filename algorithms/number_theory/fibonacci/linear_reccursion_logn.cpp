/*
* author: pavveu
* task: Find N-th Fibonacci number modulo M
* time: O(logn)
* solution: Linear Recurrences + Matrix Multiply + Binary Exponent
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

using matrix = vector<vll>;
const ll mod = 1e9 + 7;

matrix multiply(const matrix& A, const matrix& B) {
    int r = A.size(), K = B.size(), c = B[0].size();

    matrix C(r, vll(c, 0));
    for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++) 
    for (int k = 0; k < K; k++)
        C[i][j] = ( C[i][j] + A[i][k] * B[k][j] ) % mod;

    return C;
}

// matrix has to be square to be powered!
matrix binExp(matrix& A, ll b) {
    int n = A.size();  

    matrix result(n, vll(n, 0) );
    for (int i = 0; i < n; i++) 
        result[i][i] = 1;

    while ( b > 0  ) {
        if ( b & 1 ) result = multiply(A, result); 
        A = multiply(A, A);
        b /= 2;
    }

    return result;
}

void go() {
    // Transformation matrix for linear recurrences
    // i+1-th element in i-th row is equal to 1 
    // and last row is c(0), c(1) ....  for fib its 1 and 1

    // F1 is row vector which shows first K variables, for fib its 1 and 1 
    matrix F1 { { 0 }, { 1 } };
    matrix T { {0, 1}, { 1, 1 } }; 

    // Fi = Fi - 1 * T
    ll n; cin >> n;

    matrix M { binExp(T, n) };
    matrix FN { multiply(M, F1) };

    // FN = { Fib(n), Fib(n + 1) }
    cout << "Fib(" << n << ") = " << FN[0][0] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    go();
    return 0;
}