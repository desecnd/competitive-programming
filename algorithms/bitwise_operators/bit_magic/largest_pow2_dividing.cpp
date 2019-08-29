/* Find largest power of 2 dividing n
//
// Time: O(1)
//
// This algorithm uses fact how binary system works
// n - 1 -> in binary it means, flip least significant bit to 0
// and whole flip whole suffix to 1
// so if n == 100010000
// n - 1   == 100001111
// then, we can invert all bits ~(n - 1)
// ~(n - 1) == 011110000
// and bitwise and-it with original value n
// n & (~(n - 1)) == 000010000
*/

#include <bits/stdc++.h>
using namespace std;

void go() {
	unsigned int n, x;	
	cin >> n;
	x = n & (~(n - 1));

	cout << x << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	go();
}
