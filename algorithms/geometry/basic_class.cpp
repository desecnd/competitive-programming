#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

using ll = long long;

struct Point {
    using ll = long long;
    ll x, y;

    Point(ll a = 0, ll b = 0) : x(a), y(b) {}

    Point& operator+=(const Point& p) {
        this->x += p.x; this->y += p.y;
        return *this; 
    }

    friend Point operator+(Point lhs, const Point& rhs) {
        lhs += rhs;
        return lhs; 
    }

    Point& operator-=(const Point& p) {
        this->x -= p.x; this->y -= p.y;
        return *this;
    }
    
    friend Point operator-(Point lhs, const Point& rhs) {
        lhs -= rhs;
        return lhs;
    }

    double distance(const Point& p) const {
        ll diffX = p.x - this->x;
        ll diffY = p.y - this->y;
        return sqrt(diffX * diffX + diffY * diffY );
    }

    friend double distance(const Point& lhs, const Point& rhs) {
        return lhs.distance(rhs); 
    }
};

struct Vec2D {
    using ll = long long; 
    ll x, y;

    Vec2D(Point A, Point B) : x(B.x - A.x), y(B.y - A.y) {}
    Vec2D(ll a, ll b) : x(a), y(b) {}

    // dot product / skalar product
    friend ll operator^(const Vec2D a, const Vec2D& b) {
        return a.x * b.x + a.y * b.y;
    }

    // cross product / vector product
    friend ll operator*(const Vec2D a, const Vec2D& b) {
        return a.x * b.y - a.y * b.x;
    }

    Vec2D& operator+=(const Vec2D& vec) {
        this->x += vec.x; this->y += vec.y;
        return *this;
    }

    friend Vec2D operator+(Vec2D lhs, const Vec2D& rhs) {
        lhs += rhs;
        return lhs; 
    }

    double mag() const {
        return sqrt( x * x + y * y );
    }
};

double LineToPointDistance(Point A, Point B, Point C, bool isSegment = false) {
    // simple triangle field formula
    // P = ah/2 
    // cross product of line AB and AC is simply 2*Field of ABC
    // we search for h so we need to divide 2P by a 

    ll crossProd { Vec2D(A, B) * Vec2D(A, C) };
    double a = Vec2D(A, B).mag(); 
    double dist { fabs(crossProd / a) };

    // cosine in dot product is negative if B c (90, 270)
    if ( isSegment ) {
        ll dotFromB { Vec2D(B, A) ^ Vec2D(B, C) }; 
        if ( dotFromB < 0 ) dist = distance(B, C);

        ll dotFromA { Vec2D(A, B) ^ Vec2D(A, C) }; 
        if ( dotFromA < 0 ) dist = distance(A, C);
    }
    return dist;
}


double PolygonArea(const vector<Point> &points) {
    // Points have to be given around perimeter - clockwise / counterclockwise
    Point A = points[0];
    double area = 0;

    for (int i = 1; i < points.size() - 1; i++) {
        ll crossProd { Vec2D(A, points[i]) * Vec2D(A, points[i + 1]) };
        area += crossProd;
    }
    // cross product is a field of parallelogram given by those 2 vectors 
    // we have to divide by 2 in the end to count only triangle fields
    return fabs(area / 2);
}


int main() {
    ios::sync_with_stdio(0);

    vector<Point> pointsCounterClockwise {{0,2}, {0,0}, {2,0}, {2,2}};
    vector<Point> pointsClockwise {{2,2}, {2,0}, {0,0}, {0,2}};


    cout << "Polygon Area (clockwise): " << PolygonArea(pointsClockwise) << "\n";
    cout << "Polygon Area (counter) : " << PolygonArea(pointsCounterClockwise) << "\n";

    Point A {2, 4}, B{2, 7}, C{4, 8};

    cout  << "Distance to line A-B: " << LineToPointDistance(A, B, C) << "\n";
    cout << "Distance to segment A-B: " << LineToPointDistance(A, B, C, true) << "\n";

    return 0;
}


