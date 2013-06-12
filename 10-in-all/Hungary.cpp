#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<cctype>
#include<algorithm>

using namespace std;

const int MaxN = 1000 + 5, MaxM = 1000 + 5;

int N, M, Mx[MaxN], My[MaxM];
bool vis[MaxM], g[MaxN][MaxM];

bool find(int now) {
     for (int i = 1; i <= M; ++i) if (g[now][i] && !vis[i]) {
         vis[i] = true;
         if (My[i] == -1 || find(My[i])) {
            Mx[now] = i; My[i] = now;
            return true;
         }
     } return false;
}

int Hungary() {
    memset(Mx, -1, sizeof(Mx)); memset(My, -1, sizeof(My));
    int res = 0;
    for (int i = 1; i <= N; ++i) if (Mx[i] == -1) {
        memset(vis, false, sizeof(vis));
        if (find(i)) res++;
    } return res;
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    return 0;

}
