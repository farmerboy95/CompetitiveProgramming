/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We use Digit DP here. We see that there are only 4 possibilities (3,5,7,9)
        and some leading 0s as well
        - We want to find the number of odd-digit-immune numbers from 0 to n
        - We want to keep track of
            + position
            + remainder of the current prefix when dividing by 3
            + remainder of the current prefix when dividing by 5
            + remainder of the current prefix when dividing by 7
            + remainder of the current prefix when dividing by 9
            + whether the current prefix equals to the same length prefix of n
            + whether we are done with leading 0s (we started to fill non-zero numbers or not)
        - But note that some odd-digit-immune numbers may, for example, not having any 3
        but having remainder 0 when dividing by 3, we need one more dimension for each of
        the remainders to indicate that we have 3,5,7,9 or not.
        - We use top-down DP, from most significant digit to least significant digit to
        ease our work when finding the k-th number.
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

ll dp[20][6][10][14][18][2][2];

ll solve(int i, int r3, int r5, int r7, int r9, int eq, int st, vi& a) {
    if (i == SZ(a)) {
        return (r3 != 3 && r5 != 5 && r7 != 7 && r9 != 9 && st);
    }
    if (dp[i][r3][r5][r7][r9][eq][st] != -1) return dp[i][r3][r5][r7][r9][eq][st];
    ll& res = dp[i][r3][r5][r7][r9][eq][st];
    res = 0;
    int Max = eq ? a[i] : 9;
    int hasR3 = r3 / 3, hasR5 = r5 / 5, hasR7 = r7 / 7, hasR9 = r9 / 9;
    int realR3 = r3 % 3, realR5 = r5 % 5, realR7 = r7 % 7, realR9 = r9 % 9;

    if (!st) {
        res += solve(i+1, 0, 0, 0, 0, 0, 0, a);
    }
    for (int p = 3; p <= Max; p += 2) {
        int newEq = eq && p == Max;
        int newHasR3 = hasR3 || (p == 3), newHasR5 = hasR5 || (p == 5), newHasR7 = hasR7 || (p == 7), newHasR9 = hasR9 || (p == 9);
        int newRealR3 = (realR3 * 10 + p) % 3;
        int newRealR5 = (realR5 * 10 + p) % 5;
        int newRealR7 = (realR7 * 10 + p) % 7;
        int newRealR9 = (realR9 * 10 + p) % 9;
        int newR3 = newHasR3 * 3 + newRealR3;
        int newR5 = newHasR5 * 5 + newRealR5;
        int newR7 = newHasR7 * 7 + newRealR7;
        int newR9 = newHasR9 * 9 + newRealR9;
        res += solve(i+1, newR3, newR5, newR7, newR9, newEq, 1, a);
    }
    
    return res;
}

ll count(ll n) {
    if (n <= 2) return 0;
    vi a;
    while (n) {
        a.push_back(n % 10);
        n /= 10;
    }
    reverse(ALL(a));

    MS(dp, -1);
    return solve(0, 0, 0, 0, 0, 1, 0, a);
}

void printResult(int i, int r3, int r5, int r7, int r9, int eq, int st, vi& a, ll k) {
    if (i == SZ(a)) {
        return;
    }

    if (!st) {
        if (solve(i+1, 0, 0, 0, 0, 0, 0, a) >= k) {
            printResult(i+1, 0, 0, 0, 0, 0, 0, a, k);
            return;
        }
        k -= solve(i+1, 0, 0, 0, 0, 0, 0, a);
    }

    int Max = eq ? a[i] : 9;
    int hasR3 = r3 / 3, hasR5 = r5 / 5, hasR7 = r7 / 7, hasR9 = r9 / 9;
    int realR3 = r3 % 3, realR5 = r5 % 5, realR7 = r7 % 7, realR9 = r9 % 9;

    for (int p = 3; p <= Max; p += 2) {
        int newEq = eq && p == Max;
        int newHasR3 = hasR3 || (p == 3), newHasR5 = hasR5 || (p == 5), newHasR7 = hasR7 || (p == 7), newHasR9 = hasR9 || (p == 9);
        int newRealR3 = (realR3 * 10 + p) % 3;
        int newRealR5 = (realR5 * 10 + p) % 5;
        int newRealR7 = (realR7 * 10 + p) % 7;
        int newRealR9 = (realR9 * 10 + p) % 9;
        int newR3 = newHasR3 * 3 + newRealR3;
        int newR5 = newHasR5 * 5 + newRealR5;
        int newR7 = newHasR7 * 7 + newRealR7;
        int newR9 = newHasR9 * 9 + newRealR9;
        if (solve(i+1, newR3, newR5, newR7, newR9, newEq, 1, a) >= k) {
            cout << p;
            printResult(i+1, newR3, newR5, newR7, newR9, newEq, 1, a, k);
            return;
        }
        k -= solve(i+1, newR3, newR5, newR7, newR9, newEq, 1, a);
    }
}

void printResult(ll n, ll k) {
    vi a;
    while (n) {
        a.push_back(n % 10);
        n /= 10;
    }
    reverse(ALL(a));

    printResult(0, 0, 0, 0, 0, 1, 0, a, k);
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    while (te--) {
        ll l, r, k;
        cin >> l >> r >> k;
        ll cnt = count(l-1) + k;
        ll cntR = count(r);
        if (cnt > cntR) {
            cout << -1 << "\n";
            continue;
        }
        printResult(r, cnt);
    }
    return 0;
}
