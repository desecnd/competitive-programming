/*
* author: pavveu
* source: https://vlecomte.github.io/cp-geo.pdf
* task: basic line geometry class for Competitive Programming
*/

#include <iostream>
#include <cmath>
#include <cassert>
#include <algorithm>
using namespace std;

using T = double;
double inline PI() { return atan(1)*4; } 

struct Point {
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}

    Point operator+(Point p) { return { x + p.x, y + p.y }; }
    Point operator-(Point p) { return { x - p.x, y - p.y }; }
    Point operator*(T val) { return { x * val, y * val }; }
    Point operator/(T val) { return { x / val, y / val }; }
};

bool operator==(Point a, Point b) { return a.x == b.x && a.y == b.y; }
bool operator!=(Point a, Point b) { return !(a == b); }

T sq(Point p) { return p.x * p.x + p.y * p.y; }
double abs(Point p){ return sqrt(sq(p)); }
Point perp(Point p) { return { -p.y, p.x }; }

ostream& operator<<(ostream& out, Point p) {
    return out << "(" << p.x << "," << p.y << ")";
}

T dot(Point v, Point w) { return v.x * w.x + v.y * w.y; }
bool isPerp(Point v, Point w) { return dot(v, w) == T(0); }
double angle(Point v, Point w) {
    double cosTheta = dot(v, w) / abs(v) / abs(w);
    return acos( max(-1.0, min(1.0, cosTheta)));
}

T cross(Point v, Point w) { return v.x * w.y - v.y * w.x; }
T orient(Point a, Point b, Point c) { return cross(b - a, c - a); }
double orientedAngle(Point a, Point b, Point c) {
    if ( orient(a, b, c) >= 0 ) return angle(b - a, c - a);
    else return 2 * PI() - angle(b - a, c - a);
}
bool inAngle(Point a, Point b, Point c, Point p) {
    assert( orient(a,b,c) != 0 );
    if ( orient(a, b, c) < 0 ) swap(b, c);
    return orient(a,b,p) >= 0 && orient(a,c,p) <= 0;
}


struct Line {
    // ax + by = c;
    // v = (b, -a)
    Point v; T c;

    Line(Point v, T c) : v(v), c(c) {}
    Line(T a, T b, T, T c) : v(b, -a), c(c) {}
    Line(Point p, Point q ) : v(q - p), c(cross(v, p)) {}

    // works with T = long long
    T side(Point p) { return cross(v, p) - c; }
    double dist(Point p) { return abs(side(p)) / abs(v); }
    Line perpThrough(Point p) { return { p, p + perp(v) }; }
    bool cmpProj(Point p, Point q) { return dot(v, p) < dot(v, q); } 
    Line translate(Point t) { return {v, c + cross(v, t)}; }

    // needs T = double 
    Line shiftLeft(double dist) { return { v, c + dist * abs(v) }; }
    Point proj(Point p) { return p - perp(v) * side(p) / sq(v); }
    Point refl(Point p) { return p - perp(v) * 2 * side(p) / sq(v); }
};

// floating point
bool inter(Line l1, Line l2, Point& out) {
    T d = cross(l1.v, l2.v);
    if ( d == 0 ) return false;
    out = (l2.v * l1.c - l1.v * l2.c) / d;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    Line l1 {{-5, 0}, {0, 4}};
    Line l2 {{2, 0}, {0, 2}};
    Point p, q { -4, 3};

    cout << boolalpha << inter(l1, l2, p) << "\n";
    cout << p << "\n";
    cout << l1.c << " " << l1.v << "\n";
    cout << cross(l1.v, q) << "\n";
    cout << l1.side(q) << "\n";
    cout << l1.proj(q) << "\n";
    cout << l2.refl(q) << "\n";
    cout << l1.dist(q) << "\n";


    return 0;
}

