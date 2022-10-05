/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/102852
        - Same as CF19-D12-E
        - find the DFS tree of the graph and paint it in two colors;
        - if there is exactly one contradictory back-edge, add it to the 
        answer;
        - use dynamic programming to calculate, for each span-edge, how many 
        contradictory and how many non-contradictory back-edges pass over it;
        - if a span-edge has all contradictory and no non-contradictory edges 
        passing over it, add it to the answer.
        - If you are not familiar with the dp in the code, please refer to this article:
        https://codeforces.com/blog/entry/68138 (Observation 3)
        - The only difference between 2 problems is that you should include the contradictory
        edge in the vertex cover
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

const int MAXN = 1000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, dfsNum, num[MAXN], col[MAXN], dp[MAXN], dpC[MAXN], par[MAXN];
vi a[MAXN];
vpi edges;

void dfs(int u, int p) {
    num[u] = ++dfsNum;
    TRAV(v, a[u]) {
        if (v == p) continue;
        if (num[v] == 0) {
            par[v] = u;
            dfs(v, u);
            dp[u] += dp[v];
            dpC[u] += dpC[v];
        } else {
            if (num[v] > num[u]) {
                dp[u]--;
                if (col[v] == col[u]) {
                    dpC[u]--;
                }
            } else if (num[v] < num[u]) {
                dp[u]++;
                if (col[v] == col[u]) {
                    dpC[u]++;
                }
            }
        }
    }
}

void coloring(int u) {
    TRAV(v, a[u]) {
        if (!col[v]) {
            col[v] = -col[u];
            coloring(v);
        }
    }
}

void coloring2(int u, int p) {
    col[u] = -col[u];
    TRAV(v, a[u]) {
        if (v == p) continue;
        if (par[v] == u) {
            coloring2(v, u);
        }
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
            dp[i] = dpC[i] = 0;
        }
        edges.clear();
        FOR(i,1,m) {
            int u, v;
            cin >> u >> v;
            a[u].push_back(v);
            a[v].push_back(u);
            edges.push_back({u, v});
        }

        FOR(i,1,n) col[i] = 0;
        col[1] = 1;
        coloring(1);

        vi contradictEdges;
        FOR(i,1,m) {
            int u = edges[i-1].FI, v = edges[i-1].SE;
            if (col[u] == col[v]) {
                contradictEdges.push_back(i);
            }
        }

        if (SZ(contradictEdges) == 0) {
            cout << "YES\n";
            FOR(i,1,n) 
                if (col[i] == -1) cout << 0;
                else cout << 1;
            cout << "\n";
            continue;
        }

        if (SZ(contradictEdges) == 1) {
            cout << "YES\n";

            int u = edges[contradictEdges[0]-1].FI;
            if (col[u] == -1) {
                FOR(i,1,n) col[i] = -col[i];
            }

            FOR(i,1,n) 
                if (col[i] == -1) cout << 0;
                else cout << 1;
            cout << "\n";
            continue;
        }

        dfsNum = 0;
        FOR(i,1,n) num[i] = 0;
        dfs(1, 0);

        bool found = false;
        FOR(i,1,n) {
            if (par[i] > 0) {
                if (dp[i] == dpC[i] && dpC[i] == SZ(contradictEdges)) {
                    if (col[i] == 1) {
                        FOR(j,1,n) col[j] = -col[j];
                    }
                    coloring2(i, par[i]);
                    cout << "YES\n";
                    FOR(j,1,n) 
                        if (col[j] == -1) cout << 0;
                        else cout << 1;
                    cout << "\n";
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            cout << "NO\n";
        }
    }
    return 0;
}
