/*
    Author: Nguyen Tan Bao
    Status: AC
    Statement:
        - Given N and K (3 <= K <= N <= 250)
        - Find the number of graphs that have these attributes:
            + Graph has N vertices
            + All vertices are different
            + The graph may have several connected components
            + Each connected component should have the number of edges = number of vertices (within that component)
            + Sizes of cycles in the graph should be at least K
    Idea:
        - As each component of size S has S edges, the cycle in this component is just simple cycle
        - Firstly, we calculate these values:
            + Number of trees which have size X (Cayley's formula:) = X ^ (X-2)
            + Binomial coefficient C[n][k] = n! / ((n-k)! * k!)
            + Number of simple cycles of size X: P[X] = P[X-1] * (X-1), P[3] = 1 (just put new value between 2 old adjacent values in old cycle)
            + Number of graphs which have X vertices satisfying above statement conditions but have only 1 component (call this dp2[X]).
                * Choose W (W >= K) vertices to be the in cycle
                * Fill remaining nodes in each node in cycle (use dp O(n^2))
        - Now we can use dp to find number of graphs with size i
            + dp[i] += dp[i-j] * dp2[j] * C[n-(i-j)-1][j-1] (we fix one node in this component to avoid duplicates)
        - Result = dp[N]
        - Complexity O(N^2)
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
const int MAXN = 260;
const int MAXM = 30010;
const int MAXK = 16;
const int MAXQ = 200010;

const int MOD = 30011;

int n, k, cayley[MAXN], fil[MAXN][MAXN], C[MAXN][MAXN], dp[MAXN], dp2[MAXN], p[MAXN];

int add(int a, int b) {
    return (a + b) % MOD;
}

int mul(int a, int b) {
    return a * b % MOD;
}

int sub(int a, int b) {
    return (a - b + MOD) % MOD;
}

int binPow(int a, int b) {
    a %= MOD;
    int res = 1;
    while (b > 0) {
        if (b & 1) res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

void initCayley() {
    cayley[0] = cayley[1] = cayley[2] = 1;
    FOR(i,3,n) cayley[i] = binPow(i, i-2);
}

void initC() {
    FOR(i,0,n)
        FOR(j,0,i)
            if (j == 0 || j == i) C[i][j] = 1;
            else C[i][j] = add(C[i-1][j-1], C[i-1][j]);
}

void initP() {
    p[3] = 1;
    FOR(i,4,n) p[i] = mul(p[i-1], i-1);
}

int fillInTree(int numRemain, int lenCycle) {
    if (lenCycle == 0) {
        if (numRemain) return 0;
        return 1;
    }
    if (fil[numRemain][lenCycle] != -1) return fil[numRemain][lenCycle];

    int res = 0;
    FOR(i,0,numRemain) res = add(res, mul(C[numRemain][i], mul(cayley[i+1], fillInTree(numRemain-i, lenCycle-1))));

    return fil[numRemain][lenCycle] = res;
}

int solve(int x) {
    if (x < k) return 0;
    int res = 0;
    FOR(cycle, k, x) res = add(res, mul(C[x][cycle], mul(p[cycle], fillInTree(x-cycle, cycle))));
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("shgraf.in", "r", stdin);
    freopen("shgraf.out", "w", stdout);
    cin >> n >> k;
    initCayley();
    initC();
    initP();

    FOR(i,0,n)
        FOR(j,0,n) fil[i][j] = -1;

    dp[0] = 1;
    FOR(i,1,n) dp[i] = 0;

    FOR(i,1,n) dp2[i] = solve(i);

    FOR(i,k,n)
        FOR(j,k,i) dp[i] = add(dp[i], mul(dp[i-j], mul(dp2[j], C[n-(i-j)-1][j-1])));

    cout << dp[n];

    return 0;
}
