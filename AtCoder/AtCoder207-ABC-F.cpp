/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - dp[i][j][k] = number of ways to cover j nodes in the subtree of j, in which
            + k = 0: having taka at node u
            + k = 1: not having taka at node u and u is not covered
            + k = 2: not having taka at node u and u is covered
        - The DP above naively requires O(N^2) computations when merging the DPs of 
        subtrees. Since we need to merge them N−1 times, the total computations are 
        O(N^3), which does not fit in the time limit. However, for the DP of a 
        subtree with X vertices, we can ignore j such that X<j. Therefore, we can 
        reduce to at most O(XY) the time required to merge the subtree with X vertices 
        and the subtree with Y subtrees.
        - At a glance it may just seem improving the constant factor, but actually the 
        total computation complexity of N−1 merges has essentially been improved; 
        specifically, it is O(N^2).
        - For example, the following precise analysis on complexity is possible:
            + Prepare an undirected graph G of N vertices and 0 edges, where Vertex 
            i on the tree corresponds to the Vertex i in G.
            + When merging a subtree A of X vertices and a subtree B of Y vertices, 
            add an undirected edge from every vertex in A to every vertex in B. The 
            number of edges added is O(XY), the computational cost required to merge.
            + After all merges complete, G is a complete graph with O(N^2) number of 
            edges, which is equal to the total sum of computational complexity required 
            for all merge in the DP on tree described above.
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

const int MAXN = 2010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, num[MAXN];
vi a[MAXN];

// 0 = having taka at node u
// 1 = not having taka at node u and u is not covered
// 2 = not having taka at node u and u is covered
ll dp[2][MAXN][MAXN][3];

void dfs(int u, int p) {
    num[u] = 1;
    int cur = 0;
    dp[cur][u][1][0] = 1;
    dp[cur][u][0][1] = 1;
    
    for (int v : a[u]) {
        if (v == p) continue;
        dfs(v, u);
        int nex = 1 - cur;
        FOR(i,0,num[u]) {
            FOR(k,0,2) {
                if (dp[cur][u][i][k] == 0) continue;
                FOR(j,0,num[v]) {
                    FOR(p,0,2) {
                        // 0 0 -> i+j 0
                        // 0 1 -> i+j+1 0
                        // 0 2 -> i+j 0
                        // 1 0 -> i+j+1 2
                        // 1 1 -> i+j 1
                        // 1 2 -> i+j 1
                        // 2 0 -> i+j 2
                        // 2 1 -> i+j 2
                        // 2 2 -> i+j 2
                        int sum = i+j + ((k == 0 && p == 1) || (k == 1 && p == 0));
                        int state = k;
                        if (k == 1 && p == 0) state = 2;
                        dp[nex][u][sum][state] += dp[cur][u][i][k] * dp[0][v][j][p] % MODBASE;
                        dp[nex][u][sum][state] %= MODBASE;
                    }
                }
                dp[cur][u][i][k] = 0;
            }
        }
        cur = nex;
        num[u] += num[v];
    }

    if (cur) {
        FOR(i,0,num[u]) {
            FOR(j,0,2) {
                dp[1-cur][u][i][j] = dp[cur][u][i][j];
            }
        }
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

    FOR(i,0,n) {
        ll res = (dp[0][1][i][0] + dp[0][1][i][1] + dp[0][1][i][2]) % MODBASE;
        cout << res << "\n";
    }
    return 0;
}
