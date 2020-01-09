/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let dp[t][i][j] is the probability that A[i] > A[j] after t operations.
        - dp[0][i][j] can be retrieved using O(n^2) iteration.
        - For each operation, only O(n) pairs (i, j) change its probability
        => Complexity O(n^2 + nq)
        - At the end, we have the probability of each pair, get pairs (i, j) which i < j
        and multiply its probability by 2^q, that would be the number of times A[i] > A[j]
        in all situations.
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

int n, q, a[MAXN];
ll dp[MAXN][MAXN];

ll binPowMod(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % m;
        a = a * a % m;
        b >>= 1LL;
    }
    return res;
}

ll mul(ll a, ll b) {
    return a * b % MODBASE;
}

ll add(ll a, ll b) {
    return (a + b) % MODBASE;
}

ll sub(ll a, ll b) {
    return (a - b + MODBASE) % MODBASE;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> q;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n)
        FOR(j,1,n)
            if (a[i] > a[j]) dp[i][j] = 1;
    ll inv2 = binPowMod(2, MODBASE-2, MODBASE);
    FOR(i,1,q) {
        int l, r;
        cin >> l >> r;
        FOR(x,1,n) {
            if (x == l || x == r) continue;
            dp[l][x] = dp[r][x] = mul(inv2, add(dp[l][x], dp[r][x]));
            dp[x][l] = dp[x][r] = mul(inv2, add(dp[x][l], dp[x][r]));
        }
        dp[l][r] = dp[r][l] = mul(inv2, add(dp[l][r], dp[r][l]));
    }

    ll p = binPowMod(2, q, MODBASE), res = 0;
    FOR(i,1,n)
        FOR(j,i+1,n) {
            dp[i][j] = mul(dp[i][j], p);
            res = add(res, dp[i][j]);
        }
    cout << res;
    return 0;
}
