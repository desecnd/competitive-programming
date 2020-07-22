#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define all(x) begin(x), end(x)

void go () {
	int n; cin >> n;
	vi A(n);
	for (int &i : A) cin >> i;

	vi lis;
	for (int i : A) {
		if ( !lis.size() || i >= lis.back() ) lis.push_back(i);
		else *upper_bound(all(lis), i) = i;
	}

	cout << lis.size() << "\n";
	for (int i : lis) cout << i << " ";
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	go();
	
	return 0;
}
