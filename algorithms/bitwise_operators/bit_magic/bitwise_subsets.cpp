/* Traverse all bitwise subsets of x in 2^(set bits count)  
// 
// Time O(2^K) K - set bits cnt  
// Algorithms uses neat trick, which allows to walk 
// through all bitwise subsets of x in ascending order
// 
// Bitwise subset of x is integer n such
// x & n == n 
// so if n got bit set, x must have too
// example:
//  x = 101100001
// ----------------
// s1 = 100000000
// s2 = 101000001 
// s3 = 000000001 
// ---------------- not a bitwise subset
// f1 = 010000000
// f2 = 110000000
//
*/ 

#include <bits/stdc++.h>
using namespace std;

void go() {
	unsigned int x;
	cin >> x;

	for (unsigned int i = x; i > 0; i = x & (i - 1))
		cout << setw(10) << i << " , bin = " << bitset<20>(i) << '\n';

	cout << setw(10) << 0 << " , bin = " << bitset<20>(0) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	go();
}
