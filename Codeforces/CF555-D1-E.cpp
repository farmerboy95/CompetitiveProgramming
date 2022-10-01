/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - I think this is the harder version of CEOI 17-Oneway, when this problem asks
        us to tell if there is a way to direct the edges.
        - Firstly we build DFS tree and keep only the bridges on the new tree (after we
        squeeze the connected components that do not contain any bridge), as the non-bridge
        edges are not really essential in directing (we will definitely have a way to direct
        them to make the component strongly connected)
        - Then we count the number of starting nodes in each subtree, the number of ending nodes
        in each subtree and the number of LCA nodes in each subtree.
        - Then for each edge in the new tree, let's denote it (u, v), v is the deeper node.
        We count the number of starting nodes in the subtree of v, denote it A, then the number
        of ending nodes in the subtree of v, denote it B, and the number of LCA nodes in the
        subtree of v, denote it C.
        - If A - C > 0, we know that the edge (u, v) should be directed upward, A - C == 0, the
        direction does not matter, A - C < 0, we know that the edge (u, v) should be directed
        downward.
        - Similarly, if B - C > 0, we know that the edge (u, v) should be directed downward, B - C == 0, the
        direction does not matter, B - C < 0, we know that the edge (u, v) should be directed
        upward.
        - So if exists an edge that A - C > 0 and B - C > 0, or A - C < 0 and B - C < 0, the 
        answer is No. Otherwise it's Yes.
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
string ts(bool b) { return (b ? "true" : "false"); }

template<class T> using V = vector<T>;
template<class T> string ts(complex<T> c);
string ts(V<bool> v);
template<size_t sz> string ts(bitset<sz> b);
template<class T> string ts(T v);
template<class T, class U> string ts(pair<T,U> p);
template<class ...U> string ts(tuple<U...> u);

template<class T> string ts(complex<T> c) { stringstream ss; ss << c; return ss.str(); }
string ts(V<bool> v) {string res = "{"; FOR(i,0,SZ(v)-1) res += char('0'+v[i]); res += "}"; return res; }
template<size_t sz> string ts(bitset<sz> b) { string res = ""; FOR(i,0,SZ(b)-1) res += char('0'+b[i]); return res; }
template<class T> string ts(T v) { // containers with begin(), end()
    bool fst = 1; string res = "";
    for (const auto& x: v) { if (!fst) res += " "; fst = 0; res += ts(x); }
    return res;
}
template<class T, class U> string ts(pair<T,U> p) { return "(" + ts(p.FI) + ", " + ts(p.SE) + ")"; }
template<size_t i, class T> string print_tuple_utils(const T& tup) { if constexpr(i == tuple_size<T>::value) return ")"; else return (i ? ", " : "(") + ts(get<i>(tup)) + print_tuple_utils<i + 1, T>(tup); }
template<class ...U> string ts(tuple<U...> u) { return print_tuple_utils<0, tuple<U...>>(u); }

// OUTPUT
template<class T> void pr(T x) { cout << ts(x); }
template<class T, class ...U> void pr(const T& t, const U&... u) { pr(t); pr(u...); }
void ps() { pr("\n"); } // print w/ spaces
template<class T, class ...U> void ps(const T& t, const U&... u) { pr(t); if (sizeof...(u)) pr(" "); ps(u...); }

// DEBUG
void DBG() { cerr << "]" << endl; }
template<class T, class ...U> void DBG(const T& t, const U&... u) { cerr << ts(t); if (sizeof...(u)) cerr << ", "; DBG(u...); }

#ifdef LOCAL_DEBUG
#define CONCAT(x, y) x##y
#define with_level setw(__db_level * 2) << setfill(' ') << "" << setw(0)
#define dbg(...) cerr << with_level << "Line(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#define chk(...) if (!(__VA_ARGS__)) cerr << setw(__db_level * 2) << setfill(' ') << "" << setw(0) << "Line(" << __LINE__ << ") -> function(" << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\n", exit(0);
#define db_block() debug_block CONCAT(dbbl, __LINE__)
int __db_level = 0;
struct debug_block {
    debug_block() { cerr << with_level << "{" << endl; ++__db_level; }
    ~debug_block() { --__db_level; cerr << with_level << "}" << endl; }
};
#else
#define dbg(...) 0
#define chk(...) 0
#define db_block() 0
#endif

const ld PI = acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
const ld EPS = 1e-9;
const ll MODBASE = 1000000007LL;
const int INF = 0x3f3f3f3f;

const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, dfsNum, low[MAXN], num[MAXN], numComp, grp[MAXN], par[MAXN][20], root[MAXN];
int d[MAXN], comp[MAXN], q, cntStart[MAXN], cntEnd[MAXN], cntLCA[MAXN], visited[MAXN];
vi b[MAXN];
stack<int> s;
vpi edges, edges2, a[MAXN];

void dfs(int u, int p, int eIdx) {
    low[u] = num[u] = ++dfsNum;
    s.push(u);
    TRAV(v, a[u]) {
        if (v.SE == eIdx) continue;
        if (num[v.FI] == 0) {
            dfs(v.FI, u, v.SE);
            ckmin(low[u], low[v.FI]);
        } else {
            ckmin(low[u], num[v.FI]);
        }
    }

    if (low[u] == num[u]) {
        int k = -1;
        numComp++;
        do {
            k = s.top();
            grp[k] = numComp;
            s.pop();
        } while (k != u);
    }
}

void dfs2(int u, int p, int numComp) {
    comp[u] = numComp;
    TRAV(v, b[u]) {
        if (v == p) continue;
        par[v][0] = u;
        d[v] = d[u] + 1;
        dfs2(v, u, numComp);
    }
}

void dfs3(int u, int p, int r) {
    visited[u] = 1;
    root[u] = r;
    TRAV(v, b[u]) {
        if (v == p) continue;
        dfs3(v, u, r);
        cntStart[u] += cntStart[v];
        cntEnd[u] += cntEnd[v];
        cntLCA[u] += cntLCA[v];
    }
}

int lca(int u, int v) {
    if (d[v] < d[u]) FORE(i,ceil(log2(n)),0) if (d[par[u][i]] >= d[v]) u = par[u][i];
    if (d[u] < d[v]) FORE(i,ceil(log2(n)),0) if (d[par[v][i]] >= d[u]) v = par[v][i];
    FORE(i,ceil(log2(n)),0) if (par[u][i] != par[v][i]) { u = par[u][i]; v = par[v][i]; }
    while (u != v) { u = par[u][0]; v = par[v][0]; }
    return u;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        a[u].push_back({v, i});
        a[v].push_back({u, i});
        edges.push_back({u, v});
    }

    FOR(i,1,n) num[i] = 0;
    FOR(i,1,n)
        if (!num[i]) dfs(i, 0, -1);

    TRAV(p, edges) {
        int u = grp[p.FI], v = grp[p.SE];
        if (u != v) {
            edges2.push_back({u, v});
            b[u].push_back(v);
            b[v].push_back(u);
        }
    }

    n = numComp;
    numComp = 0;
    FOR(i,1,n) {
        if (d[i] == 0) {
            par[i][0] = i;
            d[i] = 1;
            numComp++;
            dfs2(i, 0, numComp);
        }
    }

    FOR(i,1,ceil(log2(n))) {
        FOR(j,1,n) {
            par[j][i] = par[par[j][i-1]][i-1];
        }
    }

    while (q--) {
        int u, v;
        cin >> u >> v;
        
        u = grp[u]; v = grp[v];
        if (comp[u] != comp[v]) {
            cout << "No";
            return 0;
        }
        if (u == v) {
            continue;
        }
        cntStart[u]++;
        cntEnd[v]++;
        cntLCA[lca(u, v)]++;
    }
    
    FOR(i,1,n) {
        if (!visited[i]) {
            dfs3(i, 0, i);
        }
    }

    TRAV(p, edges2) {
        int u = p.FI, v = p.SE;
        if (d[u] > d[v]) swap(u, v);
        int numStart = cntStart[v], numEnd = cntEnd[v], numLCA = cntLCA[v];
        int goingUp = numStart - numLCA, goingDown = numEnd - numLCA;
        if (goingUp > 0 && goingDown > 0) {
            cout << "No";
            return 0;
        }
        if (goingUp < 0 && goingDown < 0) {
            cout << "No";
            return 0;
        }
    }

    cout << "Yes";
    return 0;
}