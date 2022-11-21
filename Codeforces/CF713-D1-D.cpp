/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - First lets calculate dp[i][j] — maximum square ending in cell (i, j). 
        For each cell, 
            + if input matrix contain 0 then dp[i][j] = 0 
            + else dp[i][j] = min(dp[i - 1][j - 1], dp[i−1][j], dp[i][j−1]) + 1.
        - We will use binary search to find the answer. Let's fix some value x. 
        For each square (i, j)..(i + x - 1, j + x - 1) we need to find maximum and 
        compare it to x. To find maximum we can use 2D sparse table.
        - We can precompute the sparse table with the base value as the dp O(NM) array.
        Then we fill in the precomputed table with f = max(a, b)
        - To query with a specific square length "len" and 2 corners (x, y) - top left 
        and (u, v) - bottom right, we increase x and y by (len - 1), then get max of
        4 corners based on the log width and height of the new square. "len" satisfies
        when the max >= len. You can easily prove this process.
        - So preprocessing takes O(NMlogNlogM), and query works in O(logN).
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

const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m;

struct RMQ2D {
    vector<vector<vector<vi>>> preComp;

    int log2_floor(unsigned long long i) {
        return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
    }

    RMQ2D(vector<vi> &a) {
        int n = SZ(a);
        int m = SZ(a[0]);
        int kN = log2_floor(n), kM = log2_floor(m);
        preComp.resize(kN+1, vector<vector<vi>>(kM+1, vector<vi>(n, vi(m))));

        FOR(i,0,n-1) {
            FOR(j,0,m-1) {
                if (a[i][j]) {
                    if (i == 0 && j == 0) preComp[0][0][i][j] = 1;
                    else if (i == 0) preComp[0][0][i][j] = preComp[0][0][i][j-1] + 1;
                    else if (j == 0) preComp[0][0][i][j] = preComp[0][0][i-1][j] + 1;
                    else preComp[0][0][i][j] = min(preComp[0][0][i-1][j], min(preComp[0][0][i][j-1], preComp[0][0][i-1][j-1])) + 1;
                } else {
                    preComp[0][0][i][j] = 0;
                }
            }
        }

        FOR(i,0,kN) {
            FOR(j,0,kM) {
                if (i + j == 0) continue;
                for (int x = 0; x + (1<<i) - 1 < n; x++) {
                    for (int y = 0; y + (1<<j) - 1 < m; y++) {
                        if (j == 0) {
                            preComp[i][j][x][y] = max(preComp[i-1][j][x][y], preComp[i-1][j][x + (1<<(i-1))][y]);
                        } else {
                            preComp[i][j][x][y] = max(preComp[i][j-1][x][y], preComp[i][j-1][x][y + (1<<(j-1))]);
                        }
                    }
                }
            }
        }
    }

    int query(int x, int y, int u, int v) {
        int lgX = log2_floor(u - x + 1), lgY = log2_floor(v - y + 1);
        return max(
            max(preComp[lgX][lgY][x][y], preComp[lgX][lgY][x][v - (1<<lgY) + 1]),
            max(preComp[lgX][lgY][u - (1<<lgX) + 1][y], preComp[lgX][lgY][u - (1<<lgX) + 1][v - (1<<lgY) + 1])
        );
    }
};

bool check(int x, int y, int u, int v, int len, RMQ2D &rmq2d) {
    return rmq2d.query(x+len-1, y+len-1, u, v) >= len;
}

int solve(int x, int y, int u, int v, RMQ2D &rmq2d) {
    int Max = min(u - x + 1, v - y + 1);
    int lef = 1, rig = Max;
    while (lef <= rig) {
        int mid = (lef + rig) >> 1;
        if (check(x, y, u, v, mid, rmq2d)) lef = mid + 1;
        else rig = mid - 1;
    }
    return rig;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    vector<vi> a(n, vi(m));
    FOR(i,0,n-1) {
        FOR(j,0,m-1) {
            cin >> a[i][j];
        }
    }
    RMQ2D rmq2d(a);

    int q;
    cin >> q;
    while (q--) {
        int x, y, u, v;
        cin >> x >> y >> u >> v;
        x--; y--;
        u--; v--;
        cout << solve(x, y, u, v, rmq2d) << "\n";
    }
    return 0;
}
