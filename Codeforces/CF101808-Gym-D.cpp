/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Mainly from https://codeforces.com/blog/entry/59696
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
const int MAXN = 20;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ld dp[MAXN][1<<18], res[MAXN][110], p;
int num[1<<18];

ld solve(int active, int mask) {
    // if we place a number that is larger than the immediate number on the left, the whole
    // part of the left side of it will become inactive as they never merge, so we don't need
    // to keep track of them.
    // let dp[active][mask] = the expected score when we start with an "active" number of active
    // cells, with "mask" contains strictly decreasing sequence of powers from left to right (as
    // each power will appear once in the active cells, if a power appears more than once, they
    // would be merged)
    if (num[mask] >= active) return 0;
    if (dp[active][mask] >= 0) return dp[active][mask];

    // adding 2
    dp[active][mask] = (1-p) * (solve(active, mask + 2) + (mask ^ (mask + 2)) - 2);

    // adding 4 
    if (mask & 2) dp[active][mask] += p * solve(active - num[mask], 4);
    else dp[active][mask] += p * (solve(active, mask + 4) + (mask ^ (mask + 4)) - 4);

    return dp[active][mask];
}

void init() {
    FOR(mask,0,(1<<18)-1) num[mask] = __builtin_popcount(mask);
    FOR(i,0,100) {
        p = i / 100.0;
        FOR(active,1,16) FOR(mask,0,(1<<18)-1) dp[active][mask] = -1;
        FOR(active,1,16) res[active][i] = solve(active, 0);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    init();
    int t;
    cin >> t;
    while (t--) {
        int n, p;
        cin >> n >> p;
        cout << fixed << setprecision(9) << res[n][p] << "\n";
    }
    return 0;
}
