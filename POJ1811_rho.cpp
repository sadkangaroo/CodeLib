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

typedef long long LL;

const LL bases[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

inline LL mul(LL a, LL b, LL mo) {
	LL res = 0;
	while (b) {
		if (b & 1) {res += a; if (res < 0 || res >= mo) res -= mo;}
		a <<= 1; if (a < 0 || a >= mo) a -= mo;  b >>= 1;
	} return res;
}

inline LL power(LL a, LL b, LL mo) {
	a %= mo;
	LL res = 1;	
	while (b) {
		if (b & 1) res = mul(res, a, mo);
		a = mul(a, a, mo); b >>= 1;
	} return res;
}

inline bool SPRP(LL x, LL a) {
	LL d = x - 1;
	while (!(d & 1)) d >>= 1;
	LL t = power(a, d, x);
	while (d != x - 1) {
		if (t == x - 1) return true;
		if (t == 1) return (d & 1);
		t = mul(t, t, x); d <<= 1;
	} return false;
}

inline bool Miller(LL x) {
	if (x < 2) return false;
	if (x == 2 || x == 3 || x == 5 || x == 7) return true;
	if (!(x % 2) || !(x % 3) || !(x % 5) || !(x % 7)) return false;
	for (int i = 0; i < 7; ++i)  
		if (bases[i] % x && !SPRP(x, bases[i]))	return false;
	return true;
}

inline LL f(LL x, LL mo, LL t) {
	LL res = mul(x, x, mo) + t;
	if (res < 0 || res >= mo) res -= mo;
	return res;
}

int T;
LL ans;

inline LL Abs(LL x) {
	if (x < 0) return -x;
	return x;
}

inline LL gcd(LL a, LL b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

bool rho(LL x, LL t) {
	if (Miller(x)) {ans = min(ans, x); return true;}
	if (ans <= 100) {
		for (int i = 2; i < ans; ++i) if (x % i == 0) {ans = i; break;}
		return true;
	}
	if (x <= 10000) {
		for (int i = 2; i * i <= x; ++i) if (x % i == 0) {ans = i; break;}
		return true;
	}
	LL cnt = 2, y = 2, d = 1;
	while (d == 1) {
		cnt = f(cnt, x, t); y = f(f(y, x, t), x, t);
		d = gcd(Abs(cnt - y), x);
	}
	if (d == x) return false;
	else {
		rho(d, t); rho(x / d, t);
		return true;
	}
}

int main() {

	freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);

	cin >> T;
	while (T--) {
		cin >> ans;
		if (Miller(ans)) puts("Prime");
		else {
			int t = 1;
			while (!rho(ans, t++)) {};
			cout << ans << endl;
		}
	}
	
	return 0;

}

