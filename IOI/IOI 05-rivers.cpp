/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Reconstruct the tree using dp sibling technique
        - Let dp[u][K][par] is the result that we need to find in the subtree of u, choosing K nodes 
        as sawmills and node par is the nearest sawmill ancestor of u
        - D[i][j] is the distance from j to an ancestor node i
        - The complexity is supposed to be O(n^2 * k^3) but it got AC because the number of states
        is not that big
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
const int MAXN = 110;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, k, leftChild[MAXN], sibling[MAXN], num[MAXN], num2[MAXN], w[MAXN], p[MAXN], d[MAXN], D[MAXN][MAXN];
ll dp[MAXN][MAXN][MAXN];
vector<int> a[MAXN];

// reconstruct the tree
void dfs(int u, int p) {
    num[u] = 1;
    int pre = -1;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (v != p) {
            if (pre == -1) leftChild[u] = v;
            else sibling[pre] = v;
            pre = v;
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
}

ll solve(int u, int K, int par) {
    if (num2[u] < K) return 1e15;
    if (dp[u][K][par] != -1) return dp[u][K][par];

    if (u == 0) return dp[u][K][par] = solve(leftChild[u], K-1, par);

    ll res = 1e15;
    int l = leftChild[u], s = sibling[u];

    // if u is leaf and has no sibling, result would depend on K
    if (l == -1 && s == -1) {
        if (K) res = 0;
        else res = (ll) D[par][u] * w[u];
    }

    // if u has child but no sibling, just go to the child and consider putting sawmill at u
    if (l != -1 && s == -1) {
        if (K) {
            // not choosing u as sawmill
            res = min(res, solve(l, K, par) + (ll) D[par][u] * w[u]);
            // choose u as sawmill
            res = min(res, solve(l, K-1, u));
        } else {
            res = solve(l, K, par) + (ll) D[par][u] * w[u];
        }
    }

    // if u is leaf and has a sibling, do as above
    if (l == -1 && s != -1) {
        if (K) {
            // not choosing u as sawmill
            res = min(res, solve(s, K, par) + (ll) D[par][u] * w[u]);
            // choose u as sawmill
            res = min(res, solve(s, K-1, par));
        } else {
            res = solve(s, K, par) + (ll) D[par][u] * w[u];
        }
    }

    // general case, just separate K between child and sibling
    if (l != -1 && s != -1) {
        if (K) {
            // not choosing u as sawmill
            FOR(i,0,K) res = min(res, solve(s, i, par) + solve(l, K-i, par) + (ll) D[par][u] * w[u]);
            // choose u as sawmill
            FOR(i,0,K-1) res = min(res, solve(s, i, par) + solve(l, K-1-i, u));
        } else {
            res = solve(s, K, par) + solve(l, K, par) + (ll) D[par][u] * w[u];
        }
    }

    return dp[u][K][par] = res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,0,n) leftChild[i] = sibling[i] = -1;
    FOR(i,1,n) {
        cin >> w[i] >> p[i] >> d[i];
        a[p[i]].push_back(i);
    }
    FOR(i,1,n) {
        int u = i, dist = 0;
        do {
            int par = p[u];
            dist += d[u];
            D[par][i] = dist;
            u = par;
        } while (u);
    }
    MS(dp, -1);
    dfs(0, -1);
    dfs2(0);

    cout << solve(0, k+1, 0) << "\n";
    return 0;
}
