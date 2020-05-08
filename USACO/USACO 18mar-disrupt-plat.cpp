/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's consider one extra pathway (u,v), that pathway will be used only if the blocked path is on
        the shortest path from u to v, it means the path from u -> lca(u,v) -> v
        - So for each original pathway, let's check if it's in any of the above path, if not => -1
        - If it's in at least one above path, take the one that have the minimum length.
        - But it would take us too long time. We may do like this: sort all extra pathway in ascending
        order of length. Then for each pathway, just fill in the result (length of the pathway) to the edges
        that are in the shortest path from u to v on the tree.
        - That may be a clever idea but somehow the considered edges be duplicated, we don't need to fill in
        the result again as the later edge's length will be larger than the current length. So we use some kind
        of data structure to ignore filled in edges. 
        - I choose disjoint set union. For each extra pathway (u,v), we find g = lca(u,v), then try
        to traverse from u to g and from v to g, fill in the result to the edge that connects 2 disjoint sets,
        then merge them and traverse until we reach a node that have depth not larger than g.
        - Remember to fill -1 to res array initially.
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
const int MAXN = 50010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct Edge {
    int u, v, c;
    Edge(int u = 0, int v = 0, int c = 0) : u(u), v(v), c(c) {}
};

bool operator< (Edge a, Edge b) {
    return a.c < b.c;
}

int n, m, res[MAXN], lab[MAXN], highest[MAXN], parent[MAXN][17], d[MAXN];
map<II, int> ma;
vector<int> a[MAXN];
Edge b[MAXN];

void dfs(int u, int p) {
    for (int v : a[u]) {
        if (v == p) continue;
        parent[v][0] = u;
        d[v] = d[u]+1;
        dfs(v, u);
    }
}

int lca(int u, int v) {
    if (d[v] < d[u]) FORE(i,16,0) if (d[parent[u][i]] >= d[v]) u = parent[u][i];
    if (d[u] < d[v]) FORE(i,16,0) if (d[parent[v][i]] >= d[u]) v = parent[v][i];
    FORE(i,16,0) if (parent[u][i] != parent[v][i]) { u = parent[u][i]; v = parent[v][i]; }
    while (u != v) { u = parent[u][0]; v = parent[v][0]; }
    return u;
}

int getRoot(int u) {
    while (lab[u] > 0) u = lab[u];
    return u;
}

int unionFind(int u, int v) {
    int x = lab[u] + lab[v];
    if (lab[u] < lab[v]) {
        lab[v] = u;
        lab[u] = x;
        // remember to update highest node
        if (d[highest[u]] > d[highest[v]]) highest[u] = highest[v];
        return u;
    }
    else {
        lab[u] = v;
        lab[v] = x;
        if (d[highest[u]] < d[highest[v]]) highest[v] = highest[u];
        return v;
    }
}

void update(int u, int p, int c) {
    if (u > p) swap(u, p);
    res[ma[II(u, p)]] = c;
}

void traverseBack(int u, int g, int c) {
    u = getRoot(u);
    int highU = highest[u];
    while (d[highU] > d[g]) {
        // merge 2 set and continue to traverse
        int p = parent[highU][0];
        update(highU, p, c);
        p = getRoot(p);
        u = unionFind(u, p);
        highU = highest[u];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("disrupt.in", "r", stdin);
    freopen("disrupt.out", "w", stdout);
    cin >> n >> m;
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
        if (u > v) swap(u, v);
        ma[II(u,v)] = i;
        res[i] = -1;
    }
    FOR(i,1,m) {
        int u, v, c;
        cin >> u >> v >> c;
        b[i] = Edge(u,v,c);
    }
    sort(b+1, b+m+1);
    FOR(i,1,n) {
        // number of nodes in the disjoint set and the node in the set that has smallest depth
        // 1 (root) is the highest node in my opinion
        lab[i] = -1;
        highest[i] = i;
    }
    // dfs and build lca
    parent[1][0] = 1;
    dfs(1, 0);
    FOR(j,1,16)
        FOR(i,1,n) parent[i][j] = parent[parent[i][j-1]][j-1];

    FOR(i,1,m) {
        int u = b[i].u, v = b[i].v, c = b[i].c;
        int g = lca(u, v);
        traverseBack(u, g, c);
        traverseBack(v, g, c);
    }

    FOR(i,1,n-1) cout << res[i] << "\n";
    return 0;
}
