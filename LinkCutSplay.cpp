#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<cctype>
#include<climits>
#include<algorithm>

using namespace std;

typedef long long LL;

const int MaxNode = 30000 + 5;

#define nonRoot(x) ((x)->fa->c[0] == (x) || (x)->fa->c[1] == (x))
#define nonNull(x) ((x)->c[0] != (x) && (x)->c[1] != (x))

void* stk[MaxNode];

struct Node {
    int key, sz, rev; Node *fa, *c[2];
    Node(): sz(0) {
        fa = c[0] = c[1] = this;
    }
    Node(int _key, Node* _fa, Node* _c0, Node* _c1): key(_key), rev(0) {
        fa = _fa; c[0] = _c0; c[1] = _c1;
    }
    void rz() {
        sz = c[0]->sz + c[1]->sz + 1;
        c[0]->fa = c[1]->fa = this;
    }
    void flip() {
        if (nonNull(this)) {
            swap(c[0], c[1]);
            rev ^= 1;
        }
    }
    void pd() {
        if (rev) {
            c[0]->flip(); c[1]->flip();
            rev = 0;
        }
    }
    void zig(bool d) {
        Node *x = fa, *y = x->fa;
        x->c[d] = c[!d]; x->rz();
        c[!d] = x; x->fa = this;
        if (y->c[0] == x) y->c[0] = this;
        else if (y->c[1] == x) y->c[1] = this;
        fa = y;
    }
    void splay() {
        int top = 0; stk[top++] = this;
        for (Node* v = this; nonRoot(v); v = v->fa) stk[top++] = v->fa;
        for (int i = top - 1; i >= 0; --i) ((Node*)stk[i])->pd();
        while (nonRoot(this)) {
            bool d = fa->c[1] == this;
            if (!nonRoot(fa)) {zig(d); break;}
            bool dd = fa->fa->c[1] == fa;
            d != dd? (zig(d), zig(dd)): (fa->zig(dd), zig(d));
        } rz();
    }
}Tnull, *null = &Tnull, buf[MaxNode], *cbuf;

struct Splay {
    Node *root;
    Splay(int x) {
       root = new(cbuf++)Node(x, null, null, null); 
       root->rz();
    }
    void select(int k) {
        Node* now = root;
        while (now->pd(), now->c[0]->sz != k) {
            if (now->c[0]->sz > k) now = now->c[0];
            else {k -= now->c[0]->sz + 1; now = now->c[1];}
        } now->splay(); root = now;
    }
    void search(int x) {
        Node* now = root;
        while (now->pd(), now->c[x > now->key] != null) {
            now = now->c[x > now->key];
        } now->splay();root = now;
        if (x > root->key) select(root->c[0]->sz + 1);
    }
    void ins(int x) {
        root->pd(); root = new(cbuf++)Node(x, null, root->c[0], root);
        root->c[1]->c[0] = null; root->c[1]->rz(); root->rz();
    }
    void del() {
        root->pd(); Node* oldroot = root;
        root = root->c[1]; root->fa = null; select(0);
        root->pd(); root->c[0] = oldroot->c[0]; root->rz();
    }
};

struct LinkCut {
    void access(Node* u) {
        for (Node* v = null; u != null; u = u->fa) {
            u->splay(); u->c[1] = v; (v = u)->rz();
        }
    }
    Node* getRoot(Node* u) {
        access(u); u->splay();
        while (u->c[0] != null) {
            u->pd(); u = u->c[0];
        } u->splay(); return u;
    }
    void setRoot(Node* u) {
        access(u); u->splay(); u->flip();
    }
    void join(Node* u, Node* v) {
        setRoot(u); 
        u->fa = v; access(u);
    }
    void cut(Node* u) {
        access(u); u->splay(); 
        u->c[0]->fa = null; u->c[0] = null; u->rz();
    }
    Node* LCA(Node* x, Node* y) {
        Node* res; access(x);
        for (Node *u = y, *v = null; u != null; u = u->fa) {
            if (u->splay(), u->fa == null) {v->fa = u; res = u;}   
            u->c[1] = v; (v = u)->rz();
        } return res;
    }
    void modify(Node* u, int x) {
        access(u); u->splay(); u->key = x; u->rz();        
    }
};

int main() {
    return 0;
}
