/* Lower Bound (subjectively) the Easiest Implementation
//
// Algorithm implements lower_bound std:: C++ library function 
// which finds first element which is >= searching value
// in std_lib LB finds first element for which comp(x, sVal) is false
//
// lower_bound can be used on any totaly ordered set (chain)
*/

#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e6 + 10;
int A[maxN];

// comp(x, sVal) = 111111111[0]00000000
int lowerBound(int fromInclusive, int toInclusive, int searchVal) {
	int lo = fromInclusive;
	int hi = toInclusive;

	while (lo <= hi) {
		int mid = lo + (hi - lo)/2;
		
		// predicate = x < sVal (less<int>()) 
		if (A[mid] < searchVal) lo = mid + 1;
		else hi = mid - 1; 
	}

	// hi = 11111111[1]000000000
	// lo = 111111111[0]00000000
	return lo;
}

void go() {	
	int n; cin >> n;
	for(int i = 0; i < n; i++)
		cin >> A[i];

	int searchVal;
	cin >> searchVal;

	// correctness check
	auto stdIndex = lower_bound(A, A + n, searchVal) - A;
	int myIndex = lowerBound(0, n-1, searchVal);
	
	assert(is_sorted(A, A+n) && myIndex == stdIndex);

	cout << "lower_bound(" << searchVal << ") at index: " << myIndex << '\n';
}

int main() {
	ios::sync_with_stdio(0);
	
	go();

	return 0;
}
