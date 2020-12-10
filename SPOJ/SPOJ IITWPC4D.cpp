/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use a treap.
        - We simply insert a node with value "idx" to the position "input value".
        - Then simply traverse the treap to get the result.
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

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct Treap {
    struct node {
        int prior, val, sz, Max;
        bool rev;
        node *l, *r;

        node(int _val = 0) {
            val = _val;
            prior = rnd();
            sz = 1;
            rev = 0;
            l = r = NULL;
            Max = 0;
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
            it->Max = it->val;
            if (it->l) it->Max = max(it->Max, it->l->Max);
            if (it->r) it->Max = max(it->Max, it->r->Max);
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

    int getMax(int qL, int qR) {
        assert(0 <= qL && qL <= qR && qR < size(root));
        pnode l, r, mid;
 
        split(root, l, r, qL);
        split(r, mid, r, qR - qL + 1);

        int res = mid->Max;
        merge(r, mid, r);
        merge(root, l, r);
        return res;
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

    void remove(pnode &t, int pos, int add = 0) {
        if (!t) return;
        push(t);
        int curKey = add + size(t->l);
        if (pos == curKey) merge(t, t->l, t->r);
        else if (pos < curKey) remove(t->l, pos, add);
        else remove(t->r, pos, add + 1 + size(t->l));
        recalc(t);
    }

    void remove(int pos) {
        assert(0 <= pos && pos < size(root));
        remove(root, pos);
    }

    void move(int qL, int qR, int qX) {
        assert(0 <= qL && qL <= qR && qR < size(root));
        int remain = size(root) - (qR - qL + 1);
        assert(0 <= qX && qX <= remain);

        pnode l, r, mid;
 
        split(root, l, r, qL);
        split(r, mid, r, qR - qL + 1);

        merge(l, l, r);
        split(l, l, r, qX);
        merge(l, l, mid);
        merge(root, l, r);
    }

    void traverse(pnode t, vector<int> &a, int add = 0) {
        if (!t) return;

        a[t->val] = add + size(t->l);

        traverse(t->l, a, add);
        traverse(t->r, a, add + size(t->l) + 1);
    }

    void solve(vector<int> &a) {
        traverse(root, a);
    }
};

int a[MAXN], n;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Test : " << o << "\n";

        Treap tr;
        cin >> n;
        FOR(i,1,n) cin >> a[i];

        bool co = true;
        FOR(i,1,n)
            if (!tr.insert(a[i], i)) {
                co = false;
                break;
            }
        
        if (!co) {
            cout << -1 << "\n";
            continue;
        }
        
        vector<int> res(n+1, 0);
        tr.solve(res);
        FOR(i,1,n) cout << n-res[i] << ' ';
        cout << "\n";
    }
    return 0;
}
