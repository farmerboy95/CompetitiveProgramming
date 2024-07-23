/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - This problem requires some expected value knowledge to solve.
        - Let dp[i][j][k] be the expected number of operations to eat all the sushi pieces, in which
            + i = number of dishes with 1 piece of sushi
            + j = number of dishes with 2 pieces of sushi
            + k = number of dishes with 3 pieces of sushi
        - We can do a top-down dp for easier understanding, starting from dp[cnt[1]][cnt[2]][cnt[3]]
        cnt[i] is the number of dishes with i pieces of sushi, i = 1, 2, 3
        - The base case is when we have no sushi left, the expected number of operations is 0, obviously
        - Let x = number of dishes with 0 pieces of sushi, it's n - i - j - k, so with one operation,
        we have the following expression
            + dp[i][j][k] = 
                + x / n * (dp[i][j][k] + 1) (when we pick a dish with 0 sushi)
                + i / n * (dp[i-1][j][k] + 1) (if i > 0) (when we pick a dish with 1 sushi)
                + j / n * (dp[i+1][j-1][k] + 1) (if j > 0) (when we pick a dish with 2 sushi)
                + k / n * (dp[i][j+1][k-1] + 1) (if k > 0) (when we pick a dish with 3 sushi)
            + Move dp[i][j][k] to the left side and reduce the equation, we have
                + dp[i][j][k] = (x + i * (dp[i-1][j][k] + 1) + j * (dp[i+1][j-1][k] + 1) + k * (dp[i][j+1][k-1] + 1)) / (n - x)
        - Time complexity: O(n^3)
        - Space complexity: O(n^3)
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

const int MAXN = 310;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int cnt[4], n;
ld dp[MAXN][MAXN][MAXN];

ld solve(int num1, int num2, int num3) {
    if (num1 == 0 && num2 == 0 && num3 == 0) return 0;
    if (dp[num1][num2][num3] >= 0) return dp[num1][num2][num3];

    ld &res = dp[num1][num2][num3];
    int num0 = n - num1 - num2 - num3;

    ld numerator = num0;
    if (num1 > 0) numerator += num1 * (solve(num1-1, num2, num3) + 1);
    if (num2 > 0) numerator += num2 * (solve(num1+1, num2-1, num3) + 1);
    if (num3 > 0) numerator += num3 * (solve(num1, num2+1, num3-1) + 1);

    return res = numerator / (n - num0);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    FOR(i,0,n)
        FOR(j,0,n)
            FOR(k,0,n) dp[i][j][k] = -1;
    
    setPrec(10);
    cout << solve(cnt[1], cnt[2], cnt[3]);
    return 0;
}
