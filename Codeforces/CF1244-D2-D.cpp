/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Each node must have less than 3 adjacent nodes to form a good painting, easy to prove.
        - So that the tree could become an array of number.
        - Let dp[i][j][k] is the minimum cost to form a good painting, considering first i nodes, 
        using color k for node i and color j for the previous node of node i (j != k)
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
const int MAXN = 100010;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, c[MAXN][3], kq[MAXN];
vector<int> a[MAXN];
vector<int> b;
ll dp[MAXN][3][3];
int trace[MAXN][3][3];
vector<int> res;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(j,0,2)
        FOR(i,1,n) cin >> c[i][j];
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        a[u].emplace_back(v);
        a[v].emplace_back(u);
    }
    FOR(i,1,n)
        if (SZ(a[i]) >= 3) {
            cout << -1;
            return 0;
        }
    int fi = -1;
    FOR(i,1,n)
        if (SZ(a[i]) == 1) {
            fi = i;
            break;
        }
    // reform the tree into an array of number b
    b.emplace_back(fi);
    while (SZ(b) != n) {
        int u = b[SZ(b)-1];
        FOR(i,0,SZ(a[u])-1) {
            int v = a[u][i];
            if (SZ(b) >= 2) {
                if (v == b[SZ(b)-2]) continue;
            }
            b.emplace_back(v);
            break;
        }
    }
    // dp on array b
    FOR(i,0,2)
        FOR(j,0,2)
            if (i != j) dp[1][i][j] = c[b[0]][i] + c[b[1]][j];
            else dp[1][i][j] = 1e18;
    FOR(i,2,SZ(b)-1)
        FOR(j,0,2)
            FOR(k,0,2) dp[i][j][k] = 1e18;
    FOR(i,1,SZ(b)-2)
        FOR(j,0,2)
            FOR(k,0,2)
                if (j != k) {
                    int add = 3 - j - k;
                    if (dp[i][j][k] + c[b[i+1]][add] < dp[i+1][k][add]) {
                        dp[i+1][k][add] = dp[i][j][k] + c[b[i+1]][add];
                        trace[i+1][k][add] = j;
                    }
                }
    // get the result
    ll Min = 1e18;
    int g = -1, h = -1;
    FOR(i,0,2)
        FOR(j,0,2)
            if (i != j)
                if (dp[SZ(b)-1][i][j] < Min) {
                    Min = dp[SZ(b)-1][i][j];
                    g = i;
                    h = j;
                }
    cout << Min << "\n";
    res.emplace_back(h);
    res.emplace_back(g);
    FORE(i,SZ(b)-1,2) {
        int k = trace[i][g][h];
        h = g;
        g = k;
        res.emplace_back(g);
    }
    reverse(ALL(res));
    FORE(i,SZ(res)-1,0) {
        int u = b[i];
        kq[u] = res[i] + 1;
    }
    FOR(i,1,n) cout << kq[i] << ' ';
    return 0;
}
