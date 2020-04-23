/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Do not use greedy in any form. This test set is an example.
        3 4
        1 2
        2 3
        2 3
        2 3
        - We use flow to solve this problem. We create 1 source, connections from source
        to each input purchases (we have m edges, with capacity is 2), 1 sink, connections 
        from each child to sink (we have n child, with capacity is the number of cards he has).
        Finally, for each purchase, create one connection from purchase to one child and one
        connection from purchase to another child, both with capacity is 2.
        - After running flow algo, the flow between one purchase and one child would be 0, 1 or 2,
        exactly the same as the problem condition. From here we can extract the result of each
        input purchases.
        - Now we have a number of cards each child has after subtracting from input purchases,
        it's time to use greedy. Proceed with child who has more than one card first, the opponent
        should be anyone. Then we would have children with 0 or 1 card left. Get all the children
        with 1 card and create purchases by pairs.
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
const int MAXN = 110;
const int MAXM = 1010;
const int MAXK = 16;
const int MAXQ = 200010;


const int MAX = 1000000000;
const int oo = 0x3c3c3c3c;
struct Edge {
    int from, to, cap, flow, index;
    Edge(int from, int to, int cap, int flow, int index) : from(from), to(to), cap(cap), flow(flow), index(index) {} 
};

struct Dinic {
    int N, flow, t;
    vector<int> d, Dfs, ptr;
    vector<vector<Edge> > G;
    queue<int> q;
    Dinic(int N) {
        this->N = N;
        G.resize(N);
        ptr.resize(N);
        d.resize(N);
        Dfs.resize(N);
        flow = t = 0;
    }

    void addEdge(int u, int v, int gt, bool rev = false) { 
        G[u].push_back(Edge(u, v, gt, 0, G[v].size()));
        if (u == v) G[u].back().index++;
        if (rev) G[v].push_back(Edge(v, u, gt, 0, G[u].size() - 1)); 
        else G[v].push_back(Edge(v, u, 0, 0, G[u].size() - 1)); 
    }

    bool bfs(int S, int T) {
        FOR(i,0,N-1) d[i] = 0;
        while (!q.empty()) q.pop();
        q.push(S); d[S]=1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == T) return true;
            FOR(i,0,SZ(G[u])-1) {
                int v = G[u][i].to;
                if (!d[v] && G[u][i].cap - G[u][i].flow > 0) {
                    q.push(v);
                    d[v] = d[u] + 1;
                } 
            }
        }
        return false;
    }

    int visit(int u, int Min, int T) {
        if (u == T) return Min;
        if (Dfs[u]!=t) Dfs[u]=t;
        else return 0;
        for (; ptr[u] < (int) G[u].size(); ++ptr[u]) { 
            int v = G[u][ptr[u]].to;
            if (G[u][ptr[u]].cap - G[u][ptr[u]].flow > 0)
                if (Dfs[v] != t && d[v] == d[u]+1)
                    if (int x = visit(v, min(Min, G[u][ptr[u]].cap - G[u][ptr[u]].flow), T)) {
                        G[u][ptr[u]].flow += x;
                        G[v][G[u][ptr[u]].index].flow -= x;
                        return x;
                    }
        }
        return 0;
    }

    void getFlow(int S, int T) {
        while (bfs(S, T)) {
            FOR(i,0,N-1) ptr[i] = 0;
            while (1) {
                t++;
                int x = visit(S, oo, T);
                if (!x) break;
                flow += x;
            }
        }
    }

    vector<II> getResult(int n, int m) {
        vector<II> res;
        FOR(i,1,m) {
            FOR(j,0,SZ(G[i])-1) {
                if (G[i][j].flow == 1) {
                    int node = G[i][j].to - m;
                    res.push_back(II(node, 1));
                    break;
                }
                else if (G[i][j].flow == 2) {
                    int node = G[i][j].to - m;
                    res.push_back(II(node, 2));
                    break;
                }
            }
        }
        return res;
    }

};

int n, m, c[MAXN];
vector<II> edges;
vector<int> res;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    Dinic dinic(1+n+m+1);
    FOR(i,1,m) dinic.addEdge(0, i, 2);
    FOR(i,m+1,m+n) {
        cin >> c[i-m];
        dinic.addEdge(i, n+m+1, c[i-m]);
    }
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        dinic.addEdge(i, m+u, 2);
        dinic.addEdge(i, m+v, 2);
        edges.push_back(II(u, v));
    }
    dinic.getFlow(0, n+m+1);
    vector<II> p = dinic.getResult(n, m);
    FOR(i,0,SZ(p)-1)
        if (p[i].SE == 1) {
            int u = edges[i].FI, v = edges[i].SE;
            c[u]--;
            c[v]--;
            res.push_back(1);
        }
        else {
            int u = edges[i].FI, v = edges[i].SE;
            if (p[i].FI == u) {
                c[u] -= 2;
                res.push_back(2);
            }
            else {
                c[v] -= 2;
                res.push_back(0);
            }
        }
    FOR(i,1,n)
        while (c[i] > 1) {
            c[i] -= 2;
            int diff = i + 1;
            if (diff > n) diff = i - 1;
            edges.push_back(II(i, diff));
            res.push_back(2);
        }
    vector<int> only1;
    FOR(i,1,n)
        if (c[i] == 1) only1.push_back(i);
    while (SZ(only1)) {
        int u = only1.back(); only1.pop_back();
        int v = only1.back(); only1.pop_back();
        edges.push_back(II(u, v));
        res.push_back(1);
    }
    cout << SZ(res) << "\n";
    FOR(i,0,SZ(res)-1) cout << edges[i].FI << ' ' << edges[i].SE << ' ' << res[i] << "\n";
    return 0;
}
