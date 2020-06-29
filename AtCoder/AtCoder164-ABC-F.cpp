/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - First, when binary notated, the value of each bit can be determined independently, so we
        consider each bit independently. Then this problem falls into a construction of matrix of 
        size NxN consisting of 0 and 1 that satisfies the conditions. 
        - We solve the above problem by max-flow. We have 4 + n + n nodes.
            + 0 as source.
            + 1 as sink.
            + 2 manages the remaining 1s after filling the columns.
            + 3 manages the remaining 1s after filling the row.
            + 4 -> n+3: rows from 1 to n
            + n+4 -> n+n+3: columns from 1 to n
        - The addRange function shows how to add edges to keep the number of 1s in a row / column
        in the range of [Min, Max]. The way of using the function depends on the current entity is
        a row or a column. Then we need to have edges from rows to columns and from 3 to 2, to the number
        of filled 1s to each other (row -> col, col -> row)
        - The basic idea is to fill the matrix with lower bound of number of 1s. When we fill a row with
        some 1s, columns may need to be filled too, so the edges from rows to columns will do it. If there
        are remainders of 1 in column, the edge from 3 to 2 will pass it back to rows to fill again.
        Therefore, it's guaranteed to fill with the lower bound number of 1s if possible.
        - Finally, we can try to trace the result if the solution exists based on the graph after getting
        flow.
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
using ull = unsigned long long;
using ld = double;
typedef pair<int, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 510;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, s[MAXN], t[MAXN];
ull u[MAXN], v[MAXN], res[MAXN][MAXN];

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
    int expected;

    Dinic(int N) {
        this->N = N;
        G.resize(N);
        ptr.resize(N);
        d.resize(N);
        Dfs.resize(N);
        flow = t = expected = 0;
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

    void addRange(int u, int v, int Min, int Max) {
        if (Max < Min) return;
        addEdge(0, v, Min);
        addEdge(u, 1, Min);
        addEdge(u, v, Max - Min);
        expected += Min;
    }
    
    void getResult(int n, int bit) {
        FOR(i,1,n) {
            int I = i+3;
            FOR(j,0,SZ(G[I])-1) {
                int node = G[I][j].to - n - 3;
                if (node >= 1 && node <= n)
                    if (G[I][j].flow == 1) res[i][node] += (1ULL << bit);
            }
        }
    }

};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> s[i];
    FOR(i,1,n) cin >> t[i];
    FOR(i,1,n) cin >> u[i];
    FOR(i,1,n) cin >> v[i];

    FOR(bit,0,63) {
        Dinic dinic(4+n+n);
        FOR(i,1,n) {
            if (s[i]) {
                if (u[i] & (1ULL << bit)) {
                    // row OR = 1
                    dinic.addRange(2, i+3, 1, n);
                } else {
                    // row OR = 0
                    // range [0, 0] => do nothing
                }
            } else {
                if (u[i] & (1ULL << bit)) {
                    // row AND = 1
                    dinic.addRange(2, i+3, n, n);
                } else {
                    // row AND = 0
                    dinic.addRange(2, i+3, 0, n-1);
                }
            }

            if (t[i]) {
                if (v[i] & (1ULL << bit)) {
                    // col OR = 1
                    dinic.addRange(n+i+3, 3, 1, n);
                } else {
                    // col OR = 0
                    // range [0, 0] => do nothing
                }
            } else {
                if (v[i] & (1ULL << bit)) {
                    // col AND = 1
                    dinic.addRange(n+i+3, 3, n, n);
                } else {
                    // col AND = 0
                    dinic.addRange(n+i+3, 3, 0, n-1);
                }
            }
            FOR(j,1,n) dinic.addEdge(i+3, n+j+3, 1);
        }
        dinic.addEdge(3, 2, 2000000000);

        dinic.getFlow(0, 1);
        if (dinic.flow != dinic.expected) {
            cout << -1;
            return 0;
        }

        dinic.getResult(n, bit);
    }
    FOR(i,1,n) {
        FOR(j,1,n) cout << res[i][j] << ' ';
        cout << "\n";
    }
    return 0;
}
