/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/85348
        - Keywords: Floyd-Warshall, Bipartite, Negative Cycle
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
const int MAXN = 210;
const int MAXM = 2010;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, d[MAXN][MAXN], u[MAXM], v[MAXM], b[MAXM], col[MAXN];
vector<int> a[MAXN];

bool dfs(int u) {
    for (int v : a[u]) {
        if (col[v] != -1) {
            if (col[v] != 1-col[u]) return false;
        } else {
            col[v] = 1-col[u];
            if (!dfs(v)) return false;
        }
    }
    return true;
}

bool reducable() {
    FOR(k,1,n)
        FOR(i,1,n)
            FOR(j,1,n) 
                if (d[i][j] > d[i][k] + d[k][j]) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n)
        FOR(j,1,n) 
            if (i == j) d[i][j] = 0;
            else d[i][j] = 1e9;
    
    FOR(i,1,m) {
        cin >> u[i] >> v[i] >> b[i];
        d[u[i]][v[i]] = 1;
        d[v[i]][u[i]] = (b[i] ? -1 : 1);
        a[u[i]].push_back(v[i]);
        a[v[i]].push_back(u[i]);
    }

    // check bipartite
    FOR(i,1,n) col[i] = -1;
    col[1] = 0;
    if (!dfs(1)) {
        cout << "NO";
        return 0;
    }

    FOR(k,1,n)
        FOR(i,1,n)
            FOR(j,1,n) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    
    // check negative cycle
    if (reducable()) {
        cout << "NO";
        return 0;
    }

    int res = -1, source = 0;
    FOR(i,1,n)
        FOR(j,1,n) 
            if (d[i][j] > res) {
                res = d[i][j];
                source = i;
            }

    cout << "YES\n";
    cout << res << "\n";
    FOR(i,1,n) cout << d[source][i] << ' ';
    return 0;
}
