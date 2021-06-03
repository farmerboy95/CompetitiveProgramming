/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/59625?#comment-433247
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

const int MAXN = 1000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

vector<vi> edges;
int n, m, k, d[MAXN], D[MAXN];
multiset<pi> dd[MAXN], DD[MAXN];
vpi a[MAXN];

int solveK5() {
    int res = INF;

    if (k == 1) {
        // k = 1, check if there is (1, n)
        FOR(i,0,SZ(a[1])-1)
            if (a[1][i].FI == n) return a[1][i].SE;
        return -1;
    }

    // d[i] = distance from 1 to i
    // D[i] = distance from n to i
    // since there is at most one edge (u, v), d[i] and D[i] are just one value
    FOR(i,1,n) d[i] = D[i] = -1;
    FOR(i,0,SZ(a[1])-1) d[a[1][i].FI] = a[1][i].SE;
    FOR(i,0,SZ(a[n])-1) D[a[n][i].FI] = a[n][i].SE;

    if (k == 2) {
        // k = 2, check all i and calculate 1 - i - n
        FOR(i,2,n-1)
            if (d[i] != -1 && D[i] != -1) res = min(res, d[i] + D[i]);
        if (res == INF) res = -1;
        return res;
    }

    if (k == 3) {
        // k = 3, check all edges (u, v) and calculate 1 - u - v - n
        // don't forget 1 - v - u - n
        FOR(i,0,SZ(edges)-1) {
            int u = edges[i][0], v = edges[i][1], c = edges[i][2];
            if (u == 1 || u == n || v == 1 || v == n) continue;
            if (d[u] != -1 && D[v] != -1) res = min(res, c + d[u] + D[v]);
            if (d[v] != -1 && D[u] != -1) res = min(res, c + d[v] + D[u]);
        }
        if (res == INF) res = -1;
        return res;
    }

    // dd[i] stores at most 3 smallest distances from 1 to i (1 -> x -> i)
    FOR(u,2,n-1)
        if (d[u] != -1) {
            FOR(j,0,SZ(a[u])-1) {
                int v = a[u][j].FI, c = a[u][j].SE;
                if (v == 1 || v == n) continue;
                dd[v].insert({d[u] + c, u});
                while (SZ(dd[v]) > 3) {
                    auto it = dd[v].end(); it--;
                    dd[v].erase(it);
                }
            }
        }
    
    // DD[i] stores at most 3 smallest distances from n to i (n -> x -> i)
    FOR(u,2,n-1)
        if (D[u] != -1) {
            FOR(j,0,SZ(a[u])-1) {
                int v = a[u][j].FI, c = a[u][j].SE;
                if (v == 1 || v == n) continue;
                DD[v].insert({D[u] + c, u});
                while (SZ(DD[v]) > 3) {
                    auto it = DD[v].end(); it--;
                    DD[v].erase(it);
                }
            }
        }
    
    if (k == 4) {
        // k = 4, consider all i, calculate 1 - x - i - y - n
        FOR(i,2,n-1) {
            FORALL(it, dd[i]) {
                FORALL(itt, DD[i]) {
                    if (it->SE != itt->SE) {
                        res = min(res, it->FI + itt->FI);
                    }
                }
            }
        }
        if (res == INF) res = -1;
        return res;
    }

    // k = 5, consider all (u, v), calculate 1 - x - u - v - y - n
    // don't forget the case 1 - x - u - v - y - n
    FOR(i,0,SZ(edges)-1) {
        int u = edges[i][0], v = edges[i][1], c = edges[i][2];
        if (u == 1 || u == n || v == 1 || v == n) continue;
        
        FORALL(it, dd[u]) {
            FORALL(itt, DD[v]) {
                if (it->SE != itt->SE && it->SE != v && itt->SE != u) {
                    res = min(res, it->FI + itt->FI + c);
                }
            }
        }

        FORALL(it, dd[v]) {
            FORALL(itt, DD[u]) {
                if (it->SE != itt->SE && it->SE != u && itt->SE != v) {
                    res = min(res, it->FI + itt->FI + c);
                }
            }
        }
    }

    if (res == INF) res = -1;
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    FOR(i,1,m) {
        int u, v, c;
        cin >> u >> v >> c;
        if (u > v) swap(u, v);
        a[u].push_back({v, c});
        a[v].push_back({u, c});
        edges.push_back({u, v, c});
    }
    if (k > m || k >= n) {
        cout << -1;
        return 0;
    }

    // we are left with K <= 5 only
    cout << solveK5();
    return 0;
}
