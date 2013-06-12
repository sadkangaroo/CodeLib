#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<cctype>
#include<algorithm>
#include<queue>

using namespace std;

const int MaxNode = 10000 + 5, MaxE = 100000 + 5;
const int oo = 0x7fffffff;

int ans, d[MaxNode], pre[MaxNode], S, T, Num;
bool vis[MaxNode];
queue<int> Q;

struct etp {
    int t, c, v; etp *nxt, *p;
    etp() {}
    etp(int _t, int _c, int _v, etp* _nxt): t(_t), c(_c), v(_v), nxt(_nxt) {}
    void* operator new(size_t, void* p) {return p;}
}*e[MaxNode], buf[MaxE], *cbuf = buf, *r[MaxNode];

void Me(int a, int b, int cab, int cba, int vab, int vba) {
     e[a] = new(cbuf++)etp(b, cab, vab, e[a]);
     e[b] = new(cbuf++)etp(a, cba, vba, e[b]);
     (cbuf - 2)->p = cbuf-1; (cbuf - 1)->p = cbuf-2;
}

bool aug() {
     memset(vis, false, sizeof(vis)); vis[S] = true;
     for (int i = 0; i < Num; ++i) d[i] = oo; d[S] = 0;
     Q.push(S); int o, Max = oo, Cost = 0;
     while (!Q.empty()) {
           o = Q.front(); Q.pop(); vis[o] = false;
           for (etp* u = e[o]; u; u = u->nxt) 
               if (u->c && d[o] + u->v < d[u->t]) {
                  d[u->t] = d[o] + u->v; pre[u->t] = o; r[u->t] = u;
                  if (!vis[u->t]) {vis[u->t] = true; Q.push(u->t);}
               }
     }
     if (d[T] == oo) return false;
     for (int i = T; i != S; i = pre[i]) Max = min(Max, r[i]->c);
     for (int i = T; i != S; i = pre[i]) {
         Cost += r[i]->v; r[i]->c -= Max; r[i]->p->c += Max;
     } ans += Cost * Max; return true;
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    ans = 0; while (aug()) {}

    return 0;

}
