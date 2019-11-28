/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://codeforces.com/blog/entry/71805
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
const int MAXN = 300010;
const int MAXM = 30010;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN], k, sum[30];
ll dp[30][MAXN];

ll solve(int cnt, int pos) {
    if (dp[cnt][pos] != -1) return dp[cnt][pos];
    ll res = 1e18;
    if (a[pos] == -1) return 0;
    int remain = sum[cnt] - pos;

    if (cnt < k) res = min(res, solve(cnt+1, pos+1)) + a[pos];
    if (remain) res = min(res, solve(cnt, pos+1));

    return dp[cnt][pos] = res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,0,n-1) cin >> a[i];
    reverse(a, a+n);

    for (int i = 1; i < n; i *= 2, k++);

    for (int i = 1, x = n/2; i <= k; i++, x /= 2) sum[i] = sum[i-1] + x;

    MS(dp, -1);
    cout << solve(0, 0);
    return 0;
}
