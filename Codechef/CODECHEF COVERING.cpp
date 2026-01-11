/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - The problem statement can be intepreted as:
            + For a mask X, if we have 3 masks A, B, C that their OR sum can cover
            X, we add F[A] * G[B] * H[C] to the R(X). We need to get sum(R(i)),
            i = 0 -> 2^n - 1 (First commented code block, it takes O(2^4n)).
            + We can easily see that F[A] * G[B] * H[C] contributed W times to the
            result, W is the number of set bits of A | B | C (Second commented code
            block, it takes O(2^3n)).
        - Let dpF, dpG, dpH be the SOS DP of F, G, H, respectively. For example,
        dpF[mask] = sum of F[X] that (X & mask = X), in other words, X is a subset
        of mask.
        - Let dpC be dpF * dpG * dpH, so dpC[mask] = dpF[mask] * dpG[mask] * dpH[mask].
        dpC[mask] will be the F[A] * G[B] * H[C] that A | B | C = W, and W is a subset
        of mask (subset, NOT the mask itself).
        - So we need to exclude W that is not equal to mask from dpC[mask]. We can do
        this by doing SOS DP in reverse (in https://codeforces.com/blog/entry/105247).
        At the end dpC[mask] will contain F[A] * G[B] * H[C] that A | B | C = mask.
        - Iterate through dpC again and multiply each with the number of set bits,
        then add to the result.
        - Complexity O(n).
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

int n;
ll f[1<<MAXN], g[1<<MAXN], h[1<<MAXN];
mi dpF[1<<MAXN], dpG[1<<MAXN], dpH[1<<MAXN], dpC[1<<MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,0,(1<<n)-1) {
        cin >> f[i];
        dpF[i] = f[i];
    }
    FOR(i,0,(1<<n)-1) {
        cin >> g[i];
        dpG[i] = g[i];
    }
    FOR(i,0,(1<<n)-1) {
        cin >> h[i];
        dpH[i] = h[i];
    }

    FOR(i,0,n-1) {
        FOR(mask,0,(1<<n)-1) {
            if (mask & (1<<i)) {
                dpF[mask] += dpF[mask ^ (1<<i)];
                dpG[mask] += dpG[mask ^ (1<<i)];
                dpH[mask] += dpH[mask ^ (1<<i)];
            }
        }
    }
    FOR(mask,0,(1<<n)-1) {
        dpC[mask] = dpF[mask] * dpG[mask] * dpH[mask];
    }

    FOR(i,0,n-1) {
        FOR(mask,0,(1<<n)-1) {
            if (mask & (1<<i)) {
                dpC[mask] -= dpC[mask ^ (1<<i)];
            }
        }
    }

    mi res = 0;

    // FOR(mask,0,(1<<n)-1) {
    //     FOR(a,0,(1<<n)-1) {
    //         FOR(b,0,(1<<n)-1) {
    //             FOR(c,0,(1<<n)-1) {
    //                 int w = (a | b | c);
    //                 if ((w & mask) != mask) continue;
    //                 res += mi(f[a]) * g[b] * h[c];
    //             }
    //         }
    //     }
    // }

    // FOR(a,0,(1<<n)-1) {
    //     FOR(b,0,(1<<n)-1) {
    //         FOR(c,0,(1<<n)-1) {
    //             int w = (a | b | c);
    //             mi t = 1 << pct(w);
    //             res += mi(f[a]) * g[b] * h[c] * t;
    //         }
    //     }
    // }

    FOR(mask,0,(1<<n)-1) {
        mi t = 1 << pct(mask);
        res += dpC[mask] * t;
    }
    cout << int(res);
    return 0;
}
