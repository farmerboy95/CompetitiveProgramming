/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Remove all edges that have length > L
        - Use Floyd-Warshall on the graph
        - For each point i, use a simple bfs to get number of times refulling the fuel tank, save in dp[i][u]
        - Simply print result with asked u, v
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
const int MAXN = 310;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, m;
ll a[MAXN][MAXN], L;
int dp[MAXN][MAXN];

void bfs(int p) {
    FOR(i,1,n) dp[p][i] = 1000000000;
    dp[p][p] = 0;
    queue<int> q;
    q.push(p);
    // dp[p][v] is number of step <= L needed to go from u to v
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        FOR(v,1,n) 
            if (a[u][v] <= L) {
                if (dp[p][v] > dp[p][u] + 1) {
                    dp[p][v] = dp[p][u] + 1;
                    q.push(v);
                }
            }
    }
    // deduct 1 from each dp[p][i] if dp[p][i] < MAX_INT
    FOR(i,1,n) 
        if (i == p) continue;
        else if (dp[p][i] == 1000000000) dp[p][i] = -1;
        else dp[p][i]--;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> L;
    FOR(i,1,n)
        FOR(j,1,n) {
            if (i == j) a[i][j] = 0;
            else a[i][j] = 1e15;
            dp[i][j] = -1;
        }
    FOR(i,1,m) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        // remove edges that have length > L as we cannot move on these edges
        if (c > L) continue;
        a[u][v] = min(a[u][v], c);
        a[v][u] = min(a[v][u], c);
    }
    // Floyd-Warshall
    FOR(k,1,n)
        FOR(i,1,n)
            FOR(j,1,n) a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
    // BFS
    FOR(i,1,n) bfs(i);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << dp[u][v] << "\n";
    }
    return 0;
}
