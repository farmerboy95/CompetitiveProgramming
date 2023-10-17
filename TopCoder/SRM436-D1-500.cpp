/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Our state would be the coordinate of the robot and the direction it is facing.
        - At each state, we can go straight (cost 0), turn left or turn right (cost 1).
        - So we can use BFS01 to find the shortest path from (0, 0) to (N-1, N-1).
        - Remember to use tuple to store the state instead of vector to avoid MLE.
        - Here we can also store the current value of the distance to the deque to avoid
        considering the same state when value is smaller.
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
const int dx[4] = {-1,0,1,0}, dy[4] = {0,1,0,-1};
const ld EPS = 1e-9;
const ll MODBASE = 1000000007LL;
const int INF = 0x3f3f3f3f;

const int MAXN = 510;
const int MAXM = 1000010;
const int MAXK = 16;
const int MAXQ = 200010;

int X[MAXM], Y[MAXM];
int d[MAXN][MAXN][4];
int grid[MAXN][MAXN];

class DoNotTurn {
    public:
    int minimumTurns(int N, int X0, int A, int B, int Y0, int C, int D, int P, int M) {
        if (M) {
            X[0] = X0 % P;
            FOR(i,1,M-1) X[i] = ((ll) X[i-1] * A + B) % P;
            Y[0] = Y0 % P;
            FOR(i,1,M-1) Y[i] = ((ll) Y[i-1] * C + D) % P;
        }

        FOR(i,0,N-1) FOR(j,0,N-1) grid[i][j] = 0;
        FOR(i,0,M-1) grid[X[i] % N][Y[i] % N] = 1;
        grid[0][0] = grid[N-1][N-1] = 0;

        FOR(i,0,N-1) FOR(j,0,N-1) FOR(k,0,3) d[i][j][k] = INF;
        deque<tuple<int, int, int, int> > q;
        FOR(i,0,3) {
            d[0][0][i] = 0;
            q.push_back({0, 0, i, 0});
        }

        while (SZ(q)) {
            auto r = q.front(); q.pop_front();
            int u = get<0>(r), v = get<1>(r), dir = get<2>(r), val = get<3>(r);

            if (d[u][v][dir] != val) continue;

            if (u == N-1 && v == N-1) return val;

            int g = u + dx[dir], h = v + dy[dir];
            if (g >= 0 && g < N && h >= 0 && h < N && !grid[g][h]) {
                if (d[g][h][dir] > d[u][v][dir]) {
                    d[g][h][dir] = d[u][v][dir];
                    q.push_front({g, h, dir, d[g][h][dir]});
                }
            }

            int left = (dir + 3) % 4;
            int right = (dir + 1) % 4;

            if (d[u][v][left] > d[u][v][dir] + 1) {
                d[u][v][left] = d[u][v][dir] + 1;
                q.push_back({u, v, left, d[u][v][left]});
            }
            if (d[u][v][right] > d[u][v][dir] + 1) {
                d[u][v][right] = d[u][v][dir] + 1;
                q.push_back({u, v, right, d[u][v][right]});
            }
        }

        return -1;
    } 
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    DoNotTurn sol;
    cout << sol.minimumTurns(2,0,0,1,0,0,1,10,2) << '\n';
    cout << sol.minimumTurns(3,0,1,1,1,1,0,3,3) << "\n";
    cout << sol.minimumTurns(3,0,1,1,1,1,1,3,3) << "\n";
    cout << sol.minimumTurns(500,911111,845499,866249,688029,742197,312197,384409,40) << "\n";
    cout << sol.minimumTurns(5,23,2,3,35,5,7,9,3) << "\n";
    cout << sol.minimumTurns(2,0,0,0,0,0,0,1,0) << "\n";

    return 0;
}
