/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Submitted at: https://open.kattis.com/problems/congest
        - Idea: https://www.csc.kth.se/~austrin/icpc/finals2013solutions.pdf
        - Keep directed edges (u, v) that d[u] = d[v] + t
        - We can group the commuter based on their distance to downtown, and process 
        each group separately, as two commuters that are at two nodes that have a 
        different distance to downtown can never interfere with each other.
        - For each group, Add a dummy node s and connect it to all the starting nodes 
        of the commuters in the group. Then, the maximum number of commuters that can 
        go simultaneously within this group equals the maximum number of edge-disjoint 
        paths from s to downtown, which equals the max-flow from s to downtown if you 
        put unit capacities on all the (directed) edges.
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

const int MAXN = 25010;
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

struct Node {
    int minTime;
    int node;
    Node(int minTime = 0, int node = 0) : minTime(minTime), node(node) {}
    bool friend operator< (Node a, Node b) {
        return a.minTime > b.minTime;
    }
};

int n, m, k, C[MAXN], d[MAXN];
vector<vi> edges, newEdges;
vpi a[MAXN];
priority_queue<Node> h;

void dijkstra() {
    FOR(i,1,n) d[i] = INF;
    d[1] = 0;
    h.push(Node(0, 1));
    while (1) {
        while (!h.empty() && h.top().minTime != d[h.top().node]) h.pop();
        if (h.empty()) break;
        Node r = h.top();
        h.pop();
        int u = r.node;
        FOR(i,0,SZ(a[u])-1) {
            int v = a[u][i].FI;
            int c = a[u][i].SE;
            int ti = d[u] + c;
            if (d[v] > ti) {
                d[v] = ti;
                h.push(Node(d[v], v));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    FOR(i,1,m) {
        int u, v, c;
        cin >> u >> v >> c;
        edges.push_back({u, v, c});
        a[u].push_back({v, c});
        a[v].push_back({u, c});
    }

    FOR(i,1,k) cin >> C[i];
    dijkstra();

    FOR(i,0,SZ(edges)-1) {
        int u = edges[i][0], v = edges[i][1], c = edges[i][2];
        if (d[u] == d[v] + c || d[v] == d[u] + c) newEdges.push_back(edges[i]);
    }

    vpi D;
    FOR(i,1,k) D.push_back({d[C[i]], C[i]});
    sort(ALL(D));

    int now = 0, res = 0;
    while (now < SZ(D)) {
        pi z = D[now];
        now++;
        vi init;
        init.push_back(z.SE);
        while (now < SZ(D) && D[now].FI == z.FI) {
            init.push_back(D[now].SE);
            now++;
        }

        Dinic dinic(n+1);
        int source = 0, sink = 1;

        TRAV(x, init) {
            dinic.addEdge(source, x, 1);
        }
        
        TRAV(x, newEdges) {
            int u = x[0], v = x[1], c = x[2];
            if (d[u] == d[v] + c) dinic.addEdge(u, v, 1);
            if (d[v] == d[u] + c) dinic.addEdge(v, u, 1);
        }

        dinic.getFlow(source, sink);
        res += dinic.flow;
    }
    cout << res;

    return 0;
}
