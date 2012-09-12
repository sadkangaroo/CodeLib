#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "Point.h"
#include "Line.h"

struct Circle {
    #define eps (1e-8)
    #define pi (3.141592653589793238)
    #define sqr(x) ((x) * (x))
    Point o; double r; int lab;
    Circle() {}
    Circle(Point _o, double _r): o(_o), r(_r) {}
    void load(int _lab = 0) {
        o.load(); scanf("%lf", &r);
    }
    double area() const {
        return pi * r * r;
    }
    bool strictlyIn(const Circle &t) const {
        return o.dis(t.o) < t.r - r - eps;
    }
    bool inOn(const Circle &t) const {
        return fabs(t.r - r - o.dis(t.o)) < eps;
    }
    bool strictlyTo(const Circle &t) const {
        return r + t.r < o.dis(t.o) - eps;
    }
    bool toOn(const Circle &t) const {
        return fabs(r + t.r - o.dis(t.o)) < eps;
    }
    bool coincide(const Circle &t) const {
        return o == t.o && fabs(r - t.r) < eps;
    }
    bool strictlyIntersectWith(const Circle &t) const {
        double d = o.dis(t.o);
        return d > fabs(r - t.r) + eps && d < r + t.r - eps;
    }
    bool notStrictlyIntersectWith(const Circle &t) const {
        double d = o.dis(t.o);
        return d > fabs(r - t.r) - eps && d < r + t.r + eps;
    }
    double Acos(double x) const {
        if (x < -1) x = -1;
        if (x > 1) x = 1;
        return acos(x);
    }
    int countIntersection(const Line &t) const {
        double d = t.disAsLine(o); if (d > r + eps) return 0;
        if (d < r - eps) return 2; else return 1;
    }
    int getIntersectionAsLine(const Line &t, Point* pts) const {
        double d = t.disAsLine(o); if (d > r + eps) return 0;
        Point p = t.getProjection(o);
        double x = sqrt(fabs(sqr(r) - sqr(d)));
        Point delta = (t.b - t.a).normalize() * x;
        pts[0] = p - delta; pts[1] = p + delta;
        if (pts[0] == pts[1]) return 1; else return 2;
    }
    int strictlyGetIntersectionAsSeg(const Line &t, Point* pts) const {
        double d = t.disAsLine(o); if (d > r + eps) return 0;
        Point p = t.getProjection(o);
        double x = sqrt(fabs(sqr(r) - sqr(d)));
        int res = 0; delta = (t.b - t.a).normalize() * x;
        if (t.strictlyContainsPointAsSeg(p - delta)) pts[res++] = p - delta;
        if (t.strictlyContainsPointAsSeg(p + delta)) pts[res++] = p + delta;
        return res;
    }
    int getIntersection(const Circle &t, Point* pts) const {    /* ensure not coincide */
        double d = o.dis(t.o);
        if (d < fabs(r - t.r) - eps || d > r + t.r + eps) return 0;
        double x = (sqr(r) + sqr(d) - sqr(t.r)) / (2 * d);
        Point p = (o * (d - x) + t.o * x) / d;
        double y = sqrt(fabs(sqr(r) - sqr(x)));
        Point delta = (t.o - o).turn().normalize() * y;
        pts[0] = p - delta; pts[1] = p + delta;
        if (pts[0] == pts[1]) return 1; else return 2;
    }
    double interArea(const Circle &t) const {
        if (strictlyTo(t) || toOn(t)) return 0; 
        if (strictlyIn(t) || inOn(t)) return area(); 
        if (t.strictlyIn(*this) || t.inOn(*this)) return t.area();
        double a1 = 2 * Acos((sqr(r) + o.dis2(t.o) - sqr(t.r)) / (2 * r * o.dis(t.o)));
        double a2 = 2 * Acos((sqr(t.r) + o.dis2(t.o) - sqr(r)) / (2 * t.r * o.dis(t.o)));
        return fabs(sqr(r) * (a1 - sin(a1)) / 2 + sqr(t.r) * (a2 - sin(a2)) / 2);
    }
    double interArea(const Point &t1, const Point &t2) const {
        Point tmp[4]; int top = 0; tmp[top++] = t1; 
        top += strictlyGetIntersectionAsSeg(Line(t1, t2), tmp + 1); 
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
    #undef eps
    #undef pi
    #undef sqr
};

#endif
