/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - First, choosing K columns to change their values is equivalent to removing those columns.
        - Let dp[i][j] is the minimum number of operation needed when considering to column i, used j removal.
        (0 <= i <= N+1, 0 <= j <= K) 
        - So at each i, we consider removing p columns from i-p to i-1 and calculate dp.
        - Result is min(dp[N+1][j]) (0 <= j <= K)
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
const int MAXN = 310;
const int MAXM = 600010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, k, a[MAXN];
ll dp[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,n) cin >> a[i];
    FOR(i,0,n+1)
        FOR(j,0,k) dp[i][j] = 1e15;
    dp[0][0] = 0;
    FOR(i,1,n+1)
        FOR(j,0,k)
            FOR(p,0,j) {
                if (i - p - 1 < 0) break;
                dp[i][j] = min(dp[i][j], dp[i-p-1][j-p] + max(0, a[i] - a[i-p-1]));
            }
    ll res = 1e18;
    FOR(j,0,k) res = min(res, dp[n+1][j]);
    cout << res;
    return 0;
}
