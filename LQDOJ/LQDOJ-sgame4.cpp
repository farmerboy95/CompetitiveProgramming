/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Heavy-Light Decomposition (HLD)
        - As the addition is on edge, not on node, we can ignore updating on the lca.
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

vector<int> a[MAXN];
int n, m, d[MAXN], f[MAXN], parent[MAXN][17], nChain, chainHead[MAXN], nBase, chainInd[MAXN], posInBase[MAXN], q[MAXN];

struct SegmentTreeLazy {
    public:
    int N;

    // 0-indexed
    SegmentTreeLazy(int n) {
        t.resize(4*n);
        lazy.resize(4*n);
        N = n;
        FOR(i,0,SZ(t)-1) {
            t[i] = 0;
            lazy[i] = 0;
        }
    }

    SegmentTreeLazy(vector<ll> &a) {
        t.resize(4*SZ(a));
        lazy.resize(4*SZ(a));
        N = SZ(a);
        build(1, 0, N-1, a);
        FOR(i,0,SZ(t)-1) lazy[i] = 0;
    }

    ll get(int k, int l, int r, int u, int v) {
        lazyUpdate(k, l, r);
        if (l > r || r < u || v < l) return 0;
        if (u <= l && r <= v) return t[k];
        int m = (l + r) >> 1;
        ll lef = get(k*2, l, m, u, v);
        ll rig = get(k*2+1, m+1, r, u, v);
        return merge(lef, rig);
    }

    void lazyUpdate(int k, int l, int r) {
        if (l > r) return;
        if (lazy[k] == 0) return;
        t[k] += lazy[k] * (r-l+1);
        if (l < r) {
            mergeLazy(lazy[k*2], lazy[k]);
            mergeLazy(lazy[k*2+1], lazy[k]);
        }
        lazy[k] = 0;
    }

    void update(int k, int l, int r, int u, int v, int val) {
        lazyUpdate(k, l, r);
        if (l > r || r < u || v < l) return;
        if (u <= l && r <= v) {
            lazy[k] = val;
            lazyUpdate(k, l, r);
            return;
        }
        int m = (l + r) >> 1;
        update(k*2, l, m, u, v, val);
        update(k*2+1, m+1, r, u, v, val);
        t[k] = merge(t[k*2], t[k*2+1]);
    }

    private:
    vector<ll> t;
    vector<ll> lazy;

    void build(int k, int l, int r, vector<ll> &a) {
        if (l > r) return;
        if (l == r) {
            t[k] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(k*2, l, m, a);
        build(k*2+1, m+1, r, a);
        t[k] = merge(t[k*2], t[k*2+1]);
    }

    ll merge(ll &a, ll &b) {
        return a+b;
    }

    void mergeLazy(ll &ol, ll &ne) {
        ol += ne;
    }
};

void dfs(int u, int p) {
    f[u] = 1;
    for (int v : a[u]) {
        if (v == p) continue;
        parent[v][0] = u;
        d[v] = d[u]+1;
        dfs(v, u);
        f[u] += f[v];
    }
}

int lca(int u, int v) {
    if (d[v] < d[u]) FORE(i,16,0) if (d[parent[u][i]] >= d[v]) u = parent[u][i];
    if (d[u] < d[v]) FORE(i,16,0) if (d[parent[v][i]] >= d[u]) v = parent[v][i];
    FORE(i,16,0) if (parent[u][i] != parent[v][i]) { u = parent[u][i]; v = parent[v][i]; }
    while (u != v) { u = parent[u][0]; v = parent[v][0]; }
    return u;
}

void hld(int u, int p) {
    if (chainHead[nChain] == 0) chainHead[nChain] = u;
    chainInd[u] = nChain;
    posInBase[u] = ++nBase;
    q[nBase] = u;
    int mVtx = -1;
    for (int v : a[u]) {
        if (v == p) continue;
        if (mVtx == -1 || f[mVtx] < f[v]) mVtx = v;
    }
    if (mVtx > -1) hld(mVtx, u);
    for (int v : a[u]) {
        if (v == p) continue;
        if (v != mVtx) {
            nChain++;
            hld(v, u);
        }
    }
}

ll gethld(SegmentTreeLazy &st, int u, int g) {
    int uchain = chainInd[u];
    int gchain = chainInd[g];
    ll res = 0;
    while (1) {
        if (uchain == gchain) {
            res += st.get(1,0,st.N-1,posInBase[g],posInBase[u]-1);
            break;
        }
        res += st.get(1,0,st.N-1,posInBase[chainHead[uchain]]-1,posInBase[u]-1);
        u = parent[chainHead[uchain]][0];
        uchain = chainInd[u];
    }
    return res;
}

void updatehld(SegmentTreeLazy &st, int u, int g, int val) {
    int uchain = chainInd[u];
    int gchain = chainInd[g];
    while (1) {
        if (uchain == gchain) {
            st.update(1,0,st.N-1,posInBase[g],posInBase[u]-1,val);
            break;
        }
        st.update(1,0,st.N-1,posInBase[chainHead[uchain]]-1,posInBase[u]-1,val);
        u = parent[chainHead[uchain]][0];
        uchain = chainInd[u];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    d[1] = 1;
    dfs(1, 0);
    FOR(j,1,16)
        FOR(i,1,n) parent[i][j] = parent[parent[i][j-1]][j-1];
    nChain = 1;
    MS(chainHead, 0);
    nBase = 0;
    hld(1, 0);

    SegmentTreeLazy st(n);
    while (m--) {
        char ch; int u, v;
        cin >> ch >> u >> v;
        int g = lca(u, v);
        if (ch == 'P') {
            updatehld(st, u, g, 1);
            updatehld(st, v, g, 1);
        } else {
            cout << gethld(st, u, g) + gethld(st, v, g) << "\n";
        }
    }
    return 0;
}
