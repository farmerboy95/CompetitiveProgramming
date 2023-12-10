/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Create a graph with directed edges from i to a[i].
        - Each weakly connected component consists of two parts: a directed cycle 
        and directed trees rooted at distinct vertices in the cycle, directed towards 
        the root (also called reverse-oriented arborescences). This graph is also
        called a functional graph.
        - You will need to break each component into a cycle and a tree, then to check
        if v is reachable from u, we have several cases:
            + u and v not in the same component => -1
            + u and v in the cycle => simply check the path from u to v in the cycle
            + u in the cycle, v is not => -1, as we can't go from cycle to tree
            + v in the cycle, u is not => go from u to root of the tree, then go from
            root of the tree to v in the cycle
            + u and v in the tree
                + if root[u] != root[v] => -1
                + if depth[u] <= depth[v] => -1
                + let dist = depth[u] - depth[v], we try to find the ancestor of u that
                is dist levels above u, if it is v, we have the answer, otherwise -1
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

int n, q, a[MAXN], visited[MAXN], comp[MAXN], par[MAXN][20], root[MAXN], cyclePos[MAXN], d[MAXN];
vi cycles[MAXN];

void precompute() {
    FOR(i,1,n) {
        visited[i] = -1;
        cyclePos[i] = -1;
    }

    int numComp = 0;
    FOR(i,1,n) {
        if (visited[i] == -1) {
            int u = i;
            vi st;
            while (visited[u] == -1) {
                visited[u] = i;
                st.push_back(u);
                u = a[u];
            }
            st.push_back(u);
            if (visited[u] == i) {
                // cycle
                numComp++;
                cycles[numComp].clear();
                do {
                    root[st.back()] = st.back();
                    par[st.back()][0] = st.back();
                    comp[st.back()] = numComp;
                    cycles[numComp].push_back(st.back());
                    cyclePos[st.back()] = SZ(cycles[numComp]) - 1;
                    d[st.back()] = 0;
                    st.pop_back();
                } while (st.back() != u);
                while (SZ(st) > 1) {
                    int p = st.back(); st.pop_back();
                    int x = st.back();
                    comp[x] = numComp;
                    root[x] = u;
                    d[x] = d[p] + 1;
                    par[x][0] = p;
                }
            } else {
                // previously visited node u
                while (SZ(st) > 1) {
                    int p = st.back(); st.pop_back();
                    int x = st.back();
                    comp[x] = comp[u];
                    root[x] = root[u];
                    d[x] = d[p] + 1;
                    par[x][0] = p;
                }
            }
        }
    }

    FOR(i,1,19)
        FOR(j,1,n)
            par[j][i] = par[par[j][i-1]][i-1];
}

int getAnc(int u, int k) {
    FOR(i,0,19)
        if (k & (1<<i)) u = par[u][i];
    return u;
}

int solve(int u, int v) {
    if (comp[u] != comp[v]) return -1;
    if (u == v) return 0;
    if (cyclePos[u] != -1 && cyclePos[v] != -1) {
        int x = cyclePos[u], y = cyclePos[v];
        if (x == y) return 0;
        if (x > y) return x - y;
        return SZ(cycles[comp[u]]) - y + x;
    }
    if (cyclePos[u] != -1) {
        return -1;
    }
    if (cyclePos[v] != -1) {
        int U = root[u];
        int x = cyclePos[U], y = cyclePos[v];
        if (x == y) return d[u];
        if (x > y) return d[u] + x - y;
        return d[u] + SZ(cycles[comp[U]]) - y + x;
    }
    if (d[v] >= d[u]) return -1;
    int res = d[u] - d[v];
    if (getAnc(u, res) == v) return res;
    return -1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> q;
    FOR(i,1,n) cin >> a[i];
    precompute();
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << solve(u, v) << "\n";
    }
    return 0;
}
