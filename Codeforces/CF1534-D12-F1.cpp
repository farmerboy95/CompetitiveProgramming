/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - If we create a graph in which nodes are # cells and edge from u to v means
        disturbed u can disturb v, we can see that we need to find the minimum number
        of nodes that we can travel the whole graph from those nodes.
        - We can find the strongly connected components and condense them into a node,
        after that, we can topologically sort the new graph and get the result.
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

const int MAXN = 400010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

string s[MAXN];
int used[MAXN], num[MAXN], low[MAXN], visited[MAXN];
int n, m, dfsNum, w[MAXN], sccCnt;
vi a[MAXN], A[MAXN];
stack<int> st;
vpi edges;

inline bool isInside(int u, int v) {
    return u >= 0 && u < n && v >= 0 && v < m;
}

inline int getIndex(int u, int v) {
    return u * m + v;
}

void scc(int u) {
    low[u] = num[u] = ++dfsNum;
    st.push(u);
    visited[u] = true;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (num[v] == -1) scc(v);
        if (visited[v]) low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
        int k = -1;
        sccCnt++;
        do {
            k = st.top();
            st.pop();
            w[k] = sccCnt;
            visited[k] = false;
        } while (k != u);
    }
}

vi ans;

void dfs(int u) {
    visited[u] = true;
    FOR(i,0,SZ(A[u])-1) {
        int v = A[u][i];
        if (!visited[v]) dfs(v);
    }
    ans.push_back(u);
}

void dfs2(int u) {
    visited[u] = true;
    FOR(i,0,SZ(A[u])-1) {
        int v = A[u][i];
        if (!visited[v]) dfs(v);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,0,n-1) cin >> s[i];

    FOR(i,0,m-1) {
        int x;
        cin >> x;
    }

    FOR(i,0,n-1)
        FOR(j,0,m-1)
            if (s[i][j] == '#') {
                int u = getIndex(i, j);
                used[u] = 1;
                if (isInside(i-1, j) && s[i-1][j] == '#') {
                    int v = getIndex(i-1, j);
                    a[u].push_back(v);
                    edges.push_back({u, v});
                }
                
                FOR(x,i,n-1) {
                    if (isInside(x, j-1) && s[x][j-1] == '#') {
                        int v = getIndex(x, j-1);
                        a[u].push_back(v);
                        edges.push_back({u, v});
                    }
                    if (isInside(x, j+1) && s[x][j+1] == '#') {
                        int v = getIndex(x, j+1);
                        a[u].push_back(v);
                        edges.push_back({u, v});
                    }
                    if (i == n-1) break;
                    if (isInside(x+1, j) && s[x+1][j] == '#') {
                        int v = getIndex(x+1, j);
                        a[u].push_back(v);
                        edges.push_back({u, v});
                        break;
                    }
                }
            }
    
    FOR(i,0,n*m-1) num[i] = -1;
    FOR(i,0,n*m-1)
        if (used[i] && num[i] == -1) scc(i);
    
    TRAV(edge, edges) {
        int u = edge.FI, v = edge.SE;
        int U = w[u], V = w[v];
        if (U == V) continue;
        A[U].push_back(V);
    }
    FOR(i,1,sccCnt) visited[i] = 0;
    FOR(i,1,sccCnt)
        if (!visited[i]) dfs(i);
    reverse(ALL(ans));

    FOR(i,1,sccCnt) visited[i] = 0;
    int res = 0;
    FOR(i,0,SZ(ans)-1) {
        int u = ans[i];
        if (!visited[u]) {
            dfs2(u);
            res++;
        }
    }
    cout << res;
    return 0;
}
