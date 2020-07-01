/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/hackercup/problem/127561170642475/
    Status: AC
    Idea:
        - Note that two sequences are considered different if their lengths differ or there is at least 
        one position at which they differ. It means that if we can produce 2 identical subsequences by 
        deleting 2 sets of elements, those 2 subsequences are actually the same (use sample test 4).
        - In this problem, we note that we should get numbers from both sides from the smallest to the
        biggest and the current number must be higher than number of picked numbers.
        - First we set a[0] = 0, a[n+1] = -1.
        - Then define nex[i][j] = p means a[p] = j and p > i and p-i min, pre[i][j] = p means a[p] = j
        and p < j and j-p min
        - Now, we are going to use dp to solve, define dp[l][r][k] = the diversity number of the sequence
        starting from l, ending at r and we have picked k numbers. Result would be dp[0][n+1][0]
        - Only count when a[l] > a[r] as we try to separate the left side and the right side of the sequence
        by that condition and that's why a[n+1] = -1.
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

int n, a[MAXN], nex[MAXN][MAXN], pre[MAXN][MAXN];
ll dp[MAXN][MAXN][MAXN];

ll solve(int l, int r, int k) {
    if (l > r) return 0;
    if (dp[l][r][k] != -1) return dp[l][r][k];
    ll res = 0;
    if (a[l] > a[r]) res = 1;
    // a[r]+1 as we want to make it count when getting the left sequence
    // no worries about i-k < 0 sometimes as there would be i-k = 0 previously
    FOR(i, max(a[l], a[r]+1), 100) res = (res + (ll) (i - k) * solve(nex[l][i], r, k+1)) % MODBASE;
    // getting right sequence
    FOR(i, max(a[l], a[r]), 100) res = (res + (ll) (i - k) * solve(l, pre[r][i], k+1)) % MODBASE;
    return dp[l][r][k] = res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n;
        FOR(i,1,n) cin >> a[i];
        MS(dp, -1);
        a[0] = 0; a[n+1] = -1;
        FOR(i,0,n+1) {
            FOR(j,0,100) {
                nex[i][j] = n+2;
                FOR(k,i+1,n+1)
                    if (a[k] == j) { nex[i][j] = k; break; }
            }
            FOR(j,0,100) {
                pre[i][j] = -2;
                FORE(k,i-1,0)
                    if (a[k] == j) { pre[i][j] = k; break; }
            }
        }
        cout << solve(0, n+1, 0) << "\n";
    }
    return 0;
}
