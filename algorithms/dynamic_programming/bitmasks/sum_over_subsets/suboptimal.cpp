/*
// Suboptimal algorithms for finding sum over subsets
// so for every subset x of elements of array A
// find sum of bitwise subsets i of this subset 
// 
// Solution is to go only for 1's bits of subset x
// because there is (n k) subsets and 2^k ones we got 
// O( n^3 ) solution
// 
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int,int>;

#define all(x) begin(x), end(x)
#define f first
#define s second


void go() {
	int n; cin >> n;
	vi F(1 << n), A(1 << n);

	for (int &i : A) cin >> i;
	
	for (int mask = 0; mask < (1 << n); ++mask) {
		cout << "F[" << mask << "] = A[0] ";
		F[mask] = A[0];
		for (int i = mask; i > 0; i = (i - 1) & mask) {
			cout << "+ A[" << i << "] "; 
			F[mask] += A[i];
		}
		cout << '\n';
	}


	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	go();
}
