/*
    Author: Nguyen Tan Bao
    Statement: https://icpc.kattis.com/problems/bustour
    Status: AC
    Idea:
        - First we use Floyd-Warshall to find shortest path length of each pair of nodes.
        - There is one special case, in which h/2 == 0, it's n = 3, we can easily handle this case.
        - Let dp[i][mask] = the length of the shortest path from 0 to i, passing through nodes
        which have set bit in mask.
        - Let dp2[i][mask] = the length of the shortest path from n-1 to i, passing through nodes
        which have set bit in mask.
        - We need to make the h/2 first hotels of the first travel be the h/2 first hotels of
        the second travel (no need to be in the same order of the first one). So we iterate through
        masks which have h/2 set bits. Then we have 2 regions, the set bits and the unset bits, they
        need to be connected by 2 nodes, let's iterate those 2 nodes.
        - So we can calculate the shortest path from 0 to n-1 with a specific mask with h/2 set bits.
        And we can simutaneously calculate the shortest path from n-1 to 0 in the same way. Then 
        compare the result with sum of 2 above values.
        - Complexity O(2^n * n^2)
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
const int MAXN = 25;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, a[MAXN][MAXN], dp[MAXN][1<<21], dp2[MAXN][1<<21];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int o = 0;
    while (cin >> n >> m) {
        o++;
        cout << "Case " << o << ": ";
        FOR(i,0,n-1)
            FOR(j,0,n-1)
                if (i == j) a[i][j] = 0;
                else a[i][j] = 1e9;
        FOR(i,1,m) {
            int u, v, c;
            cin >> u >> v >> c;
            a[u][v] = min(a[u][v], c);
            a[v][u] = min(a[v][u], c);
        }

        // floyd-warshall
        FOR(k,0,n-1)
            FOR(i,0,n-1)
                FOR(j,0,n-1) a[i][j] = min(a[i][j], a[i][k]+a[k][j]);
        
        // corner case, which h/2 = 0
        if (n == 3) {
            int res = a[0][1] + a[1][2];
            res *= 2;
            cout << res << "\n";
            continue;
        }
        
        FOR(i,0,n-1)
            FOR(mask,0,(1<<n)-1) {
                dp[i][mask] = 1e9;
                dp2[i][mask] = 1e9;
            }
        dp[0][1] = 0;
        FOR(mask,0,(1<<n)-2)
            FOR(i,0,n-1)
                if (dp[i][mask] < 1e9) {
                    int numBit = __builtin_popcount(mask);
                    int Max = n-2;
                    if (numBit == n-1) Max = n-1;
                    FOR(j,1,Max)
                        if (!(mask & (1<<j)))
                            dp[j][mask ^ (1<<j)] = min(dp[j][mask ^ (1<<j)], dp[i][mask] + a[i][j]);
                }
        
        dp2[n-1][1<<(n-1)] = 0;
        FOR(mask,0,(1<<n)-2)
            FOR(i,0,n-1)
                if (dp2[i][mask] < 1e9) {
                    int numBit = __builtin_popcount(mask);
                    int Min = 1;
                    if (numBit == n-1) Min = 0;
                    FOR(j,Min,n-2)
                        if (!(mask & (1<<j)))
                            dp2[j][mask ^ (1<<j)] = min(dp2[j][mask ^ (1<<j)], dp2[i][mask] + a[i][j]);
                }


        int res = 1e9;
        FOR(mask,0,(1<<n)-1) {
            int numBit = __builtin_popcount(mask);
            if (numBit == n/2 && mask % 2 && !(mask & (1<<(n-1)))) {
                int firstHotels = mask ^ 1;
                int g = 1e9, h = 1e9;
                FOR(i,1,n-2)
                    if (firstHotels & (1<<i)) {
                        // dp[i][mask]
                        // dp2[i][firstHotels + (1<<(n-1))]

                        FOR(j,1,n-2)
                            if (!(firstHotels & (1<<j))) {
                                // dp2[j][(1<<n)-1-mask]
                                // dp[j][(1<<n)-1-(firstHotels + (1<<(n-1)))]
                                
                                g = min(g, dp[i][mask] + dp2[j][(1<<n)-1-mask] + a[i][j]);
                                h = min(h, dp2[i][firstHotels + (1<<(n-1))] + dp[j][(1<<n)-1-(firstHotels + (1<<(n-1)))] + a[i][j]);
                            }
                    }
                
                res = min(res, g+h);

            }
        }
        cout << res << "\n";
    }
    return 0;
}
