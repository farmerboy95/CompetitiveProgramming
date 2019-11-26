/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Max: 
            + dfs from each node with inner degree 0, all nodes except the starting one are dead
            + only cycles remain, dfs them, only one node in each cycle is still alive (except cycle 1)
        - Min:
            + bfs from nodes with inner degree 0 (mark them as alive), clear their adjacent nodes (mark them as dead), 
            then keep doing bfs
            + only cycles remain, assume size of cycle is K => the minimum number of death is K - K / 2
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
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 1000010;
const int MAXM = 30010;
const int MAXK = 16;
const int MAXQ = 200010;

int n, sh[MAXN], deg[MAXN], cnt;
bool visited[MAXN];
queue<int> q;

void dfs(int u) {
    cnt++;
    visited[u] = true;
    if (!visited[sh[u]]) dfs(sh[u]);
}

int findMin() {
    FOR(i,1,n) visited[i] = false;

    FOR(i,1,n)
        if (deg[i] == 0) q.push(i);

    int res = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        visited[u] = true;
        int v = sh[u];
        if (!visited[v]) {
            res++;
            visited[v] = true;
            if (!visited[sh[v]] && --deg[sh[v]] == 0) q.push(sh[v]);
        }
    }

    FOR(i,1,n)
        if (!visited[i]) {
            cnt = 0;
            dfs(i);
            res += cnt - cnt / 2;
        }
    return res;
}

int findMax() {
    int res = 0;
    FOR(i,1,n)
        if (deg[i] == 0) {
            cnt = 0;
            dfs(i);
            res += cnt - 1;
        }
    
    FOR(i,1,n)
        if (!visited[i]) {
            cnt = 0;
            dfs(i);
            res += cnt - 1 + (cnt == 1);
        }

    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("paintball.in", "r", stdin);
    freopen("paintball.out", "w", stdout);
    cin >> n;
    FOR(i,1,n) cin >> sh[i];
    FOR(i,1,n) deg[sh[i]]++;

    int Max = findMax();
    int Min = findMin();

    cout << Min << ' ' << Max;
    return 0;
}
