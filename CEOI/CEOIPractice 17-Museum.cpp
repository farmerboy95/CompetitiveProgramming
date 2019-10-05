/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Reconstruct the tree using dp sibling technique
        - Let dp[u][K][p] is the minimum length that we need to find in the subtree of u, choosing K nodes
        p = 0 means we are not going to finish the journey in this subtree, otherwise p = 1
        - The complexity is supposed to be O(n/2 * n^2) but with some optimization, it got AC
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
const int MAXN = 10010;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, k, leftChild[MAXN], sibling[MAXN], num[MAXN], num2[MAXN];
int dp[MAXN][MAXN][2];
II par[MAXN];
vector<II> a[MAXN];

// reconstruct the tree
void dfs(int u, int p) {
    num[u] = 1;
    int pre = -1;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i].FI;
        int c = a[u][i].SE;
        if (v != p) {
            if (pre == -1) leftChild[u] = v;
            else sibling[pre] = v;
            pre = v;
            par[v] = II(u, c);
            dfs(v, u);
            num[u] += num[v];
        } 
    }
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
    // init dp array
    dp[u][0][0] = dp[u][0][1] = 0;
    FOR(i,1,num2[u]) dp[u][i][0] = dp[u][i][1] = -1;
}

int solve(int u, int K, int p) {
    if (num2[u] < K) return 1000000000;
    if (dp[u][K][p] != -1) return dp[u][K][p];

    int res = 1000000000;
    int l = leftChild[u], s = sibling[u];
    int e = par[u].SE;

    // if u is leaf and has no sibling, result would depend on p
    if (l == -1 && s == -1) {
        if (p == 0) res = 2 * e;
        else res = e;
    }

    // if u has child but no sibling, just go to the child and add to the result the length depending on p
    if (l != -1 && s == -1) {
        if (p == 0) res = min(res, solve(l, K-1, 0) + 2 * e);
        else res = min(res, solve(l, K-1, 1) + e);
    }

    // if u is leaf and has a sibling, consider separating K between u and sibling
    if (l == -1 && s != -1) {
        if (p == 0) res = min(res, min(solve(s, K, 0), solve(s, K-1, 0) + 2 * e));
        else res = min(res, min(solve(s, K, 1), min(solve(s, K-1, 0) + e, solve(s, K-1, 1) + 2*e)));
    }

    // general case, depending on p, just separate K between child and sibling
    if (l != -1 && s != -1) {
        // get the possible range of number of nodes which can be distributed to child and sibling
        int L = max(0, K-1-num2[s]), R = min(K-1, num2[l]);
        if (p == 0) {
            res = min(res, solve(s, K, 0));
            FOR(i,L,R) res = min(res, solve(l, i, 0) + solve(s, K-i-1, 0) + 2*e);
        }
        else {
            res = min(res, solve(s, K, 1));
            FOR(i,L,R) {
                res = min(res, solve(l, i, 1) + solve(s, K-i-1, 0) + e);
                res = min(res, solve(l, i, 0) + solve(s, K-i-1, 1) + 2*e);
            }
        }
    }

    return dp[u][K][p] = res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int x;
    cin >> n >> k >> x;
    FOR(i,1,n) leftChild[i] = sibling[i] = -1;
    FOR(i,1,n-1) {
        int u, v, c;
        cin >> u >> v >> c;
        a[u].emplace_back(II(v, c));
        a[v].emplace_back(II(u, c));
    }
    dfs(x, 0);
    dfs2(x);

    cout << solve(x, k, 1);
    return 0;
}
