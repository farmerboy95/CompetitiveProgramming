/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Compress the values
        - Now we create one treap for each value, the key would be the index in the array.
        - When proceeding a query (x, y), first we remove the index x from the treap a[x], then
        insert index x to the treap y and update the array as well.
        - Counting is also easy because it's based on size of subtree in treap y.
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

    void remove(pnode &t, int key) {
        if (!t) return;
        if (key == t->key) merge(t, t->l, t->r);
        else remove(key < t->key ? t->l : t->r, key);
        recalc(t);
    }

    void remove(int pos) {
        return remove(root, pos);
    }

    int count(pnode &t, int key) {
        if (!t) return 0;
        if (key >= t->key) return 1 + size(t->l) + count(t->r, key);
        return count(t->l, key);
    }

    int count(int pos) {
        return count(root, pos);
    }
};

vector<int> b;
int a[MAXN], x[MAXN], y[MAXN];
OrdinaryTreap tr[MAXN * 2];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    FOR(i,1,n) {
        cin >> a[i];
        b.push_back(a[i]);
    }
    FOR(i,1,q) {
        cin >> x[i] >> y[i];
        b.push_back(y[i]);
    }
    sort(ALL(b));
    b.resize(unique(ALL(b)) - b.begin());
    FOR(i,1,n) a[i] = lower_bound(ALL(b), a[i]) - b.begin();
    FOR(i,1,q) y[i] = lower_bound(ALL(b), y[i]) - b.begin();

    FOR(i,1,n) tr[a[i]].insert(i);
    
    FOR(i,1,q) {
        int pos = x[i]+1;
        tr[a[pos]].remove(pos);
        a[pos] = y[i];
        tr[a[pos]].insert(pos);
        cout << tr[a[pos]].count(pos-1) << "\n";
    }
    return 0;
}
