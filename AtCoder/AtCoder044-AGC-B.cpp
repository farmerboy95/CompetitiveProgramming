/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Same as the editorial: https://img.atcoder.jp/agc044/editorial.pdf
        - Let h[i][j] is the minimum length of path from cell (i, j) to the side of the square.
        - Let g[i][j] = 0 if there is no viewer sitting at cell (i, j), otherwise = 1.
        - After adding h[x][y] to result and remove viewer at cell (x, y), we dfs from (x, y)
        to update array h, as the new h[i][j] will be <= the old h[i][j] and initially, sum of
        all h[i][j] <= N^3 / 6, dfs will update the cell (i, j) that has new h[i][j] < old h[i][j].
        Then the total number of updates will be O(N^3)
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
const int MAXN = 510;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, h[MAXN][MAXN], g[MAXN][MAXN];
int dx[4] = {1,0,0,-1};
int dy[4] = {0,1,-1,0};

void dfs(int x, int y) {
    int k = h[x][y] + g[x][y];
    FOR(i,0,3) {
        int u = x + dx[i], v = y + dy[i];
        if (u >= 1 && u <= n && v >= 1 && v <= n && k < h[u][v]) {
            h[u][v] = k;
            dfs(u, v);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;

    FOR(i,1,n)
        FOR(j,1,n) {
            h[i][j] = min(min(i, n+1-i), min(j, n+1-j)) - 1;
            g[i][j] = 1;
        }

    int res = 0;
    FOR(i,1,n*n) {
        int w;
        cin >> w;
        int x, y;
        if (w % n == 0) {
            x = w / n;
            y = n;
        }
        else {
            x = w / n + 1;
            y = w % n;
        }
        res += h[x][y];
        g[x][y] = 0;
        dfs(x, y);
    }
    cout << res;
    return 0;
}
