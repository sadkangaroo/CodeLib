#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<cctype>
#include<algorithm>
#include<complex>
#include<vector>
#include<queue>
#include<set>
#include<map>

using namespace std;

const int MaxN = 100 + 5, MaxM = 10000 + 5;

int N, M, a[MaxM], b[MaxM], tot, top;
int root[MaxN], l[MaxM], r[MaxM], dis[MaxM], fa[MaxN], stk[MaxN];
double c[MaxM], lazy[MaxM], x[MaxN], y[MaxN], ans;
bool g[MaxN][MaxN], vis[MaxN];

#define Mset(a, x) memset(a, x, sizeof(a));
#define sq(x) ((x) * (x))

inline void pd(int now) {
    c[l[now]] += lazy[now]; c[r[now]] += lazy[now];
    lazy[l[now]] += lazy[now]; lazy[r[now]] += lazy[now];
    lazy[now] = 0;
}

int grand(int x) {
    if (fa[x] != x) fa[x] = grand(fa[x]);
    return fa[x];
}

void merge(int &x, int &y) {
     if (c[x] > c[y]) swap(x, y);
     if (y) {
        pd(x); merge(r[x], y);
        if (dis[l[x]] < dis[r[x]]) swap(l[x], r[x]);
        dis[x] = dis[r[x] + 1];
     }
}

inline bool circle(int now) {
     Mset(vis, false); vis[1] = true;
     top = 0; int o = now;
     while (!vis[now]) {
           vis[now] = true;
           stk[top++] = now;
           now = grand(a[root[now]]);
     }
     return now == o;
}

void dfs(int now) {
     vis[now] = true; tot++;
     for (int i = 1; i <= N; ++i) 
         if (!vis[i] && g[now][i]) dfs(i);
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    while (scanf("%d%d", &N, &M) != -1) {
          Mset(g, false); Mset(root, 0); Mset(dis, 0); dis[0] = -1;
          Mset(l, 0); Mset(r, 0); for (int i = 0; i <= M; ++i) lazy[i] = 0;
          for (int i = 1; i <= N; ++i) scanf("%lf%lf", x + i, y + i);
          c[0] = 1e50;
          for (int i = 1; i <= M; ++i) {
              scanf("%d%d", a + i, b + i);
              if (a[i] == b[i]) {M--; i--; continue;}
              c[i] = sqrt(sq(x[a[i]] - x[b[i]]) + sq(y[a[i]] - y[b[i]]));
              g[a[i]][b[i]] = true;
              int j = i; merge(root[b[i]], j);
          }
          Mset(vis, false); tot = 0; dfs(1);
          if (tot != N) puts("poor snoopy");
          else {
               ans = 0;
               for (int i = 1; i <= N; ++i) fa[i] = i;
               for (int i = 2; i <= N; ++i) if (fa[i] == i)
                   while (circle(i)) {
                         for (int j = 0; j < top; ++j) {
                             int e = root[stk[j]]; lazy[e] -= c[e];
                             ans += c[e]; fa[stk[j]] = i; pd(e);
                             merge(l[e], r[e]); root[stk[j]] = l[e];
                             if (stk[j] != i) merge(root[i], root[stk[j]]);
                         }
                   }
               for (int i = 2; i <= N; ++i) if (fa[i] == i) 
                   ans += c[root[i]];
               printf("%.2lf\n", ans + 1e-9);    
          }
    }

    return 0;

}
