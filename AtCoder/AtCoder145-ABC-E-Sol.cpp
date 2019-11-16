/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let dp[i][j][k] is the maximum value that can be achieved when considering first i dishes, use j minutes
        and we have chosen the last dish or not (k = 0 / 1) (0 <= j <= T-1).
        - Use dp like knapsack.
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
const int MAXN = 3010;
const int MAXM = 600010;
const int MAXK = 110;
const int MAXQ = 200010;

int dp[MAXN][MAXN][2], n, t;
II a[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> t;
    FOR(i,1,n) cin >> a[i].FI >> a[i].SE;

    dp[0][0][0] = dp[0][0][1] = 0;
    FOR(i,1,t-1) dp[0][i][0] = dp[0][i][1] = -1000000000;

    FOR(i,1,n)
        FOR(j,0,t-1) {
            FOR(k,0,1) {
                dp[i][j][k] = dp[i-1][j][k];
                if (j - a[i].FI >= 0) dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-a[i].FI][k] + a[i].SE);

                if (k) dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][1-k] + a[i].SE);
            }
        }

    int res = 0;
    FOR(j,0,t-1) res = max(res, dp[n][j][1]);
    cout << res;
    return 0;
}