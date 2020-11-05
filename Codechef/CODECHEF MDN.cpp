/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://discuss.codechef.com/t/mdn-editorial/29178
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
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, k, m, a[MAXN];
int dp[2][110][55];
int MOD = MODBASE;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k >> m;
    FOR(i,1,n) {
        // turn the A[i] to 0/1 array
        int x;
        cin >> x;
        a[i] = x >= m;
    }
    // we need to take at least (K+1)/2 number 1
    dp[0][0][0] = 1;
    ll res = 0;
    int cur = 0;
    int upper = 51;
    FOR(i,1,n) {
        cur = 1-cur;
        dp[cur][0][0] = dp[1-cur][0][0];
        dp[cur][1][0] = dp[1-cur][1][0];
        dp[cur][1][1] = dp[1-cur][1][1];
        // there are i ways to take the first element, this one is a really clever approach
        // explained in the editorial
        dp[cur][1][a[i]] += i;
        dp[cur][1][a[i]] %= MOD;
        FOR(j,2,min(i,k)) {
            FOR(sum,0,upper-1) {
                dp[cur][j][sum] = dp[1-cur][j][sum];
                dp[cur][j][sum] += dp[1-cur][j-1][sum-a[i]];
                dp[cur][j][sum] %= MOD;
            }
            if (j >= upper) {
                dp[cur][j][upper] = dp[1-cur][j][upper];
                dp[cur][j][upper] += dp[1-cur][j-1][upper];
                dp[cur][j][upper] %= MOD;
                if (a[i]) dp[cur][j][upper] += dp[1-cur][j-1][upper-1];
                dp[cur][j][upper] %= MOD;
            }
        }

        FOR(j,k/2+1,min(k,upper)) {
            // we check the number of valid subsequences ending here, multiply with n-i+1
            ll diff = dp[cur][k][j] - dp[1-cur][k][j];
            diff = (diff + MOD) % MOD;
            diff = diff * (n-i+1) % MOD;
            res = (res + diff) % MOD;
        }
    }
    cout << res;
    return 0;
}
