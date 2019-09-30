/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - For each edge (u, v, v is a child of u), if we visit x nodes in the subtree of v, so there are k - x nodes outside of the subtree to visit.
        => We would use edge min(x, k-x) * 2 times.
        - Let dp[u][p] is the maximum length of journey if we choose p nodes in the subtree of u
        => Result is dp[1][k]
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
const int MAXN = 1010;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, k, num[MAXN];
ll dp[MAXN][MAXK], dp2[MAXN][MAXK], dp3[MAXN][MAXK];
vector<II> a[MAXN];

// subtree of u, parent, number of chosen nodes
void dfs2(int u, int p, int K) {
    if (dp[u][K] != -1) return;
    // init 2 array dp2[u] and dp3[u]
    // dp2[u][i] is for choosing i nodes in the subtree of u
    // dp3[u][i] is a temporary array to save dp2 when adding j more chosen nodes in the subtree of considering node v
    dp2[u][0] = dp3[u][0] = 0;
    FOR(i,1,K) dp2[u][i] = dp3[u][i] = -1;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i].FI;
        int c = a[u][i].SE;
        if (v != p) {
            int numV = num[v];
            FOR(j,1,min(K, numV)) {
                // number of needed nodes outside of the subtree must be larger than or equal to k-j+1
                // (+1 means adding the root, it's the final node to go to, can be considered as a chosen node)
                int remain = n - numV;
                if (remain < k - j + 1) continue;
                ll e = (ll) c * min(j, k - j + 1) * 2;
                dfs2(v, u, j);
                // use knapsack to add j more nodes in subtree of v to dp2[u] array
                FORE(w,K,1)
                    if (j <= w) {
                        if (dp2[u][w-j] == -1) continue;
                        dp3[u][w] = max(dp3[u][w], dp2[u][w-j] + dp[v][j] + e);
                    }
                    else break;
            }
            // move dp3 to dp2
            FOR(w,0,K) dp2[u][w] = dp3[u][w];
        }
    }
    // since dp2 only get 1 -> K-1 nodes, if K == num[u], we should take K-1 in dp2
    if (K == num[u]) dp[u][K] = dp2[u][K-1];
    // otherwise, we should get the maximum between K (not choosing node u) and K-1 (choosing node u)
    else dp[u][K] = max(dp2[u][K], dp2[u][K-1]);
}

void dfs(int u, int p) {
    num[u] = 1;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i].FI;
        if (v != p) {
            dfs(v, u);
            num[u] += num[v];
        } 
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case " << o << ": ";
        cin >> n >> k;
        FOR(i,1,n) a[i].clear();
        // set up edges
        FOR(i,2,n) {
            int u, v;
            cin >> u >> v;
            a[i].emplace_back(II(u, v));
            a[u].emplace_back(II(i, v));
        }
        // set up dp array
        FOR(i,1,n)
            FOR(j,1,k) dp[i][j] = -1;
        // get num[u] = number of nodes in the subtree of u
        dfs(1, 0);
        // dp top-down
        dfs2(1, 0, k);
        cout << dp[1][k] << "\n";
    }
    return 0;
}
