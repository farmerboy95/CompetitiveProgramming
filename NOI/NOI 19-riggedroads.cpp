/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Firstly, create a tree based on n-1 edges in R, build a LCA tree simutaneously
        - How to get the lexicographically minimal permutation?
        - For each edges i from 1 to m,
            + When we encounter an edge (u, v), let's say, first edge, we need to find the minimum weight to assign it,
            but if that edge is not in R, we have to make sure that that edge could not be added into the spanning tree.
            How? This edge cannot be added to the spanning tree if and only if we already have edges from g to u and g to v
            (g is LCA of u and v) => weight of (u, v) is minimum
            + So, let's do exactly as it requires, consider all edges from u to g and v to g (by going up by parent), if 
            that edge doesn't have weight, just assign it a weight.
        - But, this naive approach can only work in O(n^2). Let's optimize it a bit.
        - We need to find a way to ignore some assigned edges. More formally, for each node, we need to find the closest node
        upward that we would have an unassigned edge connecting that closest node and its parent.
        - We use DSU idea to solve this problem.
        - For all assigned edges, their nodes form a group, just like that of DSU, let lab[u] = higher node of u in DSU tree,
        lab of root in DSU tree has number of nodes of that DSU tree, val[u] is the closest node that we are looking for.
        - When merging 2 groups, just do like normal DSU merging and val[newRoot] = higher node(val[DSU tree of u] 
        and val[DSU tree of v])
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
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 300010;
const int MAXM = 10010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, m, b[MAXN], parent[MAXN][20], d[MAXN], res[MAXN], cnt, lab[MAXN], val[MAXN];
vector<II> A[MAXN];
vector<int> c;
II a[MAXN], par[MAXN];
bool f[MAXN];

void dfs(int u, int p) {
    FOR(i,0,SZ(A[u])-1) {
        int v = A[u][i].FI;
        int cs = A[u][i].SE;
        if (v == p) continue;
        parent[v][0] = u;
        par[v] = II(u, cs);
        d[v] = d[u]+1;
        dfs(v, u);
    }
}

int lca(int u, int v) {
    if (d[v] < d[u]) FORE(i,19,0) if (d[parent[u][i]] >= d[v]) u = parent[u][i];
    if (d[u] < d[v]) FORE(i,19,0) if (d[parent[v][i]] >= d[u]) v = parent[v][i];
    FORE(i,19,0) if (parent[u][i] != parent[v][i]) { u = parent[u][i]; v = parent[v][i]; }
    while (u != v) { u = parent[u][0]; v = parent[v][0]; }
    return u;
}

int getRoot(int u) {
    while (lab[u] > 0) u = lab[u];
    return u;
}

void unionFind(int u, int v) {
    int x = lab[u] + lab[v];
    int newVal = 0;
    if (d[val[u]] < d[val[v]]) newVal = val[u];
    else newVal = val[v];
    if (lab[u] < lab[v]) {
        lab[v] = u;
        lab[u] = x;
        val[u] = newVal;
    }
    else {
        lab[u] = v;
        lab[v] = x;
        val[v] = newVal;
    }
}

void fillResult(int u, int g) {
    while (d[u] > d[g]) {
        int U = getRoot(u);
        int x = val[U];

        if (u != x) {
            // if u != x, jump to x
            u = x;
        }
        else {
            // otherwise, add weight to edge
            int p = par[u].FI;
            int cs = par[u].SE;
            c.emplace_back(cs);
            int P = getRoot(p);
            unionFind(U, P);
            u = p;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,m) cin >> a[i].FI >> a[i].SE;
    FOR(i,1,n-1) cin >> b[i];

    // create tree
    FOR(i,1,n-1) {
        int u = a[b[i]].FI, v = a[b[i]].SE;
        A[u].emplace_back(II(v, b[i]));
        A[v].emplace_back(II(u, b[i]));
        f[b[i]] = true;
    }

    // dfs and build lca
    parent[1][0] = 1;
    dfs(1, 0);
    FOR(j,1,19)
        FOR(i,1,n) parent[i][j] = parent[parent[i][j-1]][j-1];

    // init dsu
    FOR(i,1,n) {
        lab[i] = -1;
        val[i] = i;
    }

    FOR(i,1,m) {
        int u = a[i].FI;
        int v = a[i].SE;
        if (f[i]) {
            if (!res[i]) {
                // merge 2 group
                int U = getRoot(u), V = getRoot(v);
                unionFind(U, V);
                res[i] = ++cnt;
            }
        }
        else {
            c.clear();
            int g = lca(u, v);
            // find from u to g
            fillResult(u, g);
            // find from v to g
            fillResult(v, g);
            // sort all chosen edge and assign weight from lower index to higher one
            sort(ALL(c));
            FOR(j,0,SZ(c)-1) res[c[j]] = ++cnt;
            // assign weight to this edge
            res[i] = ++cnt;
        }
    }

    FOR(i,1,m) cout << res[i] << ' ';
    return 0;
}
