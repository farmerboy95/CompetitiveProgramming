/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let dp[i][j][k][l][m] is the number of ways to place cards in a line such that
        no two adjacent cards have the same value, and we have i suits with 1 card, j suits
        with 2 cards, k suits with 3 cards, l suits with 4 cards, and the suits containing
        the previous card have m cards.
        - We have about 1.5 * 10^6 states only.
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
using ll = unsigned long long; using ld = double; 
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

const int MAXN = 53;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

vector<char> values = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
vector<vector<vector<vector<vector<ll>>>>> dp;
vector<vector<vector<vector<vector<bool>>>>> found;

ll solve(int num1, int num2, int num3, int num4, int lastCnt) {
    if (num1 == 0 && num2 == 0 && num3 == 0 && num4 == 0) return 1;
    if (found[num1][num2][num3][num4][lastCnt]) return dp[num1][num2][num3][num4][lastCnt];
    found[num1][num2][num3][num4][lastCnt] = 1;
    ll &res = dp[num1][num2][num3][num4][lastCnt];
    res = 0;

    if (lastCnt == 1) {
        if (num1 > 1) res += solve(num1-1, num2, num3, num4, 0) * (num1-1);
    } else {
        if (num1) res += solve(num1-1, num2, num3, num4, 0) * num1;
    }

    if (lastCnt == 2) {
        if (num2 > 1) res += solve(num1+1, num2-1, num3, num4, 1) * (num2-1) * 2;
    } else {
        if (num2) res += solve(num1+1, num2-1, num3, num4, 1) * num2 * 2;
    }

    if (lastCnt == 3) {
        if (num3 > 1) res += solve(num1, num2+1, num3-1, num4, 2) * (num3-1) * 3;
    } else {
        if (num3) res += solve(num1, num2+1, num3-1, num4, 2) * num3 * 3;
    }

    if (num4) res += solve(num1, num2, num3+1, num4-1, 3) * num4 * 4;
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    FOR(i,0,52) {
        dp.push_back(vector<vector<vector<vector<ll>>>> ());
        found.push_back(vector<vector<vector<vector<bool>>>> ());
        FOR(j,0,52) {
            if (i+j > 52) break;
            dp[i].push_back(vector<vector<vector<ll>>> ());
            found[i].push_back(vector<vector<vector<bool>>> ());
            FOR(k,0,52) {
                if (i+j+k > 52) break;
                dp[i][j].push_back(vector<vector<ll>> ());
                found[i][j].push_back(vector<vector<bool>> ());
                FOR(l,0,52) {
                    if (i+j+k+l > 52) break;
                    dp[i][j][k].push_back(vector<ll>());
                    found[i][j][k].push_back(vector<bool>());
                    FOR(p,0,3) {
                        dp[i][j][k][l].push_back(0);
                        found[i][j][k][l].push_back(0);
                    }
                }
            }
        }
    }

    dp[0][0][0][0][0] = 1;

    int te;
    cin >> te;
    FOR(o,1,te) {
        int n;
        cin >> n;
        vi cnt(SZ(values), 0);
        FOR(i,1,n) {
            string s;
            int v = 0;
            cin >> s;
            FOR(j,0,SZ(values)-1)
                if (values[j] == s[0]) v = j;
            cnt[v]++;
        }
        vi f(5, 0);
        FOR(i,0,SZ(values)-1) {
            if (cnt[i]) {
                f[cnt[i]]++;
            }
        }
        cout << "Case " << o << ": " << solve(f[1], f[2], f[3], f[4], 0) << "\n";
    }
    return 0;
}
