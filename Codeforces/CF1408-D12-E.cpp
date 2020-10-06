/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's make a bipartite graph with m vertices on the left side and n vertices on the 
        right side.
        - We will connect vertex i from the left side with all elements of A[i].
        - It can be proven, that the graph, which we create using our sets don't have rainbow 
        cycles if and only if our bipartite graph don't have cycles.
        - So, our task is equivalent of finding the Maximum Spanning Tree of this bipartite graph, 
        where edge between i (from left side) and j (from right side) has weight equal to a[i] + b[j].
        - Result = sum of all edges - Maximum Spanning Tree size
*/

#include <bits/stdc++.h>
#define FI first
#define SE second
#define EPS 1e-9
#define ALL(a) a.begin(),a.end()
#define SZ(a) int((a).size())
#define MS(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x

using namespace std;
using ll = long long;
using ld = double;
typedef pair<int, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, a[MAXN], b[MAXN];

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
    cin >> m >> n;
    FOR(i,1,m) cin >> a[i];
    FOR(i,1,n) cin >> b[i];
    FOR(i,1,m) {
        int k, x;
        cin >> k;
        while (k--) {
            cin >> x;
            edges.push_back(Edge(i-1, m+x-1, a[i] + b[x]));
        }
    }
    sort(ALL(edges));
    DisjointSetUnion dsu(m+n);
    ll res = 0;
    for (Edge e : edges) res += e.c;
    for (Edge e : edges) {
        // cout << e.u << ' ' << e.v << ' ' << e.c << endl;
        if (dsu.same(e.u, e.v)) continue;
        dsu.merge(e.u, e.v);
        res -= e.c;
    }
    cout << res;
    return 0;
}
