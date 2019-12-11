/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Simple topological sort
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
typedef pair<ll, ll> II;
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m;
vector<int> ans, a[MAXN];
int visited[MAXN];

void dfs(int u) {
    visited[u] = true;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (!visited[v]) dfs(v);
    }
    ans.push_back(u);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    while (cin >> n >> m && n) {
        FOR(i,1,n) a[i].clear();
        FOR(i,1,m) {
            int u, v;
            cin >> u >> v;
            a[u].emplace_back(v);
        }
        ans.clear();
        FOR(i,1,n) visited[i] = false;
        FOR(i,1,n)
            if (!visited[i]) dfs(i);
        reverse(ALL(ans));
        FOR(i,0,SZ(ans)-1) cout << ans[i] << ' ';
        cout << "\n";
    }
    return 0;
}
