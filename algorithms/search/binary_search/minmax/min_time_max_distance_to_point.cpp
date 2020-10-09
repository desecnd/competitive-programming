/*
* author: pavveu
* task: A - Get Together from Codeforces EDU
*       Cities lay on number line
*       Every citizen got 
*           x[i] - coordinate
*           v[i] - velocity 
*       
*       Find point x such that meeting there for all citizens
*       takes minimum time possible
*
* solution: BinSearch MinMax
*       Binary Search minimum value t such that 
*       every citizen can get to some point x 
*           (for every citizen calculate range of possible x'es
*               answer is set intersection) 
* time: O(n * log(1/eps * n))
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;

#define FOR(name__, upper__) for (int name__ = 0; name__ < (upper__); ++name__)
#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple

bool good(const vector<double>& x, const vector<double>& v, double t) {
	double x_ub { 1e9 + 100 };
	double x_lb { -x_ub };

	FOR(i, (int) x.size()) {
		double lb { x[i] - t * v[i] };
		double ub { x[i] + t * v[i] };

		x_ub = std::min(ub, x_ub);
		x_lb = std::max(lb, x_lb);
	}

	if ( x_ub < x_lb ) return false;
	else return true;
}

void go() {
	int n; cin >> n;
	vector<double> x(n);  
	vector<double> v(n);  
	FOR(i, n) {
		cin >> x[i] >> v[i];
	}

	double l = -1.0; // l is bad
	double r = 2e9 + 10.0; // r is good

    // Iterate ~ log(1/eps * n) times gives proper precision
    // open interval (l, r)
	FOR(i, 100) {
		double m = (l + r)/2.0;
		if ( good(x, v, m) ) r = m;
		else l = m;
	}

	cout << fixed << setprecision(6) << r << endl;
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);
	go();

	return 0;
}
