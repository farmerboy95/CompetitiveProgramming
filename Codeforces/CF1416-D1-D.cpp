/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: The same as https://codeforces.com/blog/entry/83036
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
const int MAXN = 500010;
const int MAXM = 300010;
const int MAXK = 16;
const int MAXQ = 500010;

int n, m, q, a[MAXN], del[MAXM], lab[MAXN], itr, L[MAXN], R[MAXN];
II t[MAXN * 4];
II e[MAXM], qu[MAXQ];
vector<int> A[MAXN];

int getRoot(int u) {
    if (lab[u] == u) return u;
    return lab[u] = getRoot(lab[u]);
}

void unionPair(int u, int v) {
    // DO NOT use small-to-large here as we need to maintain the root node of each merge for querying later
    // create another root node to connect to boss nodes
    int U = getRoot(u), V = getRoot(v);
    if (U == V) return;
    n++;
    lab[U] = lab[V] = lab[n] = n;
    A[n].push_back(U);
    A[n].push_back(V);
}

void dfs(int u) {
    // now we have a tree, we can flatten it using a dfs, a query on a subtree is equivalent to a query
    // on segment tree with segment [ L[u], R[u] ]
    L[u] = ++itr;
    for (int v : A[u]) dfs(v);
    R[u] = itr;
}

void update(int k, int l, int r, int u, II val) {
    if (l > r || r < u || u < l) return;
    if (l == r) {
        t[k] = val;
        return;
    }
    int mid = (l + r) >> 1;
    update(k*2, l, mid, u, val);
    update(k*2+1, mid+1, r, u, val);
    t[k] = max(t[k*2], t[k*2+1]);
}

II get(int k, int l, int r, int u, int v) {
    if (l > r || r < u || v < l) return II(0, 0);
    if (u <= l && r <= v) return t[k];
    int mid = (l + r) >> 1;
    return max(get(k*2, l, mid, u, v), get(k*2+1, mid+1, r, u, v));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        e[i] = II(u, v);
    }
    FOR(i,1,q) {
        int u, v;
        cin >> u >> v;
        qu[i] = II(u, v);
        if (u == 2) del[v] = 1;
    }
    FOR(i,1,n) lab[i] = i;
    // create edges in dsu-tree that are not in queries first
    FOR(i,1,m)
        if (!del[i]) unionPair(e[i].FI, e[i].SE);
    
    // proceed queries reversely
    FORE(i,q,1)
        if (qu[i].FI == 2) {
            int idx = qu[i].SE;
            unionPair(e[idx].FI, e[idx].SE);
        } else qu[i].SE = getRoot(qu[i].SE);
    
    FOR(i,1,n)
        if (lab[i] == i) dfs(i);

    // init input values first
    FOR(i,1,n) update(1,1,n,L[i],II(a[i], L[i]));

    FOR(i,1,q)
        if (qu[i].FI == 1) {
            // proceed type 1 queries only, as for each type 1 query, we know the root node of the subtree we
            // want to query on.
            int root = qu[i].SE;
            II x = get(1,1,n,L[root],R[root]);
            cout << x.FI << "\n";
            // update node value to 0 after getting result not 0
            if (x.FI) update(1,1,n,x.SE,II(0,0));
        }
    return 0;
}
