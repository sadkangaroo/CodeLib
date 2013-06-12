#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<cctype>
#include<algorithm>

using namespace std;

const int MaxLen = 100000 + 5, MaxKey = MaxLen;

int Len;
int SA[MaxLen], tmp[MaxLen], height[MaxLen];
int a[MaxLen * 2], rank[MaxLen * 2], tmp2[MaxLen * 2];
int hash[MaxKey];

void RadixSort(int* key) {
     memset(hash, 0, sizeof(hash));
     for (int i = 1; i <= Len; ++i) hash[key[i]]++;
     for (int i = 1; i < MaxKey; ++i) hash[i] += hash[i - 1];
     for (int i = Len; i >= 1; --i) SA[hash[key[tmp[i]]]--] = tmp[i];
}

void GetSA() {
     if (Len == 1) {SA[1] = rank[1] = 1; return;}
     for (int i = 1; i <= Len; ++i) tmp[i] = i;
     memcpy(rank, a, sizeof(rank)); RadixSort(rank);
     for (int k = 1; k < Len; k <<= 1) {
         RadixSort(rank + k); memcpy(tmp, SA, sizeof(tmp));
         RadixSort(rank); memcpy(tmp2, rank, sizeof(tmp2));
         for (int i = 1, p = 1; i <= Len; ++i) {
             rank[SA[i]] = p;
             if (tmp2[SA[i]] != tmp2[SA[i + 1]]
                || tmp2[SA[i] + k] != tmp2[SA[i + 1] + k]) p++;
         }
     }
}

void GetHeight() {
     int i, j, p = 0; height[1] = 0;
     for (i = 1; i <= Len; ++i) {
         if (p) p--; if (rank[i] == 1) continue;
         j = SA[rank[i] - 1];
         while (a[i + p] == a[j + p]) p++;
         height[rank[i]] = p;
     }
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    return 0;

}
