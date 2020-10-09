/*
* author: pavveu
* task: 
*       Find root of a continous function in an interval [a,b]
*       and f(a) * f(b) < 0 
* solution:
*       Binary Search - Bisection Method
* time: 
*       O(logn)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define FOR(name__, upper__) for (int name__ = 0; name__ < (upper__); ++name__)
#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple


double f(double x) {
    return x*x*x - x - 2;
}

double bisection(double a, double b) {
    assert("Different signs on interval ends" && (f(a) * f(b) < 0.0));

    double l = a; 
    double r = b;

    int iters = 70; // precision is 10^18 so-> log2(1/eps * n) ~ 70 iterations
    FOR(i, iters) {
        double m { (l + r) / 2.0 };
        if ( f(m) == 0.0 ) return m;
        else if ( f(r) * f(m) > 0 ) r = m;
        else l = m;
    }
    return r;
}

void go() {
    cout << fixed << setprecision(9) << bisection(1, 2) << endl;
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);
	go();

	return 0;
}
