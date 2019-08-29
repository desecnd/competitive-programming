/* Upper Bound (subjectively) the Easiest Implementation
//
// Algorithm implements upper_bound std:: C++ library function 
// it finds first element which is > searching value
// in std_lib UB finds first element for which !comp(sVal, x) is false 
//
// upper_bound can be used on any totaly ordered set (chain)
// comp(x,y) returns true if x < y 
*/

#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e6 + 10;
int A[maxN];

// !comp(val, x) = 11111111111[0]0000000
int upperBound(int fromInclusive, int toInclusive, int searchVal) {
	int lo = fromInclusive;	
	int hi = toInclusive;

	while (lo <= hi) {
		int mid = lo + (hi - lo)/2;
			
		// predicate = !(sVal OP x) 
		if(!(searchVal < A[mid])) lo = mid + 1;
		else hi = mid - 1;
	}
	
	// hi = 1111111111[1]00000000
	// lo = 11111111111[0]0000000
	return lo;
}

void go() {	
	int n; cin >> n;
	for(int i = 0; i < n; i++)
		cin >> A[i];

	int searchVal;
	cin >> searchVal;

	auto stdIndex = upper_bound(A, A + n, searchVal) - A;
	int myIndex = upperBound(0, n-1, searchVal);
	
	assert(is_sorted(A, A+n) && myIndex == stdIndex);

	cout << "upper_bound(" << searchVal << ") at index: " << myIndex << '\n';
}


int main() {
	ios::sync_with_stdio(0);

	go();

	return 0;
}
