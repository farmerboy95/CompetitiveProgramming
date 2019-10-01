/*
    Author: Nguyen Tan Bao
    Status: ACX
    Idea:
        - Use dp sibling, reconstruct the tree.
        - Let dp[u][parent][need] is the number of ways to divide the subtree of u, "parent" is the 
        assigned value (0/1) to the parent of u, "need" is whether we need one more node to pair with
        parent of u which has the same value.
        - Result is dp[1][0][0]
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
const int MAXN = 100010;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, leftChild[MAXN], sibling[MAXN];
ll dp[MAXN][2][2];
vector<int> a[MAXN];

// reconstruct the tree using sibling mechanism
void dfs(int u, int p) {
    int pre = -1;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (v != p) {
            if (pre == -1) leftChild[u] = v;
            else sibling[pre] = v;
            pre = v;
            dfs(v, u);
        } 
    }
}

ll solve(int u, int parent, int need) {
    if (dp[u][parent][need] != -1) return dp[u][parent][need];
    ll res = 0;

    int l = leftChild[u], s = sibling[u];

    // if u is leaf and it has no sibling, result is 1 because its value must match the parent's value
    if (l == -1 && s == -1) {
        res = 1;
    }

    // if u has no sibling
    if (l != -1 && s == -1) {
        // must assign parent's value to u because parent need it
        if (need) res = solve(l, parent, 0);
        else {
            // corner case: if u is the root, all need values must be 1
            if (u == 1) res = (solve(l, 1-parent, 1) + solve(l, parent, 1)) % MODBASE;
            // if we assign u the parent's value, need of child node should be 0, otherwise it should be 1
            else res = (solve(l, 1-parent, 1) + solve(l, parent, 0)) % MODBASE;
        }
    }

    // if u has sibling only => u is leaf, its value must match the parent's value, then the sibling's need is 0
    if (l == -1 && s != -1) {
        res = solve(s, parent, 0);
    }

    // if u has both sibling and child
    if (l != -1 && s != -1) {
        if (need) {
            // put 1-parent to u
            res = solve(s, parent, 1) * solve(l, 1-parent, 1) % MODBASE;
            // put parent to u
            res = (res + solve(s, parent, 0) * solve(l, parent, 0)) % MODBASE;
        }
        else {
            // put 1-parent to u
            res = solve(s, parent, 0) * solve(l, 1-parent, 1) % MODBASE;
            // put parent to u
            res = (res + solve(s, parent, 0) * solve(l, parent, 0)) % MODBASE;
        }
    }
    
    return dp[u][parent][need] = res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) leftChild[i] = sibling[i] = -1;
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        a[u].emplace_back(v);
        a[v].emplace_back(u);
    }
    dfs(1, 0);
    FOR(i,1,n) FOR(j,0,2) FOR(k,0,1) dp[i][j][k] = -1;
    cout << solve(1, 0, 0);
    return 0;
}
