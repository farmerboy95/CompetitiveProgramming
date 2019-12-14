/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - First we remove a from the graph and dfs from b to find the number of nodes that need to go through
        a to reach b (it's the number of non-visited nodes after dfs from b) (1)
        - Similarly, we remove b from the graph and dfs from a to find the number of nodes that need to go through
        b to reach a (2)
        - result = (1) * (2)
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
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;
 
int n, m, a, b;
bool visit[MAXN];
vector<II> edges;
vector<int> A[MAXN];
 
void createGraphWithout(int x) {
    FOR(i,1,n) A[i].clear();
    FOR(i,0,SZ(edges)-1) {
        int u = edges[i].FI;
        int v = edges[i].SE;
        if (u == x || v == x) continue;
        A[u].emplace_back(v);
        A[v].emplace_back(u);
    }
}
 
void dfs(int u) {
    visit[u] = true;
    FOR(i,0,SZ(A[u])-1) {
        int v = A[u][i];
        if (!visit[v]) dfs(v);
    }
}
 
ll calc(int x) {
    FOR(i,1,n) visit[i] = false;
    dfs(x);
    int cnt = 0;
    FOR(i,1,n) cnt += visit[i];
    return n - cnt - 1;
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m >> a >> b;
        edges.clear();
        FOR(i,1,m) {
            int u, v;
            cin >> u >> v;
            edges.emplace_back(II(u,v));
        }
        ll res = 1;
 
        createGraphWithout(a);
        res = res * calc(b);
        createGraphWithout(b);
        res = res * calc(a);
 
 
        cout << res << "\n";
    }
    return 0;
}