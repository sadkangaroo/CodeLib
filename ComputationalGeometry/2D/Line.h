#ifndef _Line_H_
#define _Line_H_

#include "Point.h"

struct Line {
	#define eps (1e-9)
	Point a, b; double ang; int lab;
	Line() {}
	Line(Point _a, Point _b): a(_a), b(_b) {}
	void load(int _lab = 0) {
		a.load(); b.load();
		lab = _lab;
	}
	void load(double A, double B, double C) { // (A, B) - leftside
		if (fabs(A) < eps) a = Point(0, -C / B);
		else a = Point(-C / A, 0);
		b = a + Point(B, -A);
	}
	double det(const Line &t) const {
		return (b - a).det(t.b - t.a);
	}
	double dot(const Line &t) const {
		return (b - a).dot(t.b - t.a);
	}
	bool coincideWith(const Line &t) const {
		return fabs((b - a).det(t.a - a)) < eps && fabs((b - a).det(t.b - a)) < eps;	
	}
	bool parallelWith(const Line &t) const {
		return fabs((b - a).det(t.b - t.a)) < eps;
	}
	bool strictlyIntersectWith(const Line &t) const {
		return (b - a).det(t.a - a) * (b - a).det(t.b - a) < -eps
			&& (t.b - t.a).det(a - t.a) * (t.b - t.a).det(b - t.a) < -eps;
	}
	bool normallyIntersectWith(const Line &t) const {
		return !coincideWith(t) && (b - a).det(t.a - a) * (b - a).det(t.b - a) < eps
			&& (t.b - t.a).det(a - t.a) * (t.b - t.a).det(b - t.a) < eps;
	}
	Point getIntersection(const Line &t) const {
		double t1 = (b - a).det(t.a - a), t2 = -(b - a).det(t.b - a);
		return (t.a * t2 + t.b * t1) / (t1 + t2);
	}
	Point getProjection(const Point &t) const {
		return a + (b - a) * ((b - a).dot(t - a) / b.dis2(a));
	}
	Point getMirror(const Point &t) const {
		return getProjection(t) * 2 - t;
	}
	void getAng() {
		ang = atan2(b.y - a.y, b.x - a.x);
	}
	#undef eps
};

#endif

struct Line {
	#define eps (1e-9)
	Point a, b; double ang; int lab;
	Line() {}
	Line(Point _a, Point _b): a(_a), b(_b) {}
	void load(int _lab = 0) {
		a.load(); b.load();
		lab = _lab;
	}
	void load(double A, double B, double C) {	/* (A, B) - leftside */
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
	bool coincideWith(const Line &t) const {
		return fabs((b - a).det(t.a - a)) < eps && fabs((b - a).det(t.b - a)) < eps;	
	}
	bool parallelWith(const Line &t) const {
		return fabs((b - a).det(t.b - t.a)) < eps;
	}
	bool strictlyIntersectWith(const Line &t) const {
		return (b - a).det(t.a - a) * (b - a).det(t.b - a) < -eps
			&& (t.b - t.a).det(a - t.a) * (t.b - t.a).det(b - t.a) < -eps;
	}
	bool normallyIntersectWith(const Line &t) const {
		return !coincideWith(t) && (b - a).det(t.a - a) * (b - a).det(t.b - a) < eps
			&& (t.b - t.a).det(a - t.a) * (t.b - t.a).det(b - t.a) < eps;
	}
	Point getIntersection(const Line &t) const {
		double t1 = (b - a).det(t.a - a), t2 = -(b - a).det(t.b - a);
		return (t.a * t2 + t.b * t1) / (t1 + t2);
	}
	Point getProjection(const Point &t) const {
		return a + (b - a) * ((b - a).dot(t - a) / b.dis2(a));
	}
	Point getMirror(const Point &t) const {
		return getProjection(t) * 2 - t;
	}
	void getAng() {
		ang = atan2(b.y - a.y, b.x - a.x);
	}
	#undef eps
};
