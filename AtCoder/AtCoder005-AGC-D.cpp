/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Consider a bipartite graph with 2N vertices. The vertices are labelled L1, ..., LN , 
        R1, ..., RN . A perfect matching in this bipartite graph corresponds to a permutation. 
        A permutation p1, ..., pN corresponds to a matching that uses the edges (Li, Rpi). 
        - In this task, we need to count the number of perfect matchings that doesn’t use edges 
        (Li, Ri+K) and (Li, Ri−K).
        - By inclusion-exclusion principle, we get the following. Consider a bipartite graph 
        that consists of bad edges: (Li, Ri+K) and (Li, Ri−K) for eachi. Let Mk be the number 
        of matchings of size k in this graph. Then, the answer is sum(Mi * (N-i)! * (-1)^i) (i = 0..n)

        - So how to calculate Mk? Since this graph is a disjoint union of paths, the values of 
        Mk can be easily computed in O(N^2) time in DP.
        - For example, let's consider N = 7, K = 2. We have these paths (I will use number x for
        vertices on the left side and x' for vertices on the right side)
            1 --- 3' --- 5 --- 7'
            1' --- 3 --- 5' --- 7
            2 --- 4' --- 6
            2' --- 4 --- 6'
        - We can calculate F[i][j] = number of ways to choose j edges out of i edges of a path
        but the edges are disjoint (For example, we cannot choose 3' --- 5 and 5 --- 7' at the
        same time)
        - Let dp[i] = M[i]. We consider the path (with length "len") one by one and calculate 
        new dp array using this
            dptmp[a+b] = sum(dp[a] * F[len][b])
        - This dp formula runs in O(N^2), not O(N^3)
        - Proof: Let x[i] is (length of path i) + 1 (including 0), we have sum(x[i]) ~ 2*N.
        Number of paths is m. So the number of operations is
            1 * x[1] + (1 + x[1]) * x[2] + (1 + x[1] + x[2]) * x[3] + ... + (1 + x[1] + ... + x[m-1]) * x[m]
            = sum(x[i]) + x[1] * (x[2] + ... + x[m]) + x[2] * (x[3] + ... + x[m]) + ...
            = sum(x[i]) + x[1] * (sum - x[1]) + x[2] * (sum - x[1] - x[2]) + ...
            = sum(x[i]) + sum(x[i]) * sum(x[i]) - ....
            = O(N) + O(N) * O(N) - ....
            = O(N^2)
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
const int MAXN = 2010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ll MOD = 924844033;

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

ll sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

int n, k;
ll f[MAXN], dp[MAXN * 2], dptmp[MAXN * 2], F[MAXN*2][MAXN*2];
vector<int> b;

ll binPowMod(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % m;
        a = a * a % m;
        b >>= 1LL;
    }
    return res;
}

void getM() {
    FOR(i,0,4000) {
        F[i][0] = 1;
        FOR(j,1,i) {
            F[i][j] = F[i-1][j];
            if (j) {
                if (i > 1) F[i][j] = add(F[i][j], F[i-2][j-1]);
                else F[i][j] = 1;
            }
        }
    }

    // b contains length of paths
    FOR(i,1,k) {
        int gap = n - i;
        b.emplace_back(gap / k);
        b.emplace_back(gap / k);
    }

    int now = 0;
    dp[now] = 1;
    FOR(i,0,SZ(b)-1) {
        int x = b[i];
        int nextNow = x + now;
        FOR(j,0,nextNow) dptmp[j] = 0;
        FOR(j,0,now)
            FOR(p,0,x) dptmp[j+p] = add(dptmp[j+p], mul(dp[j], F[x][p]));
        FOR(j,0,nextNow) dp[j] = dptmp[j];
        now = nextNow;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    f[0] = 1;
    FOR(i,1,n) f[i] = mul(f[i-1], i);

    // calculate array M (array dp in code)
    getM();

    // calculate result
    ll res = 0;
    FOR(i,0,n) {
        ll p = mul(dp[i], f[n-i]);
        if (i % 2) res = sub(res, p);
        else res = add(res, p);
    }
    cout << res;

    return 0;
}
