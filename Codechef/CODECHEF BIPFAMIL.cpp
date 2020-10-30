/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - This solution subtracts the disconnected Range Graphs from the total number of Range Graphs:
        https://discuss.codechef.com/t/acmind18-icpc-online-round-solution-outlines/20684
        - I will directly calculate the number of connected Range Graphs.
        - Let dp[n][m] be number of connected Range Graphs with n nodes on the left and m nodes on
        the right.
        - Let's say we added edges for all nodes i from 1 to n-1. There would be 2 cases here:
            + The graph is a connected Range Graph, we are free to add edges for node n, there are
            m * (m+1) / 2 ways to add edges => dp[n-1][m] * m * (m+1) / 2
            + The graph is not a connected Range Graph. So we have several connected components here.
            But we only care about the first and the last ones. Let number of nodes in those components
            are x and y, respectively. So the number of ways to add edges for node n is x * y, obviously.
            (x > 0, y > 0, x+y <= m)
        - We need to talk more about case 2. Let A be the number of nodes on the left having edges
        connecting to the first connected component on the right side, B be the number of nodes on
        the left having edges connecting to the last connected component on the right side 
        (0 <= A + B <= n-1, as we are considering n-1 nodes)
        - Let k[n][m] = number of Range Graphs = (m * (m+1) / 2) ^ n
        - So the number of ways for case 2 is:
            Q = C(n-1, A) * dp[A][x] * C(n-1-a, B) * dp[B][y] * k[n-1-A-B][m-x-y] * x * y
            (x > 0, y > 0, x+y <= m)
            (0 <= A + B <= n-1)
            + C(n-1, A) * dp[A][x]: We have n-1 nodes now, and we choose A nodes to connect to x nodes
            on the right side, how many ways to make x nodes connected? dp[A][x]
            + C(n-1-a, B) * dp[B][y]: Like above
            + k[n-1-A-B][m-x-y]: We can connect the remaining nodes in any arbitrary way
            + x * y: finally, we add edges for node n for the graph to be connected.
        - But this approach takes O((n*m)^3) => TLE. We need to change it somehow.
        - C(n-1, A) * C(n-1-a, B) = 1/A! * 1/B! * (n-1)! / (n-1-A-B)!
        => Q = (dp[A][x] * x / A!) * (dp[B][y] * y / B!) * (n-1)! / (n-1-A-B)! * k[n-1-A-B][m-x-y]
        - Let P[n][m] = dp[n][m] * m / n!
        => Q = P[A][x] * P[B][y] * (n-1)! / (n-1-A-B)! * k[n-1-A-B][m-x-y]
        (x > 0, y > 0, x+y <= m)
        (0 <= A + B <= n-1)
        - Let w[n][m] = P[i][j] * P[n-i][m-j]. We can calculate this along with the process of calculating
        dp[n][m].
        - We can iterate n-1-A-B and m-x-y and get the dp, then update p and w.
        - Remember to add dp[0][1] = 1.
        - Complexity O((n*m)^2)
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
const int MAXN = 2510;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ll dp[MAXN][MAXN], f[MAXN], rev[MAXN], p[MAXN][MAXN], w[MAXN][MAXN], k[MAXN][MAXN];
ll MOD = MODBASE;
vector<II> q;

ll binPowMod(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1LL;
    }
    return res;
}

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

ll getP(int u, int v) {
    return mul(dp[u][v], mul(v, rev[u]));
}

void init() {
    f[0] = 1;
    rev[0] = binPowMod(f[0], MOD-2);
    FOR(i,1,2500) {
        f[i] = mul(f[i-1], i);
        rev[i] = binPowMod(f[i], MOD-2);
    }
    dp[0][1] = 1;
    p[0][1] = getP(0, 1);
    w[0][2] = add(w[0][2], mul(p[0][1], p[0][1]));
    q.push_back(II(0, 1));

    FOR(i,0,2500)
        FOR(j,0,2500) {
            if (i+j > 2500) break;
            k[i][j] = binPowMod(j * (j+1) / 2, i);
        }

    FOR(i,1,2500)
        FOR(j,1,2500) {
            if (i * j > 2500) break;
            if (i == 1) dp[i][j] = 1;
            else {
                dp[i][j] = mul(dp[i-1][j], j * (j+1) / 2);
                // n-1, m
                // x, y > 0 => m-x-y <= m-2
                FOR(u,0,i-1)
                    FOR(v,0,j-2) {
                        dp[i][j] = add(dp[i][j], 
                                        mul(
                                            mul(w[i-1-u][j-v], f[i-1]), 
                                            mul(rev[u], k[u][v]))
                                        );
                    }
            }
            p[i][j] = getP(i, j);
            for (II x : q) {
                int u = x.FI + i, v = x.SE + j;
                if (u * v > 2500) continue;
                // remember to multiple with 2 if the two parts are different
                w[u][v] = add(w[u][v], mul(2, mul(p[x.FI][x.SE], p[i][j])));
            }
            if (i*2*j*2 <= 2500) {
                w[i*2][j*2] = add(w[i*2][j*2], mul(p[i][j], p[i][j]));
            }
            q.push_back(II(i, j));
        }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    init();
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        cout << dp[n][m] << "\n";
    }
    return 0;
}
