/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/51598
        - Let's change definition of G(x) so that f(S) >= x rather than f(S) = x. 
        Here "y >= x" means that if y and x are considered as strings, then each 
        digit in a particular position in y is greater than its corresponding 
        digit in x. This is then easy to compute, since the numbers we can use 
        must satisfy the constraint that each digit is larger than the corresponding 
        position in x. So, we can go from 999999 to 0 and do inclusion/exclusion to 
        change the >= condition to =, by fixing which digits are fixed and which 
        ones are strictly greater, so it takes 2^6 time per value of x to compute.
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

const int MAXN = 1000000;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

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

int n, a[MAXN], add[1<<6], cnt[MAXN], mu10[7];
mi dpCnt[MAXN][7], dpSum[MAXN][7], dpSum2[MAXN][7];
mi sumDpCnt[MAXN][7], sumDpSum[MAXN][7], sumDpSum2[MAXN][7];

void merge(int x, int y, int u, int v) {
    // merge sumDp[u][v] to dp[x][y]
    // simply merge 2 set of subsets
    dpSum2[x][y] = dpSum2[x][y] * sumDpCnt[u][v] + sumDpSum2[u][v] * dpCnt[x][y] + mi(2) * dpSum[x][y] * sumDpSum[u][v];
    dpSum[x][y] = dpSum[x][y] * sumDpCnt[u][v] + sumDpSum[u][v] * dpCnt[x][y];
    dpCnt[x][y] *= sumDpCnt[u][v];
}

void merge2(int x, int y, int u, int v) {
    // merge sumDp[u][v] to sumDp[x][y]
    sumDpSum2[x][y] = sumDpSum2[x][y] * sumDpCnt[u][v] + sumDpSum2[u][v] * sumDpCnt[x][y] + mi(2) * sumDpSum[x][y] * sumDpSum[u][v];
    sumDpSum[x][y] = sumDpSum[x][y] * sumDpCnt[u][v] + sumDpSum[u][v] * sumDpCnt[x][y];
    sumDpCnt[x][y] *= sumDpCnt[u][v];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,0,n-1) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    mu10[0] = 1;
    FOR(i,1,6) mu10[i] = mu10[i-1] * 10;

    FOR(mask,0,(1<<6)-1) {
        FOR(i,0,5) {
            if (mask & (1<<i)) {
                add[mask] += mu10[i];
            }
        }
    }

    ll res = 0;
    FORE(i,999999,0) {
        int bad = 0, cur = i;
        FOR(j,0,5) {
            int x = cur % 10;
            if (x == 9) {
                bad |= (1<<j);
            }
            cur /= 10;
        }

        // create a number of subsets from the current value i
        mi ways = 1;
        mi sums = 0;
        mi sqSums = 0;
        FOR(j,1,cnt[i]) {
            sqSums = sqSums + sqSums + ways * i * i + mi(i) * 2 * sums;
            sums = sums + sums + i * ways;
            ways *= 2;
        }

        // the subsets having f(subset) >= i (in first j digits, the rest are equal)
        dpCnt[i][0] = ways; // how many tuples, including empty tuple
        dpSum[i][0] = sums; // sum of all tuples' sums
        dpSum2[i][0] = sqSums; // sum of all tuples' squared sums
        FOR(j,0,5) {
            dpCnt[i][j+1] = dpCnt[i][j];
            dpSum[i][j+1] = dpSum[i][j];
            dpSum2[i][j+1] = dpSum2[i][j];
            if (!(bad & (1<<j))) {
                // need to merge dp[i][j+1] with dp[i+mu10[j]][j] 
                // until we cannot add mu10[j] to i, that's why we need
                // suffix sum arrays in the next for loop.
                merge(i, j+1, i + mu10[j], j);
            }
        }

        FOR(j,0,5) {
            sumDpCnt[i][j] = dpCnt[i][j]; 
            sumDpSum[i][j] = dpSum[i][j];
            sumDpSum2[i][j] = dpSum2[i][j];
            if (!(bad & (1<<j))) {
                merge2(i, j, i + mu10[j], j);
            }
        }

        // dpSum2[i][6] contains sum of squared sums of all subsets having
        // f(subset) larger than i in each of the 6 digits
        // We can use a simple O(2^6) inclusion-exclusion principle here
        sqSums = dpSum2[i][6];
        FOR(mask,1,(1<<6)-1) {
            if (mask & bad) continue;
            int numBit = pct(mask);
            int p = i + add[mask];
            if (numBit % 2) sqSums -= sumDpSum2[p][5];
            else sqSums += sumDpSum2[p][5];
        }

        res ^= (ll) i * sqSums.v;
    }
    cout << res;
    return 0;
}
