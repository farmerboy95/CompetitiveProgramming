/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use treap with keys as the input values.
*/

#include <bits/stdc++.h>
#define FI first
#define SE second
#define EPS 1e-9
#define ALL(a) a.begin(),a.end()
#define SZ(a) int((a).size())
#define MS(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x

using namespace std;
using ll = long long;
using ld = double;
typedef pair<int, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct OrdinaryTreap {
    struct node {
        int key, prior, sz;
        node *l, *r;

        node(int _key = 0) {
            key = _key;
            prior = rnd();
            sz = 1;
            l = r = NULL;
        }
    };
    typedef node* pnode;
    pnode root;

    void clear() {
        root = NULL;
    }

    OrdinaryTreap() {
        clear();
    }

    int size(pnode it) {
        return it ? it->sz : 0;
    }

    void recalc(pnode it) {
        if (it) {
            it->sz = size(it->l) + size(it->r) + 1;
        }
    }

    void merge(pnode &t, pnode l, pnode r) {
        // largest key of tree l should be smaller than smallest key of tree r
        if (!l || !r) t = l ? l : r;
        else if (l->prior > r->prior) merge(l->r, l->r, r), t = l;
        else merge(r->l, l, r->l), t = r;
        recalc(t);
    }

    void split(pnode t, pnode &l, pnode &r, int key) {
        if (!t) {
            l = r = NULL;
            return;
        }
        // right tree has keys >= key
        // left tree has keys < key
        if (key <= t->key) split(t->l, l, t->l, key), r = t;
        else split(t->r, t->r, r, key), l = t;
        recalc(t);
    }

    void insert(pnode &t, pnode it) {
        if (!t) t = it;
        else if (it->prior > t->prior) split(t, it->l, it->r, it->key), t = it;
        else insert(it->key < t->key ? t->l : t->r, it);
        recalc(t);
    }

    void insert(int u) {
        pnode w = new node(u);
        insert(root, w);
    }

    bool search(pnode &t, int key) {
        if (!t) return false;
        bool co = false;
        if (key == t->key) co = true;
        else if (key < t->key) co |= search(t->l, key);
        else co |= search(t->r, key);
        recalc(t);
        return co;
    }

    bool search(int key) {
        return search(root, key);
    }

    void remove(pnode &t, int key) {
        if (!t) return;
        if (key == t->key) merge(t, t->l, t->r);
        else remove(key < t->key ? t->l : t->r, key);
        recalc(t);
    }

    void remove(int pos) {
        return remove(root, pos);
    }

    int findPos(pnode &t, int key) {
        if (!t) return -1;
        if (key == t->key) return 1 + size(t->l);
        else if (key > t->key) {
            int e = findPos(t->r, key);
            if (e != -1) return 1 + size(t->l) + e;
            return -1;
        }
        return findPos(t->l, key);
    }

    int findPos(int val) {
        return findPos(root, val);
    }

    int getVal(pnode &t, int pos) {
        if (!t) return -1;

        int e = size(t->l);
        if (e >= pos) return getVal(t->l, pos);

        pos -= e;
        if (pos == 1) return t->key;

        pos--;
        return getVal(t->r, pos);
    }

    int getVal(int pos) {
        if (size(root) < pos) return -1;
        return getVal(root, pos);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int u, v;
    OrdinaryTreap tr;
    while (cin >> u && u != -1) {
        cin >> v;
        if (u == 1) {
            if (!tr.search(v)) tr.insert(v);
        } else if (u == 2) {
            tr.remove(v);
        } else if (u == 3) {
            cout << tr.findPos(v) << "\n";
        } else {
            cout << tr.getVal(v) << "\n";
        }
    }
    return 0;
}
