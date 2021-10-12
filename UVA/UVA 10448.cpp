/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - It's a tree
        - After finding the path from u to v, remove all edges once and then do Coin Change
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

const int MAXN = 55;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, dp[100010], par[MAXN];
vpi a[MAXN];

void dfs(int u, int p) {
    TRAV(x, a[u]) {
        int v = x.FI;
        int c = x.SE;
        if (v == p) continue;
        par[v] = u;
        dfs(v, u);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cin >> n >> m;
        FOR(i,1,n) {
            a[i].clear();
        }
        map<pi, int> ma;
        FOR(i,1,m) {
            int u, v, c;
            cin >> u >> v >> c;
            a[u].push_back({v, c});
            a[v].push_back({u, c});
            ma[{u, v}] = c;
            ma[{v, u}] = c;
        }

        dfs(1, 0);

        int q;
        cin >> q;
        while (q--) {
            int u, v, c;
            cin >> u >> v >> c;
            vi U, V;
            while (u != 0) {
                U.push_back(u);
                u = par[u];
            }
            while (v != 0) {
                V.push_back(v);
                v = par[v];
            }
            reverse(ALL(U));
            reverse(ALL(V));
            int pos = 0;
            FOR(i,0,min(SZ(U), SZ(V))-1)
                if (U[i] == V[i]) pos = i;
            
            vi path;
            FORE(i,SZ(U)-1,pos) path.push_back(U[i]);
            FOR(i,pos+1,SZ(V)-1) path.push_back(V[i]);
            vi val;
            FOR(i,1,SZ(path)-1) val.push_back(ma[{path[i], path[i-1]}]);

            if (SZ(val) == 0) {
                cout << "No\n";
                continue;
            }

            int res = SZ(val);

            FOR(i,0,SZ(val)-1) c -= val[i];
            if (c < 0) {
                cout << "No\n";
                continue;
            }
            val.pop_back();

            dbg(val, c);
            FOR(i,0,c) dp[i] = INF;
            dp[0] = 0;

            FOR(i,0,SZ(val)-1)
                FOR(j,0,c)
                    if (dp[j] < INF)
                        if (val[i] * 2 + j <= c) ckmin(dp[val[i] * 2 + j], dp[j] + 2);

            if (dp[c] == INF) cout << "No\n";
            else cout << "Yes " << res + dp[c] << "\n";
        }
        if (o < te) cout << "\n";
    }
    return 0;
}
