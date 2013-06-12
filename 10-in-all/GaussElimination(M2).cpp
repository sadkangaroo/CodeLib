#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<cctype>
#include<algorithm>

using namespace std;

const int MaxN = 100 + 5;

int N;
int a[MaxN][MaxN];

int Gauss() {
    int i, j, k, p;
    for (i = 0, j = 0; i < N, j < N; ++i, ++j) {
        for (k = i; k < N; ++k) if (a[k][j]) break;
        if (k == N) {i--; continue;}
        for (p = 0; p <= N; ++p) swap(a[i][p], a[k][p]);
        for (k = i + 1; k < N; ++k) if (a[k][j])
            for (p = 0; p <= N; ++p) a[k][p] ^= a[i][p];
    }
    for (k = i; k < N; ++k) if (a[k][N]) return -1;
    return 1 << (N - i);
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    return 0;

}
