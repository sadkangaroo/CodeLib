#ifndef _Point_H_
#define _Point_H_

struct Point {
	#define sqr(x) ((x) * (x))
	#define eps (1e-8)
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
		return Point(x * t.x + y * t.y, y * t.x - x * t.y) / t.mo2();
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
	double mo() const {
		return sqrt(sqr(x) + sqr(y));
	}
	double mo2() const {
		return sqr(x) + sqr(y);
	}
	double dis(const Point &t) const {
		return sqrt(sqr(x - t.x) + sqr(y - t.y));
	}
	double dis2(const Point &t) const {
		return sqr(x - t.x) + sqr(y - t.y);
	}
	Point normalize() const {	/* avoid (0, 0) before */
		return *this / mo();
	}
	Point rotate(double a) {
		return *this * Point(cos(a), sin(a));
	}
	void makeLine(const Point &t, double &A, double &B, double &C) const {	/* (A, B) - leftside, Ax + By + C > 0 */
		A = y - t.y; B = t.x - x; C = det(t); 
	}
	double getAng() {	/* avoid (0, 0) before */
		return ang = atan2(y, x);
	}
	#undef sqr
	#undef eps
};

#endif
