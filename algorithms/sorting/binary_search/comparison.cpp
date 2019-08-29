/* Binary Search Implementations Comparison 
//
// Program checks different implementations of Binary Search,
// understanding why particular algorithm works, and what are
// similarities between them, will help finding implementation
// that suit's you the most, and troubleshooting when something 
// goes wrong
//
// Task is to find first even number in array:
// { odd, odd, odd, .....,  even, even, even } numbers;
// in O(log n) time
*/

#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e6 + 10;
int A[maxN]; // search array 

// predicate for binary search - true if number is even 
inline bool p(int i) {
	return (A[i]%2 == 0);
}

// 000000000[1]111111 [,]
int binarySearchTopcoder(int fromInclusive, int toInclusive) { 
	int lo = fromInclusive;				
	int hi = toInclusive;
	
	while (lo < hi) {
		int mid = lo + (hi - lo + 1)/2;	
		
		if (p(mid)) hi = mid - 1;
		else lo = mid;
	}
	return hi + 1;
}

// 000000000[1]1111111 [,)
int binarySearchIndy256Codeforces(int fromInclusive, int toInclusive) {
	int lo = fromInclusive;
	int hi = toInclusive + 1;
		
	while (lo < hi) {
		int mid = (lo & hi) + ((lo ^ hi) >> 1);
		
		if (p(mid)) hi = mid;
		else lo = mid + 1;
	}
	
	return lo;
}

// 000000000[1]111111  [,)
int binarySearchFirstTrueOpen(int fromInclusive, int toInclusive) {
	int lo = fromInclusive;
	int hi = toInclusive + 1;

	while (lo < hi) {
		int mid = lo + (hi - lo)/2;
		
		if(p(mid)) hi = mid;
		else lo = mid + 1;
	}

	return lo;
}

// 000000000[1]111111 [,]
int binarySearchFirstTrueClosed(int fromInclusive, int toInclusive) {
	int lo = fromInclusive;	
	int hi = toInclusive;
		
	while (lo < hi + 1) { // lo <= hi
		int mid = lo + (hi - lo + 1)/2;
		
		if(p(mid)) hi = mid - 1; // hi + 1 = mid
		else lo = mid + 1;	
	}
	
	// hi is last 0	
	return lo;
}

// 00000000[1]1111111111 [,]
int binarySearchClosed(int fromInclusive, int toInclusive) {
	int lo = fromInclusive; 
	int hi = toInclusive;

	while(lo < hi + 1) {
		int mid = (hi + lo) / 2;
		
		if(p(mid)) hi = mid - 1;
		else lo = mid + 1;
	}
	
	// lo = 000000000[1]1111111
	// hi = 00000000[0]11111111
	return lo;
}

// 000000000[1]11111111 [,)
int binarySearchOpen(int fromInclusive, int toInclusive) {
	int lo = fromInclusive;
	int hi = toInclusive + 1;

	while(lo < hi) {
		int mid = (hi + lo) / 2;	
		
		if (p(mid)) hi = mid;
		else lo = mid + 1;
	}
	
	// lo = 000000000[1]11111111
	// hi = 000000000[1]11111111
	return lo;
}

void binarySearchTest(int n = maxN - 1) {
	int x = rand() % (n+1);
	// [0 - x), [x, n) 
	for(int i = 0; i < x; i++) A[i] = 2*i + 1;
	for(int i = x; i < n; i++) A[i] = 2*i;
	
	int b1 = binarySearchTopcoder(0, n-1);
	int b2 = binarySearchIndy256Codeforces(0, n-1);
	int b3 = binarySearchFirstTrueOpen(0, n-1);
	int b4 = binarySearchFirstTrueClosed(0, n-1);
	int b5 = binarySearchClosed(0, n-1);
	int b6 = binarySearchOpen(0, n-1);
		
	assert(x == b1 && x == b2 && x == b3 && x == b4 && x == b5 && x == b6);
}

int main() {
	srand(time(0));

	int t = 1000;
	cout << "Running " << t << " tests...\n";

	while(t--) {
		binarySearchTest();
	}
	cout << "Result: OK\n";

	return 0;
}
