/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Easily see that this is a knapsack problem, a[i] is weight, b[i] is value.
        - Let dp[i][j] is the maximum value that can be achieved when considering first i dishes, use j minutes.
        (0 <= j <= T-1)
        - But we can choose one last dish to eat regardless of the time of eating it.
        - So that for each i, get max(dp[i][j]), then choose max(B[p]) (i+1 <= p <= n) as dish p is the last one.

        - A problem emerges at this step, as we may ignore dish k (1 <= k <= i) that we didn't consider in dp[i][j] (because a[k] >= T)
        - We can resolve this by sorting pair(a[i], b[i])
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

int dp[MAXN][MAXN], n, t;
II a[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> t;
    FOR(i,1,n) cin >> a[i].FI >> a[i].SE;
    sort(a+1, a+n+1);

    dp[0][0] = 0;
    FOR(i,1,t-1) dp[0][i] = -1000000000;

    FOR(i,1,n)
        FOR(j,0,t-1) {
            dp[i][j] = dp[i-1][j];
            if (j - a[i].FI >= 0) dp[i][j] = max(dp[i][j], dp[i-1][j-a[i].FI] + a[i].SE);
        }

    int res = 0;
    FOR(i,0,n) {
        int Max = 0;
        FOR(j,0,t-1) Max = max(Max, dp[i][j]);
        int Max2 = 0;
        FOR(j,i+1,n) Max2 = max(Max2, a[j].SE);
        res = max(res, Max + Max2);
    }
    cout << res;
    return 0;
}
