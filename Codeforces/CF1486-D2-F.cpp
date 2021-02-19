/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We can easily see that the intersection of 2 paths should be LCA of one of the paths (in
        case there is one intersection).
        - We find LCA of each path and try to put paths in DFS order to the tree from the root.
        - There are 3 kinds of path: dot (u and v are the same), segment (u is ancestor of v or vice
        versa), 2-segment (LCA is neither u or v)
        - We maintain 2 segment trees using Heavy Light Decomposition (HLD). The first one (stNode)
        maintains the number of paths going through one node. The second one (stEdge) maintains the 
        number of paths going through one edge (it's basically the same as the first one, we just don't
        update the highest node in the path)
        - For each dot, the result is just the number of paths going through that dot.
        - For each segment, the result is the number of paths going through the LCA - the number of
        paths going through the edge (LCA, child of LCA)
        - For each 2-segment, the result is the number of paths going through the LCA - the number of
        paths going through the edge (LCA, child 1 of LCA) - the number of paths going through the 
        edge (LCA, child 2 of LCA) + the number of paths going through both childs (can be retrieved
        using a simple map)
        - Don't forget to update the segment trees after getting the answer of each path.
*/

#include <bits/stdc++.h>
#define FI first
#define SE second
#define ALL(a) a.begin(), a.end()
#define SZ(a) int((a).size())
#define MS(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define TRAV(x, a) for (auto &x : a)

using namespace std;
using ll = long long; using ld = double; 
using pi = pair<int, int>; using pl = pair<ll, ll>; using pd = pair<ld, ld>;
using cd = complex<ld>; using vcd = vector<cd>;

using vi = vector<int>; using vl = vector<ll>;
using vd = vector<ld>; using vs = vector<string>;
using vpi = vector<pi>; using vpl = vector<pl>; using vpd = vector<pd>; // vector<pair>

template<class T> using min_pq = priority_queue<T, vector<T>, greater<T> >;
template<class T> inline int ckmin(T& a, const T& val) { return val < a ? a = val, 1 : 0; }
template<class T> inline int ckmax(T& a, const T& val) { return a < val ? a = val, 1 : 0; }
template<class T> void remDup(vector<T>& v) { sort(ALL(v)); v.erase(unique(ALL(v)), end(v)); }

constexpr int pct(int x) { return __builtin_popcount(x); } // # of bits set
constexpr int bits(int x) { return x == 0 ? 0 : 31-__builtin_clz(x); } // floor(log2(x)) 
constexpr int p2(int x) { return 1<<x; }
constexpr int msk2(int x) { return p2(x)-1; }

ll ceilDiv(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); } // divide a by b rounded up
ll floorDiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); } // divide a by b rounded down
void setPrec(int x) { cout << fixed << setprecision(x); }

// TO_STRING
#define ts to_string
string ts(char c) { return string(1, c); }
string ts(const char* s) { return (string) s; }
string ts(string s) { return s; }
string ts(bool b) { return ts((int)b); }
template<class T> string ts(complex<T> c) { stringstream ss; ss << c; return ss.str(); }
template<class T> using V = vector<T>;
string ts(V<bool> v) {string res = "{"; FOR(i,0,SZ(v)-1) res += char('0'+v[i]); res += "}"; return res; }
template<size_t sz> string ts(bitset<sz> b) { string res = ""; FOR(i,0,SZ(b)-1) res += char('0'+b[i]); return res; }
template<class T, class U> string ts(pair<T,U> p);
template<class T> string ts(T v) { // containers with begin(), end()
    bool fst = 1; string res = "";
    for (const auto& x: v) { if (!fst) res += " "; fst = 0; res += ts(x); }
    return res;
}
template<class T, class U> string ts(pair<T,U> p) { return "("+ts(p.FI)+", "+ts(p.SE)+")"; }

// OUTPUT
template<class T> void pr(T x) { cout << ts(x); }
template<class T, class ...U> void pr(const T& t, const U&... u) { pr(t); pr(u...); }
void ps() { pr("\n"); } // print w/ spaces
template<class T, class ...U> void ps(const T& t, const U&... u) { pr(t); if (sizeof...(u)) pr(" "); ps(u...); }

// DEBUG
void DBG() { cerr << "]" << endl; }
template<class T, class ...U> void DBG(const T& t, const U&... u) { cerr << ts(t); if (sizeof...(u)) cerr << ", "; DBG(u...); }
#define dbg(...) cerr << "Line(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#define chk(...) if (!(__VA_ARGS__)) cerr << "Line(" << __LINE__ << ") -> function(" \
        << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\n", exit(0);

const ld PI = acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
const ld EPS = 1e-9;
const ll MODBASE = 1000000007LL;
const int INF = 0x3f3f3f3f;

const int MAXN = 300010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

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

int n, m;
vi a[MAXN];
int d[MAXN], f[MAXN], parent[MAXN][19], nChain, chainHead[MAXN], nBase, chainInd[MAXN], posInBase[MAXN], q[MAXN];

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
    if (d[v] < d[u]) FORE(i,18,0) if (d[parent[u][i]] >= d[v]) u = parent[u][i];
    if (d[u] < d[v]) FORE(i,18,0) if (d[parent[v][i]] >= d[u]) v = parent[v][i];
    FORE(i,18,0) if (parent[u][i] != parent[v][i]) { u = parent[u][i]; v = parent[v][i]; }
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
            res += st.get(1,0,st.N-1,posInBase[g]-1,posInBase[u]-1);
            break;
        }
        res += st.get(1,0,st.N-1,posInBase[chainHead[uchain]]-1,posInBase[u]-1);
        u = parent[chainHead[uchain]][0];
        uchain = chainInd[u];
    }
    return res;
}

void updatehld(SegmentTreeLazy &st, int u, int g, int val, int updateG) {
    int uchain = chainInd[u];
    int gchain = chainInd[g];
    while (1) {
        if (uchain == gchain) {
            st.update(1,0,st.N-1,posInBase[g]-updateG,posInBase[u]-1,val);
            break;
        }
        st.update(1,0,st.N-1,posInBase[chainHead[uchain]]-1,posInBase[u]-1,val);
        u = parent[chainHead[uchain]][0];
        uchain = chainInd[u];
    }
}

int lift(int u, int dist) {
    FORE(i,18,0)
        if (dist & (1<<i)) u = parent[u][i];
    return u;
}

ll res = 0;
vpi path[MAXN];

void dfs2(int u, int p, SegmentTreeLazy &stNode, SegmentTreeLazy &stEdge) {
    map<pi, int> ma;
    TRAV(x, path[u]) {
        int l = x.FI, r = x.SE;
        ll intersect = gethld(stNode, u, u);
        if (u == l && u == r) {
            res += intersect;
            updatehld(stNode, l, u, 1, 1);
        } else if (u == l || u == r) {
            if (u == l) swap(l, r);
            int range = d[l] - d[u] - 1;
            int L = lift(l, range);
            ll exc = gethld(stEdge, L, L);
            intersect -= exc;
            res += intersect;
            updatehld(stNode, l, u, 1, 1);
            updatehld(stEdge, l, u, 1, 0);
        } else {
            int rangeL = d[l] - d[u] - 1, rangeR = d[r] - d[u] - 1;
            int L = lift(l, rangeL), R = lift(r, rangeR);
            ll excL = gethld(stEdge, L, L), excR = gethld(stEdge, R, R);
            intersect -= excL + excR;
            if (L > R) swap(L, R);
            intersect += ma[{L, R}];
            ma[{L, R}]++;
            res += intersect;
            updatehld(stNode, l, u, 1, 1);
            updatehld(stNode, r, u, 1, 0);
            updatehld(stEdge, l, u, 1, 0);
            updatehld(stEdge, r, u, 1, 0);
        }
    }
    TRAV(v, a[u]) {
        if (v == p) continue;
        dfs2(v, u, stNode, stEdge);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    d[1] = 1;
    dfs(1, 0);
    FOR(j,1,18)
        FOR(i,1,n) parent[i][j] = parent[parent[i][j-1]][j-1];
    nChain = 1;
    MS(chainHead, 0);
    nBase = 0;
    hld(1, 0);
    cin >> m;
    SegmentTreeLazy stNode(n), stEdge(n);
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        int g = lca(u, v);
        path[g].push_back({u, v});
    }
    dfs2(1, 0, stNode, stEdge);
    cout << res;
    return 0;
}
