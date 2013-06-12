#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<cctype>
#include<algorithm>

using namespace std;

const int oo = 0x7fffffff;
const int MaxNode = 100000 + 5;

struct Node {
    int key, size; Node* c[2];
    Node(): key(oo), size(0) {c[0] = c[1] = this;}
    Node(int _key, Node* _c0, Node* _c1): key(_key) {c[0] = _c0; c[1] = _c1;}
    Node* rz() {return size = c[0]->size + c[1]->size + 1, this;}
    void* operator new(size_t, void* p) {return p;}
}Tnull, *null = &Tnull, buf[MaxNode], *cbuf = buf;

struct splay {
    Node* root;
    splay() {root = (new(cbuf++)Node(*null))->rz();}
    void zig(bool d) {
         Node *t = root->c[d]; root->c[d] = null->c[d];
         null->c[d] = root; root = t;
    }
    void zigzig(bool d) {
         Node *t = root->c[d]->c[d]; root->c[d]->c[d] = null->c[d];
         null->c[d] = root->c[d]; root->c[d] = null->c[d]->c[!d];
         null->c[d]->c[!d] = root->rz(); root = t;
    }
    void finish(bool d) {
         Node *t = null->c[d], *p = root->c[!d];
         while (t != null) {
               t = null->c[d]->c[d]; null->c[d]->c[d] = p;
               p = null->c[d]->rz(); null->c[d] = t;
         } root->c[!d] = p;
    }
    void select(int k) {
         for (;;) {int t;
             bool d = (k > (t = root->c[0]->size));
             if (k == t) break; if (d) k -= (t + 1);
             bool dd = (k > (t = root->c[d]->c[0]->size));
             if (k == t) {zig(d); break;} if (dd) k -= (t + 1);
             d != dd? zig(d), zig(dd): zigzig(d);
         }finish(0); finish(1); root->rz();
    }
    void search(int x) {
         for (;;) {
             bool d = (x > root->key); 
             if (root->c[d] == null) break;
             bool dd = (x > root->c[d]->key); 
             if (root->c[d]->c[dd] == null) {zig(d); break;}
             d != dd? zig(d), zig(dd): zigzig(d);
         }finish(0); finish(1); root->rz(); 
         if (x > root->key) select(root->c[0]->size + 1);
    }
    void ins(int x) {
         Node* oldroot = root; root = new(cbuf++)Node(x, root->c[0], root);
         oldroot->c[0] = null; oldroot->rz(); root->rz();
    }
    void del() {
         Node* oldroot = root; root = root->c[1];
         select(0); root->c[0] = oldroot->c[0]; root->rz();
    }
}sp;

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    return 0;

}
