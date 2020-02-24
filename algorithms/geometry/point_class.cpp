/*
* author: https://vlecomte.github.io/cp-geo.pdf
* task: basic point geometry class for Competitive Programming
*/

#include <iostream>
#include <cmath>
#include <cassert>
#include <algorithm>
using namespace std;

using T = long long;
double inline PI() { return atan(1)*4; }

struct Point {
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}

    Point operator+(Point p) { return { x + p.x, y + p.y}; }
    Point operator-(Point p) { return { x - p.x, y - p.y}; }
    Point operator*(T val) { return { x * val, y * val}; }
    Point operator/(T val) { return { x / val, y / val}; }
};

bool operator==(Point a, Point b) { return a.x == b.x && a.y == b.y; }
bool operator!=(Point a, Point b) { return !(a == b); }
T sq(Point p) { return p.x*p.x + p.y*p.y; }
double abs(Point p) { return sqrt(sq(p)); }

T dot(Point v, Point w) { return v.x * w.x + v.y * w.y; } 
bool isPerp(Point v, Point w) { return dot(v, w) == T(0); }
double angle(Point v, Point w) {
    double cosTheta = dot(v, w) / abs(v) / abs(w);
    return acos(max(-1.0, min(1.0, cosTheta)));
}

T cross(Point v, Point w) { return v.x * w.y - w.x * v.y; }
T orient(Point a, Point b, Point c) { return cross(b-a, c-a); }
bool inAngle(Point a, Point b, Point c, Point p) {
    assert(orient(a,b,c) != 0);
    if ( orient(a, b, c) < 0 ) swap(b,c);
    return orient(a,b,p) >= 0 && orient(a,c,p) <= 0;
}
double orientedAngle(Point a, Point b, Point c) {
    if ( orient(a,b,c) >= 0 ) return angle(b-a, c-a);
    else return 2*PI() - angle(b-a, c-a);
}

ostream& operator<<(ostream& out, Point p) {
    return out << "(" <<  p.x << "," << p.y << ")";
} 

int main() {
    ios::sync_with_stdio(0);

    Point a{2,4}, b{7,3}, c{-3,3};
    cout << "Oriented Angle AB, AC (counterclockwise): " << orientedAngle(a,b,c) / PI() * 180 << "\n";
    cout << "Angle between AB, AC: " << angle(b-a, c-a) / PI() * 180 << "\n";
    cout << "Angle between AC, AB: " << angle(c-a, b-a) / PI() * 180 << "\n";
    Point d{6, 4}, e {2, 3};
    cout << "Point " << d << " in angle: " << a << b << c << " = " <<  boolalpha << inAngle(a,b,c,d) << "\n";
    cout << "Point " << e << " in angle: " << a << b << c << " = " <<  boolalpha << inAngle(a,b,c,e) << "\n";

    cout << "Point " << d << " in angle: " << a << c << b << " = " <<  boolalpha << inAngle(a,c,b,d) << "\n";
    cout << "Point " << e << " in angle: " << a << c << b << " = " <<  boolalpha << inAngle(a,c,b,e) << "\n";

    return 0;
}