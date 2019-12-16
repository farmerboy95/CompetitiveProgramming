/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - If there is a portal from u to v (u > v) and there is a portal from p to v (p > v),
        we should send a soldier to v from max(u, p) because the soldier would go to v anyway,
        it's better to keep him to go the largest node (we need soldiers to conquer castles from
        u to p or p to u)
        - Let Max[i] is the furthest node u from i that there is a portal from u to i
        - For each node u, get list of nodes v that Max[v] = u, sort them from the largest c[] to the smallest 
        (O(n) elements totally)
        - Now we can use dp[i][j] with i is the node now and j is the number of soldiers remaining.
        - Complexity O(n^2)
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
const int MAXN = 5010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, k, a[MAXN], b[MAXN], c[MAXN], Max[MAXN];
vector<II> d[MAXN];
int dp[MAXN][MAXN];

int solve(int u, int num) {
    if (num < 0) return -1;
    if (dp[u][num] != -2) return dp[u][num];
    if (num < a[u]) return dp[u][num] = -1;
    int res = 0;
    bool hasRes = false;
    if (u < n) {
        int nex = solve(u+1, num+b[u]);
        if (nex != -1) {
            res = nex;
            hasRes = true;
        }
    }
    int sum = 0;
    // this part is O(n^2) globally
    FOR(i,0,SZ(d[u])-1) {
        int p = d[u][i].FI;
        sum += p;
        int nex = 0;
        if (u < n) nex = solve(u+1, num-(i+1)+b[u]);
        if (nex == -1) continue;
        res = max(res, sum + nex);
        hasRes = true;
    }
    if (!hasRes) res = -1;
    return dp[u][num] = res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    FOR(i,1,n) {
        cin >> a[i] >> b[i] >> c[i];
        Max[i] = i;
    }
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        Max[v] = max(Max[v], u);
    }
    FOR(i,1,n) {
        int u = Max[i];
        d[u].emplace_back(II(c[i], i));
    }

    FOR(i,1,n) {
        sort(ALL(d[i]));
        reverse(ALL(d[i]));
    }
    FOR(i,1,n)
        FOR(j,0,5000) dp[i][j] = -2;
    cout << solve(1, k);
    return 0;
}
