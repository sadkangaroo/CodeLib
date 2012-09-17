#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "Basic.h"
#include "Point.h"
#include "Line.h"

struct Circle {
    Point o; double r; int lab;
    Circle() {}
    Circle(Point _o, double _r): o(_o), r(_r) {}
    void load(int _lab = 0) {
        o.load(); scanf("%lf", &r);
    }
    double area() const {
        return pi * r * r;
    }
    bool in(const Circle &t) const {
        return o.dis(t.o) < t.r - r + eps;
    }
    bool to(const Circle &t) const {
        return o.dis(t.o) > t.r + r - eps;
    }
    bool operator == (const Circle &t) const {
        return o == t.o && fabs(r - t.r) < eps;
    }
    Point intersect(const Point &a, const Point &b) const {    /* ensure normally intersected, returned point closer to a */
        double x = Sqrt(Sqr(r) - Sqr(Line(a, b).disToLine(o)));
        return Line(a, b).getProjection(o) - (b - a).normalize() * x;
    }
    Point intersect(const Circle &t) const {    /* ensure normally intersected, especially not coincide, returned point on the right side of (o, t.o) */
        double d = o.dis(t.o);
        double x = 0.5 * ((Sqr(r) - Sqr(t.r)) / d + d);
        double h = Sqrt(Sqr(r) - Sqr(x));
        return (o * (d - x) + t.o * x) / d - (t.o - o).rotate().normalize() * h;
    }
    double interArea(const Circle &t) const {
        if (to(t)) return 0; 
        if (in(t)) return area(); if (t.in(*this)) return t.area();
        double a1 = 2 * Acos((Sqr(r) + o.dis2(t.o) - Sqr(t.r)) / (2 * r * o.dis(t.o)));
        double a2 = 2 * Acos((Sqr(t.r) + o.dis2(t.o) - Sqr(r)) / (2 * t.r * o.dis(t.o)));
        return fabs(Sqr(r) * (a1 - sin(a1)) / 2 + Sqr(t.r) * (a2 - sin(a2)) / 2);
    }
    double interArea(const Point &t1, const Point &t2) const {
        Point tmp[4], cx; int top = 0; tmp[top++] = t1; 
        if (Line(t1, t2).disToLine(o) < r - eps) {
            if (Line(t1, t2).strictlyContains(cx = intersect(t1, t2)))
                    tmp[top++] = cx;
            if (Line(t1, t2).strictlyContains(cx = intersect(t2, t1)))
                    tmp[top++] = cx;
        }
        tmp[top++] = t2; double res = 0;
        for (int i = 0; i + 1 < top; ++i) {
            if (tmp[i].dis(o) > eps && tmp[i + 1].dis(o) > eps && 
                    (tmp[i].dis(o) > r + eps || tmp[i + 1].dis(o) > r + eps)) 
                res += ((tmp[i + 1] - o) / (tmp[i] - o)).getAng() * r * r;
            else res += (tmp[i] - o).det(tmp[i + 1] - o);
        } return 0.5 * res;
    }
    double interArea(Point* pts, int N) const {
        double res = 0;
        for (int i = 0; i < N; ++i) 
            if (i == N - 1) res += interArea(pts[i], pts[0]);
            else res += interArea(pts[i], pts[i + 1]);
        return fabs(res);
    }
};

#endif
