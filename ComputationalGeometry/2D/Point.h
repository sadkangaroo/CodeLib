#ifndef _Point_H_
#define _Point_H_

struct Point {
	double x, y, ang; int lab;
	Point() {}
	Point(double _x, double _y): x(_x), y(_y) {}
	void load(int _lab = 0);
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
	double det(const Point &t) const {
		return x * t.y - y * t.x;
	}
	double dot(const Point &t) const {
		return x * t.x + y * t.y;
	}
	double mo() const {
		return sqrt(x * x + y * y);
	}
	double mo2() const {
		return x * x + y * y;
	}
	double dis(const Point &t) const {
		return sqrt((x - t.x) * (x - t.x) + (y - t.y) * (y - t.y));
	}
	double dis2(const Point &t) const {
		return (x - t.x) * (x - t.x) + (y - t.y) * (y - t.y);
	}
	Point normalize() const {
		return *this / mo();
	}
};

#endif
