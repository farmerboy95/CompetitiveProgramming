/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - a[i] + a[j] = i + j => a[i] - i = -(a[j] - j)
        - F(a) max when there are n/2 numbers a[i] - i = x and n/2 numbers a[i] - i = -x 
        (x is positive). If n is odd, there are 2 cases for this.
        - For each number i (1->n), we can put numbers from l to r into it, so a[i] - i will
        be from l - i to r - i. When i increases by 1, the range will be moved 1 to the left.
        Note that because l <= 1 < n <= r so 0 will be on at least one range.
        - Let's consider each number in our list of ranges, consider the positive ones only, 
        call it x, and an even n for simplicity (we can do the same with odd n).
        - So we need to choose n/2 numbers for x and n/2 numbers for -x. Here one special
        thing is that the positive ones are from 1, and negative ones are from n, you can
        draw a list of ranges to see this. When decreasing, number of possible positive 
        numbers for x increases by 1 and the same thing happens for the number of possible 
        negative numbers.
        - But 10^9 <= l < r <= 10^9, so the range can be so big, but we know that at one moment
        the number of possible positive numbers and negative ones stop at n, so we can calculate
        the rest in O(1), after increasing and calculating in O(n).
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
const ll MODBASE = 1000000007LL;
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

int n, l, r;
mi f[MAXN], rev[MAXN];

inline mi C(int n, int k) {
    if (k > n || k < 0) return 0;
    return f[n] * rev[n-k] * rev[k];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    f[0] = 1;
    rev[0] = inv(f[0]);
    FOR(i,1,200000) {
        f[i] = f[i-1] * i;
        rev[i] = inv(f[i]);
    }

    int te;
    cin >> te;
    while (te--) {
        cin >> n >> l >> r;
        int minLef = 0, maxRig = 0;
        FOR(i,1,n) {
            int lef = l - i, rig = r - i;
            minLef = min(minLef, lef);
            maxRig = max(maxRig, rig);
        }

        int L = 1, nowLef = minLef;
        int R = 1, nowRig = maxRig;
        if (abs(minLef) >= maxRig) {
            while (abs(nowLef) != abs(nowRig)) {
                nowLef++;
                L = min(L + 1, n);
                if (L == n) {
                    nowLef = -abs(nowRig);
                    break;
                }
            }
        } else {
            while (abs(nowLef) != abs(nowRig)) {
                nowRig--;
                R = min(R + 1, n);
                if (R == n) {
                    nowRig = abs(nowLef);
                    break;
                }
            }
        }

        mi res = 0;
        while (!(L == n && R == n)) {
            if (L + R < n) {
                nowLef++;
                L = min(L + 1, n);
                nowRig--;
                R = min(R + 1, n);
                continue;
            }
            int common = L + R - n;
            int uncommonL = L - common;
            int uncommonR = R - common;

            if (n % 2 == 0) {
                int needL = n / 2 - uncommonL;
                res += C(common, needL);
            } else {
                int needL = (n + 1) / 2 - uncommonL;
                res += C(common, needL);
                needL = n - (n + 1) / 2 - uncommonL;
                res += C(common, needL);
            }

            nowLef++;
            L = min(L + 1, n);
            nowRig--;
            R = min(R + 1, n);
        }

        if (n % 2 == 0) {
            res += mi(nowRig) * C(n, n / 2);
        } else {
            res += mi(nowRig) * (C(n, (n + 1) / 2) + C(n, n / 2));
        }
        cout << int(res) << "\n";
    }
    return 0;
}
