/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - There are 3 steps:
            + Find the minimum length of the supersequence
            + Find the number of ways to form the supersequence
            + Find the lexicographically smallest supersequence
        - Before DP, preprocess nex[i][j] = the next position of character j in C from position i
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

const int MAXN = 100;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, p, nex[MAXN*3][26], dp[MAXN][MAXN][MAXN*3], cnt[MAXN][MAXN][MAXN*3];
string A, B, C, kq;

int check(string &s, int i, int k) {
    FOR(x,i,SZ(s)-1) {
        if (k == p) return 0;
        int ch = s[x] - 'a';
        if (nex[k][ch] == -1) return 0;
        k = nex[k][ch] + 1;
    }
    return 1;
}

int solve(int i, int j, int k) {
    if (i == n) {
        if (check(B, j, k)) {
            return m - j;
        }
        return INF;
    } 
    if (j == m) {
        if (check(A, i, k)) {
            return n - i;
        }
        return INF;
    }
    if (k == p) {
        return INF;
    }
    if (dp[i][j][k] != -1) return dp[i][j][k];
    int &res = dp[i][j][k];
    res = INF;
    if (A[i] == B[j]) {
        if (nex[k][A[i] - 'a'] != -1) {
            ckmin(res, solve(i+1,j+1,nex[k][A[i] - 'a'] + 1) + 1);
        }
    } else {
        if (nex[k][A[i] - 'a'] != -1) {
            ckmin(res, solve(i+1,j,nex[k][A[i] - 'a'] + 1) + 1);
        }
        if (nex[k][B[j] - 'a'] != -1) {
            ckmin(res, solve(i,j+1,nex[k][B[j] - 'a'] + 1) + 1);
        }
    }
    return res;
}

int solve1(int i, int j, int k) {
    if (i == n || j == m) return 1;
    if (k == p) return 0;
    if (cnt[i][j][k] != -1) return cnt[i][j][k];
    int &res = cnt[i][j][k];

    res = 0;
    if (A[i] == B[j]) {
        int x = nex[k][A[i] - 'a'];
        if (x != -1 && solve(i+1, j+1, x+1) + 1 == solve(i, j, k)) {
            res += solve1(i+1, j+1, x+1);
            res %= MODBASE;
        }
    } else {
        int x = nex[k][A[i] - 'a'];
        if (x != -1 && solve(i+1, j, x+1) + 1 == solve(i, j, k)) {
            res += solve1(i+1, j, x+1);
            res %= MODBASE;
        }
        int y = nex[k][B[j] - 'a'];
        if (y != -1 && solve(i, j+1, y+1) + 1 == solve(i, j, k)) {
            res += solve1(i, j+1, y+1);
            res %= MODBASE;
        }
    }
    
    return res;
}

void solve2(int i, int j, int k) {
    if (i == n) {
        kq += B.substr(j);
        return;
    }
    if (j == m) {
        kq += A.substr(i);
        return;
    }
    if (k == p) {
        return;
    }
    int cur = solve(i,j,k);
    if (A[i] == B[j]) {
        kq += A[i];
        solve2(i+1,j+1,nex[k][A[i] - 'a'] + 1);
    } else {
        int x = nex[k][A[i] - 'a'];
        int y = nex[k][B[j] - 'a'];
        if (x != -1 && y != -1 && cur == solve(i+1, j, x+1) + 1 && cur == solve(i, j+1, y+1) + 1) {
            if (A[i] < B[j]) {
                kq += A[i];
                solve2(i+1,j,x+1);
            } else {
                kq += B[j];
                solve2(i,j+1,y+1);
            }
        } else if (x != -1 && cur == solve(i+1, j, x+1) + 1) {
            kq += A[i];
            solve2(i+1,j,x+1);
        } else {
            kq += B[j];
            solve2(i,j+1,y+1);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case " << o << ": ";
        cin >> A >> B >> C;
        n = SZ(A);
        m = SZ(B);
        p = SZ(C);

        FOR(i,0,n-1)
            FOR(j,0,m-1)
                FOR(k,0,p-1) {
                    dp[i][j][k] = -1;
                    cnt[i][j][k] = -1;
                }
    
        FORE(i,p-1,0) {
            if (i == p-1) {
                FOR(j,0,25) nex[i][j] = -1;
            } else {
                FOR(j,0,25) nex[i][j] = nex[i+1][j];
            }
            nex[i][C[i] - 'a'] = i;
        }

        int minLen = solve(0,0,0);
        if (minLen == INF) {
            cout << "0\nNOT FOUND\n";
            continue;
        }

        int res = solve1(0,0,0);
        cout << res << "\n";

        kq = "";
        solve2(0,0,0);
        cout << kq << "\n";

    }
    return 0;
}
