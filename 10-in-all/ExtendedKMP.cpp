#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<cctype>
#include<algorithm>

using namespace std;

const int MaxN = 100000, MaxM = 100000;

int Next[MaxM], Extend[MaxN];

void GetNext(char* s) {
     int k = 0, a = 1, j;
     while (s[k] == s[k + 1]) k++; Next[1] = k;
     for (k = 2; s[k]; ++k) {
         if (k + Next[k - a] < a + Next[a]) {Next[k] = Next[k - a]; continue;}
         j = max(a + Next[a] - k, 0);
         while (s[k + j] && s[k + j] == s[j]) j++;
         Next[k] = j; a = k;
     }
}

void GetExtend(char* s1, char* s2) {
     int k = 0, a = 0, j;
     while (s1[k] && s2[k] && s1[k] == s2[k]) k++; Extend[0] = k;
     for (k = 1; s1[k]; ++k) {
         if (k + Next[k - a] < a + Extend[a]) {Extend[k] = Next[k - a]; continue;}
         j = max(a + Extend[a] - k, 0);
         while (s1[k + j] && s2[j] && s1[k + j] == s2[j]) j++;
         Extend[k] = j; a = k;
     }
}

void ExtendedKMP(char* s1, char* s2) {GetNext(s2); GetExtend(s1, s2);}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    return 0;

}
