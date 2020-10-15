/*
    Author: Nguyen Tan Bao
    Status: AC 
    Idea: Same as https://atcoder.jp/contests/arc104/editorial/163
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
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, k, m;
ll MOD;

ll binPowMod(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1LL;
    }
    return res;
}

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

ll dp[MAXN][MAXN * MAXN * MAXN / 2], g[MAXN * MAXN * MAXN / 2];
int Max;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k >> m;
    MOD = m;
    Max = n * (n + 1) / 2 * k;

    // dp[i][j] = number of set totalling j considering 1, 2..., i
    // g[j] = dp[i][j] + dp[i][j - (i+1)] + dp[i][j - (i+1) * 2] + ...
    dp[0][0] = 1;
    FOR(j,0,Max) {
        g[j] = dp[0][j];
        if (j >= 1) g[j] = add(g[j], g[j-1]);
    }
    FOR(i,1,n) {
        FOR(j,0,Max) {
            dp[i][j] = g[j];
            // not taking from e backward, as there are K number max
            int e = j - i * (k+1);
            if (e >= 0) dp[i][j] = sub(dp[i][j], g[e]);
        }
        
        FOR(j,0,Max) {
            g[j] = dp[i][j];
            if (j >= i+1) g[j] = add(g[j], g[j - i-1]);
        }
    }

    FOR(i,1,n) {
        ll res = 0;
        // left part and right part should have the same sum, with number of i is from 0 to K
        FOR(j,0,Max) res = add(res, mul(k+1, mul(dp[i-1][j], dp[n-i][j])));
        // remove one case with no number chosen (sum = 0, no i)
        res = sub(res, 1);
        cout << res << "\n";
    }
    return 0;
}
