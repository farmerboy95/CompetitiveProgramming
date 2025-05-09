/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - DP on tree
        - Let dp[u][v] is number of edges that need to be removed in the subtree of u to get a smaller
        subtree with v nodes rooted at u
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

const int MAXN = 410;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, k, dp[MAXN][MAXN], num[MAXN], tmp[MAXN];
vi trace[MAXN][MAXN];
pi par[MAXN];
vpi a[MAXN];

void dfs(int u, int p) {
    num[u] = 1;
    for (auto [v, idx] : a[u]) {
        if (v == p) continue;
        par[v] = {u, idx};
        dfs(v, u);
        num[u] += num[v];
    }
}

void dfs2(int u, int p) {
    dp[u][1] = 0;
    for (auto [v, idx] : a[u]) {
        if (v == p) continue;
        dfs2(v, u);
        trace[u][v].resize(num[u]+1);
        FOR(i,1,num[u]) {
            tmp[i] = -1;
            FOR(j,0,i) {
                if (dp[u][i-j] == -1 || dp[v][j] == -1) continue;
                if (tmp[i] == -1 || tmp[i] > dp[u][i-j] + dp[v][j]) {
                    tmp[i] = dp[u][i-j] + dp[v][j];
                    trace[u][v][i] = j;
                }
            }
        }
        FOR(i,1,num[u]) dp[u][i] = tmp[i];
    }
    if (u != 1) {
        dp[u][0] = 1;
    }
}

void getResult(vi &ans, int cur, int K) {
    if (K == 0) {
        ans.push_back(par[cur].SE);
        return;
    }
    FORE(i,SZ(a[cur])-1,0) {
        int v = a[cur][i].FI;
        if (v == par[cur].FI) continue;
        int j = trace[cur][v][K];
        getResult(ans, v, j);
        K -= j;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        a[u].push_back({v, i});
        a[v].push_back({u, i});
    }

    MS(dp, -1);
    // dp[u][v] = min number of edges to remove to make the subtree rooted at u have v vertices
    dfs(1, 0);

    dfs2(1, 0);

    int res = INF;
    int root = 0;
    FOR(i,1,n) {
        if (dp[i][k] != -1) {
            if (res > dp[i][k] + (i != 1)) {
                res = dp[i][k] + (i != 1);
                root = i;
            }
        }
    }
    vi ans;
    if (root != 1) {
        ans.push_back(par[root].SE);
    }

    getResult(ans, root, k);

    cout << res << "\n";
    TRAV(x, ans) {
        cout << x << " ";
    }
    return 0;
}
