/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Reconstruct the tree using dp sibling technique
        - There must be a state that has exactly k nodes, assume that state contain node 1
        - Let dp[u][K] is number of edges that need to be removed in the subtree of u (in sibling graph), choosing K nodes
        - But that is just a state which contains node 1, what about state which contain other nodes but not node 1
        => We simply cut the edge connecting 1 and its direct child (in real tree), and do the same dp on that subtree (in real tree)
        => Complexity O(n*k*k)
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
const int MAXN = 410;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, k, num[MAXN], num2[MAXN], leftChild[MAXN], sibling[MAXN], numChild[MAXN], dp[MAXN][MAXN][2], edge[MAXN];
vector<II> a[MAXN];
II par[MAXN], trace[MAXN][MAXN][2];

// reconstruct the tree
void dfs(int u, int p) {
    num[u] = 1;
    int pre = -1, cnt = 0;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i].FI;
        int idx = a[u][i].SE;
        if (v != p) {
            cnt++;
            if (pre == -1) leftChild[u] = v;
            else sibling[pre] = v;
            pre = v;
            par[v] = II(u, cnt);
            edge[v] = idx;
            dfs(v, u);
            num[u] += num[v];
        } 
    }
    numChild[u] = cnt;
}

void dfs2(int u) {
    num2[u] = 1;
    if (leftChild[u] != -1) {
        dfs2(leftChild[u]);
        num2[u] += num2[leftChild[u]];
    }
    if (sibling[u] != -1) {
        dfs2(sibling[u]);
        num2[u] += num2[sibling[u]];
    }
}

// isRoot = 1 means that node u is the root node when we consider the subtree of u, it would not have sibling node (even if it has one in sibling graph)
int solve(int u, int K, int isRoot) {
    if (dp[u][K][isRoot] != -1) return dp[u][K][isRoot];

    int res = 1000000000;
    if (K < 0) return dp[u][K][isRoot] = res;
    if (num2[u] < K) return dp[u][K][isRoot] = res;
    if (isRoot && num[u] < K) return dp[u][K][isRoot] = res;
    int l = leftChild[u], s = sibling[u];
    // not considering sibling node when isRoot = 1
    if (isRoot) s = -1;

    // u is leaf and has no sibling, K must only be 0 or 1, cut if K = 0 and keep if K = 1
    if (l == -1 && s == -1) {
        res = 1-K;
    }

    // u has child but has no sibling, cut if K = 0 and keep if K = 1
    if (l != -1 && s == -1) {
        if (K == 0) res = 1;
        else {
            trace[u][K][isRoot] = II(l, K-1);
            res = solve(l, K-1, 0);
        }
    }

    // u is leaf and has sibling, "cut and pass K to sibling" or "keep and pass K-1 to sibling"
    if (l == -1 && s != -1) {
        trace[u][K][isRoot] = II(s, K);
        res = solve(s, K, 0) + 1;
        if (K) {
            int p = solve(s, K-1, 0);
            if (p < res) {
                res = p;
                trace[u][K][isRoot] = II(s, K-1);
            }
        }
    }

    // general case: "cut and pass K to sibling" or "keep i and pass K-1-i to sibling" (because we also keep 1 node u)
    if (l != -1 && s != -1) {
        trace[u][K][isRoot] = II(s, K);
        res = min(res, solve(s, K, 0) + 1);
        if (K)
            FOR(i,0,K-1) {
                int p = solve(l, i, 0) + solve(s, K-1-i, 0);
                if (p < res) {
                    res = p;
                    trace[u][K][isRoot] = II(l, i);
                }
            }
    }

    // remember to cut once more if node is not 1
    if (isRoot && u != 1) res++;
    return dp[u][K][isRoot] = res;
}

// print the result based on the trace array
void printResult(int u, int K, int isRoot) {
    if (isRoot && u != 1) cout << edge[u] << "\n";

    int l = leftChild[u], s = sibling[u];
    if (isRoot) s = -1;

    if (l == -1 && s == -1) {
        if (K == 0) cout << edge[u] << "\n";
    }

    if (l != -1 && s == -1) {
        if (K == 0) cout << edge[u] << "\n";
        else printResult(l, K-1, 0);
    }

    if (l == -1 && s != -1) {
        II r = trace[u][K][isRoot];
        if (r.SE == K) cout << edge[u] << "\n";
        printResult(r.FI, r.SE, 0);
    }

    if (l != -1 && s != -1) {
        II r = trace[u][K][isRoot];
        if (r.SE == K) {
            cout << edge[u] << "\n";
            printResult(r.FI, r.SE, 0);
        }
        else {
            printResult(r.FI, r.SE, 0);
            printResult(s, K-1-r.SE, 0);
        }
    }
}

// start to dp from each node
void dfs3(int u, int p) {
    solve(u, k, 1);
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i].FI;
        if (v != p) dfs3(v, u);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,n) leftChild[i] = sibling[i] = -1;
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        a[u].emplace_back(II(v, i));
        a[v].emplace_back(II(u, i));
    }
    dfs(1, 0);
    dfs2(1);
    FOR(i,1,n) FOR(j,0,k) FOR(p,0,1) dp[i][j][p] = -1;
    dfs3(1, 0);
    // get number of edges that need to be removed
    int res = 1000000000, st = -1;
    FOR(i,1,n) {
        if (dp[i][k][1] < res) {
            res = dp[i][k][1];
            st = i;
        }
    }
    cout << res << "\n";
    // start to print result
    printResult(st, k, 1);
    return 0;
}
