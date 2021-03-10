/* 
 * author: pavveu
 * task: Determine if point is inside convex polygon
 * time: O(n)
 * solution: 
 *  for every edge in counter-clockwise direction check using cross-product 
 *  if point p lies on the right (cross_product < 0) from the edge, if so, it cannot
 *  be inside convex polygon
 */

#include <iostream>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

#define FOR(_iter, _to) for(int _iter = 0; _iter < (_to); _iter++)

using T = long long;
struct point {
    T x, y;
    point(T x = 0, T y = 0) : x(x), y(y) {}

    point operator+(point p) { return { x + p.x, y + p.y}; }
    point operator-(point p) { return { x - p.x, y - p.y}; }
    point operator*(T val) { return { x * val, y * val}; }
    point operator/(T val) { return { x / val, y / val}; }
};

T cross(point v, point w) { return v.x * w.y - w.x * v.y; }
// orient(a, b, c) < 0 -> a->c is on the right from a->b
T orient(point a, point b, point c) { return cross(b-a, c-a); }

istream& operator>>(istream& in, point& p) {
    return in >> p.x >> p.y;
}

ostream& operator<<(ostream& out, point p) {
	return out << "(" << p.x << ", " << p.y << ")";
}

// points of polygon in counterclockwise direction
using polygon = vector<point>;

bool point_in_convex_polygon(const polygon& poly, point p) {
    int n = poly.size();
    for (int j = n - 1, i = 0; i < n; j = i++) {
		// p is on a right from poly[j] -> poly[i] 
        if ( orient(poly[j], poly[i], p) < 0 ) 
			return false;
    }
    return true;
}

void go() {
    int n_points; cin >> n_points;
	polygon poly(n_points); 
    for (auto& p : poly) cin >> p;

	point p; 
	cin >> p;
	if ( point_in_convex_polygon(poly, p) ) {
		cout<< p << " is inside convex polygon" << endl;
	} else {
		cout << p << " is outside convex polygon" << endl;
	}
}

int main() {
    ios::sync_with_stdio(0);
    go();
    return 0;
}
