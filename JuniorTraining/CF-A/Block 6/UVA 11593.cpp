/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - If there is an alive cell in the connected component, increase the result
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
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

char ch[MAXN][MAXN];
bool visited[MAXN][MAXN];
int n, m, alive;

int dx[4] = {1,0,0,-1};
int dy[4] = {0,1,-1,0};

void dfs(int u, int v) {
    visited[u][v] = true;
    if (ch[u][v] == 'x') alive++;
    FOR(i,0,7) {
        int g = u + dx[i];
        int h = v + dy[i];
        if (g >= 1 && g <= n && h >= 1 && h <= n)
            if ((ch[g][h] == 'x' || ch[g][h] == '@') && !visited[g][h]) dfs(g, h);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cin >> n;
        FOR(i,1,n)
            FOR(j,1,n) cin >> ch[i][j];
        MS(visited, false);
        int res = 0;
        FOR(i,1,n)
            FOR(j,1,n)
                if ((ch[i][j] == 'x' || ch[i][j] == '@') && !visited[i][j]) {
                    alive = 0;
                    dfs(i,j);
                    if (alive) res++;
                }
        cout << "Case " << o << ": " << res << "\n";
    }
    return 0;
}
