/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Same as https://github.com/thecodingwizard/competitive-programming/blob/master/DMOJ/CCO%2017-Connection.cpp
        - Keywords: Parallel Binary Search and Finding Bridge Online
        - Note: Vertices are numbered from 0 to n, not to n-1
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
const int MAXN = 150010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, d, q, L[MAXN], R[MAXN], res[MAXN], iter;
int dsu_cc[MAXN], dsu_2ecc[MAXN], vis[MAXN], par[MAXN], cc_sz[MAXN], ecc_sz[MAXN];
vector<II> roads, queries;
vector<int> check[MAXN];

int getRoot(int u) {
    return dsu_cc[u] == u ? u : dsu_cc[u] = getRoot(dsu_cc[u]);
}

int getRoot2(int u) {
    if (u == -1) return -1;
    return dsu_2ecc[u] == u ? u : dsu_2ecc[u] = getRoot2(dsu_2ecc[u]);
}

void mergePath(int u, int v) {
    // just go to parent and store the path, lca exposes when revisiting
    iter++;
    vector<int> pathU, pathV;
    int lca = -1;
    while (lca == -1) {
        if (u != -1) {
            u = getRoot2(u);
            pathU.push_back(u);
            if (vis[u] == iter) lca = u;
            vis[u] = iter;
            u = par[u];
        }
        if (v != -1) {
            v = getRoot2(v);
            pathV.push_back(v);
            if (vis[v] == iter) lca = v;
            vis[v] = iter;
            v = par[v];
        }
    }
    // transform the whole cycle into one point
    FOR(i,0,SZ(pathU)-1) {
        dsu_2ecc[pathU[i]] = lca;
        if (lca == pathU[i]) break;
    }
    FOR(i,0,SZ(pathV)-1) {
        dsu_2ecc[pathV[i]] = lca;
        if (lca == pathV[i]) break;
    }
}

void makeRoot(int u) {
    // traversal to the root of 2-edge connected component to redirect parent to u
    // change the root of the component to u
    u = getRoot2(u);
    int root = u;
    int child = -1;
    while (u != -1) {
        int p = getRoot2(par[u]);
        par[u] = child;
        dsu_cc[u] = root;
        child = u;
        u = p;
    }
    cc_sz[root] = cc_sz[child];
}

void addEdge(int u, int v) {
    u = getRoot2(u);
    v = getRoot2(v);
    // in the same 2-edge-connected component
    if (u == v) return;
    // in the same connected component
    if (getRoot(u) == getRoot(v)) {
        mergePath(u, v);
        return;
    }
    // not in 1 connected component
    if (cc_sz[getRoot(u)] > cc_sz[getRoot(v)]) swap(u, v);
    // now merge u into v
    makeRoot(u);
    dsu_cc[u] = par[u] = v;
    cc_sz[getRoot(v)] += cc_sz[getRoot(u)];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> d >> q;
    FOR(i,1,d) {
        int u, v;
        cin >> u >> v;
        roads.push_back(II(u, v));
    }
    FOR(i,1,q) {
        int u, v;
        cin >> u >> v;
        queries.push_back(II(u, v));
    }
    int logD = 25;
    FOR(i,0,q-1) {
        L[i] = 0;
        R[i] = d;
        res[i] = -1;
    }
    FOR(step,1,logD) {
        FOR(i,0,n) {
            dsu_cc[i] = dsu_2ecc[i] = i;
            vis[i] = par[i] = -1;
            cc_sz[i] = ecc_sz[i] = 1;
        }
        FOR(i,0,d-1) check[i].clear();
        FOR(i,0,q-1)
            if (L[i] != R[i]) {
                int m = (L[i] + R[i]) >> 1;
                if (m < d) check[m].push_back(i);
            }
        FOR(i,0,d-1) {
            addEdge(roads[i].FI, roads[i].SE);
            FOR(j,0,SZ(check[i])-1) {
                int k = check[i][j];
                if (getRoot2(queries[k].FI) == getRoot2(queries[k].SE)) {
                    R[k] = i;
                    res[k] = i;
                }
                else L[k] = i+1;
            }
        }
    }

    FOR(i,0,q-1) cout << res[i] << "\n";
    return 0;
}
