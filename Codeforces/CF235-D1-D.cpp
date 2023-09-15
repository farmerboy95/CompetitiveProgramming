/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/5592
        - Let's consider a tree with n nodes.
        - Use Event(A,B) to denote the following event "when we select A as the 
        deleting point, B is connected to A". Clearly, if Event(A,B) happens, it would 
        add 1 to totalCost. So we can just simply calculate the probability of every 
        Event(A,B), and add them up, note that A can be the same as B.
        - So how to calculate the probability of Event(A,B)? Assume there are x nodes
        in the path from A to B, we claim that the probability is simply 1/x. We prove
        it using induction
            + Let's assume there is a connected sub-graph of tree containing both A and B
            if the sub-graph only has x vertices, then the event happens only if we select 
            vertex A, so the probability is 1/x.
            + Otherwise, assume it has n vertices, there are 2 cases: whether the selected 
            vertex is on the path between A and B or not, there are x vertices on the path
            from A to B.
                + First case: the probability of Event(A,B) happen is 1/n because if we 
                don't select A, Event(A,B) will never happen.
                + Second case, the sub-graph containing A,B has become smaller, so the 
                probability is ((n - x) / n) * (1 / x).
                + We add both cases up so it becomes 1/x, just like the base case.
        - Then we can solve the tree case by simply add up the inverse of every path's length
        in the tree.
        - And for the original case, there's at most 2 paths between A and B. If there's only 
        one path, then everything is the same with the tree case.
        - Otherwise, the path between A and B should pass the cycle in the graph. There are 2
        types of vertex here:
            + Vertex on the path of A to cycle or B to cycle, they should not be selected before
            A because once they're selected, A and B lost connectivity, let us call them X.
            + Vertex on the cycle, the two paths from A to B, each path contains a path in the 
            cycle, let us call them Y and Z.
        - So there are two possibilities: X and Y are free when A is selected, X and Z are free
        when A is selected. And we should subtract the case that X and Y, Z are all free when A 
        is selected because it double-counts before.
        - So the probability is 1 / (X + Y) + 1 / (X + Z) - 1 / (X + Y + Z).
        - For 2 different nodes, we can twice the probability because they are basically the same.
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

const int MAXN = 3010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, depth[MAXN], numNodesToCurTreeRoot[MAXN], treeIdx[MAXN], root[MAXN], idxInCycle[MAXN], d[MAXN], parent[MAXN][13];
vi a[MAXN];
vi dfsStack, cycle;
vi groups[MAXN];

void dfs(int u, int p) {
    dfsStack.push_back(u);
    TRAV(v, a[u]) {
        if (!depth[v]) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        } else {
            if (v == p) continue;
            if (depth[v] < depth[u]) {
                // back edge
                FORE(i,SZ(dfsStack)-1,0) {
                    cycle.push_back(dfsStack[i]);
                    if (dfsStack[i] == v) break;
                }
            } else if (depth[v] > depth[u]) {
                // forward edge
            }
        }
    }
}

void dfs2(int idx, int u, int p1, int p2 = -1) {
    treeIdx[u] = idx;
    groups[idx].push_back(u);
    TRAV(v, a[u]) {
        if (v == p1 || v == p2) continue;
        numNodesToCurTreeRoot[v] = numNodesToCurTreeRoot[u] + 1;
        parent[v][0] = u;
        d[v] = d[u] + 1;
        dfs2(idx, v, u);
    }
}

int lca(int u, int v) {
    if (d[v] < d[u]) FORE(i,12,0) if (d[parent[u][i]] >= d[v]) u = parent[u][i];
    if (d[u] < d[v]) FORE(i,12,0) if (d[parent[v][i]] >= d[u]) v = parent[v][i];
    FORE(i,12,0) if (parent[u][i] != parent[v][i]) { u = parent[u][i]; v = parent[v][i]; }
    while (u != v) { u = parent[u][0]; v = parent[v][0]; }
    return u;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    depth[0] = 1;
    // get the cycle first
    dfs(0, -1);
    
    FOR(i,0,SZ(cycle)-1) {
        // dfs from the node cycle[i] to the tree that contains cycle[i]
        int nex = (i + 1) % SZ(cycle);
        int pre = (i - 1 + SZ(cycle)) % SZ(cycle);

        numNodesToCurTreeRoot[cycle[i]] = 1;
        root[i] = cycle[i];
        idxInCycle[cycle[i]] = i;
        d[cycle[i]] = 0;
        parent[cycle[i]][0] = cycle[i];

        dfs2(i, cycle[i], cycle[nex], cycle[pre]);

        // prepare for lca later
        FOR(j,1,12)
            TRAV(k, groups[i]) parent[k][j] = parent[parent[k][j-1]][j-1];
    }

    ld res = 0;
    FOR(i,0,n-1) {
        FOR(j,i,n-1) {
            if (treeIdx[i] == treeIdx[j]) {
                // they are in the same subtree with root in the cycle, so we simply do lca here
                int g = lca(i, j);
                int len = numNodesToCurTreeRoot[i] + numNodesToCurTreeRoot[j] - 2 * numNodesToCurTreeRoot[g] + 1;
                if (i == j) res += 1.0 / len;
                else res += 2.0 / len;
            } else {
                // otherwise, we need to know which trees they are from
                int X = numNodesToCurTreeRoot[i] + numNodesToCurTreeRoot[j];
                // since 2 nodes on the cycle are actually in X, by definition
                // we need to remove them from Y and Z
                int Y = abs(idxInCycle[root[treeIdx[i]]] - idxInCycle[root[treeIdx[j]]]) - 1;
                int Z = SZ(cycle) - Y - 2;
                res += 2.0 / (X + Y) + 2.0 / (X + Z) - 2.0 / (X + Y + Z);
            }
        }
    }

    setPrec(9);
    cout << res;
    return 0;
}
