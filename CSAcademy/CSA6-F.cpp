/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - As long as every vertex has even degree, it's a union of edge-disjoint cycles
        - Importantly, if we take two (unions of edge-disjoint cycles), then (the set of all 
        edges that are in exactly one of them) is a union of edge-disjoint cycles.
        - Cycle basis is a set of simple cycles that forms a basis of the cycle space of the
        graph. It works exactly like how XOR basis works. Find out more here: https://en.wikipedia.org/wiki/Cycle_basis
        - A fundamental cycle basis may be formed from any spanning tree or spanning forest 
        of the given graph, by selecting the cycles formed by the combination of a path in the 
        tree and a single edge outside the tree. We can use this to create a cycle basis.
        - Get the spanning tree of the given graph, then for each edge that is not in the tree,
        we try to add its xor sum value into the basis.
        - Finding the max xor sum is trivial. Refer to https://codeforces.com/blog/entry/68953
        (Problem 3)
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
typedef pair<int, ll> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
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

struct Edge {
    int u, v;
    ll c;
    Edge(int u = 0, int v = 0, ll c = 0) : u(u), v(v), c(c) {}
};

int n, m;
ll prefXor[MAXN];
vector<Edge> extra;
vector<II> a[MAXN];
const int D = 61;
ll basis[D];

void dfs(int u, int p) {
    for (II w : a[u]) {
        if (w.FI == p) continue;
        prefXor[w.FI] = prefXor[u] ^ w.SE;
        dfs(w.FI, u);
    }
}

void insertVector(ll mask) {
    FORE(i,D-1,0) {
        if (!(mask & (1LL<<i))) continue;
        if (!basis[i]) {
            basis[i] = mask;
            return;
        }
        mask ^= basis[i];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    DisjointSetUnion dsu(n);
    FOR(i,1,m) {
        int u, v; ll c;
        cin >> u >> v >> c;
        u--;
        v--;
        if (dsu.same(u, v)) extra.push_back({u, v, c});
        else {
            dsu.merge(u, v);
            a[u].push_back(II(v, c));
            a[v].push_back(II(u, c));
        }
    }
    dfs(0,-1);
    for (Edge e : extra) {
        ll cycleXor = prefXor[e.u] ^ prefXor[e.v] ^ e.c;
        insertVector(cycleXor);
    }
    ll res = 0;
    FORE(i,D-1,0)
        if (basis[i]) {
            if (res & (1LL << i)) continue;
            res ^= basis[i];
        }
    cout << res;
    return 0;
}
