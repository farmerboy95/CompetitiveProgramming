/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's consider all sizes of spiral, from 3 to min(n, m), size is odd.
        - For size 3 and 5, we can consider the top-left corner of the spiral, then we can calculate
        the sum of the spiral in O(1) using prefix sum.
        - For size 7 and above, you can see that after 4 times of moving to the right, we will be
        reduced to the case of size - 4, so we can use dp to calculate the sum of the spiral.
        - Using O(n^3) dp array will lead to MLE, in this case we can maintain dp[size-4] and dp[size-2]
        to calculate dp[size] in O(n^2) time.
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

const int MAXN = 510;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, a[MAXN][MAXN];
int rowSum[MAXN][MAXN], colSum[MAXN][MAXN];

int getRowSum(int row, int l, int r) {
    return rowSum[row][r] - rowSum[row][l-1];
}

int getColSum(int col, int u, int d) {
    return colSum[d][col] - colSum[u-1][col];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) FOR(j,1,m) cin >> a[i][j];

    FOR(i,1,n) {
        FOR(j,1,m) {
            rowSum[i][j] = rowSum[i][j-1] + a[i][j];
            colSum[i][j] = colSum[i-1][j] + a[i][j];
        }
    }

    int res = -INF;
    vector<vi> dp1(n+1, vi(m+1, 0)), dp2(n+1, vi(m+1, 0));

    FOR(i,1,n) FOR(j,1,m) {
        if (i + 2 > n || j + 2 > m) continue;
        int &cur = dp2[i][j];
        cur += getRowSum(i, j, j+2);
        cur += getColSum(j+2, i+1, i+2);
        cur += getRowSum(i+2, j, j+1);
        ckmax(res, cur);
    }

    FOR(i,1,n) FOR(j,1,m) {
        if (i + 4 > n || j + 4 > m) continue;
        int &cur = dp1[i][j];
        cur += getRowSum(i, j, j+4);
        cur += getColSum(j+4, i+1, i+4);
        cur += getRowSum(i+4, j, j+3);
        cur += getColSum(j, i+2, i+3);
        cur += getRowSum(i+2, j+1, j+2);
        ckmax(res, cur);
    }

    for (int sz = 7; sz <= min(n, m); sz += 2) {
        vector<vi> tmp(n+1, vi(m+1, 0));
        FOR(i,1,n) {
            FOR(j,1,m) {
                if (i + sz - 1 > n || j + sz - 1 > m) continue;
                int &cur = tmp[i][j];
                cur += getRowSum(i, j, j+sz-1);
                cur += getColSum(j+sz-1, i+1, i+sz-1);
                cur += getRowSum(i+sz-1, j, j+sz-2);
                cur += getColSum(j, i+2, i+sz-2);
                cur += getRowSum(i+2, j+1, j+1);
                cur += dp2[i+2][j+2];
                ckmax(res, cur);
            }
        }
        swap(dp1, dp2);
        swap(dp1, tmp);
    }

    cout << res;
    return 0;
}
