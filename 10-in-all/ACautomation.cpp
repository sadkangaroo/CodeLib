#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<cctype>
#include<algorithm>
#include<queue>

using namespace std;

const int MaxNode = 100000 + 5;

struct Node {
    int t; Node *f, *c[26];
    void* operator new(size_t, void* p) {return p;}
    Node* rz(Node* fa) {t = 0; f = fa; return memset(c, 0, sizeof(c)), this;}
}trie[MaxNode], *cbuf = trie, *root = (new(cbuf++)Node)->rz(NULL); 
queue<Node*> Q;

void Ins(Node* now, char* s) {
     for (int i = 0; s[i]; ++i) {
         if (now->c[s[i] - 'a']) now = now->c[s[i] - 'a'];
         else now = now->c[s[i] - 'a'] = (new(cbuf++)Node)->rz(now);
     } now->t++;
}

void GetNext() {
     Q.push(root); Node *u, *v;
     while (!Q.empty()) {
           u = Q.front(); Q.pop();
           for (int i = 0; i < 26; ++i) if (u->c[i]) {
               Q.push(u->c[i]); if (u == root) continue;
               v = u->f; while (v != root && !v->c[i]) v = v->f;
               if (v->c[i]) u->c[i]->f = v->c[i]; else u->c[i]->f = root;
           }
     }
}

int Match(Node* now, char* s) {
    int ret = 0; Node* d;
    for (int i = 0; s[i]; ++i) {
        while (now != root && !now->c[s[i] - 'a']) now = now->f;
        if (now->c[s[i] - 'a']) now = now->c[s[i] - 'a'];
        for (d = now; d != root && d->t != -1; d = d->f) 
            ret += d->t, d->t = -1;
    } return ret;
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    
    return 0;

}
