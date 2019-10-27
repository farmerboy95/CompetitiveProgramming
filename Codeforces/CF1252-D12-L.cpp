/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use max flow
        - From source, add edge from it to each of the worker, capacity = 1 (k nodes of worker here)
        - From each worker, add edge from it to the material that he is familiar to work on, 
        capacity = 1, before that, re-number material that workers need, throw away all 
        materials that no one uses. (max k nodes of material here)
        - From each material, add edges from it to the road that can be constructed using this material
        capacity = 1 (n nodes of road here)
        - Because we have n edges in the graph, there must be one cycle in the graph, get that cycle (size x),
        for each road in cycle, add edge from it to a special node (cap = 1) that then will have the edge
        to the sink (capacity = x-1) (because we only allow x-1 road to be built)
        - If road is not in the cycle, simply add edge from it to the sink (cap = 1)
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
const int MAXN = 2010;
const int MAXM = 10010;
const int MAXK = 110;
const int MAXQ = 200010;
const int MAX = 1000000000;
const int oo = 0x3c3c3c3c;

int n, k, a[MAXN], m[MAXM], c[MAXN], mate, work[MAXN], road[MAXN];
bool inCycle[MAXN];
vector<int> b[MAXN], B[MAXN], A[MAXN];
map<int, int> ma;

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
        // cout << u << ' ' << v << ' ' << gt << endl;
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

    void getRes() {
        // if flow < n-1, it means the graph is not connected
        if (flow < n-1) {
            cout << -1;
            return;
        }

        // mark workers who need to work
        FOR(i,1,k) {
            FOR(j,0,SZ(G[i])-1) {
                Edge e = G[i][j];
                int u = i, v = e.to, fl = e.flow;
                if (v > k && fl == 1) work[u] = true;
            }
        }

        // mark roads which need to be built with the material needed
        FOR(i,1,mate)
            FOR(j,0,SZ(G[k+i])-1) {
                Edge e = G[k+i][j];
                int u = i, v = e.to, fl = e.flow;
                if (v > k + mate && fl == 1) {
                    v -= k + mate;
                    road[v] = i;
                }
            }

        // map 2 above arrays
        FOR(i,1,k)
            if (work[i]) {
                int col = ma[c[i]];
                FOR(j,1,n)
                    if (col == road[j]) {
                        road[j] = 0;
                        cout << j << ' ' << a[j] << "\n";
                        break;
                    }
            } 
            else cout << "0 0\n";

    }

};

bool visited[MAXN];
int root = 0;
vector<int> listV;

void dfs(int u, int p) {
    visited[u] = true;
    FOR(i,0,SZ(A[u])-1) {
        int v = A[u][i];
        if (v != p) {
            if (!visited[v]) dfs(v, u);
            else {
                root = v;
            }
        }
        if (root) {
            listV.push_back(u);
            return;
        }
    }
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,n) {
        cin >> a[i] >> m[i];
        FOR(j,1,m[i]) {
            int x;
            cin >> x;
            b[i].emplace_back(x);
        }
    }
    FOR(i,1,k) cin >> c[i];

    // re-numbering the materials
    FOR(i,1,k)
        if (!ma.count(c[i])) ma[c[i]] = ++mate;

    FOR(i,1,n)
        FOR(j,0,m[i]-1) {
            int col = b[i][j];
            if (ma.count(col)) B[i].emplace_back(ma[col]);
        }
    
    // create init graph
    FOR(i,1,n) {
        A[i].emplace_back(a[i]);
        A[a[i]].emplace_back(i);
    }

    // get cycle and mark roads that are in cycle
    dfs(1, 0);
    while (listV[SZ(listV)-1] != root) listV.pop_back();
    int len = SZ(listV);
    listV.push_back(listV[0]);
    FOR(i,1,SZ(listV)-1) {
        if (a[listV[i-1]] == listV[i]) inCycle[listV[i-1]] = true;
        else if (a[listV[i]] == listV[i-1]) inCycle[listV[i]] = true;
    }
    
    // built flow graph
    Dinic dinic(1+k+mate+n+1+1);
    FOR(i,1,k) dinic.addEdge(0, i, 1);
    FOR(i,1,k) dinic.addEdge(i, k + ma[c[i]], 1);
    FOR(i,1,n)
        FOR(j,0,SZ(B[i])-1) dinic.addEdge(k + B[i][j], k + mate + i, 1);
    FOR(i,1,n)
        if (inCycle[i]) dinic.addEdge(k + mate + i, k + mate + n + 1, 1);
        else dinic.addEdge(k + mate + i, k + mate + n + 1 + 1, 1);
    dinic.addEdge(k + mate + n + 1, k + mate + n + 1 + 1, len-1);
    dinic.getFlow(0, k + mate + n + 1 + 1);
    dinic.getRes();
    return 0;
}