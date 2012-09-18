#ifndef _TriangleCenter_H_
#define _TriangleCenter_H_

#include "Basic.h"
#include "Point.h"

namespace TC {
    Point centroid(const Point &a, const Point &b, const Point &c) {
        return (a + b + c) / 3;
    }
    Point circumcenter(Point a, Point b, Point c) {
        b = b - a, c = c - a;
        double d = b.det(c) * 2;
        Point p = Point(b.norm2(), c.norm2());
        return a + Point(p.det(Point(b.y, c.y)), Point(b.x, c.x).det(p)) / d;
    }
    Point incenter(const Point &a, const Point &b, const Point &c) {
        double A = b.dis(c), B = a.dis(c), C = a.dis(b);
        return (a * A + b * B + c * C) / (A + B + C);
    }
    Point orthocenter(const Point &a, const Point &b, const Point &c) {
        return a + b + c - circumcenter(a, b, c) * 2;
    }
}

#endif

