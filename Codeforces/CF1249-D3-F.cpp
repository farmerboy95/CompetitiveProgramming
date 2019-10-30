/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let dp[u][x] = maximum weight of subset chosen in the subtree of u, the distance of the closest chosen node is at least x
        - Let K = k+1
        - dp[u][0] = val[u] + sum(dp[v][K-1])
        - Let g = K / 2
        - For each distance j from 1 to g, dp[u][j] = dp[V][j-1] + sum(dp[v][K-j-1])
            + In this situation, distance from chosen nodes in subtree of one v (let it V) to u is j <= K/2, 
            then the distance from other subtrees to u should be at least K-j, to avoid the situation that there
            is a pair of chosen nodes with distance < K
        - For each distance j from g+1 to K, dp[u][j] = sum(dp[v][j-1])
            + In this situation, distance from chosen nodes to u is larger K/2, then the distance between 
            closest pair of nodes should be larger than K
        - dp[u][j] = max(dp[u][j+1 -> K])
        - Result is dp[1][0]
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
typedef pair<ll, int> IIl;
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 210;
const int MAXM = 10010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, k, val[MAXN];
vector<int> a[MAXN];
int dp[MAXN][MAXN];

void dfs(int u, int p) {
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (v == p) continue;
        dfs(v, u);
    }

    dp[u][0] = val[u];
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (v == p) continue;
        dp[u][0] += dp[v][k];
    }

    int g = (k + 1) / 2;
    FOR(j,1,g) {
        int other = k + 1 - j - 1;
        int sumOther = 0;
        FOR(i,0,SZ(a[u])-1) {
            int v = a[u][i];
            if (v == p) continue;
            sumOther += dp[v][other];
        }
        FOR(i,0,SZ(a[u])-1) {
            int v = a[u][i];
            if (v == p) continue;
            dp[u][j] = max(dp[u][j], dp[v][j-1] + sumOther - dp[v][other]);
        }
    }

    FOR(j,g+1,k+1) {
        FOR(i,0,SZ(a[u])-1) {
            int v = a[u][i];
            if (v == p) continue;
            dp[u][j] += dp[v][j-1];
        }
    }

    FORE(j,k,0) dp[u][j] = max(dp[u][j], dp[u][j+1]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,n) cin >> val[i];

    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        a[u].emplace_back(v);
        a[v].emplace_back(u);
    }

    dfs(1, 0);
    cout << dp[1][0];
    return 0;
}
