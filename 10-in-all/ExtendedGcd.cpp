#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<cctype>
#include<algorithm>

using namespace std;

int x, y;

int ExtendedGcd(int a, int b) {
    if (b == 0) {x = 1; y = 0; return a;}
    int d = ExtendedGcd(b, a % b);
    int t = x; x = y; y = t - a / b * y;
    return d;
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    return 0;

}
