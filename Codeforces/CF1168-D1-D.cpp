/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Mainly from https://codeforces.com/blog/entry/67241
        - The editorial mentioned HLD, we are actually not using it here, we just use its
        concept to compress the tree as described in the editorial.
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
const int MAXN = 150010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, q, par[MAXN], d[MAXN], up[MAXN], upChain[MAXN], cnt[MAXN][26], dp[MAXN][26], sum[MAXN], depth, bad;
vector<int> a[MAXN], A[MAXN];
char ch[MAXN];

void dfs(int u) {
    for (int v : a[u]) {
        d[v] = d[u] + 1;
        dfs(v);
    }
}

int allLeavesSameDepth() {
    dfs(1);
    set<int> s;
    FOR(i,1,n)
        if (SZ(a[i]) == 0) s.insert(d[i]);
    if (SZ(s) == 1) return *s.begin();
    return -1;
}

int getLen(int u) {
    return depth - d[u];
}

void update(int u, char c) {
    // O(sqrt(n))
    int C = c - 'a';
    while (1) {
        // remove the bad flag temporarily
        if (sum[u] > getLen(u)) bad--;
        // remove dp from sum temporarily
        sum[u] -= dp[u][C];
        // recalculate the dp
        dp[u][C] = 0;
        for (int v : A[u]) dp[u][C] = max(dp[u][C], dp[v][C] + cnt[upChain[v]][C]);
        // readd dp to sum
        sum[u] += dp[u][C];
        // check the flag again
        if (sum[u] > getLen(u)) bad++;
        // move to the parent in the compressed tree
        if (u == 1) break;
        u = up[u];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> q;
    FOR(i,2,n) {
        int p; char c;
        cin >> p >> c;
        a[p].push_back(i);
        par[i] = p;
        ch[i] = c;
    }
    par[1] = 1;

    // obviously, if all the leaves not having same depth => -1
    depth = allLeavesSameDepth();
    if (depth == -1) {
        while (q--) cout << "Fou\n";
        return 0;
    }

    // compress the tree
    FOR(i,1,n) {
        if (SZ(a[par[i]]) > 1 || par[i] == 1) {
            up[i] = par[i];
            upChain[i] = i;
        } else {
            up[i] = up[par[i]];
            upChain[i] = upChain[par[i]];
        }
        if (i > 1 && ch[i] != '?') cnt[upChain[i]][ch[i]-'a']++;
    }

    // after compressing, the tree now contains the nodes with 0 or 2 children
    // dp[i][j] = maximum number of letter j if we go from i to one of the leaves
    FORE(i,n,2)
        if (SZ(a[i]) != 1) {
            FOR(j,0,25) dp[up[i]][j] = max(dp[up[i]][j], dp[i][j] + cnt[upChain[i]][j]);
            A[up[i]].push_back(i);
        }
    
    // if at a node, sum[i] > len[i], we increase the number of bad node
    // should have used the 0 or 2 children condition here as well but it does not affect the above statement
    bad = 0;
    FOR(i,1,n) {
        FOR(j,0,25) sum[i] += dp[i][j];
        if (sum[i] > getLen(i)) bad++;
    }

    up[1] = 0;
    while (q--) {
        int u; char c;
        cin >> u >> c;
        // remove character
        if (ch[u] != '?') {
            cnt[upChain[u]][ch[u] - 'a']--;
            update(up[u], ch[u]);
        }
        // add character
        ch[u] = c;
        if (ch[u] != '?') {
            cnt[upChain[u]][ch[u] - 'a']++;
            update(up[u], ch[u]);
        }
        if (bad) cout << "Fou\n";
        else {
            cout << "Shi ";
            int res = 0;
            // number of '?' + number of the letter c (dp[1][c])
            FOR(i,0,25) res += (depth - sum[1] + dp[1][i]) * (i+1);
            cout << res << "\n";
        }
    }
    return 0;
}
