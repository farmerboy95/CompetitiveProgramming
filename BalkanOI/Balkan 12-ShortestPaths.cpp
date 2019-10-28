/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: 
        - More or less like this implementation: https://github.com/luciocf/OI-Problems/blob/master/Balkan/Balkan%202012/paths.cpp
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
typedef pair<ll, int> IIl;
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 2010;
const int MAXM = 10010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, m, s, k, t, parentPath[MAXN], parent[MAXN], son[MAXN];
vector<II> a[MAXN];
vector<int> path, A[MAXN];
ll d[MAXN], D[MAXN];
bool lck[MAXN], inPath[MAXN], ok[MAXN];
multiset<ll> val[MAXN];
priority_queue<IIl, vector<IIl>, greater<IIl> > h;

void dijkstraFromSource() {
    FOR(i,1,n) {
        d[i] = 1e18;
        lck[i] = false;
    }
    d[s] = 0;
    while (!h.empty()) h.pop();
    h.push(IIl(d[s], s));

    while (!h.empty()) {
        while (!h.empty() && h.top().FI != d[h.top().SE]) h.pop(); 
        if (h.empty()) break;
        int u = h.top().SE;
        h.pop();
        lck[u] = true;
        FOR(i,0,SZ(a[u])-1) {
            int v = a[u][i].FI;
            int c = a[u][i].SE;
            if (!lck[v] && d[v] > d[u] + c) {
                d[v] = d[u] + c;
                h.push(IIl(d[v], v));
                parent[v] = u;
            }
            else if (d[v] == d[u] + c && u == parentPath[v]) {
                // this part will force child nodes in given tree are actually child nodes in the shortest path tree
                parent[v] = u;
            }
        }
    }
}

void dijkstraFromSink() {
    FOR(i,1,n) {
        D[i] = 1e18;
        lck[i] = false;
    }
    D[t] = 0;
    while (!h.empty()) h.pop();
    h.push(IIl(D[t], t));

    while (!h.empty()) {
        while (!h.empty() && h.top().FI != D[h.top().SE]) h.pop(); 
        if (h.empty()) break;
        int u = h.top().SE;
        h.pop();
        lck[u] = true;
        FOR(i,0,SZ(a[u])-1) {
            int v = a[u][i].FI;
            int c = a[u][i].SE;
            if (!lck[v] && D[v] > D[u] + c) {
                D[v] = D[u] + c;
                h.push(IIl(D[v], v));
            }
        }
    }
}

void remove(int u) {
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i].FI;
        int c = a[u][i].SE;

        // you should read the "add" function first
        // we can reach some new nodes in dfs1, as we iterate given path from root to leaf
        // this "remove" function allows us to remove added values in "add" function
        // the idea is the same as "add" function but v is now an "ok" node, which is not in the subtree of previous "ban"
        if (ok[v] && v != parentPath[u] && val[v].count(c + D[u])) {
            multiset<ll>::iterator it = val[v].find(c + D[u]);
            val[v].erase(it);
        }
    }
}

void dfs1(int u, int p, int ban) {
    inPath[u] = false;
    remove(u);

    FOR(i,0,SZ(A[u])-1) {
        int v = A[u][i];
        if (v == p || v == ban) continue;
        dfs1(v, u, ban);
    }
}

void add(int u) {
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i].FI;
        int c = a[u][i].SE;
        // u is now not in the subtree of considering point "ban"
        // if v is in that subtree and edge (u, v) is not in the given path, 
        // we should add the edge (u, v) + dist(t, v) (in the init graph) to the multiset
        if (inPath[v] && v != son[u] && v != parentPath[u]) {
            val[u].insert(c + D[v]);
        }
    }
}

void dfs2(int u, int p, int ban) {
    ok[u] = true;
    add(u);

    FOR(i,0,SZ(A[u])-1) {
        int v = A[u][i];
        if (v == p || v == ban) continue;
        dfs2(v, u, ban);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> s >> t;
    FOR(i,1,m) {
        int u, v, c;
        cin >> u >> v >> c;
        a[u].push_back(II(v, c));
        a[v].push_back(II(u, c));
    }

    // set parent node of each node in the given shortest path
    cin >> k;
    FOR(i,1,k) {
        int u;
        cin >> u;
        if (i == 1) parentPath[u] = 0;
        else parentPath[u] = path.back();
        path.push_back(u);
    }

    // marking son of each node in the given shortest path
    FOR(i,1,k-1) son[path[i-1]] = path[i];

    // get shortest distance from starting point to every node
    dijkstraFromSource();
    // get shortest distance from every node to ending point
    dijkstraFromSink();

    // create shortest path tree
    FOR(i,1,n)
        if (parent[i]) {
            A[i].push_back(parent[i]);
            A[parent[i]].push_back(i);
        }

    // inPath[i] is whether node u is in the subtree of a considering node v
    FOR(i,1,n) inPath[i] = true;

    FOR(i,0,SZ(path)-2) {
        int u = path[i];

        dfs1(u, parent[u], path[i+1]);
        dfs2(u, parent[u], path[i+1]);

        // get result
        ll res = 1e18;
        FOR(j,1,n)
            if (ok[j] && SZ(val[j])) res = min(res, d[j] + *val[j].begin());
        if (res == 1e18) cout << "-1\n";
        else cout << res << "\n";
    }

    return 0;
}
