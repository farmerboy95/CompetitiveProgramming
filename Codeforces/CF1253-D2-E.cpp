/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - b[i] stores initial scope of antenna i
        - Sort array b ascending by left boundary.
        - Let dp[i][j] is the minimum coin needed to cover all points from 1 to at least j, dp[0][0] = 0
        => Result = dp[n][m]
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
const int MAXN = 85;
const int MAXM = 100010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, m;
II a[MAXN], b[MAXN];
int dp[MAXN][MAXM];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) {
        cin >> a[i].FI >> a[i].SE;
        b[i].FI = a[i].FI - a[i].SE;
        b[i].SE = a[i].FI + a[i].SE;
    }
    sort(b+1, b+n+1);
    FOR(i,0,n) 
        FOR(j,0,m) dp[i][j] = 1000000000;
    dp[0][0] = 0;
    FOR(i,1,n) {
        FOR(j,0,m) {
            dp[i][j] = min(dp[i][j], dp[i-1][j]);
            if (j < b[i].FI-1) {
                int coin = b[i].FI - j - 1;
                dp[i][min(b[i].SE+coin, m)] = min(dp[i][min(b[i].SE+coin, m)], dp[i-1][j] + coin);
            }
            else if (j < b[i].SE) {
                dp[i][min(b[i].SE, m)] = min(dp[i][min(b[i].SE, m)], dp[i-1][j]);
            }
        }
        FOR(j,2,m) dp[i][j] = min(dp[i][j], dp[i][j-1] + 1);
    }
    cout << dp[n][m];
    return 0;
}
