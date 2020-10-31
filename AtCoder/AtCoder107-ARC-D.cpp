/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let dp(N,K) be the number of multisets with sum k and size N. 
        - You can recursively formulate dp(N,K)=dp(N,2∗K)+dp(N−1,K−1).
        - The first term dp(N,2∗K) is the case when you don't take 1 and so the 
        sequence starts from 1/2 so it is equivalent of taking sum to 2∗k and 
        let the sequence to start from 1.
        - The other term, dp(N−1,K−1) is the case when you have taken 1 in the 
        multiset, so your sum reduces to k−1 and length to N−1 and you can still 
        start from 1.
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

ll dp[MAXN][MAXN];
ll MOD = 998244353;

ll solve(int n, int k) {
    if (n < k) return 0;
    if (n == k) return 1;
    if (k == 0) return 0;
    if (dp[n][k] != -1) return dp[n][k];

    ll &res = dp[n][k];
    res = (solve(n, k*2) + solve(n-1, k-1)) % MOD;
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    MS(dp, -1);
    cout << solve(n, k);
    return 0;
}
