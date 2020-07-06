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
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;

#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple

void go() {
	int n, m; cin >> n >> m;
	
	// init
	vector<vi> A (n, vi(m));
	vector<vll> PS (n + 1, {0});
	PS[0] = vll(m + 1, 0ll);

	for (vi &v : A) 
	for (int &i : v) cin >> i;
	
	// calculate prefixSum for every row of A
	for (int i = 0; i < n; i++) {
		for (int j : A[i]) 	{
			ll next = j + PS[i + 1].back();
			PS[i + 1].push_back(next);
		}
	}

	// summing up all colums to get 2D prefSums 
	for (int j = 1; j <= m; j++) 
	for (int i = 1; i <= n; i++) 
		PS[i][j] += PS[i - 1][j];

	int q; cin >> q;
	pii a, b;

	while (q--) {
		cin >> a.first >> a.second >> b.first >> b.second;
		cout << "Sum[(" << a.first << "," << a.second << "):(" 
			<< b.first << "," << b.second << ")] = ";

		// answering queries, explained above
		ll AB = PS[b.first][b.second] + PS[a.first - 1][a.second - 1];
		ll CD = PS[b.first][a.second - 1] + PS[a.first - 1][b.second];
		cout << AB - CD << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	go();
}
