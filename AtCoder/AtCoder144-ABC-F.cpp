/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let dp[i] is expected number of passages going through before going to n
        - dp[i] = 1 + dp[j] / deg[i] (deg[i] = out degree of i, there is a passage from i to j)
        - Calculate dp[i] for the general case first (no block)
        - For each point, consider all of passages starting from it, get the highest dp[j], try to block it and dp again
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
typedef pair<ll, ll> II;
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 610;
const int MAXM = 10010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, m, A[MAXN][MAXN];
ld dp[MAXN];
vector<II> a[MAXN];
int check[MAXN];

inline int cmp(ld a, ld b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

ld solve(int u, int ban) {
    if (dp[u] != -1) return dp[u];

    int num = 0;

    FOR(i,0,SZ(a[u])-1) {
        int idx = a[u][i].SE;
        if (idx == ban) continue;
        num++;
    }

    ld res = 0;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i].FI;
        int idx = a[u][i].SE;
        if (idx == ban) continue;
        res += 1.0 / num * (solve(v, ban) + 1);
    }

    if (cmp(res, 0) == 0) res = -1000000000;

    return dp[u] = res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        a[u].emplace_back(II(v, i));
        A[u][v] = i;
    }

    FOR(i,1,n) dp[i] = -1;
    dp[n] = 0;
    ld res = solve(1, 0);
    FOR(i,1,n) {
        int pos = 0;
        ld Max = 0;
        FOR(j,0,SZ(a[i])-1) {
            int v = a[i][j].FI;
            if (dp[v] > Max) {
                Max = dp[v];
                pos = v;
            }
        }
        if (pos > 0) check[i] = pos;
    }

    FOR(i,1,n) {
        if (!check[i]) continue;
        FOR(j,1,n) dp[j] = -1;
        dp[n] = 0;
        int edge = A[i][check[i]];
        ld x = solve(1, edge);
        if (cmp(x, 0) <= 0) continue;
        // cout << i << ' ' << x << endl;
        res = min(res, x);
    }

    cout << fixed << setprecision(9) << res;
    return 0;
}
