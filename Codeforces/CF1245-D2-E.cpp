/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use basic dp top down
        - Let dp[i][j] = expected number of step needed to finish the game
        - At a specific state (i, j), just consider all cases of dice number, let it be u
            + if u > distance from (i, j) to (1, 1), increase number t (init t = 0) and leave it there
            + otherwise, move (i, j) to new position, if that new position contains bottom of a ladder,
            we should calculate min(dp[new pos], dp[climb ladder]) as player will choose optimally, then
            res += (1 + min) / 6. If that new position does not contain bottom of a ladder, res += (1 + dp[new pos]) / 6
            + now we would have dp[i][j] = res + t / 6 * (1 + dp[i][j]), as we must stay when u > distance
            => dp[i][j] = (t + res * 6) / (6 - t)
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
const int MAXN = 2010;
const int MAXM = 10010;
const int MAXK = 110;
const int MAXQ = 200010;
 
int a[11][11], dist[11][11], d[11]; 
ld dp[11][11];
 
inline int cmp(ld a, ld b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}
 
II move(int i, int j, int u) {
    while (u) {
        if (!d[i]) {
            if (j == 10) i--;
            else j++;
        }
        else {
            if (j == 1) i--;
            else j--;
        }
        u--;
    }
    return II(i, j);
}
 
ld solve(int i, int j) {
    if (i == 1 && j == 1) return 0;
    if (cmp(dp[i][j], -1) != 0) return dp[i][j];
 
    ld res = 0;
    int t = 0;
 
    FOR(u,1,6) {
        if (u > dist[i][j]) t++;
        else {
            II r = move(i,j,u);
            if (!a[r.FI][r.SE]) res += 1.0 * (1 + solve(r.FI, r.SE)) / 6;
            else {
                ld x = solve(r.FI, r.SE);
                ld y = solve(r.FI - a[r.FI][r.SE], r.SE);
                res += 1.0 * (1 + min(x, y)) / 6;
            }
        }
    }
 
    if (t) res = (t + res * 6) / (6 - t);
    return dp[i][j] = res;
}
 
void init() {
    int dir = 0;
    int cnt = -1;
    FOR(i,1,10) {
        dir = 1-dir;
        d[i] = dir;
        if (dir) {
            FOR(j,1,10) dist[i][j] = ++cnt;
        }
        else {
            FORE(j,10,1) dist[i][j] = ++cnt;
        }
    }
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    FOR(i,1,10) FOR(j,1,10) cin >> a[i][j];
    FOR(i,1,10) FOR(j,1,10) dp[i][j] = -1;
    init();
    cout << fixed << setprecision(9) << solve(10, 1);
    return 0;
}