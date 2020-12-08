/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Statement is confusing. The task is: for the i-th aphid with input (A[i], V[i]) after xor, 
        the first part of the ID is A[i], the second part of the ID is equal to sum(V[k] for k <= i 
        and A[k] <= A[i]).
        - The first value in the pair is our key. As we need to keep the keys distinct, we do like this:
            + If the key exists in our treap, just add the value to the node with key.
            + If not, insert new element into our treap.
        - Then do a simple tree traverse to get the result.
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
typedef pair<ll, ll> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct OrdinaryTreap {
    struct node {
        ll sum, key, val;
        int prior, sz;
        node *l, *r;

        node(ll _key = 0, ll _val = 0) {
            key = _key;
            val = sum = _val;
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

    void recalc(pnode it) {
        if (it) {
            it->sz = size(it->l) + size(it->r) + 1;
            it->sum = it->val + getSum(it->l) + getSum(it->r);
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

    bool search(pnode &t, ll key, ll add) {
        if (!t) return false;
        if (key == t->key) {
            t->val += add;
            recalc(t);
            return true;
        } else if (key < t->key) {
            if (search(t->l, key, add)) {
                recalc(t);
                return true;
            }
        } else {
            if (search(t->r, key, add)) {
                recalc(t);
                return true;
            }
        }
        return false;
    }

    void insert(pnode &t, pnode it) {
        if (!t) t = it;
        else if (it->prior > t->prior) split(t, it->l, it->r, it->key), t = it;
        else insert(it->key < t->key ? t->l : t->r, it);
        recalc(t);
    }

    void insert(ll u, ll v) {
        pnode w = new node(u, v);
        insert(root, w);
    }

    ll traverse(pnode t, ll u) {
        if (!t) return 0;
        if (u < t->key) return traverse(t->l, u);
        return getSum(t->l) + t->val + traverse(t->r, u);
    }
};

II solve(OrdinaryTreap &tr, ll u, ll v) {
    if (!tr.search(tr.root, u, v)) tr.insert(u, v);
    return II(u, tr.traverse(tr.root, u));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int q;
    ll sec = 0;
    OrdinaryTreap tr;
    cin >> q;
    while (q--) {
        ll u, v;
        cin >> u >> v;
        u ^= sec;
        v ^= sec;
        II res = solve(tr, u, v);
        cout << res.FI << ' ' << res.SE << "\n";
        sec = res.SE;
    }
    return 0;
}
