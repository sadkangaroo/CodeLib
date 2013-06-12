#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<complex>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
#include<map>

using namespace std;

typedef pair<int, int> pii;

const int MaxN = 1000 + 5, MaxNode = MaxN * 2;
const int MaxE = MaxNode * MaxNode * 4;

int N, Stack[MaxNode], top, cnt, bl[MaxNode], d[MaxNode];
pii a[MaxN][2];
bool vis[MaxNode], ifcho[MaxNode];
vector<int> List[MaxNode];

#define lab(a, b) ((a) * 2 + (b))
#define Pair(a) (((a) | 1) * 2 - 1 - (a))

struct etp {
	int t; etp *nxt;
	etp() {}
	etp(int _t, etp* _nxt): t(_t), nxt(_nxt) {}
	void* operator new(size_t, void* p) {return p;}
}*e[MaxNode], *er[MaxNode], *ne[MaxNode], buf[MaxE], *cbuf = buf;

bool intersection(pii a, pii b) {return a.first < b.second && a.second > b.first;}

void Init() {
	scanf("%d", &N); int h1, m1, h2, m2, d;
	memset(e, 0, sizeof(e)); memset(er, 0, sizeof(er)); memset(ne, 0, sizeof(ne));
	for (int i = 0; i < N; ++i) {
		scanf("%d:%d %d:%d %d", &h1, &m1, &h2, &m2, &d);
		a[i][0] = pii(h1 * 60 + m1, h1 * 60 + m1 + d);
		a[i][1] = pii(h2 * 60 + m2 - d, h2 * 60 + m2);
	}
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) if (i != j) 
		for (int p = 0; p < 2; ++p) for (int q = 0; q < 2; ++q) 
			if (intersection(a[i][p], a[j][q])) {	
				int x = lab(i, p), y = lab(j, q ^ 1);
				e[x] = new(cbuf++)etp(y, e[x]);	
				er[y] = new(cbuf++)etp(x, er[y]);
			}
}

void dfs(int now) {
	vis[now] = true;
	for (etp* u = e[now]; u; u = u->nxt) if (!vis[u->t])
		dfs(u->t);
	Stack[top++] = now;
}

void rdfs(int now) {
	vis[now] = true; bl[now] = cnt;
	for (etp* u = er[now]; u; u = u->nxt) 
		if (!vis[u->t]) rdfs(u->t);
}

void SCC() {
	memset(vis, false, sizeof(vis)); top = cnt = 0;
	for (int i = 0; i < N * 2; ++i) if (!vis[i]) dfs(i);
	memset(vis, false, sizeof(vis));
	for (int i = N * 2 - 1; i >= 0; --i) if (!vis[Stack[i]]) {
		rdfs(Stack[i]);
		cnt++;
	}
}

bool JudgeLegal() {
	for (int i = 0; i < N; ++i) if (bl[lab(i, 0)] == bl[lab(i, 1)]) {
		puts("NO"); return false;	
	} return true;
}

void MakeRtopG() {
	for (int i = 0; i < N * 2; ++i) List[bl[i]].push_back(i);	
	memset(d, 0, sizeof(d));
	for (int i = 0; i < N * 2; ++i) 
		for (etp* u = er[i]; u; u = u->nxt) if (bl[i] != bl[u->t]) {
			int x = bl[i], y = bl[u->t];
			ne[x] = new(cbuf++)etp(y, ne[x]); d[y]++;		
		}
	top = 0;
	for (int i = 0; i < cnt; ++i)
		if (d[i] == 0) Stack[top++] = i;
}

void deldfs(int now) {
	vis[now] = true; 
	for (etp* u = er[now]; u; u = u->nxt) 
		if (!vis[u->t]) deldfs(u->t);
}

void Cut(int S) {
	for (int i = 0; i < List[S].size(); ++i) 
		if (!vis[List[S][i]]) deldfs(List[S][i]);
}

void Solve() {
	int Now; memset(ifcho, false, sizeof(ifcho));
	memset(vis, false, sizeof(vis));
	while (top) {
		Now = Stack[top - 1]; top--; if (vis[List[Now][0]]) continue;
		for (etp* u = ne[Now]; u; u = u->nxt) if (!vis[List[u->t][0]]) {
			d[u->t]--; if (d[u->t] == 0) Stack[top++] = u->t;
		}
		for (int i = 0; i < List[Now].size(); ++i) {
			int t = List[Now][i];
			ifcho[t] = true; Cut(bl[Pair(t)]);
		}	
	}
}

void Output() {
	puts("YES"); int x, y;
	for (int i = 0; i < N; ++i) {
		if (ifcho[lab(i, 0)]) x = a[i][0].first, y = a[i][0].second;
		else x = a[i][1].first, y = a[i][1].second;
		printf("%02d:%02d %02d:%02d\n", x / 60, x % 60, y / 60, y % 60);
	}
}

int main() {
	
	Init();
	SCC();
	if (JudgeLegal()) {
		MakeRtopG();
		Solve(); Output();
	}
	
	return 0;
	
}
