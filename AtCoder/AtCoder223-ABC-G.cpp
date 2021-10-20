/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let 1 be the root
        - Let dp[u][0/1] be the max matching in subtree of u, 0 when there is no chosen edge with
        u as endpoint, 1 when there is one edge with u as endpoint
        - Let dp2[u][0/1] be the max matching in the whole tree, excluding the subtree of u (still
        keep node u)
        - So the max matching when removing node i is dp[i][0] + dp2[i][0]
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

const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, par[MAXN], dp[MAXN][2], sdp[MAXN], dp2[MAXN][2];
pi dpPos[MAXN];
vi a[MAXN];

void dfs(int u, int p) {
    TRAV(v, a[u]) {
        if (v == p) continue;
        par[v] = u;
        dfs(v, u);
        dp[u][0] += max(dp[v][0], dp[v][1]);
    }
    TRAV(v, a[u]) {
        if (v == p) continue;
        // store the second best value of dp[u][1] in sdp[u], the chosen edge in dpPos[u] (best choice, second best choice)
        int g = 1 + dp[v][0] + dp[u][0] - max(dp[v][0], dp[v][1]);
        if (g >= dp[u][1]) {
            dpPos[u].SE = dpPos[u].FI;
            dpPos[u].FI = v;
            sdp[u] = dp[u][1];
            dp[u][1] = g;
        }
    }
}

void dfs2(int u, int p) {
    if (u == 1) {
        dp2[u][0] = dp2[u][1] = 0;
    } else {
        // when picking edge (u, p), do not choose any edge with pattern (p, x)
        dp2[u][1] = 1 + dp[p][0] - max(dp[u][0], dp[u][1]) + dp2[p][0];

        // when not picking edge (u, p), there are 2 cases
        // 1. pick edge (p, par[p]) or not
        dp2[u][0] = max(dp2[p][0], dp2[p][1]) + dp[p][0] - max(dp[u][0], dp[u][1]);

        // 2. pick edge (p, one of child of p not u)
        // this is the place the second best dp[p][1] is needed
        pi pairPos = dpPos[p];
        int cur = 0;
        if (pairPos.FI != u) {
            cur = dp[p][1] - max(dp[u][0], dp[u][1]);
        } else if (pairPos.SE != 0) {
            cur = sdp[p] - max(dp[u][0], dp[u][1]);
        }
        // remember to pick the parent part of p in this case
        cur += dp2[p][0];
        ckmax(dp2[u][0], cur);
    }

    TRAV(v, a[u]) {
        if (v == p) continue;
        dfs2(v, u);
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

    dfs(1, 0);
    int cur = max(dp[1][0], dp[1][1]);

    dfs2(1, 0);

    int res = 0;
    FOR(i,1,n) {
        int cnt = dp[i][0] + dp2[i][0];
        if (cnt == cur) res++;
    }
    cout << res;
    return 0;
}
