#ifndef _MinCircleCover_H_
#define _MinCircleCover_H_

#include "Basic.h"
#include "Point.h"
#include "Circle.h"

namespace MCC {
    Circle minCircle(Point* _pts, int N) {
        Point* pts = new Point[N];
        for (int i = 0; i < N; ++i) pts[i] = _pts[i];
        random_shuffle(pts, pts + N);
        Circle res(Point(0, 0), 0);   
        for (int i = 0; i < N; ++i) if (!res.contains(pts[i])) {
            res = Circle(pts[i], 0);
            for (int j = 0; j < i; ++j) if (!res.contains(pts[j])) {
                res = Circle(pts[i], pts[j]);
                for (int k = 0; k < j; ++k) if (!res.contains(pts[k])) 
                    res = Circle(pts[i], pts[j], pts[k]); 
            }
        }
        delete[] pts;
        return res;
    }
}

#endif
