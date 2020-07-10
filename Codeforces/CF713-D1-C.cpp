/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let a[i] = a[i] - i, then we just have to make the sequence non-decreasing instead of 
        strictly increasing.
        - Then do like problem C in this editorial: https://codeforces.com/blog/entry/364
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
const int MAXN = 5010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN], b[MAXN];
ll dp[MAXN][MAXN];

ll solve(int u, int v) {
    if (dp[u][v] != -1) return dp[u][v];
    ll res = 0;
    if (u == 1 && v == 1) res = abs(a[u] - b[v]);
    else if (u == 1) res = min((ll) abs(a[u] - b[v]), solve(u, v-1));
    else if (v == 1) res = solve(u-1, v) + (ll) abs(a[u] - b[v]);
    else res = min(solve(u, v-1), solve(u-1, v) + abs(a[u] - b[v]));
    return dp[u][v] = res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n) {
        a[i] -= i;
        b[i] = a[i];
    }
    MS(dp, -1);
    sort(b+1, b+n+1);
    cout << solve(n, n);
    return 0;
}
