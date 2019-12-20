/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let Xi (1 <= i <= n) = number of times you take out the joker in one shuffle (Xi = 0 or 1)
        - Let X = X1 + X2 + ... + Xn
        => Result = E(X^K) 
                  = E((X1 + X2 + ... + Xn) ^ K)
                  = E((X1 + X2 + ... + Xn) * (X1 + X2 + ... + Xn) * ... * (X1 + X2 + ... + Xn)) (K times)
        - At the end we would have something like this
        - E(X^K) = E(Xi^a * Xj^b * Xp^c ... + ...)
                 = E(Xi^a * Xj^b * Xp^c ...) + E(...)
                 = E(Xi^a) * E(Xj^b) * E(Xp^c) * E(...) + E(...) (because Xi and Xj are independent)
        - We have E(Xi) = 1/m * 1 + (m-1)/m * 0 = 1/m (easily prove)
        => E(Xi^a) = 1/m * 1^a + (m-1)/m * 0^a = 1/m = E(Xi)
        => E(X^K) = sum((1/m)^x * C[x])
        - We need to count the number of group (Xi * Xj * Xp ...) (length K) with x distinct Xi
        - Use dp[i][j] is the number of sequences of length i with j distinct values
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
typedef pair<II, ll> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 5010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ll MOD = 998244353;

ll add(ll a, ll b) {
    return (a+b) % MOD;
}

ll sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

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

ll inv(ll a) {
    return binPowMod(a, MOD-2, MOD);
}

int n, m, k;
ll dp[MAXN][MAXN];
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    dp[1][1] = n;
    FOR(i,1,k-1) {
        FOR(j,1,min(n, k)) {
            dp[i+1][j] = add(dp[i+1][j], mul(dp[i][j], j));
            dp[i+1][j+1] = add(dp[i+1][j+1], mul(dp[i][j], n-j));
        }
    }
    ll p = inv(m);
    ll res = 0;
    FOR(i,1,k) res = add(res, mul(dp[k][i], binPowMod(p, i, MOD)));
    cout << res;
    return 0;
}