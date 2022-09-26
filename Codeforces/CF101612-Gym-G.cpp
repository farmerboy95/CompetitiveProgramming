/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Build a DFS tree. It's clear that the starting node can reach the ending node
        via span edges. This is because if one node is not ancestor of the other in DFS
        tree, there won't be any other path connecting 2 nodes satisfying the condition
        of the problem statement.
        - Let's get the starting node first. We consider the highest edge (closest to the
        root of DFS tree) which has 2 or more back edges passing through that edge. So
        the parent node (in the 2 nodes of the current edge) is the starting node.
        - What about the ending node? We find the above back edges, take 2. So the LCA of
        those 2 is the ending node.
        - Finally we build the path of the 3 solutions.
        - If you are not familiar with the dp in the code, please refer to this article:
        https://codeforces.com/blog/entry/68138 (Observation 3)
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

const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, level[MAXN], dp[MAXN], par[MAXN];
vi a[MAXN], span[MAXN];
vpi res;
int st, nextSt, en;

void dfs(int u, int p) {
    TRAV(v, a[u]) {
        if (v == p) continue;
        if (!level[v]) {
            // span edge
            level[v] = level[u] + 1;
            par[v] = u;
            span[u].push_back(v);
            dfs(v, u);
            dp[u] += dp[v];
        } else {
            // back edge
            if (level[v] > level[u]) {
                // going down
                dp[u]--;
            } else if (level[v] < level[u]) {
                // going up
                dp[u]++;
            }
        }
    }

    if (p != 0 && dp[u] >= 2) {
        st = p;
        nextSt = u;
    }
}

void dfs2(int u, int root) {
    TRAV(v, a[u]) {
        if (par[v] == u) continue;
        if (par[u] == v) continue;
        if (level[v] < level[u]) {
            if (level[v] <= level[root]) {
                if (SZ(res) >= 2) continue;
                res.push_back({u, v});
            }
        }
    }
    TRAV(v, span[u]) {
        dfs2(v, root);
    }
}

int getLCA(int u, int v, int root) {
    vi U;
    while (u != root) {
        U.push_back(u);
        u = par[u];
    }
    vi V;
    while (v != root) {
        V.push_back(v);
        v = par[v];
    }
    reverse(ALL(U));
    reverse(ALL(V));
    int kq = 0;
    FOR(i,0,min(SZ(U),SZ(V))-1) {
        if (U[i] == V[i]) {
            kq = U[i];
        }
    }
    return kq;
}

void printStraight(int st, int en) {
    vi kq;
    while (en != st) {
        kq.push_back(en);
        en = par[en];
    }
    kq.push_back(st);
    reverse(ALL(kq));

    cout << SZ(kq) << ' ';
    TRAV(x, kq) cout << x << ' ';
    cout << "\n";
}

void printCycle(int st, int top, int bot, int en) {
    vi kq;
    while (st != top) {
        kq.push_back(st);
        st = par[st];
    }
    kq.push_back(st);

    while (bot != en) {
        kq.push_back(bot);
        bot = par[bot];
    }
    kq.push_back(bot);

    cout << SZ(kq) << ' ';
    TRAV(x, kq) cout << x << ' ';
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("grand.in", "r", stdin);
    freopen("grand.out", "w", stdout);
    int te;
    cin >> te;
    while (te--) {
        cin >> n >> m;
        FOR(i,1,n) {
            a[i].clear();
            span[i].clear();
        }
        res.clear();
        FOR(i,1,m) {
            int u, v;
            cin >> u >> v;
            a[u].push_back(v);
            a[v].push_back(u);
        }

        FOR(i,1,n) {
            level[i] = 0;
            dp[i] = 0;
            par[i] = 0;
        }
        st = 0, nextSt = 0, en = 0;
        FOR(i,1,n) {
            if (!level[i]) {
                level[i] = 1;
                dfs(i, 0);
            }
        }

        if (st == 0) {
            cout << -1 << "\n";
            continue;
        }

        dfs2(nextSt, st);

        if (SZ(res) < 2) {
            cout << -1 << "\n";
            continue;
        }

        if (res[0].SE != st && res[1].SE != st) {
            cout << -1 << "\n";
            continue;
        }

        en = getLCA(res[0].FI, res[1].FI, st);
        
        cout << st << ' ' << en << "\n";
        printStraight(st, en);

        printCycle(st, res[0].SE, res[0].FI, en);
        printCycle(st, res[1].SE, res[1].FI, en);
    }
    return 0;
}
