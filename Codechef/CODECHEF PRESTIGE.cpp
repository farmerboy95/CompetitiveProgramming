/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use treap to solve. 
        - Non-decreasing k helps us to divide the first deck to 2 parts, -1 part and +1 part.
        - As we are modifying val and sum at push, we need to push everytime we reach a node
        e.g. when we get sum or get size.
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
        int prior, val1, val2, sz;
        ll sum1, sum2;
        bool rev;
        node *l, *r;

        node(int _val1 = 0, int _val2 = 0) {
            val1 = _val1;
            val2 = _val2;
            sum1 = _val1;
            sum2 = _val2;
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
        push(it);
        return it ? it->sz : 0;
    }

    ll getSum1(pnode it) {
        push(it);
        return it ? it->sum1 : 0;
    }

    ll getSum2(pnode it) {
        push(it);
        return it ? it->sum2 : 0;
    }

    void recalc(pnode it) {
        if (it) {
            it->sz = size(it->l) + size(it->r) + 1;
            it->sum1 = getSum1(it->l) + getSum1(it->r) + it->val1;
            it->sum2 = getSum2(it->l) + getSum2(it->r) + it->val2;
        }
    }

    void push(pnode it) {
        if (it && it->rev) {
            it->rev = 0;
            swap(it->l, it->r);
            swap(it->val1, it->val2);
            swap(it->sum1, it->sum2);
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
        if (key <= curKey) split(t->l, l, t->l, key, add), r = t;
        else split(t->r, t->r, r, key, add + 1 + size(t->l)), l = t;
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
        printf("%d %d %lld %d\n", t->val1, t->val2, t->sum1, t->prior);
        output(t->r);
    }

    bool insert(int pos, int val1, int val2) {
        if (!(0 <= pos && pos <= size(root))) return false;
        if (!root) {
            pnode to_add = new node(val1, val2);
            root = to_add;
            return true;
        }
 
        pnode l, r, mid;
        mid = new node(val1, val2);
 
        split(root, l, r, pos);
        merge(l, l, mid);
        merge(root, l, r);
        return true;
    }

    ll solve(int qL, int qR, int qU, int qV, int x) {
        pnode l, r, mid;
 
        split(root, l, r, qL);
        split(r, mid, r, qR - qL + 1);

        pnode midL, midR;
        split(mid, midL, midR, x - qU + 1);

        ll res = getSum1(midR) - getSum1(midL);
        merge(r, midR, r);
        merge(r, midL, r);
        merge(root, l, r);
        return res;
    }
};

int n, q, a[MAXN], b[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> q;
    FOR(i,0,n-1) cin >> a[i];
    FOR(i,0,n-1) cin >> b[i];

    Treap tr;
    FOR(i,0,n-1) tr.insert(i, a[i], b[i]);

    int x = -1;
    while (q--) {
        int ch, u, v, l, r;
        cin >> ch;
        if (ch == 1) {
            cin >> l >> r;
            l--;
            r--;
            tr.reverse(l, r);
        } else if (ch == 2) {
            cin >> u;
            u--;
            x = u - x - 1;
        } else {
            cin >> u >> v >> l >> r;
            u--; v--; l--; r--;
            cout << tr.solve(u, v, l, r, x) << "\n";
        }
    }
    return 0;
}
