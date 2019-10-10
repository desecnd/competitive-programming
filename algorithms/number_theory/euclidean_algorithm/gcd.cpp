#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int,int>;
using pll = pair<ll, ll>;

#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple

// Recursive Euclidean Algorithm
ll rgcd(ll a, ll b) { return b? rgcd(b, a % b) : a; } 

// Extended Recursive Euclidean Algorithm
ll ergcd(ll a, ll b, ll & x, ll & y) {
	if ( !b ) {
		x = 1; y = 0; return a;
	}

	ll d = ergcd(b, a % b, x, y);
	
	// we know that ax + by = gcd(a, b)
	// so b(xt) + (a % b)(yt) = gcd(b, a % b)
	// a % b = a - floor(a / b) * b
	// where floor(a/b) = q
	// so a(yt) + b(xt - floor(a/b) * yt) 
	// so we got that x = yt and y = xt - [a/b] * yt

	ll temp = y;
	y = x - (a / b) * y;
	x = temp;
	return d;	
}

// Iterative Euclidean Algorithm
ll igcd(ll a, ll b) {
	while ( b ) { 
		a %= b; 
		swap(a, b); 
	}
	return a;
}

// Extended Iterative Euclidean Algorithm
ll eigcd(ll a, ll b, ll &x, ll &y) {
	pll s{1, 0}, t{0, 1}, r(a, b);

	while ( r.second ) {
		int q = r.first / r.second;
		s = mp( s.second, s.first - q * s.second );	
		t = mp( t.second, t.first - q * t.second );	
		r = mp( r.second, r.first - q * r.second );	
	}

	x = s.first;
	y = t.first;
	return r.first;
}

void go() {
	ll a, b, x, y;
	while ( cin >> a >> b ) {
		cout << "rgcd(" << a << "," << b << ") = " << rgcd(a, b) << '\n';
		cout << "igcd(" << a << "," << b << ") = " << igcd(a, b) << '\n';
		cout << "ergcd(" << a << "," << b << ") = " << ergcd(a, b, x, y);
		cout << " = " << x << "*" << a << " + " << y << "*" << b << '\n';
		cout << "eigcd(" << a << "," << b << ") = " << eigcd(a, b, x, y);
		cout << " = " << x << "*" << a << " + " << y << "*" << b << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); 
	go();
}
