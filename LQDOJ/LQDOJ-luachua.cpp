/*
    Author: Nguyen Tan Bao
    Status: AC
    Statement: https://lqdoj.edu.vn/problem/luachua
    Idea:
        - Use DP as described in the code
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

const int MAXN = 500010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, f[MAXN], cnt[MAXN];
ll dp[MAXN][2];
vi a[MAXN];

void dfs(int u, int p) {
    cnt[u] = f[u];
    TRAV(v, a[u]) {
        if (v == p) continue;
        dfs(v, u);
        cnt[u] += cnt[v];
    }
    if (cnt[u] == 0) {
        // only dp[u][0] exists
        dp[u][0] = 0;
    } else if (f[u]) {
        // only dp[u][1] exists
        dp[u][1] = 0;
        TRAV(v, a[u]) {
            if (v == p) continue;
            dp[u][1] += dp[v][0];
        }
        dp[u][1] = min(dp[u][1], (ll) INF);
    } else {
        // dp[u][0]
        // separate at node u
        ll tong = 1;
        TRAV(v, a[u]) {
            if (v == p) continue;
            tong += min(dp[v][0], dp[v][1]);
        }
        ckmin(dp[u][0], tong);

        // not separate at node u
        tong = 0;
        TRAV(v, a[u]) {
            if (v == p) continue;
            tong += dp[v][0];
        }
        ckmin(dp[u][0], tong);

        // dp[u][1]
        TRAV(v, a[u]) {
            if (v == p) continue;
            ckmin(dp[u][1], tong - dp[v][0] + dp[v][1]);
        }
    }
}

void dfs2(int u, int p) {
    TRAV(v, a[u]) {
        if (v == p) continue;
        dfs2(v, u);
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
    FOR(i,1,m) {
        int x;
        cin >> x;
        f[x] = 1;
    }

    FOR(i,1,n) FOR(j,0,1) dp[i][j] = INF;

    // dp[i][j] = the minimum nodes to be deleted to make the all the dotted nodes separated,
    // j = 0: there is no dotted nodes in the component containing i
    // j = 1: there is one dotted nodes in the component containing i
    dfs(1, 0);

    // FOR(i,1,n) dbg(dp[i][0], dp[i][1]);

    int res = min(dp[1][0], dp[1][1]);
    if (res == INF) res = -1;
    cout << res;
    return 0;
}
