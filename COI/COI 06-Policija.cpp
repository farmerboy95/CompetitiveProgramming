/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - It's easy to see that edge x-y in the first type of queries must be a bridge, 
        and node x in the second type of queries must be an articulation point. Before
        finding out how to solve each of the query type, we need to solve a small problem:
        How to know that u is an ancestor of v on the DFS tree? As we have a tree now, we
        can flatten it to an array so that one node occupies one segment on the array. So,
        u is an ancestor of v then segment of u covers segment of v.
        - Query type 1:
            + Assume y is x's child WLOG. We check if u and v are descendants of y on the
            DFS tree. If both of them are or are not, clearly they will be in the same
            connected component when cutting x-y edge, otherwise, they won't
        - Query type 2:
            + If both of the nodes are not descendants of x on the DFS tree, clearly they
            are in the same connected component when removing node x
            + If one of them (u) is descendant of x, if there is no backedge connecting 
            subtree which contain u passing the edge connecting x and parent[x], u and v
            are not in the same connected component. In other words, the subtree is one 
            factor that makes x an articulation point.
            + If both are descendants of x, firstly they are in the same connected component
            if they are in the same subtree. Otherwise, they are not in the same subtree when
            one of them is in the "factor" subtree
            + But how to check if a subtree is a factor? We know that if one of the child v
            has low[v] >= num[u] then u is an articulation point (subtree v is a factor subtree)
            So how can we get a child of x that we can go to the considering node. We can
            use binary lifting to find the kth ancestor of a node on a tree.
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

int n, m, bridgeCnt, arti[MAXN], dfsNum, low[MAXN], num[MAXN], par[MAXN][18], d[MAXN];
int segmentTreeN, l[MAXN], r[MAXN];
vi a[MAXN], b[MAXN];

int binaryLiftingToChildX(int v, int x) {
    int dist = d[v] - d[x] - 1;
    FORE(i,ceil(log2(n)),0) {
        if (dist & (1<<i)) {
            dist ^= (1<<i);
            v = par[v][i];
        }
    }
    return v;
}

int isAncestor(int u, int v) {
    // is U ancestor of V?
    return l[u] <= l[v] && r[v] <= r[u];
}

bool check1(int u, int v, int x, int y) {
    if (d[x] > d[y]) {
        swap(x, y);
    }
    if (low[y] <= num[x]) {
        return true;
    }

    // edge (x, y) should be on the tree
    bool res = false;
    int numInSubTree = isAncestor(y, u) + isAncestor(y, v);
    if (numInSubTree == 0 || numInSubTree == 2) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool check2(int u, int v, int x) {
    if (!arti[x]) {
        return true;
    }

    bool res = false;

    int numInSubTree = isAncestor(x, u) + isAncestor(x, v);
    if (numInSubTree == 0) {
        res = true;
    } else if (numInSubTree == 1) {
        if (isAncestor(x, u)) {
            swap(u, v);
        }
        int childX = binaryLiftingToChildX(v, x);
        if (low[childX] >= num[x]) {
            res = false;
        } else {
            res = true;
        }
    } else {
        int childXU = binaryLiftingToChildX(u, x);
        int childXV = binaryLiftingToChildX(v, x);
        if (childXU == childXV) {
            res = true;
        } else if (low[childXU] >= num[x] || low[childXV] >= num[x]) {
            res = false;
        } else {
            res = true;
        }
    }
    return res;
}

void dfs(int u, int p) {
    low[u] = num[u] = ++dfsNum;
    int span = 0;
    bool isAr = false;
    TRAV(v, a[u]) {
        if (v == p) continue;
        if (num[v] == 0) {
            span++;
            b[u].push_back(v);
            b[v].push_back(u);
            dfs(v, u);
            ckmin(low[u], low[v]);
            if (low[v] >= num[u]) {
                isAr = true;
            }
            if (low[v] > num[u]) {
                // is bridge
            }
        } else {
            ckmin(low[u], num[v]);
        }
    }
    if (isAr) {
        if (p == 0) {
            if (span > 1) arti[u] = 1;
        } else {
            arti[u] = 1;
        }
    }
}

void dfs2(int u, int p) {
    l[u] = segmentTreeN++;
    TRAV(v, b[u]) {
        if (v == p) continue;
        par[v][0] = u;
        d[v] = d[u] + 1;
        dfs2(v, u);
    }
    r[u] = segmentTreeN-1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> m;
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    dfsNum = 0;
    dfs(1, 0);

    par[1][0] = 1;
    d[1] = 0;
    segmentTreeN = 0;
    dfs2(1, 0);
    FOR(i,1,ceil(log2(n))) {
        FOR(j,1,n) {
            par[j][i] = par[par[j][i-1]][i-1];
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int ch, u, v, x, y;
        cin >> ch;
        int r = 0;
        if (ch == 1) {
            cin >> u >> v >> x >> y;
            r = check1(u, v, x, y);
        } else {
            cin >> u >> v >> x;
            r = check2(u, v, x);
        }
        if (r) cout << "yes\n";
        else cout << "no\n";
    }
    return 0;
}
