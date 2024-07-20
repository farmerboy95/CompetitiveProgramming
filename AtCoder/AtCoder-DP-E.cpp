/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - You may be confused when you check the problem constraints, as the maximum value of W
        is 10^9. But you can see that the maximum value of v[i] is 10^3, so the maximum value of
        the sum of v[i] is 10^5. Here you can actually use V as the second dimension of the dp array
        like W in the original problem.
        - Let dp[i][j] be the minimum weight that can be achieved with the first i items such that
        the total value is j. We can compute dp[i][j] using the following transition:
            + dp[i][j] = dp[i-1][j] (not taking the i-th item)
            + dp[i][j] = dp[i-1][j-v[i]] + w[i] (taking the i-th item, and j >= v[i])
        - dp[0][0] = 0, dp[0][j] = INF for all j > 0 because initially we haven't taken any item
        so we don't have any weight.
        - Since the invalid states are too big, the valid one will fill up the dp array so we don't
        need to worry about the invalid states in transition.
        - The result is the maximum value of j such that dp[N][j] <= W.
        - Time complexity: O(N * sum(v[i])
        - Space complexity:
            + O(N * sum(v[i])) if we use the above dp array to store the result.
            + Otherwise, we can just use dp[j] to store the result of current i, the transition
            will be like: dp[j] = min(dp[j], dp[j-v[i]] + w[i]), for all j >= v[i]. But since we
            need to update dp[j] with dp[j-v[i]] + w[i], in which j-v[i] < j, we need to iterate
            from sum(v[i]) to 0 to avoid duplicate calculation. So the space complexity is O(sum(v[i])).
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
const int MAXV = 100010;
const int MAXK = 16;
const int MAXQ = 200010;

int N, W, w[MAXN], v[MAXN];
// ll dp[MAXN][MAXV];
ll dp[MAXV];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> N >> W;
    FOR(i,1,N) {
        cin >> w[i] >> v[i];
    }
    
    // dp[0][0] = 0;
    // FOR(i,1,1000*N) dp[0][i] = (ll) INF * INF;

    // FOR(i,1,N) {
    //     FOR(j,0,1000*N) {
    //         dp[i][j] = dp[i-1][j];
    //         if (j >= v[i]) dp[i][j] = min(dp[i][j], dp[i-1][j-v[i]] + w[i]);
    //     }
    // }

    // int res = 0;
    // FOR(i,0,1000*N)
    //     if (dp[N][i] <= W) res = i;
    // cout << res;

    dp[0] = 0;
    FOR(i,1,1000*N) dp[i] = (ll) INF * INF;

    FOR(i,1,N) {
        FORE(j,1000*N,0) {
            if (j >= v[i]) ckmin(dp[j], dp[j-v[i]] + w[i]);
        }
    }

    int res = 0;
    FOR(i,0,1000*N)
        if (dp[i] <= W) res = i;
    cout << res;
    return 0;
}
