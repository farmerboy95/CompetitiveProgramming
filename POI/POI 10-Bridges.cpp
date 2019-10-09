/*
    Author: Nguyen Tan Bao
    Status: AC after reading editorial
    Idea: 
        - https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/POI/official/2010/editorial/mos.pdf
        - https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/POI/official/2010/code/mos/prog/mos.cpp
        - https://www.geeksforgeeks.org/hierholzers-algorithm-directed-graph/
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
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

struct InputEdge {
    int u, v, l, p;
    InputEdge(int u = 0, int v = 0, int l = 0, int p = 0) : u(u), v(v), l(l), p(p) {}
};

vector<InputEdge> a;
int n, m, deg[MAXN];
vector<int> f[MAXN];
set<II> s;
map<II, int> ma;

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

    void printResult() {
        FOR(i,1,n)
            FOR(j,0,SZ(G[i])-1) {
                Edge e = G[i][j];
                int u = i, v = e.to - n - 1, fl = e.flow;
                // only get edges that have flow = 1 in the flow graph
                if (fl == 1) s.insert(II(u, a[v].u + a[v].v - u));
            }
        FOR(i,0,m-1)
            if (s.count(II(a[i].v, a[i].u))) {
                ma[II(a[i].v, a[i].u)] = i;
                f[a[i].v].push_back(a[i].u);
            }
            else {
                ma[II(a[i].u, a[i].v)] = i;
                f[a[i].u].push_back(a[i].v);
            }
        // use Hierholzer's algorithm to get the result
        vector<int> circuit;
        stack<int> currPath;
        currPath.push(1);
        int currVtx = 1;
        while (!currPath.empty()) {
            if (SZ(f[currVtx])) {
                currPath.push(currVtx);
                int nextVtx = f[currVtx][SZ(f[currVtx])-1];
                f[currVtx].pop_back();
                currVtx = nextVtx;
            }
            else {
                circuit.emplace_back(currVtx);
                currVtx = currPath.top();
                currPath.pop();
            }
        }
        FORE(i,SZ(circuit)-2,0) {
            int u = circuit[i+1], v = circuit[i];
            cout << ma[II(u, v)] + 1 << ' ';
        }
        cout << "\n";
    }

};

// create graph just like the editorial and run Dinic's algorithm
bool check(int limit) {
    Dinic dinic(n+m+2);
    FOR(i,1,n) dinic.addEdge(0, i, deg[i] / 2);
    FOR(i,0,m-1) {
        if (a[i].l <= limit) dinic.addEdge(a[i].u, n+i+1, 1);
        if (a[i].p <= limit) dinic.addEdge(a[i].v, n+i+1, 1);
        dinic.addEdge(n+i+1, n+m+1, 1);
    }
    dinic.getFlow(0, n+m+1);
    return dinic.flow == m;
}

// rerun Dinic with limit and print result
void printResult(int limit) {
    Dinic dinic(n+m+2);
    FOR(i,1,n) dinic.addEdge(0, i, deg[i] / 2);
    FOR(i,0,m-1) {
        if (a[i].l <= limit) dinic.addEdge(a[i].u, n+i+1, 1);
        if (a[i].p <= limit) dinic.addEdge(a[i].v, n+i+1, 1);
        dinic.addEdge(n+i+1, n+m+1, 1);
    }
    dinic.getFlow(0, n+m+1);
    dinic.printResult();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,m) {
        int u, v, l, p;
        cin >> u >> v >> l >> p;
        a.emplace_back(InputEdge(u, v, l, p));
        deg[u]++;
        deg[v]++;
    }
    // binary search the upper limit of edge value
    int dau = 1, cuoi = 1000, mid;
    while (dau <= cuoi) {
        mid = (dau + cuoi) >> 1;
        if (check(mid)) cuoi = mid-1;
        else dau = mid+1;
    }
    if (dau > 1000) cout << "NIE\n";
    else {
        cout << dau << "\n";
        printResult(dau);
    }
    return 0;
}
