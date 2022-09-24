/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - It's very important to note that a solution always exists
        - Firstly we detect the brigdes. Then we have the strongly connected components.
        We can easily see that in SCCs, there are solutions to choose edge direction so
        that each node in the component can reach another node in the same component. So
        we mark those edges "B"
        - Then we squeeze those components into nodes in a new graph. Now the graph looks 
        like a tree.
        - So for the rest of the edges, how to know their direction? For each of the
        requirement, we increase the cnt of the source node and decrease the cnt of the
        destination node. As the solution always exists, the 2 nodes must be from the same
        tree. So when we consider one edge (u, v), we get sum of the cnt of the subtree of u
        and the rest of the tree. If the sum = 0, means the direction of the edge can be B,
        otherwise, we direct the edge to the component with negative sum.
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

const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, level[MAXN], dp[MAXN], par[MAXN], cnt[MAXN];
int res[MAXN], newIdx[MAXN], N;
vector<vi> a[MAXN], b[MAXN], edges2;
vpi edges;
bool visited[MAXN];

void dfs(int u, int p, int edgeIdx) {
    TRAV(pa, a[u]) {
        int v = pa[0];
        int idx = pa[1];
        int dir = pa[2];
        if (!level[v]) {
            level[v] = level[u] + 1;
            res[idx] = dir;
            dfs(v, u, idx);
            dp[u] += dp[v];
        } else {
            if (idx == edgeIdx) continue;
            res[idx] = 2;
            if (level[v] > level[u]) {
                // going down
                dp[u]--;
            } else {
                // going up
                dp[u]++;
            }
        }
    }

    if (p != 0 && dp[u] == 0) {
        res[edgeIdx] = -1;
    } else {
        res[edgeIdx] = 2;
    }
}

void dfs2(int u, int group) {
    newIdx[u] = group;
    TRAV(pa, a[u]) {
        int v = pa[0];
        int idx = pa[1];
        int dir = pa[2];
        if (res[idx] != 2) {
            continue;
        }
        if (!newIdx[v]) {
            dfs2(v, group);
        }
    }
}

void dfs3(int u, int h) {
    visited[u] = 1;
    TRAV(pa, b[u]) {
        int v = pa[0];
        int idx = pa[1];
        int dir = pa[2];
        if (!visited[v]) {
            par[v] = u;
            dfs3(v, h);
            cnt[u] += cnt[v];
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        a[u].push_back({v, i, 1});
        a[v].push_back({u, i, 0});
        edges.push_back({u, v});
        res[i] = ' ';
    }

    FOR(i,1,n) {
        if (!level[i]) {
            level[i] = 1;
            dfs(i, 0, -1);
        }
    }

    FOR(i,1,n)
        if (!newIdx[i]) {
            N++;
            dfs2(i, N);
        }
    
    FOR(i,0,m-1) {
        int u = edges[i].FI, v = edges[i].SE, cs = i + 1;
        u = newIdx[u];
        v = newIdx[v];
        if (u != v) {
            b[u].push_back({v, cs, 1});
            b[v].push_back({u, cs, 0});
            edges2.push_back({u, v, cs});
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        u = newIdx[u];
        v = newIdx[v];
        if (u != v) {
            cnt[u]++;
            cnt[v]--;
        }
    }

    FOR(i,1,N) {
        if (!visited[i]) {
            dfs3(i, i);
        }
    }

    FOR(i,0,SZ(edges2)-1) {
        int u = edges2[i][0], v = edges2[i][1], c = edges2[i][2];
        if (par[u] == v) {
            int l = cnt[u], r = -cnt[u];
            if (l < 0) {
                res[c] = 0;
            } else if (r < 0) {
                res[c] = 1;
            } else {
                res[c] = 2;
            }
        } else {
            int l = cnt[v], r = -cnt[v];
            if (l < 0) {
                res[c] = 1;
            } else if (r < 0) {
                res[c] = 0;
            } else {
                res[c] = 2;
            }
        }
    }

    FOR(i,1,m) {
        if (res[i] == 2) cout << 'B';
        else if (res[i] == 1) cout << 'R';
        else cout << 'L';
    }
    return 0;
}
