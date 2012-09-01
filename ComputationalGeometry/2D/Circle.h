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
	bool strictlyIntersectWith(const Circle &t) const {
		double d = o.dis(t.o);
		return d > fabs(r - t.r) + eps && d < r + t.r - eps;
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
		double dx = t.b.x - t.a.x, dy = t.b.y - t.a.y;
		double u = t.a.x - o.x, v = t.a.y - o.y;
		double A = sqr(dx) + sqr(dy), B = 2 * (dx * u + dy * v), C = sqr(u) + sqr(v) - sqr(r);
		double delta = sqr(B) - 4 * A * C;
		if (delta < -eps) return 0;
		if (delta < 0) delta = 0;
		pts[0] = t.a + (t.b - t.a) * (-B - sqrt(delta)) / (2 * A);
		pts[1] = t.a + (t.b - t.a) * (-B + sqrt(delta)) / (2 * A);
		if (delta > eps) return 2; else return 1;
    }
	int strictlyGetIntersectionAsSeg(const Line &t, Point* pts) const {
		double dx = t.b.x - t.a.x, dy = t.b.y - t.a.y;
		double u = t.a.x - o.x, v = t.a.y - o.y;
		double A = sqr(dx) + sqr(dy), B = 2 * (dx * u + dy * v), C = sqr(u) + sqr(v) - sqr(r);
		double delta = sqr(B) - 4 * A * C;
		if (delta < -eps) return 0;
		if (delta < 0) delta = 0;
		double t1 = (-B - sqrt(delta)) / (2 * A);
		double t2 = (-B + sqrt(delta)) / (2 * A);
		int res = 0;
		if (t1 > eps && t1 < 1 - eps) pts[res++] = t.a + (t.b - t.a) * t1;
		if (t2 > eps && t2 < 1 - eps) pts[res++] = t.a + (t.b - t.a) * t2;
		return res;
    }
    int getIntersection(const Circle &t, Point* pts) const {	/* return -1 if coincide */
		if (o == t.o && fabs(r - t.r) < eps) return -1;
		double mx = t.o.x - o.x, sx = t.o.x + o.x, my = t.o.y - o.y, sy = t.o.y + o.y;
		double sq = sqr(mx) + sqr(my), d = -(sq - sqr(r - t.r)) * (sq - sqr(r + t.r));
		if (d < -eps) return 0; else d = sqrt(fabs(d));
		double tx = mx * ((sqr(r) - sqr(t.r)) + mx * sx) + sx * sqr(my);
		double ty = my * ((sqr(r) - sqr(t.r)) + my * sy) + sy * sqr(mx);
		double dx = mx * d, dy = my * d;
		pts[0] = Point((tx - dy), (ty + dx)) / (sq * 2);
		pts[1] = Point((tx + dy), (ty - dx)) / (sq * 2);
		if (d > eps) return 2; else return 1;
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
