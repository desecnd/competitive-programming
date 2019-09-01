/* Finding Largest Power of 2 Not Exceeding n in constant time
//
// Warning, it uses builtin gcc function, not working on 
// other compilators
//
// GCC got __builtin function called 'clz' -> count leading zeros
// and thats what it does, return number of leading zeros
// of unsigned integer 
//
// __builtin_clz(x) -> unsigned int x
// __builtin_clzll(x) -> unsigned long long x
//
// We can then use this fuction to find largest pow2 not exceeding x
// if we look into binary, largest pow of 2 is just 
// most significant bit, so we can find it by math
//
// if n of bits is BITS (32 for int, 64 for ll) 
// then our most significant 1 is (BITS - clz(x)) counting from 1 from right
// and (BITS - clz(x) - 1) counting from 0 (index based)
//
*/

#include <bits/stdc++.h>
using namespace std;

void go() {
	unsigned int n;
	cin >> n;

	unsigned long long x = n;
	
	cout << "Int: " << (1 << (32 - __builtin_clz(n) - 1)) << '\n';
	cout << "Long long: " << (1 << ( 64 -  __builtin_clzll(x) - 1)) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	go();

	return 0;
}
