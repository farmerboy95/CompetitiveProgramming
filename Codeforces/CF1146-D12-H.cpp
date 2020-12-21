/*
    Author: Nguyen Tan Bao
    Status: AC 
    Idea:
        - https://codeforces.com/blog/entry/66639?#comment-506612
        - The goal is to find the number of convex pentagons (can be seen with some draft). 
        We will do this through constructive DP. Take all directed segments between points 
        and sort them by angle. Then, maintain array dp[i][j][k], the number of polylines that 
        start at vertex i, end at vertex j, contain k segments, and only make clockwise turns. 
        Loop over each directed segment in order and update the DP array accordingly. Each 
        pentagon has exactly one traversal that satisfies the above constraints, so the answer 
        is just the sum of all dp[i][i][5].
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
typedef pair<ld, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 310;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, x[MAXN], y[MAXN];
ll dp[MAXN][MAXN][6];
vector<III> v;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> x[i] >> y[i];

    FOR(i,1,n)
        FOR(j,1,n)
            if (i != j) {
                int X = x[j] - x[i];
                int Y = y[j] - y[i];
                v.push_back(III(atan2(Y, X), II(i, j)));
            }
    
    sort(ALL(v));

    FOR(i,1,n)
        FOR(j,1,n) {
            FOR(k,0,5) dp[i][j][k] = 0;
            if (i == j) dp[i][j][0] = 1;
        }

    for (III w : v) {
        int u = w.SE.FI, v = w.SE.SE;
        FOR(i,1,n)
            FOR(j,0,4) dp[i][v][j+1] += dp[i][u][j];
    }
    ll res = 0;
    FOR(i,1,n) res += dp[i][i][5];
    cout << res;
    return 0;
}
