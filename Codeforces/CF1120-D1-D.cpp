/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let dp[u][0] = min cost to cover all leaf nodes in subtree of u, dp[u][1] = min cost 
        to cover all but one leaf node
        - We can easily calculate dp[u][0] and dp[u][1] using dp on tree
        - Then we can get the result by reconstructing the tree
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

int n, c[MAXN], numLeaves[MAXN], numChild[MAXN], mark[MAXN][2];
vi a[MAXN];
ll dp[MAXN][2], sum0[MAXN];
// 0 = min cost to cover all leaf nodes
// 1 = min cost to cover all but one leaf node

void dfs(int u, int p) {
    sum0[u] = 0;
    numLeaves[u] = numChild[u] = 0;
    for (int v : a[u]) {
        if (v == p) continue;
        numChild[u]++;
        dfs(v, u);
        numLeaves[u] += numLeaves[v];
        sum0[u] += dp[v][0];
    }
    if (numChild[u] == 0) {
        dp[u][0] = c[u];
        dp[u][1] = 0;
        numLeaves[u] = 1;
        return;
    }
    dp[u][0] = sum0[u];
    dp[u][1] = (ll) INF * INF;
    for (int v : a[u]) {
        if (v == p) continue;
        ckmin(dp[u][0], sum0[u] - dp[v][0] + dp[v][1] + c[u]);
        ckmin(dp[u][1], sum0[u] - dp[v][0] + dp[v][1]);
    }
}

void getResult(int u, int p, int state, vi &res) {
    if (mark[u][state]) return;
    mark[u][state] = 1;

    if (numChild[u] == 0) {
        if (state == 0) res.push_back(u);
        return;
    }

    vi go1;

    if (state == 0) {
        if (dp[u][0] == sum0[u]) {
            go1.push_back(-1);
        }
    }

    bool hasU = false;
    for (int v : a[u]) {
        if (v == p) continue;
        if (state == 0) {
            ll cdd = sum0[u] - dp[v][0] + dp[v][1] + c[u];
            if (cdd == dp[u][0]) {
                hasU = true;
                go1.push_back(v);
            }
        } else {
            ll cdd = sum0[u] - dp[v][0] + dp[v][1];
            if (cdd == dp[u][1]) {
                go1.push_back(v);
            }
        }
    }

    if (hasU) {
        res.push_back(u);
    }

    FOR(i,0,SZ(go1)-1) {
        if (go1[i] != -1) {
            getResult(go1[i], u, 1, res);
        }
    }

    if (SZ(go1)) {
        if (go1[0] == -1 || SZ(go1) >= 2) {
            for (int v : a[u]) {
                if (v == p) continue;
                getResult(v, u, 0, res);
            }
        } else {
            for (int v : a[u]) {
                if (v == p) continue;
                if (v != go1[0]) {
                    getResult(v, u, 0, res);
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> c[i];
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    dfs(1, 0);

    vi res;
    getResult(1, 0, 0, res);

    cout << dp[1][0] << ' ' << SZ(res) << "\n";
    sort(ALL(res));
    TRAV(x, res) cout << x << ' ';
    return 0;
}
