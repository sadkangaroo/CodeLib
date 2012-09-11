#ifndef _CONVEXHULL_H_
#define _CONVEXHULL_H_

#include "Point.h"

namespace CH {
    #define eps (1e-9)
    bool cmp(const Point &a, const Point &b) {
        if (fabs(a.y - b.y) < eps) return a.x < b.x;
        return a.y < b.y;
    }
    int grahamAnticlockNoBoarder(Point* pts, int N, Point* stk) {
        sort(pts, pts + N, cmp); N = unique(pts, pts + N) - pts;
        if (N == 1) {stk[0] = pts[0]; return 1;}
        int top = 0;
        for (int i = 0; i < N; ++i) {
            while (top >= 2 && (stk[top - 1] - stk[top - 2]).det(pts[i] - stk[top - 1]) < eps) top--;
            stk[top++] = pts[i];
        } int base = top - 1;
        for (int i = N - 2; i >= 0; --i) {
            while (top - base >= 2 && (stk[top - 1] - stk[top - 2]).det(pts[i] - stk[top - 1]) < eps) top--;
            stk[top++] = pts[i];
        } return top - 1;
    }
    #undef eps
}

#endif
