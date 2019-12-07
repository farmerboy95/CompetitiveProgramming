/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Binary search the result (limit), create a flow graph:
            + There are edges from source to each student (capacity = 1)
            + There are edges from each bus line to sink (capacity = 1)
            + For each student, if the distance between himself and the nearest bus stop of the bus line is 
            smaller or equal to limit, create an edge from student to bus line
        - After figuring out the result, simply trace the flow graph to get the specific result for each student.
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

const int MAX = 1000000000;
const int oo = 0x3c3c3c3c;
struct Edge {
    int from, to, cap, flow, index;
    Edge(int from, int to, int cap, int flow, int index) : from(from), to(to), cap(cap), flow(flow), index(index) {} 
};

int mustWalk[MAXN][MAXN];

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

    void printResult(int n, int k) {
        FOR(i,1,n) {
            FOR(j,0,SZ(G[i])-1) {
                if (G[i][j].flow == 1) {
                    int busLine = G[i][j].to - n;
                    cout << mustWalk[i][busLine] << "\n";
                    break;
                }
            }
        }
    }

};

int n, m, c, k;
vector<int> line[MAXN];
vector<II> student, stop;

int dist(II a, II b) {
    return (a.FI - b.FI) * (a.FI - b.FI) + (a.SE - b.SE) * (a.SE - b.SE);
}

bool check(int limit) {
    Dinic dinic(1+n+k+1);
    FOR(i,1,n) dinic.addEdge(0, i, 1);
    FOR(i,n+1,n+k) dinic.addEdge(i, n+k+1, c);
    FOR(i,1,n) {
        FOR(j,1,k) {
            int Min = 1e9;
            FOR(p,0,SZ(line[j])-1) Min = min(Min, dist(student[i-1], stop[line[j][p]-1]));
            if (Min <= limit) dinic.addEdge(i, n+j, 1);
        }
    }
    dinic.getFlow(0, n+k+1);
    return dinic.flow == n;
}

void printResult(int limit) {
    cout << limit << "\n";
    Dinic dinic(1+n+k+1);
    FOR(i,1,n) dinic.addEdge(0, i, 1);
    FOR(i,n+1,n+k) dinic.addEdge(i, n+k+1, c);
    FOR(i,1,n) {
        FOR(j,1,k) {
            int Min = 1e9;
            int pos = 0;
            FOR(p,0,SZ(line[j])-1) {
                int distance = dist(student[i-1], stop[line[j][p]-1]);
                if (distance < Min) {
                    Min = distance;
                    pos = line[j][p];
                }
            }
            if (Min <= limit) {
                dinic.addEdge(i, n+j, 1);
                mustWalk[i][j] = pos;
            }
        }
    }
    dinic.getFlow(0, n+k+1);
    dinic.printResult(n, k);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> c >> k;
    FOR(i,1,n) {
        II p;
        cin >> p.FI >> p.SE;
        student.emplace_back(p);
    }
    FOR(i,1,m) {
        II p;
        cin >> p.FI >> p.SE;
        stop.emplace_back(p);
    }
    FOR(i,1,k) {
        int p, x;
        cin >> p;
        while (p--) {
            cin >> x;
            line[i].emplace_back(x);
        }
    }
    int dau = 0, cuoi = 10000000, mid;
    while (dau <= cuoi) {
        mid = (dau + cuoi) >> 1;
        if (check(mid)) cuoi = mid-1;
        else dau = mid+1;
    }
    if (dau > 10000000) {
        cout << -1;
        return 0;
    }
    printResult(dau);
    return 0;
}
