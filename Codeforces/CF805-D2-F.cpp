/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's solve the problem for two trees.
        - Define dt as diameter of t-th tree and fti as the maximum path starting from 
        i-th vertex of t-th tree, for all valid i and j, assume that the edge is between 
        them and find the diameter with max(f1i + f2j + 1, max(d1, d2)). The answer is
                sum(sum(max(f1i + f2j + 1, max(d1, d2)))) / (sz1 * sz2)
        - We can solve this in O(min(sz1, sz2) * log(max(sz1, sz2))) when sorting f1, f2
        - There are 2 modes we should consider
            + min(sz1, sz2) < sqrt(n): Time complexity will be O(sqrt(n) * log(n)) per query
            + min(sz1, sz2) >= sqrt(n): Number of trees with sz >= sqrt(n) is at most sqrt(n),
            If we don't calculate the answer for 2 same pairs of vertices by memorization, we can 
            precompute for every "heavy" tree u answer with every other tree v in O(n log n). 
            We have at most u heavy trees, so the overall complexity is O(sqrt(n) * n log n).
        - Overall, the final time complexity is O(sqrt(n) * n log n + sqrt(n) * q log n)
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

const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct DisjointSetUnion {
  public:
    // creates an undirected graph with n vertices and 0 edges.
    DisjointSetUnion() : _n(0) {}
    DisjointSetUnion(int n) : _n(n), parent_or_size(n, -1) {}

    // add an edge (u, v)
    // If the vertices u and v were in the same connected component, 
    // it returns the representative of this connected component. 
    // Otherwise, it returns the representative of the new connected component.
    int merge(int u, int v) {
        assert(0 <= u && u < _n);
        assert(0 <= v && v < _n);
        int x = leader(u), y = leader(v);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    // It returns whether the vertices u and v are in the same connected component
    bool same(int u, int v) {
        assert(0 <= u && u < _n);
        assert(0 <= v && v < _n);
        return leader(u) == leader(v);
    }

    // It returns the representative of the connected component that contains the vertex u
    int leader(int u) {
        assert(0 <= u && u < _n);
        if (parent_or_size[u] < 0) return u;
        return parent_or_size[u] = leader(parent_or_size[u]);
    }

    // It returns the size of the connected component that contains the vertex u
    int size(int u) {
        assert(0 <= u && u < _n);
        return -parent_or_size[leader(u)];
    }

    // It divides the graph into connected components and returns the list of them
    vector<vector<int>> groups() {
        vector<int> leader_buf(_n), group_size(_n);
        FOR(i,0,_n-1) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        vector<vector<int>> result(_n);
        FOR(i,0,_n-1) result[i].reserve(group_size[i]);
        FOR(i,0,_n-1) result[leader_buf[i]].push_back(i);
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

  private:
    int _n;
    vector<int> parent_or_size;
};

int n, m, d[MAXN], h2[MAXN], dia[MAXN];
pi h1[MAXN];
map<pi, ld> ma;
vi a[MAXN], comp[MAXN], h[MAXN];
vl sumH[MAXN];
bool visited[MAXN];

ld get(int u, int v) {
    // u and v are leaders of their own tree
    if (SZ(h[u]) > SZ(h[v])) return get(v, u);

    int Max = max(dia[u], dia[v]);
    ll sum = (ll) SZ(h[u]) * SZ(h[v]);
    ll sumD = 0;
    int upperBound = SZ(h[v]);
    FOR(i,0,SZ(h[u])-1) {
        // should use binary search here but 2 pointer also get AC (no reason)
        while (upperBound - 1 >= 0 && h[v][upperBound-1] + h[u][i] >= Max) upperBound--;
        ll l = upperBound;
        ll r = SZ(h[v]) - l;

        l = l * Max;
        r = (h[u][i] + 1) * r + sumH[v][upperBound];

        sumD += l + r;
    }
    return (ld) sumD / sum;
}

ld solve(DisjointSetUnion &dsu, int u, int v) {
    int U = dsu.leader(u), V = dsu.leader(v);
    if (U > V) swap(U, V);
    if (ma.count({U, V})) return ma[{U, V}];
    return ma[{U, V}] = get(U, V);
}

int getDiameter(int root) {
    TRAV(u, comp[root]) {
        d[u] = INF;
    }
    d[root] = 0;
    queue<int> q;
    q.push(root);
    while (SZ(q)) {
        int u = q.front(); q.pop();
        TRAV(v, a[u]) {
            if (d[v] > d[u] + 1) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }

    int p = root;
    TRAV(u, comp[root]) {
        if (d[u] > d[p]) {
            p = u;
        }
    }

    TRAV(u, comp[root]) {
        d[u] = INF;
    }
    d[p] = 0;
    q.push(p);
    while (SZ(q)) {
        int u = q.front(); q.pop();
        TRAV(v, a[u]) {
            if (d[v] > d[u] + 1) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }

    int Max = 0;
    TRAV(u, comp[root]) ckmax(Max, d[u]);
    return Max;
}

void dfs1(int u, int p) {
    pi Max = {0, 0};
    TRAV(v, a[u]) {
        if (v == p) continue;
        dfs1(v, u);
        if (h1[v].FI + 1 > Max.FI) {
            Max = {h1[v].FI + 1, Max.FI};
        } else if (h1[v].FI + 1 > Max.SE) {
            Max.SE = h1[v].FI + 1;
        }
    }
    h1[u] = Max;
}

void dfs2(int u, int p) {
    TRAV(v, a[u]) {
        if (v == p) continue;
        int x = 0;
        if (h1[u].FI == h1[v].FI + 1) {
            x = h1[u].SE;
        } else {
            x = h1[u].FI;
        }
        h2[v] = max(1 + h2[u], 1 + x);
        dfs2(v, u);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int q;
    cin >> n >> m >> q;
    DisjointSetUnion dsu(n);
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        dsu.merge(u, v);
        a[u].push_back(v);
        a[v].push_back(u);
    }

    FOR(i,0,n-1) {
        int u = dsu.leader(i);
        comp[u].push_back(i);
    }

    FOR(i,0,n-1) {
        if (SZ(comp[i]) == 0) continue;
        dia[i] = getDiameter(i);

        dfs1(i, -1);
        h2[i] = 0;
        dfs2(i, -1);

        TRAV(u, comp[i]) {
            h[i].push_back(max(h1[u].FI, h2[u]));
        }

        sort(ALL(h[i]));
        FOR(j,0,SZ(h[i])) sumH[i].push_back(0);
        FORE(j,SZ(h[i])-1,0) sumH[i][j] = sumH[i][j+1] + h[i][j];
    }

    while (q--) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        if (dsu.same(u, v)) {
            cout << -1 << "\n";
            continue;
        }

        cout << fixed << setprecision(9) << solve(dsu, u, v) << "\n";
    }
    return 0;
}
