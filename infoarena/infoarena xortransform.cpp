/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use brute force to see that result after k transformations = xor sum of a[i][j] that (i | j | k) == k
        - One more thing is that if k >= min(2^x) (2^x >= n, m) then we can reduce it to k &= min(2^x) - 1 (use brute force to observe)
        - Use DP SOS to solve
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
const int MAXN = 100010;
const int MAXM = 30010;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, q, dp[5000000];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("xortransform.in", "r", stdin);
    freopen("xortransform.out", "w", stdout);
    cin >> n >> m >> q;
    FOR(i,0,n-1)
        FOR(j,0,m-1) {
            int x;
            cin >> x;
            dp[i|j] ^= x;
        }

    int Max = 1;
    while (Max < n || Max < m) Max <<= 1;

    FOR(i,0,21)
        FOR(mask,0,(1<<22)-1)
            if (mask & (1<<i)) dp[mask] ^= dp[mask ^ (1<<i)];

    int pre = 0;
    while (q--) {
        int x;
        cin >> x;
        x ^= pre;
        x &= Max-1;

        pre = dp[x];
        cout << pre << "\n";
    }
    return 0;
}
