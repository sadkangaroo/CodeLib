#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<cctype>
#include<algorithm>

using namespace std;

const int MaxNode = 10000 + 5, MaxE = 100000 + 5;
const int oo = 0x7fffffff;

int S, T, Num;
int d[MaxNode], v[MaxNode];

struct etp {
    int t, c; etp *nxt, *p;
    etp() {}
    etp(int _t, int _c, etp* _nxt): t(_t), c(_c), nxt(_nxt) {}
    void* operator new(size_t, void* p) {return p;}
}*e[MaxNode], buf[MaxE], *cbuf = buf;

void Me(int a, int b, int cab, int cba) {
     e[a] = new(cbuf++)etp(b, cab, e[a]);
     e[b] = new(cbuf++)etp(a, cba, e[b]);
     (cbuf - 2)->p = cbuf-1; (cbuf - 1)->p = cbuf-2;
}

int aug(int now, int Max) {
    if (now == T) return Max;
    int Rest = Max, dmin = Num, dt;
    for (etp* u = e[now]; u; u = u->nxt) if (u->c) {
        if (Rest && d[u->t] + 1 == d[now]) {
           dt = aug(u->t, min(Rest, u->c));
           Rest -= dt; u->c -= dt; u->p->c += dt;
           if (d[S] >= Num) return Max - Rest;
        } if (u->c) dmin = min(d[u->t] + 1, dmin);
    }
    if (Max == Rest) if (!--v[d[now]]) d[S] = Num; else ++v[d[now] = dmin];
    return Max - Rest;
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    memset(e, 0, sizeof(e));

    memset(d, 0, sizeof(d)); memset(v, 0, sizeof(v)); v[0] = Num;
    int ans = 0; while (d[S] < Num) ans += aug(S, oo);

    return 0;

}
