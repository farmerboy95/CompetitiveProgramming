/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Same as the editorial: https://img.atcoder.jp/agc013/editorial.pdf
        - Define dp[i][j][k] as the number of possible sequences of the first i operations 
        that end with j red bricks after the operations, and additionally k is a boolean 
        value that shows whether we have performed special operations.
        - We call an operation ”special” if it has the smallest possible value of x when the 
        operation is performed. That is, a ’RR’ or ’RB’ operation when x = 0, or a ’BB’ or ’BR’ 
        operation when x = 1. It's easy to see that any sequence of operations has exactly one 
        way to perform with at least one special operation.
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

ll MOD = MODBASE;

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

int n, m;
ll dp[MAXN][MAXN][2];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    // init, notice when j = 0, k must be 1
    FOR(j,0,n) dp[0][j][j == 0] = 1;
    FOR(i,0,m-1)
        FOR(j,0,n) 
            FOR(k,0,1) {
                if (!dp[i][j][k]) continue;
                if (j + 1 <= n) {
                    // note that we should update k when using one operation
                    // RR
                    dp[i+1][j+1][k | (j+1 == 0)] = add(dp[i+1][j+1][k | (j+1 == 0)], dp[i][j][k]);
                    // RB
                    dp[i+1][j][k | (j+1 == 0)] = add(dp[i+1][j][k | (j+1 == 0)], dp[i][j][k]);
                }
                if (j - 1 >= 0) {
                    // BR
                    dp[i+1][j][k | (j-1 == 0)] = add(dp[i+1][j][k | (j-1 == 0)], dp[i][j][k]);
                    // BB
                    dp[i+1][j-1][k | (j-1 == 0)] = add(dp[i+1][j-1][k | (j-1 == 0)], dp[i][j][k]);
                }
            }
    ll res = 0;
    FOR(j,0,n) res = add(res, dp[m][j][1]);
    cout << res;
    return 0;
}
