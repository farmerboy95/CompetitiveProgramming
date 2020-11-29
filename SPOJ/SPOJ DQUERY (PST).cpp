/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Idea is the same as BIT version but we use Persistent Segment Tree to query things
        online, version[i] = the segment tree of the right bound i.
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
const int MAXM = 1000010;
const int MAXK = 16;
const int MAXQ = 200010;

int n, q, a[MAXN], pos[MAXM];

struct Vertex {
    Vertex *l, *r;
    int sum;

    Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

struct PersistentSegmentTree {
    public:
    int N;
    vector <Vertex*> versions;

    PersistentSegmentTree(int n) {
        N = n;
        vector<int> a(N, 0);
        versions.push_back(build(0, N-1, a));
    }

    int get(Vertex* ve, int l, int r, int u, int v) {
        if (l > r || v < l || r < u) return 0;
        if (u <= l && r <= v) return ve->sum;
        int m = (l + r) >> 1;
        return get(ve->l, l, m, u, v) + get(ve->r, m+1, r, u, v);
    }

    Vertex* update(Vertex *ve, int l, int r, int u, int val) {
        if (l == r) return new Vertex(ve->sum + val);
        int m = (l + r) >> 1;
        if (u <= m) return new Vertex(update(ve->l, l, m, u, val), ve->r);
        return new Vertex(ve->l, update(ve->r, m+1, r, u, val));
    }

    private:
    Vertex* build(int l, int r, vector<int> &a) {
        if (l == r) return new Vertex(a[l]);
        int m = (l + r) >> 1;
        return new Vertex(build(l, m, a), build(m+1, r, a));
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    PersistentSegmentTree pst(n);
    FOR(i,1,n) {
        if (pos[a[i]] == 0) {
            pst.versions.push_back(pst.update(pst.versions.back(), 0, pst.N-1, i-1, 1));
        } else {
            Vertex* ve = pst.update(pst.versions.back(), 0, pst.N-1, pos[a[i]]-1, -1);
            pst.versions.push_back(pst.update(ve, 0, pst.N-1, i-1, 1));
        }
        pos[a[i]] = i;
    }
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << pst.get(pst.versions[r], 0, pst.N-1, l-1, r-1) << "\n";
    }
    return 0;
}
