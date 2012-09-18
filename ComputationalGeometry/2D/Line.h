#ifndef _Line_H_
#define _Line_H_

#include "Basic.h"
#include "Point.h"

struct Line {
    Point a, b; double ang; int lab;
    Line() {}
    Line(Point _a, Point _b): a(_a), b(_b) {}
    bool load(int _lab = 0) {
        lab = _lab;
        return a.load() && b.load();
    }
    void load(double A, double B, double C) {    /* (A, B) - leftside, Ax + By + C > 0 */
        if (fabs(A) < eps) a = Point(0, -C / B);
        else a = Point(-C / A, 0);
        b = a + Point(B, -A).normalize();
    }
    double det(const Line &t) const {
        return (b - a).det(t.b - t.a);
    }
    double dot(const Line &t) const {
        return (b - a).dot(t.b - t.a);
    }
    double disToLine(const Point &t) const {
        return fabs((t - a).det(t - b) / a.dis(b));
    }
    double disToSegment(const Point &t) const {
        if ((b - a).dot(t - a) > eps && (a - b).dot(t - b) > eps) return disToLine(t);        
        return min(a.dis(t), b.dis(t));
    }
    bool coincide(const Line &t) const {
		return fabs((b - a).det(t.a - a)) < eps && fabs((b - a).det(t.b - a)) < eps;	
	}
    bool strictlyIntersected(const Line &t) const {
        return (b - a).det(t.a - a) * (b - a).det(t.b - a) < -eps
            && (t.b - t.a).det(a - t.a) * (t.b - t.a).det(b - t.a) < -eps;
    }
    bool normallyIntersected(const Line &t) const {
        return !coincide(t) && (b - a).det(t.a - a) * (b - a).det(t.b - a) < eps
            && (t.b - t.a).det(a - t.a) * (t.b - t.a).det(b - t.a) < eps;
    }
    bool strictlyContains(const Point &t) const {
        return fabs((b - a).det(t - a)) < eps && (t - a).dot(t - b) < -eps;
    }
    bool normallyContains(const Point &t) const {
        return fabs((b - a).det(t - a)) < eps && (t - a).dot(t - b) < eps;
    }
    Point intersect(const Line &t) const {    /* ensure intersected before */
        double t1 = (b - a).det(t.a - a), t2 = -(b - a).det(t.b - a);
        return (t.a * t2 + t.b * t1) / (t1 + t2);
    }
    Point getProjection(const Point &t) const {
        return a + (b - a) * ((b - a).dot(t - a) / b.dis2(a));
    }
    Point getMirror(const Point &t) const {
        return getProjection(t) * 2 - t;
    }
    double getAng() {
        return ang = atan2(b.y - a.y, b.x - a.x);
    }
};

#endif
