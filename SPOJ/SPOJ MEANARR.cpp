/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We need to count the number of segments [l,r] that sum(a[i])_(i = l...r) / (r-l+1) >= k;
        => sum(a[i]) >= k * (r-l+1)
        => sum(a[i]) >= k + k + k + ... + k
        => sum(a[i] - k) >= 0
        - So we set A[i] = a[i] - k, then we have sum(A[i]) = prefixSum(r) - prefixSum(l-1) >= 0
        => prefixSum(r) >= prefixSum(l-1) (l <= r)
        - For each r, we need to count the number of l that satisfies the above condition. We can
        do it using treap, with key as the prefix sum.
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
        int prior, sz, num, sum;
        ll key;
        node *l, *r;

        node(ll _key = 0) {
            key = _key;
            num = sum = 1;
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

    int getSum(pnode it) {
        return it ? it->sum : 0;
    }

    void recalc(pnode it) {
        if (it) {
            it->sz = size(it->l) + size(it->r) + 1;
            it->sum = it->num + getSum(it->l) + getSum(it->r);
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

    bool tryToSearchAndAdd(pnode &t, ll key) {
        if (!t) return false;
        if (key == t->key) {
            t->num++;
            recalc(t);
            return true;
        } else if (key < t->key) {
            if (tryToSearchAndAdd(t->l, key)) {
                recalc(t);
                return true;
            }
        } else {
            if (tryToSearchAndAdd(t->r, key)) {
                recalc(t);
                return true;
            }
        }
        recalc(t);
        return false;
    }

    void insert(ll u) {
        if (tryToSearchAndAdd(root, u)) return;
        pnode w = new node(u);
        insert(root, w);
    }

    int get(pnode t, ll key) {
        if (!t) return 0;
        if (key < t->key) return get(t->l, key);
        else return getSum(t->l) + t->num + get(t->r, key);
    }

    int get(ll key) {
        return get(root, key);
    }
};

int n, k, a[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,n) {
        cin >> a[i];
        a[i] -= k;
    }
    OrdinaryTreap tr;
    tr.insert(0);
    ll res = 0;
    ll sum = 0;
    FOR(i,1,n) {
        sum += a[i];
        res += tr.get(sum);
        tr.insert(sum);
    }
    cout << res;
    return 0;
}
