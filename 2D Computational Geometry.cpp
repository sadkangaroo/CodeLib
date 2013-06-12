#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>
#include<complex>

using namespace std;

typedef long double LD;
typedef complex<LD> CPX;

const LD pi = acos(-1.0);

#define sq(x) ((x) * (x))

inline LD nextDouble() {
    double x; scanf("%lf", &x); return (LD)x;
}

inline int sgn1(LD x) {
    return (x > 1e-10) - (x < -1e-10);
}

inline int sgn2(LD x) {
    return (x > 1e-18) - (x < -1e-18);
}

inline LD det(LD x1, LD y1, LD x2, LD y2) {
    return x1 * y2 - x2 * y1;
}

inline LD Acos(LD a) {
       if (a > 1) a = 1; if (a < -1) a = -1;
       return acos(a);
}

/*********************************************************************/

struct Point {
    LD x, y; int lab; LD ang;
    Point() {}
    Point(const LD &_x, const LD &_y)
    : x(_x), y(_y) {}
    void getPoint() {
        x = nextDouble(); y = nextDouble();
    }
    Point operator + (const Point &t)const {
        return Point(x + t.x, y + t.y);
    }
    Point operator - (const Point &t)const {
        return Point(x - t.x, y - t.y);
    }
    Point operator * (const LD &t)const {
        return Point(x * t, y * t);
    }
    Point operator / (const LD &t)const {
        return Point(x / t, y / t);
    }
    Point operator * (const Point &t)const {
          CPX res = CPX(x, y) * CPX(t.x, t.y);
          return Point(res.real(), res.imag());
    }
    Point operator / (const Point &t)const {
          CPX res = CPX(x, y) / CPX(t.x, t.y);
          return Point(res.real(), res.imag());
    }
    bool operator == (const Point &t)const {
         return !sgn1(x - t.x) && !sgn1(y - t.y);
    }
    bool operator < (const Point &t)const {
         if (*this == t) return lab < t.lab;
         return sgn1(y - t.y)? (y < t.y): (x < t.x);
    }
    LD getAng()const {
       return atan2(y, x);
    }
    LD dot(const Point &t)const {
       return x * t.x + y * t.y;
    }
    LD det(const Point &t)const {
       return x * t.y - y * t.x;
    }
    LD dis(const Point &t)const {
       return sqrt(sq(x - t.x) + sq(y - t.y));
    }
    LD dis2(const Point &t)const {
       return sq(x - t.x) + sq(y - t.y);
    }
    LD mo()const {
       return sqrt(sq(x) + sq(y));
    }
    LD mo2()const {
       return sq(x) + sq(y);
    }
    LD getAng(const Point &t)const {
       return (t / *this).getAng();
    }
};

struct Line {
    LD A, B, C; int lab; LD ang;
    Line() {}
    Line(const LD &_A, const LD &_B, const LD &_C): A(_A), B(_B), C(_C) {}
    Line(const Point &a, const Point &b) {
         A = a.y - b.y; B = b.x - a.x; C = a.det(b);
    }
    void getLine() {
         A = nextDouble(); B = nextDouble(); C = nextDouble();
    }
    bool isPar(const Line &t)const {
        return !sgn2(det(A, B, t.A, t.B));
    }
    bool isSame(const Line &t)const {
        return isPar(t) && !sgn2(det(B, C, t.B, t.C));
    }
    LD dis(const Point &t)const {
       return fabs(A * t.x + B * t.y + C) / Point(A, B).mo();
    }
    Line move(LD d) {
        return Line(A, B, C - d * Point(A, B).mo());
    }
    Point projPoint(const Point &t)const {
          return intersect(Line(B, -A, A * t.y - B * t.x));
    }
    Point intersect(const Line &t)const {
          LD d = det(A, B, t.A, t.B);
          LD dx = det(t.C, t.B, C, B), dy = det(C, A, t.C, t.A);
          return Point(dx / d, dy / d);
    }
};

struct Vec {
    Point a, b; int lab; LD ang;
    Vec() {}
    Vec(const Point &_a, const Point _b): a(_a), b(_b) {}
    Vec(const Line &t) {
        if (!sgn1(t.A)) {a = Point(0, -t.C / t.B); b = Point(1, -t.C / t.B);}
        else if (!sgn1(t.B)) {a = Point(-t.C / t.A, 0); b = Point(-t.C / t.A, 1);}
        else {a = Point(0, -t.C / t.B); b = Point(1, (- t.C - t.A) / t.B);}
        if (sgn2((b - a).det(Point(t.A, t.B))) < 0) swap(a, b);        
    }
    void getVec() {
         a.getPoint(); b.getPoint();
    }
    bool hasPoint(const Point &t)const {
         return !sgn2((b - a).det(t - a)) && sgn2((b - t).dot(a - t)) <= 0;
    }
    Line midVertical()const {
         return Line(a.x - b.x, a.y - b.y, (b.mo2() - a.mo2()) / 2);
    }
    bool isPar(const Vec &t)const {
         return Line(a, b).isPar(Line(t.a, t.b));
    }
    LD det(const Vec &t)const {
       return (b - a).det(t.b - t.a);
    }
    Point intersect(const Vec &t)const {
          return Line(a, b).intersect(Line(t.a, t.b));
    }
};

struct Circle {
    Point o; LD r; int lab; LD ang;
    Circle() {}
    Circle(Point _o, LD _r): o(_o), r(_r) {}
    void getCircle() {
         o.getPoint(); r = nextDouble();
    }
    LD area()const {return pi * sq(r);}
    bool in(const Circle &t)const {
         return sgn1(r + o.dis(t.o) - t.r) == -1;
    }
    bool inOn(const Circle &t)const {
         return sgn1(r + o.dis(t.o) - t.r) == 0;
    }
    bool to(const Circle &t)const {
         return sgn1(r + t.r - o.dis(t.o)) == -1;
    }
    bool toOn(const Circle &t)const {
         return sgn1(r + t.r - o.dis(t.o)) == 0;
    }
    bool inter(const Circle &t)const {
         LD d = o.dis(t.o);
         return sgn1(d - r - t.r) <= 0 && sgn1(d - fabs(r - t.r)) >= 0;
    }
    int intersect(const Line &t, Point* Pts)const {
        LD d = t.dis(o); if (sgn1(d - r) == 1) return 0;
        Point p = t.projPoint(o); LD v = sqrt(fabs(sq(r) - sq(d)));
        LD m = Point(t.A, t.B).mo(); Point u = Point(- t.B / m, t.A / m) * v;
        Pts[0] = p + u; Pts[1] = p - u;
        if (sgn1(d - r) == 0) return 1; else return 2;
    }
    Line intersect(const Circle &t)const {
        LD px = t.o.x + o.x, mx = t.o.x - o.x, py = t.o.y + o.y, my = t.o.y - o.y;
        return Line(2 * mx, 2 * my, sq(t.r) - sq(r) - px * mx - py * my);
    }
    int intersect(const Circle &t, Point* Pts)const {
        LD px = t.o.x + o.x, mx = t.o.x - o.x, py = t.o.y + o.y, my = t.o.y - o.y;
        if (!sgn1(mx) && !sgn1(my)) {Pts[0] = o; return 1;}
        return intersect(Line(2 * mx, 2 * my, sq(t.r) - sq(r) - px * mx - py * my), Pts);
    }
    LD interArea(const Circle &t)const {
       if (to(t) || toOn(t)) return 0; 
       if (in(t) || inOn(t)) return area(); if (t.in(*this) || t.inOn(*this)) return t.area();
       LD a1 = 2 * Acos((sq(r) + o.dis2(t.o) - sq(t.r)) / (2 * r * o.dis(t.o)));
       LD a2 = 2 * Acos((sq(t.r) + o.dis2(t.o) - sq(r)) / (2 * t.r * o.dis(t.o)));
       return fabs(sq(r) * (a1 - sin(a1)) / 2 + sq(t.r) * (a2 - sin(a2)) / 2);
    }
    LD interArea(const Point &t1, const Point &t2)const {
       if (t1 == t2) return 0;
       Point tmp[4]; int top = 0; tmp[top++] = t1; 
       int tot = intersect(Line(t1, t2), tmp + 1); 
       for (int i = 1; i <= tot; ++i)
           if (Vec(t1, t2).hasPoint(tmp[i])) tmp[top++] = tmp[i];
       tmp[top++] = t2; LD res = 0;
       if (tot == 2 && sgn2((tmp[1] - tmp[0]).det(tmp[1] - tmp[2])) == 1) swap(tmp[1], tmp[2]);
       for (int i = 0; i + 1 < top; ++i) {
           if (sgn1(tmp[i].dis(o) - r) == 1 || sgn1(tmp[i + 1].dis(o) - r) == 1) 
              res += (tmp[i] - o).getAng(tmp[i + 1] - o) * r * r;
           else res += (tmp[i] - o).det(tmp[i + 1] - o);
       } return 0.5 * res;
    }
    LD interArea(Point* pts, int N)const {
       pts[N] = pts[0]; LD res = 0;
       for (int i = 0; i < N; ++i) 
           res += interArea(pts[i], pts[i + 1]);
       return fabs(res);
    }
};

/*********************************************************************/

LD area(Point* pts, int N) {
   LD res = 0; pts[N] = pts[0];
   for (int i = 0; i < N; ++i) 
       res += pts[i].det(pts[i + 1]);
   return fabs(res / 2);
}

LD perimeter(Point* pts, int N) {
   LD res = 0; pts[N] = pts[0];
   for (int i = 0; i < N; ++i) 
       res += pts[i].dis(pts[i + 1]);
   return fabs(res);
}

Point gravityCentre(Point* pts, int N) {
      pts[N] = pts[0]; Point p(0, 0); LD sum = 0, t;
      for (int i = 0; i < N; ++i) {
          p = p + (pts[i] + pts[i + 1]) * (t = pts[i].det(pts[i + 1]));
          sum += t;
      }
      return p / (sum * 3);
}

Point circumCentre(const Point &a, const Point &b, const Point &c) {
      return Vec(a, b).midVertical().intersect(Vec(b, c).midVertical());
}

Point orthoCentre(const Point &a, const Point &b, const Point &c) {
      Point O = circumCentre(a, b, c);
      return Point(a.x + b.x + c.x - O.x * 2, a.y + b.y + c.y - O.y * 2);
}

Point inCentre(const Point &a, const Point &b, const Point &c) {
      LD ta = b.dis(c), tb = a.dis(c), tc = a.dis(b);
      return Point((a * ta + b * tb + c * tc) / (ta + tb + tc));
}

int pointInPoly(const Point &p, Point* pts, int N) {
    pts[N] = pts[0]; LD k = log(acos(-1.0)); Point cp; int res = 0;
    for (int i = 0; i < N; ++i) {
        if (Vec(pts[i], pts[i + 1]).hasPoint(p)) return 2;
        cp = Line(p, p + Point(1, k)).intersect(Line(pts[i], pts[i + 1]));
        if (Vec(pts[i], pts[i + 1]).hasPoint(cp) 
           && sgn1((cp - p).y) > 0) res ^= 1;
    } return res;
}       

bool segParInPoly(const Vec &seg, Point* pts, int N, Point* stk) {
     if (pointInPoly(seg.a, pts, N) == 1 || pointInPoly(seg.b, pts, N) == 1)
        return true;
     if (seg.a == seg.b) return false;
     int top = 0; pts[N] = pts[0]; Point p; Line l1 = Line(seg.a, seg.b), l2;
     for (int i = 0; i < N; ++i) {
         if (!l1.isPar(l2 = Line(pts[i], pts[i + 1]))) {
            p = l1.intersect(l2);
            if (seg.hasPoint(p) && Vec(pts[i], pts[i + 1]).hasPoint(p))
               stk[top++] = p;     
         }
     }
     sort(stk, stk + top);
     for (int i = 0; i + 1 < top; ++i) {
         if (pointInPoly((stk[i] + stk[i + 1]) / 2, pts, N) == 1)
            return true;
     } return false;
}

LD lineCutPoly(const Line &ln, Point* pts, Point* stk, int N) {
    int top = 0; Point cp;
    pts[N] = pts[0]; Vec v(ln);
    for (int i = 0; i < N; ++i) {
        if (sgn2((v.b - v.a).det(pts[i] - v.a)) > 0)
            stk[top++] = pts[i];
        if (pts[i] == pts[i + 1] || Line(pts[i], pts[i + 1]).isPar(ln)) continue;
        cp = Line(pts[i], pts[i + 1]).intersect(ln);
        if (Vec(pts[i], pts[i + 1]).hasPoint(cp))
            stk[top++] = cp;
    }
    return area(stk, top);
}

int Graham_Anticlock(Point* pts, int N, Point* stk) {
    sort(pts, pts + N); N = unique(pts, pts + N) - pts;
    if (N == 1) {stk[0] = pts[0]; return 1;}
    int top = 0;
    for (int i = 0; i < N; ++i) {
        while (top >= 2 && sgn2((stk[top - 1] - stk[top - 2]).det(pts[i] - stk[top - 1])) <= 0) top--;
        stk[top++] = pts[i];
    } int base = top - 1;
    for (int i = N - 2; i >= 0; --i) {
        while (top - base >= 2 && sgn2((stk[top - 1] - stk[top - 2]).det(pts[i] - stk[top - 1])) <= 0) top--;
        stk[top++] = pts[i];
    } return top - 1;
}

LD rotatingCalipers(Point* pts, int N) {
   pts[N] = pts[0]; int j = 1; LD res = pts[0].dis(pts[1]);
   for (int i = 0; i < N; ++i) {
       while ((pts[i + 1] - pts[i]).det(pts[j + 1] - pts[i]) > (pts[i + 1] - pts[i]).det(pts[j] - pts[i])) 
             j = (j + 1) % N;
       res = max(res, max(pts[i].dis(pts[j]), pts[i + 1].dis(pts[j])));
   } return res;
}

LD farthestPair(Point* pts, int N, Point* stk) {
   N = Graham_Anticlock(pts, N, stk);
   if (N == 1) return 0;
   else return rotatingCalipers(stk, N);
}

bool cmpx(const Point &a, const Point &b) {
     return a.x < b.x;
}

bool cmpy(const Point &a, const Point &b) {
     return a.y < b.y;
}

LD dcCP(Point* pts, int l, int r, Point* tmp) {
   if (l == r) return 1e50;
   if (l + 1 == r) return pts[l].dis(pts[r]);
   int mid = (l + r) >> 1;
   LD res = min(dcCP(pts, l, mid, tmp), dcCP(pts, mid + 1, r, tmp));
   int top = 0;
   for (int i = l; i <= r; ++i)
       if (sgn1(fabs(pts[i].x - pts[mid].x) - res) == -1) tmp[top++] = pts[i];
   sort(tmp, tmp + top, cmpy);
   for (int i = 0; i < top; ++i)
       for (int j = i + 1; j < top; ++j) 
           if (sgn1(fabs(tmp[i].y - tmp[j].y) - res) >= 0) break;
           else res = min(res, tmp[i].dis(tmp[j]));
   return res;
}

LD closestPair(Point* pts, int N, Point* tmp) {
   sort(pts, pts + N, cmpx);
   return dcCP(pts, 0, N - 1, tmp);
}

bool cmpRange(const Vec &v1, const Vec &v2) {
     if (sgn2(v1.ang - v2.ang) == 0) 
        return sgn2((v2.b - v2.a).det(v1.b - v2.a)) >= 0;
     else return v1.ang < v2.ang;
}

bool judgeIn(const Vec &v, const Vec &t1, const Vec &t2) {
     Point cp = t1.intersect(t2);
     return sgn2(v.det(Vec(v.a, cp))) < 0;
}

int getKernel(Vec* seg, int N, Vec* deq, Point* pts, LD xa, LD ya, LD xb, LD yb) {
    int tN = 0;
    for (int i = 0; i < N; ++i) if (!(seg[i].a == seg[i].b)) seg[tN++] = seg[i];
    N = tN;
    seg[N++] = Vec(Point(xa, ya), Point(xb, ya));
    seg[N++] = Vec(Point(xb, ya), Point(xb, yb));
    seg[N++] = Vec(Point(xb, yb), Point(xa, yb));
    seg[N++] = Vec(Point(xa, yb), Point(xa, ya));    
    for (int i = 0; i < N; ++i) seg[i].ang = (seg[i].b - seg[i].a).getAng();
    sort(seg, seg + N, cmpRange);
    tN = 1; 
    for (int i = 1; i < N; ++i) if (sgn2(seg[i].ang - seg[i - 1].ang)) seg[tN++] = seg[i];
    N = tN; int bot = 0, top = 0;
    for (int i = 0; i < N; ++i) {
        while (top - bot >= 2 && judgeIn(seg[i], deq[top - 1], deq[top - 2])) top--;
        while (top - bot >= 2 && judgeIn(seg[i], deq[bot], deq[bot + 1])) bot++;
        if (top - bot == 1 && sgn2(deq[bot].det(seg[i])) <= 0) return 0;
        deq[top++] = seg[i];
        while (top - bot >= 3 && judgeIn(deq[bot], deq[top - 1], deq[top - 2])) top--;
        while (top - bot >= 3 && judgeIn(deq[top - 1], deq[bot], deq[bot + 1])) bot++;
    }
    deq[top] = deq[bot]; int num = 0;
    for (int i = bot; i < top; ++i) pts[num++] = deq[i].intersect(deq[i + 1]);
    return num;
}

/***********************************************************************/

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    return 0;

}
