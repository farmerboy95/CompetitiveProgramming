/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Although the coordinates ranging from -10^9 to 10^9, there are at most 3000 different Xs and 
        3000 different Ys => There are at most O(n^2) blocks dividing the planes.
        - Our job now is to find the starting block, and create walls between blocks, then we bfs/dfs from
        starting block to see if we can reach the outer blocks of the plane. If we can reach outer blocks,
        the result would simply be INF, otherwise, we can calculate the total area depending on the area
        of visited blocks.
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
const int MAXN = 4010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, a[MAXN], b[MAXN], c[MAXN], d[MAXN], e[MAXN], f[MAXN];
int ban[MAXN][MAXN][4], vis[MAXN][MAXN];
vector<int> X, Y;
int dx[4] = {-1,0,0,1};
int dy[4] = {0,1,-1,0};

void bfs(int x, int y) {
    queue<II> q;
    q.push(II(x, y));
    vis[x][y] = true;
    while (SZ(q)) {
        int u = q.front().FI, v = q.front().SE;
        q.pop();
        FOR(i,0,3) {
            if (ban[u][v][i]) continue;
            int g = u + dx[i], h = v + dy[i];
            if (g >= 0 && g <= SZ(X) && h >= 0 && h <= SZ(Y))
                if (!vis[g][h]) {
                    vis[g][h] = true;
                    q.push(II(g, h));
                }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) {
        cin >> a[i] >> b[i] >> c[i];
        X.push_back(a[i]);
        X.push_back(b[i]);
        Y.push_back(c[i]);
    }
    FOR(i,1,m) {
        cin >> d[i] >> e[i] >> f[i];
        X.push_back(d[i]);
        Y.push_back(e[i]);
        Y.push_back(f[i]);
    }
    sort(ALL(X));
    sort(ALL(Y));
    X.resize(unique(ALL(X)) - X.begin());
    Y.resize(unique(ALL(Y)) - Y.begin());
    int x = lower_bound(ALL(X), 0) - X.begin();
    int y = lower_bound(ALL(Y), 0) - Y.begin();
    FOR(i,1,n) {
        int aa = lower_bound(ALL(X), a[i]) - X.begin();
        int bb = lower_bound(ALL(X), b[i]) - X.begin();
        int cc = lower_bound(ALL(Y), c[i]) - Y.begin();
        FOR(j,aa+1,bb) ban[j][cc][1] = ban[j][cc+1][2] = true;
    }
    FOR(i,1,m) {
        int dd = lower_bound(ALL(X), d[i]) - X.begin();
        int ee = lower_bound(ALL(Y), e[i]) - Y.begin();
        int ff = lower_bound(ALL(Y), f[i]) - Y.begin();
        FOR(j,ee+1,ff) ban[dd][j][3] = ban[dd+1][j][0] = true;
    }
    bfs(x, y);
    FOR(i,0,SZ(X)) 
        if (vis[i][0] || vis[i][SZ(Y)]) {
            cout << "INF";
            return 0;
        }
    FOR(i,0,SZ(Y))
        if (vis[0][i] || vis[SZ(X)][i]) {
            cout << "INF";
            return 0;
        }
    ll res = 0;
    FOR(i,1,SZ(X)-1)
        FOR(j,1,SZ(Y)-1)
            if (vis[i][j]) res += (ll) (X[i] - X[i-1]) * (Y[j] - Y[j-1]);
    cout << res;
    
    return 0;
}
