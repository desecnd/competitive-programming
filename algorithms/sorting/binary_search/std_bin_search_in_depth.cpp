/* In Depth Look at std::lib Binary Search Functions 
// 
// We take a look on different outcomes of comp() 
// and relations between them
//
// comp(x,y) -> means relation on totaly ordered set,
// so if x < y (x is before y) comp(x,y) returns true
// 
// lower_bound, finds first element for which comp(x, val) gives false 
// -> so first >= element from val
// upper_bound, find first element for which !comp(val, x) gives false 
// -> so first > element from val
// 
// so lower_bound <- negation and swap -> upper_bound, 
// -> lower_bound<less> == upper_bound<less_equal>
// -> lower_bound<less_equal> == upper_bound<less>
//
*/

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)

void print_pretty(const vi &a, int LB, int UB) {
	int n {a.size()};
	cout << "A = ";
	for (int i = 0; i < n; i++ ) 
		cout << a[i] << " "; 
	cout << '\n';
	cout << "LB= ";
	for (int i = 0; i < n; i++ )  
		cout << (LB == i ? "^" : " ") << " "; 
	cout << '\n';
	cout << "UB= ";
	for (int i = 0; i < n; i++ ) 
		cout << (UB == i ? "^" : " ") << " "; 
	cout << '\n';
}

void go() {
	vi numbers { 1, 2, 2, 3, 3, 4, 4, 5, 5, 5, 6, 6, 7, 7, 8, 9 };
	vi rev_numbers = numbers; reverse(all(rev_numbers));
	int LB, UB; // lower_bound, upper_bound
	
	cout << "less<>()\n";
	LB = distance(numbers.begin(), lower_bound(all(numbers), 5, less<int>()));
	UB = distance(numbers.begin(), upper_bound(all(numbers), 5, less<int>()));
	print_pretty(numbers, LB, UB);

	cout << "less_equal<>()\n";
	LB = distance(numbers.begin(), lower_bound(all(numbers), 5, less_equal<int>()));
	UB = distance(numbers.begin(), upper_bound(all(numbers), 5, less_equal<int>()));
	print_pretty(numbers, LB, UB);

	// returns index from end
	cout << "less<>() reversed (rall(), greater<int>())\n";
	LB = distance(numbers.rbegin(), lower_bound(rall(numbers), 5, greater<int>()));
	UB = distance(numbers.rbegin(), upper_bound(rall(numbers), 5, greater<int>()));
	print_pretty(rev_numbers, LB, UB);

	// returns index from end
	cout << "less_equal<>() reversed (rall(), greater_equal()))\n";
	LB = distance(numbers.rbegin(), lower_bound(rall(numbers), 5, greater_equal<int>()));
	UB = distance(numbers.rbegin(), upper_bound(rall(numbers), 5, greater_equal<int>()));
	print_pretty(rev_numbers, LB, UB);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	go();

	return 0;
}
