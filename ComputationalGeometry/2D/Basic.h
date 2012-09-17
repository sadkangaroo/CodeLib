#ifndef _Basic_H_
#define _Basic_H_

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-8;

double Sqr(double x) {
    return x * x;
}

double Sqrt(double x) {
    if (x < 0) return 0;
    return sqrt(x);
}

double Asin(double x) {
    if (x > 1) x = 1;
    if (x < -1) x = -1;
    return asin(x);
}
double Acos(double x) {
    if (x > 1) x = 1;
    if (x < -1) x = -1;
    return acos(x);
}

#endif
