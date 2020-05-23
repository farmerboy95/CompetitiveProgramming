/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - The essential observation is that it is optimal to use either horizontal or vertical cut to recursively
        solve the problem. Proof: 
            https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2015/contest4_solutions/solutions.pdf
        - So we define dp[n][m][l][r][u][d] is the smallest fee to divide the floor nxm but l, r, u, d = 0 means
        the corresponding edge of floor is attached to the edge of the big floor.
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
const int MAXN = 301;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, k;
ll dp[MAXN][MAXN][2][2][2][2];

ll solve(int n, int m, int l, int r, int u, int d) {
    if (l && r && u && d) return (1LL<<60);
    if (dp[n][m][l][r][u][d] != -1) return dp[n][m][l][r][u][d];
    if (n > m) return dp[n][m][l][r][u][d] = solve(m, n, u, d, l, r);
    if (l > r) return dp[n][m][l][r][u][d] = solve(n, m, r, l, u, d);
    if (u > d) return dp[n][m][l][r][u][d] = solve(n, m, l, r, d, u);
    ll res = (ll) (n * m - k) * (n * m - k);

    if (n > 1 && solve(1, m, l, r, u, 1) + solve(n - 1, m, l, r, 1, d) < (1LL << 60))
        FOR(i,1,n-1) res = min(res, solve(i, m, l, r, u, 1) + solve(n - i, m, l, r, 1, d));

    if (m > 1 && solve(n, 1, l, 1, u, d) + solve(n, m-1, 1, r, u, d) < (1LL << 60))
        FOR(i,1,m-1) res = min(res, solve(n, i, l, 1, u, d) + solve(n, m-i, 1, r, u, d));

    return dp[n][m][l][r][u][d] = res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    MS(dp, -1);
    cout << solve(n, m, 0, 0, 0, 0);
    return 0;
}
