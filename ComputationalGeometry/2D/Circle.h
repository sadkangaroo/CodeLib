#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "Point.h"

struct Circle {
	#define eps (1e-9)
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
	bool in(const Circle &t) const {
		 return o.dis(t.o) < t.r - r - eps;
	}
	bool inOn(const Circle &t) const {
		 return fabs(t.r - r - o.dis(t.o)) < eps;
	}
	bool to(const Circle &t) const {
		 return r + t.r < o.dis(t.o) - eps;
	}
	bool toOn(const Circle &t) const {
		 return fabs(r + t.r - o.dis(t.o)) < eps;
	}
	double Acos(double x) const {
		if (x < -1) x = -1;
		if (x > 1) x = 1;
		return acos(x);
	}
	double interArea(const Circle &t) const {
       if (to(t) || toOn(t)) return 0; 
       if (in(t) || inOn(t)) return area(); 
	   if (t.in(*this) || t.inOn(*this)) return t.area();
       double a1 = 2 * Acos((sqr(r) + o.dis2(t.o) - sqr(t.r)) / (2 * r * o.dis(t.o)));
       double a2 = 2 * Acos((sqr(t.r) + o.dis2(t.o) - sqr(r)) / (2 * t.r * o.dis(t.o)));
       return fabs(sqr(r) * (a1 - sin(a1)) / 2 + sqr(t.r) * (a2 - sin(a2)) / 2);
    }
	#undef eps
	#undef pi
	#undef sqr
};

#endif
