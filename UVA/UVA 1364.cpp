/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Mostly from: https://raw.githubusercontent.com/engyebrahim/CompetitiveProgramming/master/UVA/1364.cpp
        - Find all biconnected components of the graph.
        - If a biconnected component is a bipartite graph, there is no way to put the knights into
        the Round Table.
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
const int MAXN = 1010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, edge[MAXN][MAXN], low[MAXN], num[MAXN], dfsNum, team[MAXN], col[MAXN], ok[MAXN];
vector<int> a[MAXN];
vector<vector<int> > group;
stack<II> s;

// find biconnected components
void dfs(int u, int p) {
    num[u] = low[u] = ++dfsNum;
    for (int v : a[u]) {
        if (v == p) continue;
        if (num[v] == 0) {
            s.push(II(u, v));
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= num[u]) {
                II r;
                vector<int> g;
                do {
                    r = s.top();
                    s.pop();
                    g.push_back(r.SE);
                } while (r != II(u, v) && r != II(v, u));
                group.push_back(g);
            }
        }
        else {
            // back edge
            if (num[v] < num[u]) s.push(II(u, v));
            low[u] = min(low[u], num[v]);
        }
    }
}

// check if a biconnected component is bipartite
bool isBipartite(int u) {
    bool res = true;
    for (int v : a[u]) {
        if (team[v] != team[u]) continue;
        if (col[v] == -1) {
            col[v] = 1-col[u];
            res &= isBipartite(v);
        }
        else if (col[v] == col[u]) return false;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    while (cin >> n >> m && !(n == 0 && m == 0)) {
        FOR(i,1,n) FOR(j,i+1,n) edge[i][j] = 1;
        FOR(i,1,n) {
            a[i].clear();
            team[i] = -1;
            ok[i] = 0;
        }
        group.clear();
        while (m--) {
            int u, v;
            cin >> u >> v;
            if (u > v) swap(u, v);
            edge[u][v] = 0;
        }
        // remove all input edges and create graph
        FOR(i,1,n) FOR(j,i+1,n)
            if (edge[i][j]) {
                a[i].push_back(j);
                a[j].push_back(i);
            }
        // find all biconnected components, put into "group"
        dfsNum = 0;
        FOR(i,1,n) low[i] = num[i] = 0;
        FOR(i,1,n)
            if (num[i] == 0) dfs(i, 0);
        
        // coloring each component to see if it's bipartite
        FOR(i,0,SZ(group)-1) {
            FOR(j,0,SZ(group[i])-1) {
                team[group[i][j]] = i;
                col[group[i][j]] = -1;
            }
            if (!isBipartite(group[i][0]))
                FOR(j,0,SZ(group[i])-1) ok[group[i][j]] = 1;
        }
        int res = n;
        FOR(i,1,n) res -= ok[i];
        cout << res << "\n";
    }
    return 0;
}
