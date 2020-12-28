/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Range Queries and Copies
        - Use Persistent Segment Tree to manage versions of the tree and update the version
        number for each list.
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
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct Vertex {
    Vertex *l, *r;
    ll sum;

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

    ll get(Vertex* ve, int l, int r, int u, int v) {
        if (l > r || v < l || r < u) return 0;
        if (u <= l && r <= v) return ve->sum;
        int m = (l + r) >> 1;
        return get(ve->l, l, m, u, v) + get(ve->r, m+1, r, u, v);
    }

    Vertex* update(Vertex *ve, int l, int r, int u, int val) {
        if (l == r) return new Vertex(val);
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
    int n, m;
    cin >> n >> m;
    PersistentSegmentTree pst(n);
    FOR(i,0,n-1) {
        int x;
        cin >> x;
        pst.versions.push_back(pst.update(pst.versions.back(), 0, pst.N-1, i, x));
    }
    vector<int> w;
    w.push_back(SZ(pst.versions)-1);

    while (m--) {
        int ch, u, v, c;
        cin >> ch >> u;
        u--;
        if (ch == 1) {
            cin >> v >> c;
            v--;
            pst.versions.push_back(pst.update(pst.versions[w[u]], 0, pst.N-1, v, c));
            w[u] = SZ(pst.versions)-1;
        } else if (ch == 2) {
            cin >> v >> c;
            v--;
            c--;
            cout << pst.get(pst.versions[w[u]], 0, pst.N-1, v, c) << "\n";
        } else {
            w.push_back(w[u]);
        }
    }
    return 0;
}
