/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/hackercup/problem/100623926681599/
    Status: AC
    Idea:
        - We are going to calculate the number of ways one's correct guess is exactly k. Call it res[k]
        - So res[k] = c[n][k] * g[n-k]
        - As C[n][k] = nCk, g[i] = number of ways to have no correct guess if we have i glasses of wine.
        - How can we calculate g[i]? Using the inclusion-exclusion principle, g[i] = i! - p[1] + p[2] - p[3] + ...
        with p[j] = the number of ways that we have at least j correct guesses.
        - There are C[i][j] ways to choose those j positions. Then, it doesn't matter what we put in 
        the remaining positions, we have (i-j)! ways to rearrange the remaining numbers.
        - After getting all res[k] (m <= k <= n), get sum of them and print the result.
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

ll MOD = 1051962371;
ll c[MAXN][MAXN], f[MAXN], g[MAXN];

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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t, n, m;

    FOR(i,0,100) FOR(j,0,i)
        if (j == 0 || j == i) c[i][j] = 1;
        else c[i][j] = add(c[i-1][j-1], c[i-1][j]);

    f[0] = 1;
    FOR(i,1,100) f[i] = mul(f[i-1], i);

    g[0] = 1;
    FOR(i,1,100) {
        g[i] = f[i];
        FOR(j,1,i) {
            ll p = mul(c[i][j], f[i-j]);
            if (j % 2) g[i] = sub(g[i], p);
            else g[i] = add(g[i], p);
        }
    }

    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n >> m;
        ll res = 0;
        FOR(i,m,n) res = add(res, mul(c[n][i], g[n-i]));
        cout << res << "\n";
    }
    return 0;
}
