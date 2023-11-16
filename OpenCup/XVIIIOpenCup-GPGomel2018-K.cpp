/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/57846?#comment-415340
        - https://drive.google.com/file/d/1VxsJDVRPSi8ePujB48jdcBn3sfN-Hhdk/view
        - https://codeforces.com/blog/entry/64625 - Example 4
        - Factorize m into prime factors. Check all divisors up to 10^6, then if m > 1,
        there are 3 cases:
            + m is a prime: Use Miller-Rabin algorithm to check.
            + m is a square of a prime: iterate over [sqrt(m) - 10, sqrt(m) + 10] to check.
            + otherwise, m is a product of 2 primes: we don't care about the values of 
            p and q, just know that their exponents are 1.
        - After factorizing, we have m = p1^a1 * p2^a2 * ... * pk^ak. We need to avoid 
        counting the cases with GCD != 1 and LCM != m, thus we should apply inclusion-
        exclusion principle. Let e_{i,1} = "GCD is divisible by pi" and e_{i,2} = "LCM is
        not divisible by pi^ai", then the answer is the number of sets which do not
        contain any e_{i,1} and e_{i,2}, for all i.
        - So we have in total 2k properties. Directly computing this would lead to the
        complexity of O(4^k), which is too much for k = 15 in the worst case.
        - There are 4 options for each prime divisor. After deciding that, it's easy
        to calculate t, which is the number of integers which might be in the set, as the
        product of ai+1, ai or ai-1 for all i. Then we mush add 2^t - 1 to the answer
        with an appropriate sign.
        - Since the prime divisor (in the way we define the properties) are independent,
        so t would be product of result of each prime divisor.
            + empty set: ai+1 ways
            + e_{i,1}: we want min(a'i) >= 1 so we have ai ways
            + e_{i_2}: we want max(a'i) < ai so we have ai ways
            + e_{i,1} and e_{i,2}: we want min(a'i) >= 1 and max(a'i) < ai so we have ai-1 ways
        - As mentioned before, directly computing this would lead to the complexity of
        O(4^k). But we see that the second and third options are similar, so we can
        merge them into one option, making the complexity O(3^k).
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

using u64 = uint64_t;
using u128 = __uint128_t;

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
const ll MODBASE = 998244353;
const int INF = 0x3f3f3f3f;

const int MAXN = 100010;
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

int nt[1000010];

void sieveBase(int n) {
    FOR(i,2,n) {
        if (nt[i] == 0) {
            nt[i] = i;
            for (ll j = (ll) i * i; j <= n; j += i) nt[j] = i;
        }
    }
}

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
}

bool MillerRabin(u64 n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

void inc_exc(vi &a, int pos, mi &res, ll cur, int num, int times) {
    // array of exponents of prime factors, current position, result, current value, number of sets in intersection, number of such sets
    if (pos == SZ(a)) {
        // dbg(cur, num);
        mi p = pow(mi(2), cur) - 1;
        if (num % 2) res -= p * times;
        else res += p * times;
        return;
    }
    // 0 -> empty
    inc_exc(a, pos+1, res, cur * (a[pos] + 1), num, times);

    // 1 -> e(i, 1) or e(i, 2) solely
    inc_exc(a, pos+1, res, cur * a[pos], num + 1, times * 2);

    // 2 -> e(i, 1) and e(i, 2)
    inc_exc(a, pos+1, res, cur * (a[pos] - 1), num + 2, times);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    ll m;
    cin >> m;
    sieveBase(1000000);
    // factorize m to get p1^a1 * p2^a2 * ... * pk^ak
    vi a;

    FOR(i,2,1000000) {
        if (nt[i] == i) {
            int cnt = 0;
            while (m % i == 0) {
                m /= i;
                cnt++;
            }
            if (cnt) {
                a.push_back(cnt);
            }
        }
    }

    // 3 cases here:
    // 1. we are left with a prime p
    // 2. we are left with a square of a prime p^2
    // 3. we are left with a product of 2 primes pq
    if (m > 1) {
        if (MillerRabin(m)) {
            // case 1
            a.push_back(1);
        } else {
            // case 2
            bool found = false;
            for (ll i = int(sqrt(m)) - 10; i <= int(sqrt(m)) + 10; i++) {
                if (i * i == m) {
                    found = true;
                    a.push_back(2);
                    break;
                }
            }
            if (!found) {
                // case 3
                // not interested in values of p and q
                a.push_back(1);
                a.push_back(1);
            }
        }
    }

    mi res = 0;
    inc_exc(a, 0, res, 1, 0, 1);

    cout << int(res);
    return 0;
}
