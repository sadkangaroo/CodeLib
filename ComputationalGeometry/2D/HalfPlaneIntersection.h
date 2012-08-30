#ifndef _HalfPlaneIntersection_H_
#define _HalfPlaneIntersection_H_

#include "Point.h"
#include "Line.h"

struct HalfPlaneIntersection {
	Point pts[HPIMaxN + 5];
	Line seg[HPIMaxN + 5], deq[HPIMaxN + 5];
	bool judgeIn(const Line &v, const Line &t1, const Line &t2) {
		 Point cp = t1.getIntersection(t2);
		 return (v.b - v.a).det(cp - v.a) < -eps;
	}
	int getKernel(Line* _seg, int N) {
		for (int i = 0; i < N; ++i) seg[i] = _seg[i];
		const double oo = 1e10;
		seg[N++] = Line(Point(-oo, -oo), Point(oo, -oo));
		seg[N++] = Line(Point(oo, -oo), Point(oo, oo));
		seg[N++] = Line(Point(oo, oo), Point(-oo, oo));
		seg[N++] = Line(Point(-oo, oo), Point(-oo, -oo));    
		for (int i = 0; i < N; ++i) seg[i].getAng();
		sort(seg, seg + N);
		int tN = 1; 
		for (int i = 1; i < N; ++i) 
			if (fabs(seg[i].ang - seg[i - 1].ang) > eps) seg[tN++] = seg[i];
		N = tN; 
		int bot = 0, top = 0;
		for (int i = 0; i < N; ++i) {
			while (top - bot >= 2 && judgeIn(seg[i], deq[top - 1], deq[top - 2])) top--;
			while (top - bot >= 2 && judgeIn(seg[i], deq[bot], deq[bot + 1])) bot++;
			if (top - bot == 1 && deq[bot].det(seg[i]) < eps) return 0;
			deq[top++] = seg[i];
			while (top - bot >= 3 && judgeIn(deq[bot], deq[top - 1], deq[top - 2])) top--;
			while (top - bot >= 3 && judgeIn(deq[top - 1], deq[bot], deq[bot + 1])) bot++;
		}
		deq[top] = deq[bot]; int num = 0;
		for (int i = bot; i < top; ++i) pts[num++] = deq[i].getIntersection(deq[i + 1]);
		return num;    
	}
};

#endif
