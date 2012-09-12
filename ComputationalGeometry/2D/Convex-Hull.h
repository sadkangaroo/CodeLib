#ifndef _CONVEXHULL_H_
#define _CONVEXHULL_H_

#include "Point.h"
#include "Line.h"

namespace CH {
    #define eps (1e-9)
    bool cmp(const Point &a, const Point &b) {
        if (fabs(a.y - b.y) < eps) return a.x < b.x;
        return a.y < b.y;
    }
    int grahamAnticlockNoBoarder(Point* pts, int N, Point* stk) {    // first Node returned is bottommost and as far to the left as possible
        sort(pts, pts + N, cmp); N = unique(pts, pts + N) - pts;
        if (N == 1) {stk[0] = pts[0]; return 1;}
        int top = 0;
        for (int i = 0; i < N; ++i) {
            while (top >= 2 && (stk[top - 1] - stk[top - 2]).det(pts[i] - stk[top - 1]) > -eps) top--;
            stk[top++] = pts[i];
        } int base = top - 1;
        for (int i = N - 2; i >= 0; --i) {
            while (top - base >= 2 && (stk[top - 1] - stk[top - 2]).det(pts[i] - stk[top - 1]) > -eps) top--;
            stk[top++] = pts[i];    
        } return top - 1;
    }
    double getParDis(Point* ch1, int N1, Point* ch2, int N2) {
        double res = ch1[0].dis(ch2[0]);
        int p = 0;
        for (int i = 1; i < N2; ++i) if (cmp(ch2[p], ch2[i])) p = i;
        for (int i = 0; i < N1; ++i) {
            while ((ch1[i] - ch1[i + 1]).det(ch2[p + 1] - ch2[p]) > eps) p++;
            res = min(res, Line(ch1[i], ch1[i + 1]).disAsSeg(ch2[p]));
            res = min(res, Line(ch1[i], ch1[i + 1]).disAsSeg(ch2[p + 1]));
        }
        return res;
    }
    double dis(Point* pts1, int N1, Point* pts2, int N2) {    /* default is minimal, change min to max to get maximal */
        Point *ch1 = new Point[3 * N1 + 5], *ch2 = new Point[3 * N2 + 5];
        N1 = grahamAnticlockNoBoarder(pts1, N1, ch1); 
		for (int i = N1; i < 3 * N1 + 5; ++i) ch1[i] = ch1[i - N1];
        N2 = grahamAnticlockNoBoarder(pts2, N2, ch2);
        for (int i = N2; i < 3 * N2 + 5; ++i) ch2[i] = ch2[i - N2];
        double res = min(getParDis(ch1, N1, ch2, N2), getParDis(ch2, N2, ch1, N1));
        delete[] ch1; delete[] ch2;
        return res;
    }
    #undef eps
}

#endif
