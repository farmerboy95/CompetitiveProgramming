/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's declare some arrays:
            + child[u] = number of nodes which are children of u
            + f[u] = u!
            + ways[u] = number of ways to solve the problem in subtree of u (the tree is rooted at 1)
        - Let's begin with one root, node 1, so how are we going to calculate ways[u]?
        - Consider a tree rooted at u (n nodes), we have some adjacent nodes of u, calling them 
        v1, v2, ..., vm we start to write numbers from u. Assume that we have all ways[v1], ways[v2], 
        ..., ways[vm]
        - The observation here is that no matter how we fill numbers into nodes, at the end, subtree
        of v1 will take (child[v1] + 1) spaces in n-1 remaining spaces and the order to fill in those
        (child[v1] + 1) spaces is ways[v1]. Do the same thing with the remaining v, we would have
        ways[u] = ways[v1] * C(n-1, child[v1]+1) * ways[v2] * C(n-1-(child[v1]+1), child[v2]+1) * ...
        => ways[u] = ways[v1] * ... * ways[vm] * (n-1)! / ((child[v1]+1)! * ... * (child[vm]+1)!) (1)
        - We have the result for root 1, so the remaining problem is, how to reroot when going down
        using dfs?
        - At node v, we define ways2[u] = number of ways to solve the problem in subtree of u, but
        the tree is now rooted at v
        - When we have ways2[u], we can use it with child of v to get the result at v.
        - But how to calculate ways2[u]?
        - ways2[u] = res[u] (at (1)) 
                    * 1 / ways[v] (to clear the node that we are going down to)
                    * (child[v] + 1)! (clear at the denominator)
                    * 1 / (n-1)! (clear (n-1)! at the numerator)
                    * (n-1 - child[v] - 1) (add the sum without the subtree to numerator again)
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
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, child[MAXN];
ll f[MAXN];
vector<int> a[MAXN];
ll ways[MAXN], res[MAXN], ways2[MAXN];
ll MOD = MODBASE;

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

ll rev(ll a) {
    return binPowMod(a, MOD-2);
}

void dfs(int u, int p) {
    int branch = 0;
    child[u] = 0;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (v == p) continue;
        dfs(v, u);
        child[u] += child[v] + 1;
        branch++;
    }
    ways[u] = f[child[u]]; 
    if (branch) {
        FOR(i,0,SZ(a[u])-1) {
            int v = a[u][i];
            if (v == p) continue;
            ways[u] = mul(ways[u], ways[v]);
            ways[u] = mul(ways[u], rev(f[child[v] + 1]));
        }
    }
}

void dfs2(int u, int p) {
    res[u] = f[n-1];
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (v == p) {
            res[u] = mul(res[u], ways2[v]);
            res[u] = mul(res[u], rev(f[n-1-child[u]]));
        }
        else {
            res[u] = mul(res[u], ways[v]);
            res[u] = mul(res[u], rev(f[child[v] + 1]));
        }
    }
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (v == p) continue;
        ways2[u] = mul(res[u], mul(rev(ways[v]), mul(f[child[v] + 1], mul(rev(f[n-1]), f[n-1-child[v]-1]))));
        dfs2(v, u);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    f[0] = 1;
    FOR(i,1,n) f[i] = mul(f[i-1], i);
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    dfs(1, 0);
    dfs2(1, 0);
    FOR(i,1,n) cout << res[i] << "\n";
    return 0;
}
