/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - It's like inserting an element to a position in an array.
        - Use implicit treap.
        - The value of node is the height of the person in the result.
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
struct Treap {
    struct node {
        int prior, val, sz;
        bool rev;
        node *l, *r;

        node(int _val = 0) {
            val = _val;
            prior = rnd();
            sz = 1;
            rev = 0;
            l = r = NULL;
        }
    };
    typedef node* pnode;
    pnode root;

    void clear() {
        root = NULL;
    }

    Treap() {
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

    void push(pnode it) {
        if (it && it->rev) {
            it->rev = 0;
            swap(it->l, it->r);
            if (it->l) it->l->rev ^= 1;
            if (it->r) it->r->rev ^= 1;
        }
    }

    void merge(pnode &t, pnode l, pnode r) {
        // largest key of tree l should be smaller than smallest key of tree r
        push(l);
        push(r);
        if (!l || !r) t = l ? l : r;
        else if (l->prior > r->prior) merge(l->r, l->r, r), t = l;
        else merge(r->l, l, r->l), t = r;
        recalc(t);
    }

    void split(pnode t, pnode &l, pnode &r, int key, int add = 0) {
        if (!t) {
            l = r = NULL;
            return;
        }
        push(t);
        int curKey = add + size(t->l);
        // right tree has keys >= key
        // left tree has keys < key
        if (key <= curKey) split (t->l, l, t->l, key, add), r = t;
        else split (t->r, t->r, r, key, add + 1 + size(t->l)), l = t;
        recalc(t);
    }

    // reverse all the values from qL to qR
    void reverse(int qL, int qR) {
        assert(0 <= qL && qL <= qR && qR < size(root));
        pnode l, r, mid;
 
        split(root, l, r, qL);
        split(r, mid, r, qR - qL + 1);
 
        mid->rev ^= 1;
        merge(r, mid, r);
        merge(root, l, r);
    }

    void output(pnode t) {
        if (!t) return;
        push(t);
        output(t->l);
        printf("%d ", t->val);
        output(t->r);
    }

    bool insert(int pos, int val) {
        if (!(0 <= pos && pos <= size(root))) return false;
        if (!root) {
            pnode to_add = new node(val);
            root = to_add;
            return true;
        }
 
        pnode l, r, mid;
        mid = new node(val);
 
        split(root, l, r, pos);
        merge(l, l, mid);
        merge(root, l, r);
        return true;
    }

    void cyclicShift(int qL, int qR) {
        assert(0 <= qL && qL <= qR && qR < size(root));
        pnode l, r, mid;
 
        split(root, l, r, qL);
        split(r, mid, r, qR - qL + 1);

        pnode wL, wR;
        split(mid, wL, wR, qR - qL);
 
        merge(l, l, wR);
        merge(l, l, wL);
        merge(root, l, r);
    }

    int getVal(pnode &t, int pos, int add = 0) {
        if (!t) return -1;
        push(t);
        int curKey = add + size(t->l);
        if (pos == curKey) return t->val;
        if (pos < curKey) return getVal(t->l, pos, add);
        return getVal(t->r, pos, add + 1 + size(t->l));
    }

    int getVal(int pos) {
        return getVal(root, pos);
    }
};

int n, q, m;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    vector<int> a(n);
    FOR(i,0,n-1) cin >> a[i];
    sort(ALL(a));
    Treap tr;
    FOR(i,0,n-1) {
        int x;
        cin >> x;
        tr.insert(x, i);
    }
    vector<int> res(n);
    FOR(i,0,n-1) {
        res[tr.getVal(i)] = a[i];
    }
    FOR(i,0,n-1) cout << res[i] << "\n";
    return 0;
}
