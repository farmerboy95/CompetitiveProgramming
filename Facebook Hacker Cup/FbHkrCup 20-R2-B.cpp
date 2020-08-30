/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/codingcompetitions/hacker-cup/2020/round-2/problems/B
    Status: AC
    Idea:
        - Let dp[i][j] is the expected number of matches which will occur if we have a total of 
        i players before player j get eliminated.
        - So let's imagine the situation like this: (1) 2 (3)
            + 2 is our player j
            + (1) is the group of players less skilled than j
            + (3) is the group of players more skilled than j
        - So for a match here, there would be 5 cases:
            + 1. 2 players in group 1
            + 2. 1 player in group 1 and j
            + 3. 1 player in group 1 and 1 player in group 3
            + 4. 1 player in group 3 and j
            + 2. 2 players in group 3

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
typedef pair<ll, ll> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 8010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n;
ld p, dp[MAXN][MAXN];

void input() {
    cin >> n >> p;
}

void init() {
    FOR(i,1,n)
        FOR(j,1,n) dp[i][j] = -1;
}

ld handle(int u, int v) {
    if (v > u || v < 1) return 0;
    if (dp[u][v] >= 0) return dp[u][v];
    if (u == 1) return dp[u][v] = 0;

    ld res = 0;
    int lef = v - 1, rig = u - v;
    int w = u * (u - 1) / 2;
    ld c1 = (ld) lef * (lef - 1) / 2 / w;
    ld c2 = (ld) lef / w;
    ld c3 = (ld) lef * rig / w;
    ld c4 = (ld) rig / w;
    ld c5 = (ld) rig * (rig - 1) / 2 / w;

    // case 1: 1 1
    res += c1 * (1 + handle(u-1, v-1));

    // case 2: 1 2
    res += c2 * (1 + p * handle(u-1, v-1));

    // case 3: 1 3
    res += c3 * (1 + p * handle(u-1, v-1) + (1-p) * handle(u-1, v));

    // case 4: 2 3
    res += c4 * (1 + (1-p) * handle(u-1, v));

    // case 5: 3 3
    res += c5 * (1 + handle(u-1, v));

    return dp[u][v] = res;
}

void solve() {
    init();
    FOR(i,1,n) handle(n, i);
    FOR(i,1,n) cout << fixed << setprecision(9) << dp[n][i] << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case #" << o << ":\n";
        input();
        solve();
    }
    return 0;
}
