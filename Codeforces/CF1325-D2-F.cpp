/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Our graph is undirected, so there are only 2 kinds of edge: Forward edge and Back edge.
        - Let's say we are at a node u in the DFS tree, consider a back edge that connects u to a 
        furthest ancestor of u, called v, if number of nodes from v to u >= ceil(sqrt(n)) => we print 2.
        - No such node v? That means a node can block at most ceil(sqrt(n))-1 other nodes, the ones
        connected to it by back edges, just mark them and print 1
        - Mainly from https://codeforces.com/blog/entry/74235
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
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, depth[MAXN], sq, marked[MAXN];
vector<int> a[MAXN], s;

void dfs(int u) {
    s.push_back(u);
    depth[u] = SZ(s);
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (!depth[v]) dfs(v);
        else if (depth[u] - depth[v] + 1 >= sq) {
            cout << "2\n";
            cout << depth[u] - depth[v] + 1 << "\n";
            FOR(j,depth[v]-1,depth[u]-1) cout << s[j] << " ";
            exit(0);
        }
    }
    if (!marked[u]) {
        FOR(i,0,SZ(a[u])-1) {
            int v = a[u][i];
            marked[v] = 1;
        }
    }
    s.pop_back();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    while (sq * sq < n) sq++;
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    dfs(1);
    cout << "1\n";
    FOR(i,1,n)
        if (!marked[i] && sq) {
            sq--;
            cout << i << " ";
        }
    return 0;
}
