/* Find Largest power of 2 not exceeding n
// 
// Time: O(log n)
//
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int,int>;

#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple

void go() {
	unsigned int n, x;	
	cin >> n;
	x = 1U << static_cast<unsigned int>( log2(n) + 1 );
	cout << (x >> 1) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	go();
}
