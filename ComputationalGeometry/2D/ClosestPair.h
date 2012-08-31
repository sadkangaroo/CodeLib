#ifndef _CLOSESTPAIR_H_
#define _CLOSESTPAIR_H_

#include "Point.h"

namespace CP {
	#define eps (1e-9)
	bool cmpX(const Point &a, const Point &b) {
		return a.x < b.x;
	}
	bool cmpY(const Point &a, const Point &b) {
		return a.y < b.y;
	}
	double divAndCon(Point* pts, int l, int r, Point* tmp) {
	   if (l == r) return 1e100;
	   int mid = (l + r) >> 1;
	   double res = min(divAndCon(pts, l, mid, tmp), divAndCon(pts, mid + 1, r, tmp));
	   int top = 0;
	   for (int i = l; i <= r; ++i)
		   if (fabs(pts[i].x - pts[mid].x) < res - eps) tmp[top++] = pts[i];
	   sort(tmp, tmp + top, cmpY);
	   for (int i = 0; i < top; ++i)
		   for (int j = i + 1; j < top; ++j) 
			   if (fabs(tmp[i].y - tmp[j].y) > res - eps) break;
			   else res = min(res, tmp[i].dis(tmp[j]));
	   return res;
	}
	double getShortestDis(Point* pts, int N) {
		sort(pts, pts + N, cmpX);
		Point *tmp;	
		tmp = new Point[N + 5];
		double res = divAndCon(pts, 0, N - 1, tmp);
		delete[] tmp;
		return res;
	}
	#undef eps
}

#endif
