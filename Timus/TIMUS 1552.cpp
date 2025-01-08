/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Since the statement gives that you only need at most 4 cells to get
        the shortest Brainfuck program, we can do DP on those 4 cells.
        - Let dp[i][j][k][l] = length of shortest program when cell 0 reaching
        ith character, cell 1 reaching jth character, cell 2 reaching kth character,
        and cell 3 reaching lth character.
        - You can easily find where the pointer is, it's max(i, j, k, l)
        - One special case is dp[0][0][0][0], we can start at cell 0 or cell 1
        - Print out result based on dp values.
        - Complexity: O(n^4)
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

string s;
int n;
int dp[51][51][51][51];

int fromTo(int x, int y) {
    if (x == 0) {
        return s[y] + 1;
    }
    return abs(s[x] - s[y]) + 1;
}

int solve(int A, int B, int C, int D) {
    int Max = 0;
    ckmax(Max, A); ckmax(Max, B); ckmax(Max, C); ckmax(Max, D);
    if (Max == n) return 0;
    
    if (dp[A][B][C][D] != -1) return dp[A][B][C][D];

    int &res = dp[A][B][C][D];
    res = INF;

    if (Max == 0) {
        ckmin(res, solve(1, B, C, D) + fromTo(0, 1));
        ckmin(res, solve(A, 1, C, D) + fromTo(0, 1));
        return res;
    }

    int pos = 0;
    if (Max == A) pos = 0;
    if (Max == B) pos = 1;
    if (Max == C) pos = 2;
    if (Max == D) pos = 3;

    ckmin(res, solve(Max+1, B, C, D) + abs(pos - 0) + fromTo(A, Max+1));
    ckmin(res, solve(A, Max+1, C, D) + abs(pos - 1) + fromTo(B, Max+1));
    ckmin(res, solve(A, B, Max+1, D) + abs(pos - 2) + fromTo(C, Max+1));
    ckmin(res, solve(A, B, C, Max+1) + abs(pos - 3) + fromTo(D, Max+1));

    return res;
}

void printMove(int x, int y) {
    while (x < y) {
        cout << ">";
        x++;
    }
    while (x > y) {
        cout << "<";
        x--;
    }
}

void printFromTo(int x, int y) {
    if (x == 0) {
        FOR(i,1,s[y]) {
            cout << "+";
        }
    } else {
        if (s[x] < s[y]) {
            FOR(i,s[x]+1,s[y]) {
                cout << "+";
            }
        } else {
            FOR(i, s[y]+1, s[x]) {
                cout << "-";
            }
        }
    }
    cout << ".";
}

void printResult(int A, int B, int C, int D) {
    int Max = 0;
    ckmax(Max, A); ckmax(Max, B); ckmax(Max, C); ckmax(Max, D);
    if (Max == n) return;
    int res = dp[A][B][C][D];

    if (Max == 0) {
        int x = solve(1, B, C, D) + fromTo(0, 1);
        if (res == x) {
            printFromTo(0, 1);
            printResult(1, B, C, D);
            return;
        }
        x = solve(A, 1, C, D) + fromTo(0, 1);
        if (res == x) {
            printFromTo(0, 1);
            printResult(A, 1, C, D);
            return;
        }
        return;
    }

    int pos = 0;
    if (Max == A) pos = 0;
    if (Max == B) pos = 1;
    if (Max == C) pos = 2;
    if (Max == D) pos = 3;

    int x = solve(Max+1, B, C, D) + abs(pos - 0) + fromTo(A, Max+1);
    if (res == x) {
        printMove(pos, 0);
        printFromTo(A, Max+1);
        printResult(Max+1, B, C, D);
        return;
    }

    x = solve(A, Max+1, C, D) + abs(pos - 1) + fromTo(B, Max+1);
    if (res == x) {
        printMove(pos, 1);
        printFromTo(B, Max+1);
        printResult(A, Max+1, C, D);
        return;
    }

    x = solve(A, B, Max+1, D) + abs(pos - 2) + fromTo(C, Max+1);
    if (res == x) {
        printMove(pos, 2);
        printFromTo(C, Max+1);
        printResult(A, B, Max+1, D);
        return;
    }

    x = solve(A, B, C, Max+1) + abs(pos - 3) + fromTo(D, Max+1);
    if (res == x) {
        printMove(pos, 3);
        printFromTo(D, Max+1);
        printResult(A, B, C, Max+1);
        return;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> s;
    n = SZ(s);
    s = " " + s;

    MS(dp, -1);
    int res = solve(0, 0, 0, 0);

    printResult(0, 0, 0, 0);
    return 0;
}
