#ifndef _CirclesArea_H_
#define _CirclesArea_H_

#include "Basic.h"
#include "Point.h"
#include "Line.h"
#include "Circle.h"

namespace CA {
    struct Event {
        double a; int cnt;
        Event() {}
        Event(double _a, int _cnt): a(_a), cnt(_cnt) {}
        bool operator < (const Event &t) const {
            return a < t.a;
        }
    };
    inline Point polar(double a, double r) {
        return Point(cos(a), sin(a)) * r;
    }
    void add(Event* events, int& top, double a, int t) {
        events[top++] = Event(a, t);
    }
    void addPair(Event* events, int& top, double a, double b) {
        add(events, top, a, 1); add(events, top, b, -1);
    }
    double normalize(double x) {
        if (x < -pi) x += 2 * pi;
        if (x >= pi) x -= 2 * pi;
        return x;
    }
    double calcArea(Circle* circles, int N, double* ans) {    /* return area coverd more than K times, stored in ans[K] */
        /* when only consider K == 0 or K == N - 1, remove the useless circles first to get significant speedup */
        for (int i = 0; i < N; ++i) ans[i] = 0;
        Event* events = new Event[N * 4 + 10];
        for (int i = 0; i < N; ++i) {
            Circle &a = circles[i]; int top = 0, counter = 0;      
            add(events, top, -pi, 0); add(events, top, pi, 0);
            for (int j = 0; j < N; ++j) if (j != i) {
                Circle &b = circles[j];
                if (a == b) {if (i < j) counter++;}
                else {
                    if (a.o.dis(b.o) < fabs(b.r - a.r) + eps) {if (a.r < b.r - eps) counter++;}
                    else if (a.o.dis(b.o) < a.r + b.r - eps) {
                        double d2 = a.o.dis2(b.o);
                        double ag = (b.o - a.o).getAng();
                        double tg = acos((a.r * a.r + d2 - b.r * b.r) / (2 * a.r * Sqrt(d2)));
                        double x = normalize(ag - tg), y = normalize(ag + tg);
                        if (x < y) addPair(events, top, x, y);
                        else {addPair(events, top, x, pi); addPair(events, top, -pi, y);}
                    }
                }
            }
            sort(events, events + top);
            counter += events[0].cnt;
            for (int j = 1; j < top; ++j) {    /* when only consider K, add ``if (counter == K)``, to get very good speedup */
                double delta = events[j].a - events[j - 1].a;
                if (delta < eps) {
                    counter += events[j].cnt; 
                    continue;
                }
                ans[counter] += 0.5 * Sqr(a.r) * (delta - sin(delta));
                Point p = a.o + polar(events[j - 1].a, a.r);
                Point q = a.o + polar(events[j].a, a.r);
                ans[counter] += 0.5 * p.det(q);
                counter += events[j].cnt;
            }
        }
        delete[] events;
    }
}

#endif
