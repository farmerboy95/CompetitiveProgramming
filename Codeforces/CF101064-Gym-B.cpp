/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - More or less like: https://linux.ime.usp.br/~yancouto/2016-WIP-Tutorial.pdf
        - More comments in code
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
const int MAXN = 61;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ll MOD = MODBASE;
int n;
ll dp[MAXN][MAXN][MAXN][MAXN][2];

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

// Let B[i] is the smallest selected number that can be the ith number of an increasing sequence
// let dp[a1][a2][a3][a4] is the number of permutations with LIS 3 or 4 where:
// a1: number of unselected numbers of the permutation that are smaller than B[1]
// a2: number of unselected numbers of the permutation that are smaller than B[2] but larger than B[1]
// a3: number of unselected numbers of the permutation that are smaller than B[3] but larger than B[2]
// a4: number of unselected numbers of the permutation that are smaller than B[4] but larger than B[3]
// we don't need a5 because we simply don't need LIS with size larger than 4
// use one more param ok to add those with LIS 3 or 4 only (not counting 1 or 2)
ll solve(int a1, int a2, int a3, int a4, int ok) {
    if (a1 + a2 + a3 + a4 == 0) return ok ? 1 : 0;
    if (dp[a1][a2][a3][a4][ok] != -1) return dp[a1][a2][a3][a4][ok];
    ll res = 0;
    FOR(i,1,a1) res = add(res, solve(i-1, a2 + a1 - i, a3, a4, ok));
    FOR(i,1,a2) res = add(res, solve(a1, i-1, a3 + a2 - i, a4, ok));
    FOR(i,1,a3) res = add(res, solve(a1, a2, i-1, a4 + a3 - i, 1));
    // we must take the largest number here because if not, the largest one would be chosen 
    // in some other iteration and eventually we would have a permutation with LIS = 5
    if (a4 > 0) res = add(res, solve(a1, a2, a3, a4-1, 1));
    return dp[a1][a2][a3][a4][ok] = res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    MS(dp, -1);
    ll res = 1;
    FOR(i,1,n) res = mul(res, i);
    // res = n! - (number of permutations with LIS 3 or 4)
    res = sub(res, solve(n,0,0,0,0));
    cout << res;
    return 0;
}
