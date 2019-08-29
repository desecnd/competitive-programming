#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int,int>;

#define all(x) begin(x), end(x)
#define f first
#define s second

// calculate sum over subsets for all subsets of A of size 2^n
// F[x] is a sum of all A[i] where i is a bitwise subset of x
// for x = 11
// all i = [00, 01, 10, 11] are x subsets
// 
// for x = 01
// all i = [00, 01] are x subsets
// 
// so bitwise subset if a binary number that has 1 only if mask has 1
// 
// so i is a bitwise subset of x if x & i == i
// (because all 0, are wiping out 1's in x) 
//	 
// solution
// by naive approach O(4^n) 

void go() {
	int n; cin >> n;

	vi A(1<<n);
	vi F(1<<n, 0);

	for (int &x : A) cin >> x;

	for (int mask = 0; mask < (1<<n); mask++) {
		cout << "F[" << mask << "] = sum(";		

		for (int i = 0; i < (1<<n); i++) {
			// if i is a bitwise subset of mask
			if ( (mask & i) == i ) {
				cout << "A[" << i << "],";
				F[mask] += A[i];
			}
		}
		cout << ") = " << F[mask] << '\n';
	}

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	go();
}
