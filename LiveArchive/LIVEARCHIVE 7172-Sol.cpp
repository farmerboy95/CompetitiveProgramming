/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - For each edge (u, v, v is a child of u), if we visit x nodes in the subtree of v, so there are k - x nodes outside of the subtree to visit.
        => We would use edge min(x, k-x) * 2 times.
        - Let dp[u][K] is the maximum length of journey if we choose K nodes in the subtree of u
        => Result is dp[1][k]

        - Use dp sibling, reconstruct the tree
        - For each u and K, we have the following cases:
        1. no left child and sibling => u is a leaf and no sibling => K is for u
        O(1) in this case
        2. only has left child => K is for subtree of u, we can choose u and pass K-1 to the child or pass all K to child
        O(1) in this case
        3. only has sibling => 0 or 1 of K is for u (because it's the leaf), remaining thing is for v
        O(1) in this case
        4. has both left child and sibling => part of K is for subtree of u, remaining thing is for v
        O(k) in this case

        - It seems to be O(n*k*k) after all, but why does it pass the time limit?
        - We can prove that there are at most n/4 nodes that have both left child and sibling
        => O(n*k*k/4), which can pass the time limit
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

int n, k, num[MAXN], num2[MAXN], leftChild[MAXN], sibling[MAXN];
II par[MAXN];
ll dp[MAXN][MAXK];
vector<II> a[MAXN];

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

// reconstruct the tree
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

ll solve(int u, int K) {
    if (K < 0) return -1e15;
    if (K == 0) return 0;
    if (num2[u] < K) return -1e15;
    if (dp[u][K] != -1) return dp[u][K];
    ll res = 0;

    // we calculate e basing on the number of node chosen for the subtree of u (in real tree), and the edge (u, parent of u)
    // one more thing, the chosen nodes outside of a subtree must be less than or equal to the number of nodes outside of that subtree

    // no left child and sibling => K is for u
    if (leftChild[u] == -1 && sibling[u] == -1) {
        ll e = 0;
        if (par[u].FI) e = (ll) par[u].SE * min(K, k - K + 1) * 2;
        res = e;
    }

    // only has left child => K is for subtree of u
    if (leftChild[u] != -1 && sibling[u] == -1) {
        int v = leftChild[u];
        int remain = n - num[u];
        ll e = 0;
        if (par[u].FI) {
            if (remain >= k - K + 1) e = (ll) par[u].SE * min(K, k - K + 1) * 2;
        }
        if (u == 1) res = solve(v, K) + e;
        else res = max(solve(v, K), solve(v, K-1)) + e;
    }

    // only has sibling => 0 or 1 of K is for u (because it's the leaf), remaining thing is for v
    if (leftChild[u] == -1 && sibling[u] != -1) {
        int v = sibling[u];
        int remain = n - num[u];
        
        FOR(i,0,1) {
            ll e = 0;
            if (par[u].FI) {
                if (remain >= k - i + 1) e = (ll) par[u].SE * min(i, k - i + 1) * 2;
            }
            res = max(res, solve(v, K - i) + e);
        }
    }

    // has both left child and sibling => part of K is for subtree of u, remaining thing is for v
    if (leftChild[u] != -1 && sibling[u] != -1) {
        int p = leftChild[u];
        int v = sibling[u];
        int remain = n - num[u];
        FOR(i,0,K) {
            ll e = 0;
            if (par[u].FI) {
                if (remain >= k - i + 1) e = (ll) par[u].SE * min(i, k - i + 1) * 2;
            }
            res = max(res, max(solve(p, i), solve(p, i-1)) + solve(v, K - i) + e);
        }
    }
    
    return dp[u][K] = res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case " << o << ": ";
        cin >> n >> k;
        FOR(i,1,n) {
            a[i].clear();
            leftChild[i] = sibling[i] = -1;
        }
        FOR(i,2,n) {
            int u, v;
            cin >> u >> v;
            a[i].emplace_back(II(u, v));
            a[u].emplace_back(II(i, v));
        }
        par[1] = II(0,0);
        dfs(1, 0);
        dfs2(1);
        FOR(i,1,n)
            FOR(j,1,k) dp[i][j] = -1;
        cout << solve(1, k) << "\n";
    }
    return 0;
}
