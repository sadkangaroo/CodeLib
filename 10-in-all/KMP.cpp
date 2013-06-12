#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<cctype>
#include<algorithm>

using namespace std;

const int MaxN = 100000 + 5, MaxM = 100000 + 5;

int N, M;
int a[MaxN], b[MaxM], Next[MaxM];

void GetNext() {
     Next[1] = 0;
     for (int i = 2; i <= M; ++i) {
         int t = Next[i - 1];
         while (t && b[t + 1] != b[i]) t = Next[t];
         if (b[t + 1] == b[i]) Next[i] = t + 1; else Next[i] = 0;
     }
}

void Match() {
     int j = 0;
     for (int i = 1; i <= N; ++i) {
         while (j && b[j + 1] != a[i]) j = Next[j];
         if (b[j + 1] == a[i]) j++;
         if (j == M) j = Next[j];
     }
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    return 0;

}
