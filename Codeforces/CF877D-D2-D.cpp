/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Note, that bfs can find right answer, but works in O(nmk). It's too slow. 
        - We'll store all unvisited cells in set. For each row and column we'll make own set. 
        Now it's easy to find all not visited cell which is reachable from vertex in O(cnt * log(n)), 
        where cnt is number of this cells. We need a prefix sum to find whether there is an obstacle
        between two cells in O(1).
        - In summary it works in O(nmlog(n)).
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
string ts(bool b) { return (b ? "true" : "false"); }

template<class T> using V = vector<T>;
template<class T> string ts(complex<T> c);
string ts(V<bool> v);
template<size_t sz> string ts(bitset<sz> b);
template<class T> string ts(T v);
template<class T, class U> string ts(pair<T,U> p);
template<class ...U> string ts(tuple<U...> u);

template<class T> string ts(complex<T> c) { stringstream ss; ss << c; return ss.str(); }
string ts(V<bool> v) {string res = "{"; FOR(i,0,SZ(v)-1) res += char('0'+v[i]); res += "}"; return res; }
template<size_t sz> string ts(bitset<sz> b) { string res = ""; FOR(i,0,SZ(b)-1) res += char('0'+b[i]); return res; }
template<class T> string ts(T v) { // containers with begin(), end()
    bool fst = 1; string res = "";
    for (const auto& x: v) { if (!fst) res += " "; fst = 0; res += ts(x); }
    return res;
}
template<class T, class U> string ts(pair<T,U> p) { return "(" + ts(p.FI) + ", " + ts(p.SE) + ")"; }
template<size_t i, class T> string print_tuple_utils(const T& tup) { if constexpr(i == tuple_size<T>::value) return ")"; else return (i ? ", " : "(") + ts(get<i>(tup)) + print_tuple_utils<i + 1, T>(tup); }
template<class ...U> string ts(tuple<U...> u) { return print_tuple_utils<0, tuple<U...>>(u); }

// OUTPUT
template<class T> void pr(T x) { cout << ts(x); }
template<class T, class ...U> void pr(const T& t, const U&... u) { pr(t); pr(u...); }
void ps() { pr("\n"); } // print w/ spaces
template<class T, class ...U> void ps(const T& t, const U&... u) { pr(t); if (sizeof...(u)) pr(" "); ps(u...); }

// DEBUG
void DBG() { cerr << "]" << endl; }
template<class T, class ...U> void DBG(const T& t, const U&... u) { cerr << ts(t); if (sizeof...(u)) cerr << ", "; DBG(u...); }

#ifdef LOCAL_DEBUG
#define CONCAT(x, y) x##y
#define with_level setw(__db_level * 2) << setfill(' ') << "" << setw(0)
#define dbg(...) cerr << with_level << "Line(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#define chk(...) if (!(__VA_ARGS__)) cerr << setw(__db_level * 2) << setfill(' ') << "" << setw(0) << "Line(" << __LINE__ << ") -> function(" << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\n", exit(0);
#define db_block() debug_block CONCAT(dbbl, __LINE__)
int __db_level = 0;
struct debug_block {
    debug_block() { cerr << with_level << "{" << endl; ++__db_level; }
    ~debug_block() { --__db_level; cerr << with_level << "}" << endl; }
};
#else
#define dbg(...) 0
#define chk(...) 0
#define db_block() 0
#endif

const ld PI = acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
const ld EPS = 1e-9;
const ll MODBASE = 1000000007LL;
const int INF = 0x3f3f3f3f;

const int MAXN = 1010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, k, d[MAXN][MAXN];
char ch[MAXN][MAXN];
int X1, Y1, X2, Y2;
set<int> remainRow[MAXN], remainCol[MAXN];
int rowCntObstacle[MAXN][MAXN], colCntObstacle[MAXN][MAXN];

int bfs() {
    FOR(i,1,n) FOR(j,1,m) d[i][j] = INF;
    FOR(i,1,n) {
        FOR(j,1,m) {
            if (ch[i][j] != '#') {
                remainRow[i].insert(j);
                remainCol[j].insert(i);
            }

            rowCntObstacle[i][j] = rowCntObstacle[i][j-1] + (ch[i][j] == '#');
            colCntObstacle[i][j] = colCntObstacle[i-1][j] + (ch[i][j] == '#');
        }
    }
    queue<pi> q;
    q.push({X1, Y1});
    d[X1][Y1] = 0;
    remainRow[X1].erase(Y1);
    remainCol[Y1].erase(X1);

    while (SZ(q)) {
        pi r = q.front(); q.pop();
        int u = r.FI, v = r.SE;

        if (u == X2 && v == Y2) return d[u][v];

        FOR(i,0,3) {
            if (dx[i] < 0) {
                // col, backward
                while (1) {
                    auto it = remainCol[v].lower_bound(u);
                    if (it == remainCol[v].begin()) break;
                    if (it == remainCol[v].end() && SZ(remainCol[v]) == 0) break;
                    it--;
                    int x = *it;
                    if (colCntObstacle[u][v] - colCntObstacle[x-1][v] > 0) break;
                    if (u - x > k) break;
                    d[x][v] = d[u][v] + 1;
                    q.push({x, v});
                    remainCol[v].erase(x);
                    remainRow[x].erase(v);
                }
            } else if (dx[i] > 0) {
                // col, forward
                while (1) {
                    auto it = remainCol[v].upper_bound(u);
                    if (it == remainCol[v].end()) break;
                    int x = *it;
                    if (colCntObstacle[x][v] - colCntObstacle[u-1][v] > 0) break;
                    if (x - u > k) break;
                    d[x][v] = d[u][v] + 1;
                    q.push({x, v});
                    remainCol[v].erase(x);
                    remainRow[x].erase(v);
                }
            } else if (dy[i] < 0) {
                // row, backward
                while (1) {
                    auto it = remainRow[u].lower_bound(v);
                    if (it == remainRow[u].begin()) break;
                    if (it == remainRow[u].end() && SZ(remainRow[u]) == 0) break;
                    it--;
                    int y = *it;
                    if (rowCntObstacle[u][v] - rowCntObstacle[u][y-1] > 0) break;
                    if (v - y > k) break;
                    d[u][y] = d[u][v] + 1;
                    q.push({u, y});
                    remainRow[u].erase(y);
                    remainCol[y].erase(u);
                }
            } else {
                // row, forward
                while (1) {
                    auto it = remainRow[u].upper_bound(v);
                    if (it == remainRow[u].end()) break;
                    int y = *it;
                    if (rowCntObstacle[u][y] - rowCntObstacle[u][v-1] > 0) break;
                    if (y - v > k) break;
                    d[u][y] = d[u][v] + 1;
                    q.push({u, y});
                    remainRow[u].erase(y);
                    remainCol[y].erase(u);
                }
            }
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    FOR(i,1,n) FOR(j,1,m) cin >> ch[i][j];
    cin >> X1 >> Y1 >> X2 >> Y2;

    cout << bfs() << "\n";
    return 0;
}
