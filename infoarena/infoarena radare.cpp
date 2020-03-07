/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Mainly based on https://github.com/stefdasca/CompetitiveProgramming/blob/master/Infoarena/radare.cpp
        - Flatten the dfs onto a segment, stop[u] = position that is the end of tree with root u
        - dp[i][j] = number of ways when we considered node with position from 1 to i-1 and used j times.
        - Time limit is too tight, using freopen does not work
*/
 
#include <bits/stdc++.h>
#define MOD 31333
using namespace std;
ifstream f("radare.in");
ofstream g("radare.out");
 
const int MAXN = 3010;
const int MAXM = 3510;

int n, p, dp[MAXN][MAXM], t[MAXN], id, stop[MAXN], num[MAXN], pos[MAXN], mu[MAXN];
vector<int> a[MAXN];

void dfs(int u, int p) {
    pos[++id] = u;
    num[u] = 1;
    for (int i = 0; i < int(a[u].size()); i++) {
        int v = a[u][i];
        if (v == p) continue;
        dfs(v, u);
        num[u] += num[v];
    }
    stop[u] = id;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    f >> n >> p;
    for (int i = 1; i < n; i++) {
        int u, v;
        f >> u >> v;
        a[u].emplace_back(v);
        a[v].emplace_back(u);
    }
    mu[0] = 1;
    for (int i = 1; i <= n; i++) {
        f >> t[i];
        mu[i] = mu[i-1] * 2 % MOD;
    }
 
    dfs(1, 0);
    dp[1][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= p; j++) {
            if (dp[i][j] == 0) continue;
            int u = pos[i];
            // not choosing tree with root u
            dp[stop[u]+1][j] = (dp[stop[u]+1][j] + mu[num[u]-1] * dp[i][j] % MOD) % MOD;
            // choosing tree with root u
            if (j + t[u] <= p) dp[i+1][j+t[u]] = (dp[i+1][j+t[u]] + dp[i][j]) % MOD;
        }
    g << dp[n+1][p];
    return 0;
}
