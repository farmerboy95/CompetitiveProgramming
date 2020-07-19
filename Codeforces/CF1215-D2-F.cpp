/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - More or less like: https://codeforces.com/blog/entry/69815
        - More comments in implementation
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
const int MAXN = 2000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

vector<int> a[MAXN], ts, res;
int low[MAXN], num[MAXN], dfsNum, sccCnt, w[MAXN], n, p, M, m, N, P[MAXN];
bool visited[MAXN];
stack<int> s;

void orClause(int u, int v) {
    a[u^1].push_back(v);
    a[v^1].push_back(u);
}

void xorClause(int u, int v) {
    orClause(u, v);
    orClause(u^1, v^1);
}

void andClause(int u, int v) {
    a[u].push_back(v);
    a[v].push_back(u);
}

void nXorClause(int u, int v) {
    orClause(u^1, v);
    orClause(u, v^1);
} 

void nAndClause(int u, int v) {
    a[u].push_back(v^1);
    a[v].push_back(u^1);
}

void mustTrue(int u) {
    a[u^1].push_back(u);
}

void scc(int u) {
    low[u] = num[u] = ++dfsNum;
    s.push(u);
    visited[u] = true;
    for (int v : a[u]) {
        if (num[v] == -1) scc(v);
        if (visited[v]) low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
        int k = -1;
        sccCnt++;
        do {
            k = s.top();
            s.pop();
            w[k] = sccCnt;
            visited[k] = false;
        } while (k != u);
    }
}

void dfs(int u) {
    visited[u] = true;
    for (int v : a[u])
        if (!visited[v]) dfs(v);
    ts.push_back(u);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> p >> M >> m;
    // number of nodes = p + M, even = true, odd = false
    N = 2 * (p + M);
    FOR(i,0,M-2) {
        // M variables, the i-th of them corresponding to the fact f >= i
        // if (a => b) <=> (b OR ~a)
        // if f >= i+1 => f >= i, so we add clause (f >= i) OR NOT (f >= i+1)
        int u = (p + i) * 2;
        int v = ((p + i + 1) * 2) ^ 1;
        orClause(u, v);
    }
    FOR(i,1,n) {
        int u, v;
        cin >> u >> v;
        u = (u - 1) * 2;
        v = (v - 1) * 2;
        // one of 2 stations must be chosen
        orClause(u, v);
    }
    FOR(i,1,p) {
        int l, r;
        cin >> l >> r;
        r++;
        // f >= l or station i is not used
        orClause((p + l-1) * 2, ((i - 1) * 2) ^ 1);
        // not f <= r + 1 or station i is not used
        if (r <= M) orClause(((p + r-1) * 2) ^ 1, ((i - 1) * 2) ^ 1);
    }
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        u = (u - 1) * 2;
        v = (v - 1) * 2;
        // result set should not contain both
        nAndClause(u, v);
    }
    FOR(i,0,N-1) num[i] = -1;
    MS(visited, false);
    dfsNum = -1;
    FOR(i,0,N-1)
        if (num[i] == -1) scc(i);
    bool co = true;
    FOR(i,0,N-1)
        if (w[i] == w[i^1]) co = false;
    if (!co) {
        cout << -1;
        return 0;
    }

    FOR(i,0,N-1) 
        if (!visited[i]) dfs(i);
    int kq = 0;
    reverse(ts.begin(), ts.end());
    for (int v : ts) {
        if (v % 2 == 0) {
            int k = v^1;
            if (P[k]) {
                int x = v / 2 + 1;
                if (x <= p) res.push_back(x);
                else kq = max(kq, x - p);
            }
        }
        P[v] = true;
        // If ¬x i is after x i in topological sort, x i should be FALSE. It should be TRUE otherwise.
    }
    cout << SZ(res) << " " << kq << "\n";
    for (int x : res) cout << x << ' ';
    return 0;
}
