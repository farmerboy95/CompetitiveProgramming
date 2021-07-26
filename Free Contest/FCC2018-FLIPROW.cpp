/*
    Author: Nguyen Tan Bao
    Status: AC
    Statement: https://oj.vnoi.info/problem/fc2018_fliprow
    Idea:
        - Given an nxm matrix, you can flip any row to make the final matrix having
        the following property: The numbers in each column are different
        - We can use 2-SAT here, denote true as the initial row, false as the flipped
        row. Then we can check if 2 different rows (normal or flipped) can go along 
        each other or not, then declare clauses for them, finally, run 2-SAT and print
        out the result.
        - The main problem is that, how to get those clauses, meaning how to check
        if rows can go along each other or not in fast enough time complexity.
        - We can first think of an O(n^3) approach. But it will likely get TLE. We can
        check each of the first half column, gather all numbers from that column and the
        opposite column to store in a map with types (normal or flipped). Then for each
        number, if we have more than 2 appearances, the answer is No, obviously. Otherwise,
        we can remove the only pair of rows from our list,
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

const int MAXN = 1010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m;
int b[MAXN][MAXN], f[MAXN][MAXN];

vector<int> A[MAXN * 2], topo;
int low[MAXN * 2], num[MAXN * 2], dfsNum, sccCnt, w[MAXN * 2], P[MAXN * 2];
bool visited[MAXN * 2];
stack<int> s;

void orClause(int u, int v) {
    A[u^1].push_back(v);
    A[v^1].push_back(u);
}

void xorClause(int u, int v) {
    orClause(u, v);
    orClause(u^1, v^1);
}

void andClause(int u, int v) {
    A[u].push_back(v);
    A[v].push_back(u);
}

void nXorClause(int u, int v) {
    orClause(u^1, v);
    orClause(u, v^1);
} 

void nAndClause(int u, int v) {
    A[u].push_back(v^1);
    A[v].push_back(u^1);
}

void mustTrue(int u) {
    A[u^1].push_back(u);
}

void scc(int u) {
    low[u] = num[u] = ++dfsNum;
    s.push(u);
    visited[u] = true;
    for (int v : A[u]) {
        if (num[v] == -1) scc(v);
        if (visited[v]) low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
        int k = -1;
        sccCnt++;
        do {
            k = s.top();
            s.pop();
            w[k] = sccCnt;
            visited[k] = false;
        } while (k != u);
    }
}

void dfs(int u) {
    visited[u] = true;
    for (int v : A[u])
        if (!visited[v]) dfs(v);
    topo.push_back(u);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,0,n-1) FOR(j,0,m-1) cin >> b[i][j];

    if (m % 2) {
        set<int> s;
        FOR(i,0,n-1) s.insert(b[i][m / 2]);
        if (SZ(s) < n) {
            cout << "No";
            return 0;
        }
    }

    FOR(i,0,n-1)
        FOR(j,i+1,n-1) f[i][j] = 3;

    map<int, vpi> numMap;
    FOR(j,0,m/2-1) {
        FOR(i,0,n-1) {
            numMap[b[i][j]].push_back({i, 0});
            numMap[b[i][m-j-1]].push_back({i, 1});
        }

        for (auto x : numMap) {
            vpi c = x.second;

            if (SZ(c) > 2) {
                cout << "No";
                return 0;
            }
            if (SZ(c) == 2) {
                if (c[0].SE != c[1].SE) {
                    int u = c[0].FI, v = c[1].FI;
                    if (u > v) swap(u, v);
                    if (f[u][v] & 1) f[u][v] -= 1;
                } else {
                    int u = c[0].FI, v = c[1].FI;
                    if (u > v) swap(u, v);
                    if (f[u][v] & 2) f[u][v] -= 2;
                }
            }
        }
        numMap.clear();
    }

    FOR(i,0,n-1)
        FOR(j,i+1,n-1)
            if (f[i][j] == 1) {
                xorClause(i * 2, j * 2);
            } else if (f[i][j] == 2) {
                nXorClause(i * 2, j * 2);
            } else if (f[i][j] == 0) {
                cout << "No";
                return 0;
            }

    int N = 2 * n;
    FOR(i,0,N-1) num[i] = -1;
    MS(visited, false);
    dfsNum = -1;
    FOR(i,0,N-1)
        if (num[i] == -1) scc(i);
    bool co = true;
    FOR(i,0,N-1)
        if (w[i] == w[i^1]) co = false;
    if (!co) {
        cout << "No";
        return 0;
    }

    cout << "Yes\n";

    FOR(i,0,N-1) 
        if (!visited[i]) dfs(i);
    reverse(topo.begin(), topo.end());

    vi res;
    for (int v : topo) {
        if (v % 2 == 0) {
            int k = v^1;
            if (!P[k]) {
                int x = v / 2 + 1;
                res.push_back(x);
            }
        }
        P[v] = true;
        // If ¬x i is after x i in topological sort, x i should be FALSE. It should be TRUE otherwise.
    }
    cout << SZ(res) << "\n";
    TRAV(x, res) cout << x << " ";

    return 0;
}