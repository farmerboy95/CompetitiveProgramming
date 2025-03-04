/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We can prove that any monotonous path from top-left to bottom-right derives to the
        same correct bracket sequence, also in the final grid res, res[i][j] = res[x][y] when
        i+j == x+y. The bracket sequence will have length of n+m-1, let's find it. We can find
        the priority of position pri[x] = min(p[i][j]), i+j-1 = x
        - Let's iterate through positions by pri[x], from smallest to largest, we try with open
        bracket first, count the number of correct bracket sequence with that config, if that
        number is less than k, we know that it should be a close bracket, and remove that amount
        from k.
        - How to count the number of correct bracket sequence with a particular config? We use
        an O(n^2) dp. Let dp[i][j] = number of ways to create a prefix length i of one correct 
        bracket sequence length n+m-1 and we have used j open brackets. Based on the next character
        whether it's non-determined, open bracket or close bracket that we update dp[i+1] by dp[i]
        - Complexity O(n^3)
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

int n, m, p[MAXN][MAXN], Min[MAXN*2], bracket[MAXN*2];
ll k, dp[MAXN*2][MAXN*2];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    FOR(i,1,n+m-1) Min[i] = INF;
    FOR(i,1,n) {
        FOR(j,1,m) {
            cin >> p[i][j];
            ckmin(Min[i+j-1], p[i][j]);
        }
    }
    int N = n + m - 1;
    string res = " ";

    vpi b;
    FOR(i,1,N) {
        b.push_back({Min[i], i});
        res += " ";
    }
    sort(ALL(b));

    // dp[i][j] = number of ways to create a prefix length i of one correct bracket sequence length N
    // and we have used j open brackets

    ll Max = 1e18;
    FOR(i,0,N-1) {
        int pos = b[i].SE;
        res[pos] = '(';
        FOR(x,1,N) {
            FOR(y,1,N) {
                dp[x][y] = 0;
            }
        }
        dp[0][0] = 1;
        FOR(x,0,N-1) {
            FOR(y,0,x) {
                if (dp[x][y] == 0) continue;
                if (res[x+1] == ' ' || res[x+1] == '(') {
                    dp[x+1][y+1] += dp[x][y];
                    if (dp[x+1][y+1] > Max) {
                        dp[x+1][y+1] = (ll) INF * INF;
                    }
                }
                if (res[x+1] == ' ' || res[x+1] == ')') {
                    int numClose = x - y;
                    int availOpen = y - numClose;
                    if (availOpen > 0) {
                        dp[x+1][y] += dp[x][y];
                        if (dp[x+1][y] > Max) {
                            dp[x+1][y] = (ll) INF * INF;
                        }
                    }
                }
            }
        }
        if (dp[N][N/2] <= Max) {
            if (dp[N][N/2] < k) {
                k -= dp[N][N/2];
                res[pos] = ')';
            }
        }
    }

    FOR(i,1,n) {
        FOR(j,1,m) {
            int pos = i+j-1;
            cout << res[pos];
        }
        cout << "\n";
    }
    return 0;
}
