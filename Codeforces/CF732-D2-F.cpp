/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Build a DFS tree, we can easily see that we only need to direct the bridges.
        For the rest of the edges, they are in strongly connected components, so we
        can direct them in the way that they are in the same one in the directed graph
        using DFS tree.
        - Then we squeeze those components into nodes in a new graph. Now the graph looks 
        like a tree.
        - We now have a tree, each node is a SCC in the real graph. How to know the answer?
        The answer is the largest SCC. We can build an answer that we direct all other nodes
        to that SCC.
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

const int MAXN = 400010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, level[MAXN], dp[MAXN], par[MAXN], cnt[MAXN], Max;
int res[MAXN], newIdx[MAXN], N;
vector<vi> a[MAXN], b[MAXN];
vpi edges;

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
            if (level[v] > level[u]) {
                // going down
                dp[u]--;
            } else {
                // going up
                dp[u]++;
                res[idx] = dir;
            }
        }
    }

    if (p != 0 && dp[u] == 0) {
        res[edgeIdx] = -1;
    }
}

void dfs2(int u, int group, int &cnt) {
    newIdx[u] = group;
    cnt++;
    TRAV(pa, a[u]) {
        int v = pa[0];
        int idx = pa[1];
        int dir = pa[2];
        if (res[idx] == -1) {
            continue;
        }
        if (!newIdx[v]) {
            dfs2(v, group, cnt);
        }
    }
}

void dfs3(int u, int p) {
    TRAV(pa, b[u]) {
        int v = pa[0];
        int idx = pa[1];
        int dir = pa[2];

        if (v == p) continue;

        res[idx] = 1-dir;
        dfs3(v, u);
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
        res[i] = -1;
    }

    FOR(i,1,n) {
        if (!level[i]) {
            level[i] = 1;
            dfs(i, 0, -1);
        }
    }

    int cmp = 0;
    FOR(i,1,n)
        if (!newIdx[i]) {
            N++;
            int cnt = 0;
            dfs2(i, N, cnt);
            if (cnt > Max) {
                Max = cnt;
                cmp = N;
            }
        }
    
    FOR(i,0,m-1) {
        int u = edges[i].FI, v = edges[i].SE, cs = i + 1;
        u = newIdx[u];
        v = newIdx[v];
        if (u != v) {
            b[u].push_back({v, cs, 1});
            b[v].push_back({u, cs, 0});
        }
    }

    dfs3(cmp, 0);

    cout << Max << "\n";
    FOR(i,1,m) {
        if (res[i] == 1) cout << edges[i-1].FI << ' ' << edges[i-1].SE << "\n";
        else cout << edges[i-1].SE << ' ' << edges[i-1].FI << "\n";
    }
    return 0;
}
