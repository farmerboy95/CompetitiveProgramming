/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://atcoder.jp/contests/acl1/editorial/119
        - Use Min Cost Max Flow to solve.

        - For fixed final positions of pieces, let us check whether they are possible.
        - This problem is equivalent to the bipartite matching problem. Specifically, 
        consider a bipartite graph with left vertices corresponding to the initial 
        positions of the pieces, and with right vertices corresponding to the final 
        positions of the pieces, and with edges corresponding to reachable pairs. 
        It suffices to check whether this graph has a complete matching.
        - It is obvious that existence of a perfect matching is necessary. Sufficiency 
        is shown as follows. First, pick an arbitrary perfect matching. Let us move 
        pieces along with this perfect matching. There can be problems if some pieces 
        collide. This can be circumvented by the following steps:
            + If a collision is about to happen, move the piece that originally 
            occupied the cell.
            + If the piece that originally occupied the cell cannot move, swap the 
            destination of the two about-to-collide pieces. If that incurs another 
            collision, do the same recursively.
        - Finally we get a sequence of moves where no pieces collide, which means 
        sufficiency is shown.
        - Let us maximize the number of operations performed. It is equivalent to 
        maximizing the sum of row numbers and column numbers of final positions. 
        Therefore, it can be solved by converting the aforementioned maximum matching 
        problem to the minimum-cost flow problem.
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

const int MAXN = 55;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct Edge {
    int from, to, cap, flow, index;
    ll cost;
    Edge(int _from, int _to, int _cap, int _flow, ll _cost, int _index) 
    : from(_from), to(_to), cap(_cap), flow(_flow), cost(_cost), index(_index) {} 
};

struct DinicMCF {
    int N, flow, t;
    ll cost;
    vector<int> Dfs, ptr, p;
    vector<ll> d;
    vector<vector<Edge> > G;
    int expected;

    DinicMCF(int N) {
        this->N = N;
        G.resize(N);
        ptr.resize(N);
        d.resize(N);
        p.resize(N);
        Dfs.resize(N);
        flow = t = expected = cost = 0;
    }

    void addEdge(int u, int v, int gt, int cost, bool rev = false) {
        // dbg(u, v, gt, cost);
        if (u == v) return;
        G[u].push_back(Edge(u, v, gt, 0, cost, G[v].size()));
        G[v].push_back(Edge(v, u, 0, 0, -cost, G[u].size() - 1));
        if (rev) {
            G[v].push_back(Edge(v, u, gt, 0, cost, G[u].size()));
            G[u].push_back(Edge(u, v, 0, 0, -cost, G[v].size() - 1));
        }
    }

    bool SPFA(int S, int T) {
        FOR(i,0,N-1) d[i] = (ll) INF * INF;
        vector<bool> inq(N, 0);
        queue<int> q; q.push(S);
        d[S] = 0;
        inq[S] = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = 0;
            FOR(i,0,SZ(G[u])-1) {
                int v = G[u][i].to;
                if (d[v] > d[u] + G[u][i].cost && G[u][i].cap - G[u][i].flow > 0) {
                    d[v] = d[u] + G[u][i].cost;
                    p[v] = u;
                    if (!inq[v]) {
                        q.push(v);
                        inq[v] = 1;
                    }
                }
            }
        }
        return d[T] != (ll) INF * INF;
    }

    int visit(int u, int Min, int T) {
        if (u == T) return Min;
        if (Dfs[u]!=t) Dfs[u]=t;
        else return 0;
        for (; ptr[u] < (int) G[u].size(); ++ptr[u]) { 
            int v = G[u][ptr[u]].to;
            if (G[u][ptr[u]].cap - G[u][ptr[u]].flow > 0)
                if (Dfs[v] != t && d[v] == d[u] + G[u][ptr[u]].cost)
                    if (int x = visit(v, min(Min, G[u][ptr[u]].cap - G[u][ptr[u]].flow), T)) {
                        G[u][ptr[u]].flow += x;
                        G[v][G[u][ptr[u]].index].flow -= x;
                        cost += G[u][ptr[u]].cost * x;
                        return x;
                    }
        }
        return 0;
    }

    void getFlow(int S, int T) {
        flow = cost = 0;
        while (SPFA(S, T)) {
            FOR(i,0,N-1) ptr[i] = 0;
            while (1) {
                t++;
                int x = visit(S, INF, T);
                if (!x) break;
                flow += x;
            }
        }
    }
};

int n, m, d[MAXN][MAXN];
char ch[MAXN][MAXN];

bool isOK(int u, int v) {
    return u >= 0 && u < n && v >= 0 && v < m && ch[u][v] != '#';
}

int getIndex(int u, int v) {
    return u * m + v;
}

void bfs(int x, int y) {
    FOR(i,0,n-1)
        FOR(j,0,m-1) d[i][j] = 1e9;
    d[x][y] = 0;
    queue<pi> q;
    q.push({x, y});
    while (SZ(q)) {
        pi r = q.front(); q.pop();
        FOR(i,0,1) {
            int u = r.FI + dx[i], v = r.SE + dy[i];
            if (isOK(u, v) && d[u][v] > d[r.FI][r.SE] + 1) {
                d[u][v] = d[r.FI][r.SE] + 1;
                q.push({u, v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,0,n-1) FOR(j,0,m-1) cin >> ch[i][j];

    DinicMCF dinic(n*m+2);
    int source = dinic.N - 1, sink = dinic.N - 2;

    FOR(i,0,n-1)
        FOR(j,0,m-1) {
            if (ch[i][j] == 'o') {
                // we have K pieces to be connected to source
                dinic.addEdge(source, getIndex(i,j), 1, 0);
                bfs(i, j);
                // for each piece, connect it with a destination with cost = distance
                FOR(I,0,n-1)
                    FOR(J,0,m-1)
                        if (d[I][J] < 1e9) dinic.addEdge(getIndex(i,j), getIndex(I,J), 1, -d[I][J]);
            }
            // connect usable cells to the sink
            if (ch[i][j] != '#') dinic.addEdge(getIndex(i,j), sink, 1, 0);
        }

    dinic.getFlow(source, sink);
    cout << -dinic.cost;
    return 0;
}
