/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Firstly, we flatten the tree by preorder DFS traversal. After this, any subtree can be
        represented as some sequence of continuous vertices (starting at st[u] and ending at en[u]).
        - Now let's consider a vertex v. In the path from root to v, if there is a vertex u that contains
        at least one integer in its list, the result list of v must contains the result list of u (1).
        - So how to maintain a result list? Let's do the typical DFS, if a vertex u is in at least one
        operation, the result list of u must contain the whole subtree of u. In addition, the ones paired
        with u in the operations, their subtrees must be added to the result list of u. Because of the 
        property (1), we can go to the next node while keeping the current result list and try updating
        it with new operations. When we have done considering node u, please remember to remove added
        set from the current result list.
        - Use a simple segment tree to maintain these operations:
            + Add 1 to all positions from l to r.
            + Subtract 1 from all positions from l to r.
            + Count the number of zero elements in the whole big segment.
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

int n, m, res[MAXN], now, st[MAXN], en[MAXN], t[MAXN * 8], lazy[MAXN * 8];
vector<int> a[MAXN], b[MAXN];

void dfs(int u, int p) {
    // flatten the tree
    now++;
    st[u] = now;
    for (int v : a[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    en[u] = now;
}

void update(int k, int l, int r, int u, int v, int val) {
    if (l > r || r < u || v < l) return;
    if (u <= l && r <= v) lazy[k] += val;
    else {
        int m = (l + r) >> 1;
        update(k*2, l, m, u, v, val);
        update(k*2+1, m+1, r, u, v, val);
    }
    if (lazy[k]) t[k] = r - l + 1;
    else t[k] = t[k*2] + t[k*2+1];
}

void dfs2(int u, int p) {
    if (SZ(b[u])) update(1,1,n,st[u],en[u],1);
    for (int v : b[u]) update(1,1,n,st[v],en[v],1);
    res[u] = max(0, t[1]-1);
    for (int v : a[u]) {
        if (v == p) continue;
        dfs2(v, u);
    }
    for (int v : b[u]) update(1,1,n,st[v],en[v],-1);
    if (SZ(b[u])) update(1,1,n,st[u],en[u],-1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    dfs(1, 0);

    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        b[u].push_back(v);
        b[v].push_back(u);
    }
    dfs2(1, 0);

    FOR(i,1,n) cout << res[i] << ' ';
    return 0;
}
