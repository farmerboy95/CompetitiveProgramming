/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let dp[u][k] is the maximum number of apples when we need to preserve k edges on the subtree of u
        - This tree is a binary tree
        - Complexity O(n * q * q)
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
const int MAXN = 110;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, q, dp[MAXN][MAXN];
vector<II> a[MAXN];

int solve(int u, int p, int q) {
    if (q <= 0) return 0;
    if (dp[u][q] != -1) return dp[u][q];
    // x, y are 2 direct child node of u (they are just indexes in a[u] array)
    int x = -1, y = -1;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i].FI;
        if (v == p) continue;
        if (x == -1) x = i;
        else y = i;
    }
    if (x == -1) return dp[u][q] = 0;
    int vX = a[u][x].FI;
    int cX = a[u][x].SE;
    int vY = a[u][y].FI;
    int cY = a[u][y].SE;
    int res = 0;
    // calculate the maximum number of apples
    FOR(k,0,q) {
        int lef = solve(vX, u, k-1);
        if (k > 0) lef += cX;
        int rig = solve(vY, u, q-k-1);
        if (k < q) rig += cY;
        res = max(res, lef + rig);
    }
    return dp[u][q] = res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> q;
    FOR(i,1,n-1) {
        int u, v, c;
        cin >> u >> v >> c;
        a[u].emplace_back(II(v, c));
        a[v].emplace_back(II(u, c));
    }
    FOR(i,1,n)
        FOR(j,0,q) dp[i][j] = -1;
    cout << solve(1, 0, q);
    return 0;
}
