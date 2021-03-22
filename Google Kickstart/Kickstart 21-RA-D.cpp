/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - R and C arrays are only needed to see that if a row or a column has only one -1, it
        can be found without any cost.
        - Let's define a bipartite graph that has 2n nodes, n left nodes represent rows, n right
        nodes represent columns. If -1 is at cell (x, y), there is an edge from x (left) to y (right).
        with the weight is the cost to uncover the cell's value.
        - There would be a number of connected components there, we can see that we don't need to
        use costs to uncover a tree because we can remove edges from the leaves. This leads us to
        a concept of a spanning tree, in particular, a maximum spanning tree. So we can find the
        total value of those trees in our graph and the result would be sum of all edges minus that
        value.
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

const int MAXN = 510;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, a[MAXN][MAXN], b[MAXN][MAXN], r[MAXN], c[MAXN];

struct Edge {
    int u, v, c;
    Edge(int u = 0, int v = 0, int c = 0) : u(u), v(v), c(c) {}
};

bool operator< (Edge a, Edge b) {
    return a.c > b.c;
}

vector<Edge> edges;

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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case #" << o << ": ";
        cin >> n;
        FOR(i,0,n-1) FOR(j,0,n-1) cin >> a[i][j];
        FOR(i,0,n-1) FOR(j,0,n-1) cin >> b[i][j];
        FOR(i,0,n-1) cin >> r[i];
        FOR(i,0,n-1) cin >> c[i];

        edges.clear();
        int res = 0;
        FOR(i,0,n-1)
            FOR(j,0,n-1)
                if (a[i][j] == -1) {
                    int u = i, v = n + j;
                    edges.push_back(Edge(u, v, b[i][j]));
                    res += b[i][j];
                }
        sort(ALL(edges));
        DisjointSetUnion dsu(n*2);
        TRAV(x, edges) {
            int u = x.u, v = x.v, c = x.c;
            if (dsu.same(u, v)) continue;
            dsu.merge(u, v);
            res -= c;
        }
        cout << res << "\n";
    }
    return 0;
}
