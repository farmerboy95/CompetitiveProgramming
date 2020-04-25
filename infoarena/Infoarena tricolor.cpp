/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let dpw[u] is the maximum number of pairs in the subtree of u and u is white
        - Let dpb[u][i] is the maximum number of pairs in the subtree of u, u is black and
        we have i white nodes which have all-blacked paths from u to parent of a specific 
        white node. We can also use co[u][i] which means it exists the state for dpb[u][i]
        - It's quite clear that for each subtree of u, the max i should be number of leaves
        of that subtree.
        - For each node, we can consider each child one by one and merge the result of child
        to the node. The transition is quite easy to read.
        - This seems to be a O(n^3) solution but for this kind of problem, the actual complexity
        of the below solution is only O(n^2). You can refer to the proof in subsection 4.2 and
        Appendix A (for a formal proof) in this docs
        https://github.com/farmerboy95/CompetitiveProgramming/blob/master/References/NOI_PH_2019_Week_2_DP_3.pdf
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
const int MAXN = 5010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int t, n, dpw[MAXN], dpb[MAXN][MAXN], leaves[MAXN], f[MAXN];
bool co[MAXN][MAXN], co2[MAXN];
vector<int> a[MAXN];

void dfs(int u, int p) {
    co[u][0] = true;
    int Max = 0, cntChild = 0;
    for (auto v : a[u]) {
        if (v == p) continue;
        cntChild++;
        dfs(v, u);
        leaves[u] += leaves[v];
        FOR(i,0,Max + leaves[v]) f[i] = co2[i] = 0;
        FOR(i,0,Max)
            if (co[u][i]) {
                FOR(j,0,leaves[v])
                    if (co[v][j]) {
                        f[i+j] = max(f[i+j], dpb[u][i] + i * j + dpb[v][j]);
                        co2[i+j] = true;
                    }
                f[i+1] = max(f[i+1], dpb[u][i] + i + dpw[v]);
                co2[i+1] = true;
            }
        Max += leaves[v];
        FOR(i,0,Max) {
            dpb[u][i] = f[i];
            co[u][i] = co2[i];
        }

        int MaxW = dpw[v] + 1;
        FOR(i,0,leaves[v]) if (co[v][i]) MaxW = max(MaxW, dpb[v][i] + i);
        dpw[u] += MaxW;
    }
    if (cntChild == 0) leaves[u] = 1;
} 

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("tricolor.in", "r", stdin);
    freopen("tricolor.out", "w", stdout);
    cin >> t;
    while (t--) {
        cin >> n;
        FOR(i,1,n) {
            a[i].clear();
            dpw[i] = 0;
            leaves[i] = 0;
            FOR(j,0,n) dpb[i][j] = co[i][j] = 0;
        }
        FOR(i,1,n-1) {
            int u, v;
            cin >> u >> v;
            a[u].push_back(v);
            a[v].push_back(u);
        }
        dfs(1, 0);
        int res = dpw[1];
        FOR(i,0,n) res = max(res, dpb[1][i]);
        cout << res << "\n";
    }
    return 0;
}
