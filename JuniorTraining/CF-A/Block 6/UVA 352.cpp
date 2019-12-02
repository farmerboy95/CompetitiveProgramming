/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Simple DFS to find number of connected components
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
int n;
int dx[8] = {1,0,0,-1,1,1,-1,-1};
int dy[8] = {0,1,-1,0,-1,1,-1,1};

void dfs(int u, int v) {
    visited[u][v] = true;
    FOR(i,0,7) {
        int g = u + dx[i];
        int h = v + dy[i];
        if (g >= 1 && g <= n && h >= 1 && h <= n)
            if (ch[g][h] == '1' && !visited[g][h]) dfs(g, h);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 0;
    while (cin >> n) {
        t++;
        FOR(i,1,n) FOR(j,1,n) cin >> ch[i][j];
        MS(visited, false);
        int cnt = 0;
        FOR(i,1,n)
            FOR(j,1,n)
                if (ch[i][j] == '1' && !visited[i][j]) {
                    dfs(i,j);
                    cnt++;
                }
        printf("Image number %d contains %d war eagles.\n", t, cnt);
    }
    return 0;
}
