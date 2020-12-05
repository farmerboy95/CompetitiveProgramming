/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let dp[i][x] (i <= x) be the minimum number of platforms that should be cleaned to 
        leave only one way to get to the i-th platform, where the only platform k that can 
        directly move to the i-th platform (i.e. the predecessor) has a value at most x-k
        - https://codeforces.com/blog/entry/85288
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
const int MAXN = 3010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int t, n, a[MAXN], dp[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n;
        FOR(i,1,n) cin >> a[i];

        FOR(i,2,n) {
            int cnt = 0;
            FOR(j,i,n) dp[i][j] = 1e9;
            FORE(j,i-1,1)
                if (j + a[j] >= i) {
                    dp[i][j+a[j]] = min(dp[i][j+a[j]], dp[j][i-1] + cnt);
                    cnt++;
                }
            FOR(j,i+1,n) dp[i][j] = min(dp[i][j], dp[i][j-1]);
        }
        cout << dp[n][n] << "\n";
    }
    return 0;
}
