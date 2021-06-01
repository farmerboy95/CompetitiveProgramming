/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://atcoder.jp/contests/abc193/editorial/817
        - https://codeforces.com/blog/entry/88211?#comment-766047

        - Let's suppose you had to minimize the number of adjacent pairs of cells with 
        different colors. For a final coloring of the grid, this number can be calculated 
        by dividing the nodes of the grid-graph (graph formed by adding edges among all 
        pairs of cells which share a side) into 2 parts based on their colors and then 
        counting the edges which connect nodes in different parts.
        - To minimize this value, you can just find the minimum-cut of the graph. But you 
        also have to ensure that cells that were already colored and had different colors 
        are in different parts of the cut. For this, you can add an edge with infinity 
        capacity from the source to each cell which is already colored black and from 
        each cell which is already colored white to the sink. These edges can never be 
        part of a minimum cut dividing source and sink and hence they will ensure that 
        edges with fixed but different colors are in different parts.
        - But there is a problem, let's consider an edge B-B, this one should be counted
        in the result. These 2 Bs are on the same part of the graph, how can we make them 
        being in different parts? Notice that the endpoints of all edges in the grid graph 
        have different value of (row no. + col no.) mod 2. In other words, our graph is a
        bipartite one. If we flip the fixed color of every node with (row no. + col no.) mod 2 
        == 1, then edges whose endpoints had different colors will now have same colors and 
        vice-versa.
        - The situation will be
            + Lost 1 point if c[1][1] is B and c[1][2] is W
            + Lost 1 point if c[1][1] is W and c[1][2] is B
            + Lost 1 point if c[1][1] is B and c[2][2] is W
            + Lost 1 point if c[1][1] is W and c[2][1] is B
            + Lost 1 point if c[1][2] is B and c[1][3] is W
            ...
        - Now we can make flow graph:
            + Add an edge of capacity 1 from (i, j) to (i, j+1)
            + Add an edge of capacity 1 from (i, j) to (i+1, j)
            + Add an edge of capacity 1 from (i, j) to (i-1, j)
            + Add an edge of capacity 1 from (i, j) to (i, j-1)
            + If c[i][j] = B after flipping, add an edge of capacity INF from S to (i,j)
            + If c[i][j] = W after flipping, add an edge of capacity INF from (i,j) to W
            + The ? ones will choose the min when placing ifself to one or another part 
            of the graph during maxflow process.
        - Then find the min cut from S to T = max flow from S to T
*/

#include <bits/stdc++.h>
#define FI first
#define SE second
#define ALL(a) a.begin(), a.end()
#define SZ(a) int((a).size())
#define MS(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define TRAV(x, a) for (auto &x : a)

using namespace std;
using ll = long long; using ld = double; 
using pi = pair<int, int>; using pl = pair<ll, ll>; using pd = pair<ld, ld>;
using cd = complex<ld>; using vcd = vector<cd>;

using vi = vector<int>; using vl = vector<ll>;
using vd = vector<ld>; using vs = vector<string>;
using vpi = vector<pi>; using vpl = vector<pl>; using vpd = vector<pd>; // vector<pair>

template<class T> using min_pq = priority_queue<T, vector<T>, greater<T> >;
template<class T> inline int ckmin(T& a, const T& val) { return val < a ? a = val, 1 : 0; }
template<class T> inline int ckmax(T& a, const T& val) { return a < val ? a = val, 1 : 0; }
template<class T> void remDup(vector<T>& v) { sort(ALL(v)); v.erase(unique(ALL(v)), end(v)); }

constexpr int pct(int x) { return __builtin_popcount(x); } // # of bits set
constexpr int bits(int x) { return x == 0 ? 0 : 31-__builtin_clz(x); } // floor(log2(x)) 
constexpr int p2(int x) { return 1<<x; }
constexpr int msk2(int x) { return p2(x)-1; }

ll ceilDiv(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); } // divide a by b rounded up
ll floorDiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); } // divide a by b rounded down
void setPrec(int x) { cout << fixed << setprecision(x); }

// TO_STRING
#define ts to_string
string ts(char c) { return string(1, c); }
string ts(const char* s) { return (string) s; }
string ts(string s) { return s; }
string ts(bool b) { return ts((int)b); }
template<class T> string ts(complex<T> c) { stringstream ss; ss << c; return ss.str(); }
template<class T> using V = vector<T>;
string ts(V<bool> v) {string res = "{"; FOR(i,0,SZ(v)-1) res += char('0'+v[i]); res += "}"; return res; }
template<size_t sz> string ts(bitset<sz> b) { string res = ""; FOR(i,0,SZ(b)-1) res += char('0'+b[i]); return res; }
template<class T, class U> string ts(pair<T,U> p);
template<class T> string ts(T v) { // containers with begin(), end()
    bool fst = 1; string res = "";
    for (const auto& x: v) { if (!fst) res += " "; fst = 0; res += ts(x); }
    return res;
}
template<class T, class U> string ts(pair<T,U> p) { return "("+ts(p.FI)+", "+ts(p.SE)+")"; }

// OUTPUT
template<class T> void pr(T x) { cout << ts(x); }
template<class T, class ...U> void pr(const T& t, const U&... u) { pr(t); pr(u...); }
void ps() { pr("\n"); } // print w/ spaces
template<class T, class ...U> void ps(const T& t, const U&... u) { pr(t); if (sizeof...(u)) pr(" "); ps(u...); }

// DEBUG
void DBG() { cerr << "]" << endl; }
template<class T, class ...U> void DBG(const T& t, const U&... u) { cerr << ts(t); if (sizeof...(u)) cerr << ", "; DBG(u...); }
#define dbg(...) cerr << "Line(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#define chk(...) if (!(__VA_ARGS__)) cerr << "Line(" << __LINE__ << ") -> function(" \
        << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\n", exit(0);

const ld PI = acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
const ld EPS = 1e-9;
const ll MODBASE = 1000000007LL;
const int INF = 0x3f3f3f3f;

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

};

int n;
char ch[MAXN][MAXN];

int getIndex(int u, int v) {
    return u * n + v;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,0,n-1) FOR(j,0,n-1) cin >> ch[i][j];
    int res = 2 * n * (n-1);

    // flip B and W for odd positions
    FOR(i,0,n-1)
        FOR(j,0,n-1)
            if ((i + j) % 2 && ch[i][j] != '?') ch[i][j] ^= 'B' ^ 'W';
    
    int source = n * n, sink = source + 1;
    Dinic dinic(sink + 1);

    FOR(i,0,n-1)
        FOR(j,0,n-1)
            if (ch[i][j] == 'B') dinic.addEdge(source, getIndex(i, j), 100000);
            else if (ch[i][j] == 'W') dinic.addEdge(getIndex(i, j), sink, 100000);
    
    FOR(i,0,n-1)
        FOR(j,0,n-1) {
            if (j + 1 < n) dinic.addEdge(getIndex(i, j), getIndex(i, j+1), 1, 1);
            if (i + 1 < n) dinic.addEdge(getIndex(i, j), getIndex(i+1, j), 1, 1);
        }

    dinic.getFlow(source, sink);
    res -= dinic.flow;

    cout << res;
    return 0;
}
