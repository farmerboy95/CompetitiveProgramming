/*
    Author: Nguyen Tan Bao
    Status: AC after reading code
    Origin: https://oj.uz/submission/37754
    Idea: 
        - Let dp[p][u][K] is the minimum length that we need to find in the subtree of u, choosing K nodes
        p = 0 means we are not going to finish the journey in this subtree, otherwise p = 1
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
#define WHATIS(x) cout << #x << " is " << x << endl;
#define ERROR(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
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

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll MODBASE = 1000000007LL;
const int MAXN = 10010;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, k, dp[2][MAXN][MAXN], num[MAXN];
vector<II> a[MAXN];

void dfs(int u, int p) {
    dp[0][u][1] = dp[1][u][1] = 0;
    num[u] = 1;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i].FI;
        int c = a[u][i].SE;
        if (v == p) continue;
        dfs(v, u);
        FORE(j,num[u],0)
            FORE(p,num[v],1) {
                dp[0][u][j+p] = min(dp[0][u][j+p], dp[0][u][j] + dp[0][v][p] + 2 * c);
                dp[1][u][j+p] = min(dp[1][u][j+p], dp[1][u][j] + dp[0][v][p] + 2 * c);
                dp[1][u][j+p] = min(dp[1][u][j+p], dp[0][u][j] + dp[1][v][p] + c);
            }
        num[u] += num[v];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int x;
    cin >> n >> k >> x;
    FOR(i,1,n-1) {
        int u, v, c;
        cin >> u >> v >> c;
        a[u].emplace_back(II(v, c));
        a[v].emplace_back(II(u, c));
    }
    FOR(p,0,1) FOR(i,1,n) FOR(j,1,n) dp[p][i][j] = 1000000000;
    dfs(x, 0);
    cout << dp[1][x][k];
    return 0;
}
