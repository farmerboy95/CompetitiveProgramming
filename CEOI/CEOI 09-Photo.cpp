/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Same as editorial:
        https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/CEOI/official/2009/solutions-converted.pdf
        https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/CEOI/official/2009/codes-from-web/ceoi09_photo.cpp
        - Comments in implementation
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
const int MAXM = 200010;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a, dp[MAXN][MAXN][MAXN], N, pos[MAXM];
map<int, int> ma;
II b[MAXN];

int getH(int l, int r) {
    return a / max(1, b[r].FI - b[l].FI);
}

// now we dp based on 3 lines, 2 vertical lines are left and right borders
// and one horizontal line, now we count the minimum number of rectangles 
// that can be placed inside the border (inclusive) and above the horizontal line (exclusive)
int solve(int l, int r, int x) {
    if (l > r) return 0;
    // use pos[x] instead of x because if we consider x+1 that there are no points that have y = x+1 then
    // the result would still be the same, this would reduce the number of states.
    if (dp[l][r][pos[x]] != -1) return dp[l][r][pos[x]];
    // some special cases
    if (b[l].SE <= x) return dp[l][r][pos[x]] = solve(l+1, r, x);
    if (b[r].SE <= x) return dp[l][r][pos[x]] = solve(l, r-1, x);
    int res = 1000000000;
    // now there is at least one point that is higher than x inside (l,r), it could be in either left or right border
    // place a rectangle that cover the whole [l,r] there
    if (pos[getH(l,r)] > pos[x]) res = min(res, solve(l, r, getH(l,r)) + 1);
    // otherwise, just divide the segment and continue to find
    FOR(i,l,r-1) res = min(res, solve(l,i,x) + solve(i+1,r,x));
    return dp[l][r][pos[x]] = res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> a;
    FOR(i,1,n) {
        int x, y;
        cin >> x >> y;
        // only care about highest y at each x, because when we cover highest y of an x
        // we also cover the lower y of that x
        ma[x] = max(ma[x], y);
    }
    // init dp
    MS(dp, -1);
    // recreate new array b with distinct x and the highest y of each x
    // pos[i] = 1 means that there is a point with y = i
    FORALL(it, ma) {
        b[++N] = *it;
        pos[it->SE] = 1;
    }
    // now pos[i] = number of y <= i that there is at least a point
    FOR(i,1,a) pos[i] += pos[i-1];
    cout << solve(1,N,0);
    return 0;
}
