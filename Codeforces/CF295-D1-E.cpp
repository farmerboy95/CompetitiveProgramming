/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use treap to solve.
        - Each node contains key (coordinate of the point), sum (sum of keys of the tree),
        res (result of query 2 if using on the tree)
        - Recalculation of res = resL 
                               + resR
                               + sizeL * sumR - sizeR * sumL
                               + sizeL * key - sumL
                               + sumR - sizeR * key
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
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct OrdinaryTreap {
    struct node {
        ll sum, res;
        int key;
        int prior, sz;
        node *l, *r;

        node(int _key = 0) {
            key = _key;
            sum = _key;
            res = 0;
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

    ll getSum(pnode it) {
        return it ? it->sum : 0;
    }

    ll getRes(pnode it) {
        return it ? it->res : 0;
    }

    void recalc(pnode it) {
        if (it) {
            it->sz = size(it->l) + size(it->r) + 1;
            it->sum = it->key + getSum(it->l) + getSum(it->r);
            it->res = getRes(it->l) + getRes(it->r) + getSum(it->r) * size(it->l) - getSum(it->l) * size(it->r) + (ll) size(it->l) * it->key - getSum(it->l) + getSum(it->r) - (ll) size(it->r) * it->key;
        }
    }

    void merge(pnode &t, pnode l, pnode r) {
        // largest key of tree l should be smaller than smallest key of tree r
        if (!l || !r) t = l ? l : r;
        else if (l->prior > r->prior) merge(l->r, l->r, r), t = l;
        else merge(r->l, l, r->l), t = r;
        recalc(t);
    }

    void split(pnode t, pnode &l, pnode &r, ll key) {
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

    void remove(pnode &t, int key) {
        if (!t) return;
        if (key == t->key) merge(t, t->l, t->r);
        else remove(key < t->key ? t->l : t->r, key);
        recalc(t);
    }

    void remove(int pos) {
        return remove(root, pos);
    }

    ll query(int qL, int qR) {
        pnode l, r, mid;
 
        split(root, l, r, qL);
        split(r, mid, r, qR + 1);

        ll res = getRes(mid);
 
        merge(r, mid, r);
        merge(root, l, r);
        return res;
    }
};

int n, a[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    OrdinaryTreap tr;
    FOR(i,1,n) tr.insert(a[i]);

    int q;
    cin >> q;
    while (q--) {
        int ch, u, v;
        cin >> ch >> u >> v;
        if (ch == 1) {
            tr.remove(a[u]);
            a[u] += v;
            tr.insert(a[u]);
        } else {
            cout << tr.query(u, v) << "\n";
        }
    }
    return 0;
}
