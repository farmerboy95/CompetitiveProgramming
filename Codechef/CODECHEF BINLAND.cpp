/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - The problem requires a modified queue (push, pop & number of paths).
        - If the problem required a modified stack (push, pop & number of paths), 
        it could be solved with DP. This would require O(N^2) for push operation 
        and O(1) for pop and query.
            + dp[i][y][x] = number of paths to go from char xth of the bottom of the
            stack (first row) to char yth of row ith of the stack.
        - There is a trick that allows to emulate a queue using two stacks. With this 
        trick, it’s possible to emulate a modified queue with 2 modified stacks, now 
        the push and pop would have O(N^2) amortized complexity, the query requires 
        now merging the results of both modified stacks, which can be done in O(N) 
        using the fixed columns.
        - There are 2 stacks st[0] and st[1], we push to st[0] and pop out from st[1].
        It means that when facing "remove", we move all the elements from st[0] to
        st[1] and pop from top of stack st[1].
        - Let dp[id][i][y][x] = number of paths to go from char xth of the bottom of
        the stack id (first row) to char yth of row ith of that stack.
        - When we push to st[0], we update the back of dp of st[0], and we do the same
        thing to st[1] when pushing data into it. Since the data is symmetric, going
        from char xth of the first row to yth of the ith row is the same as going from
        yth char of the ith row to xth char of the first row.
        - When both stacks have data, we just calculate the data at the cut and multiply
        them, for all the possible ways.
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

const int MAXN = 20;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 300010;

template<int MOD> struct mint {
    static const int mod = MOD;
    int v; explicit operator int() const { return v; } // explicit -> don't silently convert to int
    mint() { v = 0; }
    mint(ll _v) { v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
        if (v < 0) v += MOD; }
    friend bool operator==(const mint& a, const mint& b) { 
        return a.v == b.v; }
    friend bool operator!=(const mint& a, const mint& b) { 
        return !(a == b); }
    friend bool operator<(const mint& a, const mint& b) { 
        return a.v < b.v; }
    friend string ts(mint a) { return ts(a.v); }

    mint& operator+=(const mint& m) { 
        if ((v += m.v) >= MOD) v -= MOD; 
        return *this; }
    mint& operator-=(const mint& m) { 
        if ((v -= m.v) < 0) v += MOD; 
        return *this; }
    mint& operator*=(const mint& m) { 
        v = int((ll) v * m.v % MOD); return *this; }
    mint& operator/=(const mint& m) { return (*this) *= inv(m); }
    friend mint pow(mint a, ll p) {
        mint ans = 1; assert(p >= 0);
        for (; p; p /= 2, a *= a) if (p&1) ans *= a;
        return ans; }
    friend mint inv(const mint& a) { assert(a.v != 0); 
        return pow(a,MOD-2); }
        
    mint operator-() const { return mint(-v); }
    mint& operator++() { return *this += 1; }
    mint& operator--() { return *this -= 1; }
    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }
};

typedef mint<MODBASE> mi;
typedef vector<mi> vmi;
typedef pair<mi,mi> pmi;
typedef vector<pmi> vpmi;

int n, q;
mi dp[2][MAXQ][MAXN][MAXN];
vs st[2];

void updateBack(int id) {
    int m = SZ(st[id]);
    if (m >= 2) {
        FOR(i,0,n-1) {
            FOR(j,0,n-1) {
                dp[id][m-1][i][j] = 0;
            }
            FOR(j,i-1,i+1) {
                if (j < 0 || j >= n) continue;
                if (st[id][m-1][i] != st[id][m-2][j]) continue;
                FOR(k,0,n-1) {
                    dp[id][m-1][i][k] += dp[id][m-2][j][k];
                }
            }
        }
    } else if (m == 1) {
        FOR(i,0,n-1) {
            FOR(j,0,n-1) {
                dp[id][0][i][j] = (i == j);
            }
        }
    }
}

mi solve(int x, int y) {
    if (SZ(st[0]) == 0) {
        return dp[1][SZ(st[1])-1][x][y];
    }
    if (SZ(st[1]) == 0) {
        return dp[0][SZ(st[0])-1][y][x];
    }

    mi res = 0;
    FOR(k,0,n-1) {
        FOR(k2,k-1,k+1) {
            if (k2 < 0 || k2 >= n) continue;
            if (st[0][0][k] != st[1][0][k2]) continue;
            if (int(dp[0][SZ(st[0])-1][y][k]) == 0) continue; 
            if (int(dp[1][SZ(st[1])-1][x][k2]) == 0) continue;
            res += dp[0][SZ(st[0])-1][y][k] * dp[1][SZ(st[1])-1][x][k2];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> q;

    while (q--) {
        string s;
        cin >> s;
        if (s == "add") {
            string cols;
            cin >> cols;
            st[0].push_back(cols);
            updateBack(0);
        } else if (s == "remove") {
            if (SZ(st[1]) == 0) {
                while (SZ(st[0])) {
                    st[1].push_back(st[0].back());
                    st[0].pop_back();
                    updateBack(1);
                }
            }
            st[1].pop_back();
        } else {
            int x, y;
            cin >> x >> y;
            x--; y--;
            cout << int(solve(x, y)) << "\n";
        }
    }
    return 0;
}
