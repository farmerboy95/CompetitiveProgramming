/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: 
        - Mainly from https://codeforces.com/blog/entry/75432
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
const int MAXN = 300010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ll MOD = 998244353;

ll binPowMod(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1LL;
    }
    return res;
}

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

int n;
ll dp[MAXN][2], f[MAXN];
vector<int> a[MAXN];

void dfs(int u, int p) {
    dp[u][0] = dp[u][1] = f[u] = 1;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (v == p) continue;
        dfs(v, u);
        // dp[u][0] is the answer for subtree rooted at u with additional constraint such that u is not colored
        // dp[u][1] is the answer where u is colored 
        // f[u] be the answer where edges from u to its children are removed (u is isolated).

        // dp[u][0]
        // when going to v, there would be 2 cases
        // 1. The edge (u, v) is included in the edge-induced subgraph => dp[v][0] + dp[v][1]
        // 2. The edge (u, v) is not included in the edge-induced subgraph => (dp[v][1] - f[v]) + dp[v][0]
        // as we need to remove the cases which would make v an isolated vertex
        dp[u][0] = mul(dp[u][0], sub(add(2*dp[v][0], 2*dp[v][1]), f[v]));

        // dp[u][1]
        // when going to v, there would be 2 cases
        // 1. The edge (u, v) is included in the edge-induced subgraph => dp[v][0]
        // 2. The edge (u, v) is not included in the edge-induced subgraph => (dp[v][1] - f[v]) + dp[v][0]
        dp[u][1] = mul(dp[u][1], sub(add(2*dp[v][0], dp[v][1]), f[v]));

        // f[u]
        // When going to v, the edge (u, v) is not included in the edge-induced subgraph 
        // => (dp[v][1] - f[v]) + dp[v][0]
        f[u] = mul(f[u], sub(add(dp[v][0], dp[v][1]), f[v]));
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    dfs(1, 0);
    // result = dp[1][0] - 1 + (dp[1][1] - f[1])
    // should remove one case that there is no edge in the edge-induced subgraph
    cout << sub(sub(add(dp[1][0], dp[1][1]), f[1]), 1);
    return 0;
}
