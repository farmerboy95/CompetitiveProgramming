/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We can solve this problem in O(nlog^2n) with the help of centroid decomposition and
        polynomial multiplication with FFT.
        - Firstly we build a centroid tree of the given tree. Now the centroid tree has the height
        of O(logn).
        - Traverse each node of the centroid tree, when on a particular node, say P:
            + You need to count the distance between 2 nodes present in different subtrees of P (on
            the centroid tree).
                + Build a polynomial for each of the subtree. Polynomial should contain k * x^d, where
                d is the distance between the node and P, k is the number of nodes that have the distance
                of d to P. Note that distances here are calculated on the original tree, not the centroid
                tree.
                + Add all the polynomials of the subtrees together and square it. This will overcount
                the distance between 2 nodes present in the same subtree of P, so we need to subtract
                the square of each subtree's polynomial from the result.
                + Still we have every pair counted twice, so we need to divide the result by 2.
                + We now have a polynomial in which coefficient of x^d is the number of paths of length
                d passing through P and present in different subtrees of P.
            + You need to count distance between P and all other nodes.
                + Traverse all the subtree and update the count naively. Since the height of the centroid
                tree is O(logn), this part takes O(nlogn).
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

int n, parent[MAXN][20], depth[MAXN], maxDepth, sz[MAXN], visited[MAXN], logN;
vi a[MAXN];
vl D;

void fft(vcd &a, int invert) {
    int n = SZ(a);

    int k = 0;
    while ((1<<k) < n) k++;
    vector<int> rev(n);
    // 10110 -> rev = 01101
    rev[0] = 0;
    int high1 = -1;
    FOR(i,1,n-1) {
        if ((i & (i-1)) == 0) high1++;
        rev[i] = rev[i ^ (1<<high1)];
        rev[i] |= (1 << (k-high1-1));
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }

    // roots of unity w(n) ^ k = cos(2pi * k / n) (+/-) i * sin(2pi * k / n)
    vcd roots(n/2);
    ld alpha = 2 * acos(-1) / n * (invert ? -1 : 1);
    FOR(i,0,n/2-1) roots[i] = cd(cos(alpha * i), sin(alpha * i));

    for (int len = 2; len <= n; len <<= 1) {
        int step = n / len;
        for (int i = 0; i < n; i += len) {
            FOR(j,0,len/2-1) {
                cd u = a[i+j], v = a[i+j+len/2] * roots[j * step];
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
            }
        }
    }

    if (invert) FOR(i,0,n-1) a[i] /= n;
}

vector<ll> multiply(vector<ll> &v, vector<ll> &w) {
    vcd fv(ALL(v)), fw(ALL(w));
    int n = 1;
    while (n < SZ(v) + SZ(w) - 1) n <<= 1;
    fv.resize(n); fw.resize(n);

    fft(fv, 0); fft(fw, 0);
    FOR(i,0,n-1) fv[i] *= fw[i];

    fft(fv, 1);
    n = SZ(v) + SZ(w) - 1;
    vector<ll> res(n);
    FOR(i,0,n-1) res[i] = (ll) round(fv[i].real());

    return res;
}

void dfs(int u, int p, int d) {
    ckmax(maxDepth, d);
    parent[u][0] = p;
    depth[u] = d;
    TRAV(v, a[u]) {
        if (v == p) continue;
        dfs(v, u, d+1);
    }
}

int lca(int u, int v) {
    if (depth[v] < depth[u]) FORE(i,logN,0) if (depth[parent[u][i]] >= depth[v]) u = parent[u][i];
    if (depth[u] < depth[v]) FORE(i,logN,0) if (depth[parent[v][i]] >= depth[u]) v = parent[v][i];
    FORE(i,logN,0) if (parent[u][i] != parent[v][i]) { u = parent[u][i]; v = parent[v][i]; }
    while (u != v) { u = parent[u][0]; v = parent[v][0]; }
    return u;
}

int getSize(int u, int p) {
    sz[u] = 1;
    TRAV(v, a[u]) {
        if (v == p || visited[v]) continue;
        sz[u] += getSize(v, u);
    }
    return sz[u];
}

int getCentroid(int u, int p, int treeSize) {
    TRAV(v, a[u]) {
        if (v == p || visited[v]) continue;
        if (sz[v] * 2 > treeSize) return getCentroid(v, u, treeSize);
    }
    return u;
}

void addPolyCoeff(vl &V, int d, ll val) {
    if (SZ(V) <= d) V.resize(d+1);
    V[d] += val;
}

void addPoly(vl &V, vl &W) {
    // add polynomial W to V
    if (SZ(V) < SZ(W)) V.resize(SZ(W));
    FOR(i,0,SZ(W)-1) {
        V[i] += W[i];
    }
}

void subtractPoly(vl &V, vl &W) {
    // subtract polynomial W from V
    if (SZ(V) < SZ(W)) V.resize(SZ(W));
    FOR(i,0,SZ(W)-1) {
        V[i] -= W[i];
    }
}

void squarePoly(vl &V) {
    // square polynomial V
    V = multiply(V, V);
}

vi decompose(int u, int p) {
    // get centroid of the current subtree
    int root = getCentroid(u, p, getSize(u, p));
    // mark centroid as visited
    visited[root] = 1;

    // curTree contains all nodes in the current centroid tree
    vi curTree = {root};

    // sum contains the sum of all polynomials of all child trees
    vl sum;
    TRAV(v, a[root]) {
        if (visited[v]) continue;
        // childTree contains all nodes in the child tree
        vi childTree = decompose(v, root);

        // V is the polynomial of the child tree
        vl V;
        for (int x : childTree) {
            curTree.push_back(x);
            // d is the distance between x and root (in the initial tree)
            int d = depth[x] + depth[root] - 2 * depth[lca(x, root)];
            // add 1 to x^d of V
            addPolyCoeff(V, d, 1);

            // count distance between root and all other nodes twice, as we haven't
            // divide the D by 2.
            addPolyCoeff(D, d, 2);
        }
        addPoly(sum, V);

        // - V^2, as we need subtract the square of each subtree's polynomial from the result
        squarePoly(V);
        subtractPoly(D, V);
    }

    // + sum^2, as we square the sum of all child trees and add to the result
    if (SZ(sum) > 0) {
        squarePoly(sum);
        addPoly(D, sum);
    }
    return curTree;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    logN = 0;
    while ((1<<(logN+1)) < n) logN++;
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    // D is a polynomial, D[i] is the number of unordered pairs of vertices with
    // distance i, so here initially we have D[0] = n means that we have n unordered
    // pairs of vertices with distance 0: (0, 0), (1, 1), (2, 2), ..., (n-1, n-1)
    D = {n};

    // dfs for LCA
    dfs(0, 0, 1);
    FOR(i,1,logN)
        FOR(u,0,n-1) parent[u][i] = parent[parent[u][i-1]][i-1];
    
    // use centroid decomposition
    decompose(0, 0);
    
    // The result only requires ordered pairs and no (i, i) pairs, so we take from D[1]
    // and half of each D[i]
    FOR(i,1,n-1)
        if (i < SZ(D)) cout << D[i] / 2 << " ";
        else cout << 0 << " ";
    return 0;
}
