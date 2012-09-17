#ifndef _Point_H_
#define _Point_H_

#include "Basic.h"

struct Point {
    double x, y, ang; int lab;
    Point() {}
    Point(double _x, double _y): x(_x), y(_y) {}
    void load(int _lab = 0) {
        scanf("%lf%lf", &x, &y);
        lab = _lab;
    }
    void print();
    Point operator + (const Point &t) const {
        return Point(x + t.x, y + t.y);
    }
    Point operator - (const Point &t) const {
        return Point(x - t.x, y - t.y);
    }
    Point operator * (const double t) const {
        return Point(x * t, y * t);
    }
    Point operator / (const double t) const {
        return Point(x / t, y / t);
    }
    Point operator * (const Point &t) const {
        return Point(x * t.x - y * t.y, x * t.y + y * t.x);
    }
    Point operator / (const Point &t) const {
        return Point(x * t.x + y * t.y, y * t.x - x * t.y) / t.norm2();
    }
    bool operator == (const Point &t) const {
        return fabs(x - t.x) < eps && fabs(y - t.y) < eps;
    }
    double det(const Point &t) const {
        return x * t.y - y * t.x;
    }
    double dot(const Point &t) const {
        return x * t.x + y * t.y;
    }
    double norm() const {
        return Sqrt(Sqr(x) + Sqr(y));
    }
    double norm2() const {
        return Sqr(x) + Sqr(y);
    }
    double dis(const Point &t) const {
        return Sqrt(Sqr(x - t.x) + Sqr(y - t.y));
    }
    double dis2(const Point &t) const {
        return Sqr(x - t.x) + Sqr(y - t.y);
    }
    Point normalize() const {    /* avoid (0, 0) before */
        return *this / norm();
    }
    Point rotate(double a) {
        return *this * Point(cos(a), sin(a));
    }
    Point rotate() {    /* turn leftside 90 degrees */
        return Point(-y, x);
    }
    void makeLine(const Point &t, double &A, double &B, double &C) const {    /* (A, B) - leftside, Ax + By + C > 0 */
        A = y - t.y; B = t.x - x; C = det(t); 
    }
    double getAng() {    /* avoid (0, 0) before */
        return ang = atan2(y, x);
    }
};

#endif
