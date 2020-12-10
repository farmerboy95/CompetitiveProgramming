/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Create 10^4 treaps for all F, keys are the coordinate values.
        - First we sort all stations based on their coordinates, then iterate through them one
        by one.
        - At station i, we need to keep stations that can reach it, we can use a multiset
        to store (x+r, idx) to track the satisfied stations, otherwise, we can remove them, 
        as they cannot reach any of the next stations.
        - So now we have to find how many stations in the rest it can reach, we can iterate
        through treaps F-K -> F+K and find the number of nodes having keys larger than or equal
        to X-R, it's pretty easy with treaps.
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
const int MAXM = 10010;
const int MAXK = 16;
const int MAXQ = 200010;

struct Data {
    int x, r, f;
    Data(int _x = 0, int _r = 0, int _f = 0) : x(_x), r(_r), f(_f) {}
};

bool operator< (Data a, Data b) {
    return a.x < b.x;
}

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

    int get(int u) {
        pnode l, r;
        split(root, l, r, u);
        int res = size(r);
        merge(root, l, r);
        return res;
    }
};

OrdinaryTreap tr[MAXM];
int n, k;
vector<Data> a;
multiset<II> s;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,n) {
        int u, v, c;
        cin >> u >> v >> c;
        a.push_back(Data(u, v, c));
    }
    sort(ALL(a));
    ll res = 0;
    FOR(i,0,n-1) {
        while (SZ(s)) {
            auto it = s.begin();
            if (it->FI < a[i].x) {
                int idx = it->SE;
                s.erase(it);
                tr[a[idx].f].remove(a[idx].x);
            }
            else break;
        }

        int l = max(1, a[i].f-k), r = min(10000, a[i].f + k);
        int L = a[i].x - a[i].r;
        FOR(j,l,r) res += tr[j].get(L);

        tr[a[i].f].insert(a[i].x);
        s.insert(II(a[i].x + a[i].r, i));
    }
    cout << res;
    return 0;
}
