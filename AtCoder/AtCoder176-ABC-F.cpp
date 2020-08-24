/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - More or less like: https://codeforces.com/blog/entry/81776?#comment-685113
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
const int MAXN = 6010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN], dp[MAXN][MAXN], last[MAXN], nex[MAXN], res;

int getCost(int x, int y, int z) {
    return a[x] == a[y] && a[y] == a[z];
}

void transition(int i, int j, int pos) {
    if (pos > 3*n) return;
    if (pos == 3*n) {
        res = max(res, dp[i][j] + getCost(i, j, pos));
        return;
    }
    // 5C2 = 10 but we don't go with the case of choosing i, j because dp[i][j] would still
    // be the same as we removed all equal groups.

    // choose 1 of the remaining 9 ways
    dp[pos + 0][pos + 1] = max(dp[pos + 0][pos + 1], dp[i][j] + getCost(i, j, pos + 2));
    dp[pos + 0][pos + 2] = max(dp[pos + 0][pos + 2], dp[i][j] + getCost(i, j, pos + 1));
    dp[pos + 1][pos + 2] = max(dp[pos + 1][pos + 2], dp[i][j] + getCost(i, j, pos + 0));
    
    dp[i][pos + 0] = max(dp[i][pos + 0], dp[i][j] + getCost(j, pos + 1, pos + 2));
    dp[i][pos + 1] = max(dp[i][pos + 1], dp[i][j] + getCost(j, pos + 0, pos + 2));
    dp[i][pos + 2] = max(dp[i][pos + 2], dp[i][j] + getCost(j, pos + 0, pos + 1));
    
    dp[j][pos + 0] = max(dp[j][pos + 0], dp[i][j] + getCost(i, pos + 1, pos + 2));
    dp[j][pos + 1] = max(dp[j][pos + 1], dp[i][j] + getCost(i, pos + 0, pos + 2));
    dp[j][pos + 2] = max(dp[j][pos + 2], dp[i][j] + getCost(i, pos + 0, pos + 1));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,3*n) cin >> a[i];
    FOR(i,1,3*n) FOR(j,1,3*n) dp[i][j] = -1e9;
    dp[1][2] = 0;
    
    // remove equal groups of three
    int equalGroup = 0;
    bool change = true;
    while (change) {
        change = false;
        for (int i = 3; i + 2 <= 3 * n; i += 3)
            if (a[i] == a[i+1] && a[i+1] == a[i+2]) {
                equalGroup++;
                FOR(j,i+3,3*n) a[j-3] = a[j];
                n--;
                change = true;
                break;
            }
    }

    // nex[i] = j means the nearest to the right a[j] == a[i]
    FOR(i,1,3*n) last[i] = 3*n+1;
    FORE(i,3*n,1) {
        nex[i] = last[a[i]];
        last[a[i]] = i;
    }

    FOR(i,1,3*n)
        FOR(j,i+1,3*n) {
            // proceed next immediate group
            transition(i, j, (j+3) / 3 * 3);
            // find the next occurrence of the first (or second) card type and transition to that 
            // group of three, ignoring the groups in between
            // The intuition behind this transition is that we decided to keep the first (or second) 
            // card type for future points, so we can ignore all groups not containing it.
            if (j / 3 * 3 < nex[i] / 3 * 3) transition(i, j, nex[i] / 3 * 3);
            if (j / 3 * 3 < nex[j] / 3 * 3) transition(i, j, nex[j] / 3 * 3);
        }

    cout << res + equalGroup;
    return 0;
}
