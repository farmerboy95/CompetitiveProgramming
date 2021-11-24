/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's first see how the result of the shifted suit is better than that of the 
        current suit.
        - Denote a[0..n-1] as the real answer array, b[0..n-1] as the answers of the student.
        Let's consider one element i, when shifting, b[i] will be placed at i+1. We have this
        table:
                a[i]        a[i+1]
                Wrong       Wrong           when b[i] != a[i] and b[i] != a[i+1], unchange point
                Wrong       Correct         when a[i+1] = b[i] and a[i] != a[i+1], increase point
                Correct     Wrong           when a[i] = b[i] and a[i] != a[i+1], decrease point
                Correct     Correct         when a[i] = a[i+1], unchange point
                b[i]        b[i]
        - Here we can see that when a[i] = a[i+1], shifting does NOT change the point, so we have
        k ways to choose b[i] here.
        - Let cntEqual = number of equal pairs. Then we have r = n - cntEqual to be number of
        unequal pairs.
        - We can see that there is only one way to make the point increase in one pair, and one way
        to make the point decrease, and k-2 ways to make the point unchange.
        - So for F1, we can choose i pairs in r pairs (to be pairs with increasing points), then choose 
        j pairs in r - i pairs (to be pairs with decreasing points) (j < i), finally multiply them with 
        (k-2) ^ (r-i-j), r-i-j pairs with unchange points. Remember to add cntEqual pairs of unchange points
        into this as well. Complexity O(n^2)
        - But it takes too much time for F2, here we can choose the number of pairs with unchange points first.
        Denote it as x, we have (k-2) ^ x * C(r-x, i) ways to choose, then how to choose i that r-x-i < i?
        - Easy, if r-x is odd, it's simply 2^(r-x) / 2, otherwise it's (2^(r-x) - C(r-x, (r-x)/2)) / 2. You
        can use some simple properties of binomial coefficient to prove it. So we can calculate the result
        in O(n)
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
string ts(bool b) { return ts((int)b); }
template<class T> string ts(complex<T> c) { stringstream ss; ss << c; return ss.str(); }
template<class T> using V = vector<T>;
string ts(V<bool> v) {string res = "{"; FOR(i,0,SZ(v)-1) res += char('0'+v[i]); res += "}"; return res; }
template<size_t sz> string ts(bitset<sz> b) { string res = ""; FOR(i,0,SZ(b)-1) res += char('0'+b[i]); return res; }
template<class T, class U> string ts(pair<T,U> p);
template<class T> string ts(T v) { // containers with begin(), end()
    bool fst = 1; string res = "";
    for (const auto& x: v) { if (!fst) res += " "; fst = 0; res += ts(x); }
    return res;
}
template<class T, class U> string ts(pair<T,U> p) { return "("+ts(p.FI)+", "+ts(p.SE)+")"; }

// OUTPUT
template<class T> void pr(T x) { cout << ts(x); }
template<class T, class ...U> void pr(const T& t, const U&... u) { pr(t); pr(u...); }
void ps() { pr("\n"); } // print w/ spaces
template<class T, class ...U> void ps(const T& t, const U&... u) { pr(t); if (sizeof...(u)) pr(" "); ps(u...); }

// DEBUG
void DBG() { cerr << "]" << endl; }
template<class T, class ...U> void DBG(const T& t, const U&... u) { cerr << ts(t); if (sizeof...(u)) cerr << ", "; DBG(u...); }
#define dbg(...) cerr << "Line(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#define chk(...) if (!(__VA_ARGS__)) cerr << "Line(" << __LINE__ << ") -> function(" \
        << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\n", exit(0);

const ld PI = acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
const ld EPS = 1e-9;
const ll MODBASE = 998244353;
const int INF = 0x3f3f3f3f;

const int MAXN = 200010;
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

int n, k, a[MAXN];
mi mu[MAXN], mu2[MAXN], f[MAXN], rev[MAXN];

mi C(int n, int k) {
    if (k > n || k < 0) return 0;
    return f[n] * rev[n-k] * rev[k];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,0,n-1) cin >> a[i];

    if (k == 1) {
        cout << 0;
        return 0;
    }

    f[0] = 1;
    FOR(i,1,200000) f[i] = f[i-1] * i;
    rev[200000] = inv(f[200000]);
    FORE(i,199999,0) rev[i] = rev[i+1] * (i+1);
    mu[0] = 1;
    FOR(i,1,n) mu[i] = mu[i-1] * (k - 2);
    mu2[0] = 1;
    FOR(i,1,n) mu2[i] = mu2[i-1] * 2;

    int cntEqual = 0;
    FOR(i,0,n-1)
        if (a[i] == a[(i + 1) % n]) cntEqual++;
    
    mi ways = pow(mi(k), cntEqual);
    mi res = 0;

    int r = n - cntEqual;

    FOR(x,0,r-1) {
        // x = num0
        mi p = mu[x] * C(r, x);
        int remain = r - x;
        if (remain % 2) {
            res += p * (mu2[remain] / 2);
        } else {
            res += p * ((mu2[remain] - C(remain, remain/2)) / 2);
        }
    }

    cout << int(ways * res);
    return 0;
}
