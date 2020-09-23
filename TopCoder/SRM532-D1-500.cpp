/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's define dp[n][m][mask][p] as the number of ways to build roadmap for n nodes,
        with m edges, mask of degrees of the last k+1 nodes is "mask", and there is at least
        an edge connecting node n and node n-p. There is no edge from node n-p+1, n-p+2... n-1
        to node n.
        - The least significant bit of "mask" represents the parity of degree of node n, the 
        ith bit of "mask" represents the parity of degree of node (n-i+1)th.
        - If currently, the first bit of mask is 0, we can stop creating edge from n and move
        to n-1.
        - Or we can create an edge connecting n and a node i from n-p to n-k, and move to the next
        state, deduct m by 1, flip first bit and (i+1)th bit and update p as well.
        - Complexity O(n * m * 2^(k+1) * k * k)
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
const int MAXN = 31;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int MOD = 1000000007;

class DengklekBuildingRoads {
    public:
    int dp[MAXN][MAXN][1<<9][9], K;

    int solve(int n, int m, int mask, int put) {
        if (n == 0) return !m;

        int& res = dp[n][m][mask][put];
        if (res != -1) return res;
        res = 0;

        if (!(mask & 1)) res = (res + solve(n-1, m, mask >> 1, 1)) % MOD;

        FOR(i,put,K) {
            if (n - i <= 0) break;
            if (m == 0) break;
            res = (res + solve(n, m-1, mask ^ 1 ^ (1<<i), i)) % MOD;
        }
        return res;
    }

    int numWays(int n, int m, int k) {
        MS(dp, -1);
        K = k;
        return solve(n, m, 0, 1);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    DengklekBuildingRoads s;
    cout << s.numWays(3, 4, 1) << endl;
    cout << s.numWays(4, 3, 3) << endl;
    cout << s.numWays(2, 1, 1) << endl;
    cout << s.numWays(5, 0, 3) << endl;
    cout << s.numWays(10, 20, 5) << endl;
    return 0;
}
