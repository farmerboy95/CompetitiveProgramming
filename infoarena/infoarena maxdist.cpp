/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Observation: Assume our current diameter is u->v. When adding new node x, the new diameter
        will only be one of 3 possibilities: u->v, u->x, x->v.
        - The distance is d[u] + d[v] - 2 * d[lca(u, v)]. d[i] = distance from root to i
        - So for the second clan, we proceed adding nodes as the order of query. For the first clan,
        we add nodes which are not in the query, then add nodes in the reverse order of query.
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
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, q, parent[MAXN][20], d[MAXN], res[MAXN], res2[MAXN];
vector<int> a[MAXN], query;
bool yes[MAXN];

void dfs(int u, int p) {
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (v == p) continue;
        d[v] = d[u]+1;
        parent[v][0] = u;
        dfs(v, u);
    }
}

int lca(int u, int v) {
    if (d[v] < d[u]) FORE(i,18,0) if (d[parent[u][i]] >= d[v]) u = parent[u][i];
    if (d[u] < d[v]) FORE(i,18,0) if (d[parent[v][i]] >= d[u]) v = parent[v][i];
    FORE(i,18,0) if (parent[u][i] != parent[v][i]) { u = parent[u][i]; v = parent[v][i]; }
    while (u != v) { u = parent[u][0]; v = parent[v][0]; }
    return u;
}

int getDist(int u, int v) {
    return d[u] + d[v] - 2 * d[lca(u, v)];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("maxdist.in", "r", stdin);
    freopen("maxdist.out", "w", stdout);
    cin >> n >> q;
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    parent[1][0] = 1;
    dfs(1, 0);
    FOR(j,1,18)
        FOR(i,1,n) parent[i][j] = parent[parent[i][j-1]][j-1];

    FOR(i,1,q) {
        int x;
        cin >> x;
        query.push_back(x);
        yes[x] = true;
    }

    int A = 0, B = 0, Max = 0;
    FOR(i,0,q-1) {
        if (i == 0) A = query[i];
        else if (i == 1) {
            B = query[i];
            Max = getDist(A, B);
        }
        else {
            int xa = getDist(A, query[i]), xb = getDist(B, query[i]);
            if (xa > Max && xa > xb) {
                B = query[i];
                Max = xa;
            }
            else if (xb > Max && xb > xa) {
                A = query[i];
                Max = xb;
            }
        }
        res2[i+1] = Max;
    }

    FOR(i,1,n)
        if (!yes[i]) query.push_back(i);
    
    A = 0; B = 0; Max = 0;
    FORE(i,n-1,0) {
        if (i == n-1) A = query[i];
        else if (i == n-2) {
            B = query[i];
            Max = getDist(A, B);
        }
        else {
            int xa = getDist(A, query[i]), xb = getDist(B, query[i]);
            if (xa > Max && xa > xb) {
                B = query[i];
                Max = xa;
            }
            else if (xb > Max && xb > xa) {
                A = query[i];
                Max = xb;
            }
        }
        if (i <= q) res[i] = Max;
    }

    FOR(i,1,q) cout << res[i] << ' ' << res2[i] << "\n";
    return 0;
}
