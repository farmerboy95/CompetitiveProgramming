/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Firstly, let's solve this problem, count the number of ways to get a subsequence of
        init array length N that it has sum equal to S
        - This is a classic problem. Let dp[i][j] is number of ways to get a subsequence of
        array [1..i] that it has sum equal to j.
        - Let's get back to the original problem, we can see that f(1, R) = dp[R][S], but what
        about f(2, R) and so on?
        - Take a look at this observation: given a subsequence that has sum equal to S, its start
        element is at position x, end element is at position y, so the number of times that it 
        should be added to the final result is x * (n-y+1)
        - We may not need to care about y because we have the dp table but what about x? How to know
        the start element of a subsequence?
        - It can be solved easily by adding x when a[x] is the start element of the sequence
        - Result = sum(a[i][S])
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

ll MOD = 998244353;
int n, s, a[MAXN];
ll dp[MAXN][MAXN], dp2[MAXN][MAXN];

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll sub(ll a, ll b) {
    return (a - b) % MOD;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> s;
    FOR(i,1,n) cin >> a[i];
    dp[0][0] = 1;
    FOR(i,1,n)
        FOR(j,0,s) {
            dp[i][j] = dp[i-1][j];
            if (j >= a[i]) {
                // first element
                if (j == a[i]) dp[i][j] = add(dp[i][j], i);
                else dp[i][j] = add(dp[i][j], dp[i-1][j-a[i]]);
            }
        }
    ll res = 0;
    FOR(i,1,n) res = add(res, dp[i][s]);
    cout << res;
    return 0;
}
