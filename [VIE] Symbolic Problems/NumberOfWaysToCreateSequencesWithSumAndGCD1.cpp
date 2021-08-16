/*
    Keywords: dp, mobius function, knapsack, inclusion-exclusion
    Đề bài:
        - Cho n, m và 2 mảng l[i], r[i] n phần tử. Tìm số dãy n phần tử thoả mãn điều kiện sau:
            + l[i] <= a[i] <= r[i]
            + sum(a[i]) <= m
            + gcd(a[i]) = 1
    Lời giải:
        - Đầu tiên bỏ qua điều kiện gcd = 1. Ta có thể giải được bài toán với 2 điều kiện đầu trong
        O(n * m). Sau đó ta sẽ có số dãy có gcd >= 1. Ta cũng có thể giải bài toán với gcd >= d,
        và có thể tìm hết ways(d) (d : 1->m) trong O(nm log m).
        - Tới đây ta có 2 cách tìm gcd = 1. Đơn giản chỉ cần trừ những thằng gcd > 1 ra khỏi gcd >= 1
        (inclusion-exclusion):
            1. Dùng mobius function, nó sẽ lo phần inclusion-exclusion cho chúng ta.
            2. Duyệt ngược d từ m về 1. ways(d) = ways(>=d) - ways(2d) - ways(3d) ...
            Chỉ tốn thời gian hơn 1 chút.
    Nguồn: 
        - https://codeforces.com/contest/1559/problem/E
        - https://codeforces.com/blog/entry/93898
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

const int MAXN = 55;
const int MAXM = 100010;
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

int n, m, l[MAXN], r[MAXN], L[MAXN], R[MAXN], nt[MAXM], mobius[MAXM];
mi dp[MAXN][MAXM];

mi get(int x) {
    int M = m / x;
    FOR(i,1,n) {
        L[i] = l[i] / x;
        if (l[i] % x) L[i]++;
        if (L[i] == 0) L[i] = 1;
        R[i] = r[i] / x;
        if (L[i] > R[i]) return 0;
    }

    dp[0][0] = 1;
    FOR(i,0,n-1) {
        FOR(j,0,M+1) dp[i+1][j] = 0;

        FOR(j,0,M) {
            if (int(dp[i][j]) == 0) continue;
            int g = j + L[i+1];
            int h = j + R[i+1];
            if (g > M) continue;
            h = min(h, M);
            dp[i+1][g] += dp[i][j];
            dp[i+1][h+1] -= dp[i][j];
        }

        FOR(j,1,M) dp[i+1][j] += dp[i+1][j-1];
    }

    mi res = 0;
    FOR(j,0,M) res += dp[n][j];
    return res;
}

void sieveBase(int n) {
    FOR(i,2,n) {
        if (nt[i] == 0) {
            nt[i] = i;
            for (ll j = (ll) i * i; j <= n; j += i) nt[j] = i;
        }
    }
    mobius[1] = 1;
    FOR(i,2,n) {
        int p = i, cntFactor = 0;
        bool co = false;
        while (p > 1) {
            int k = nt[p], cnt = 0;
            while (p % k == 0) {
                p /= k;
                cnt++;
            }
            if (cnt >= 2) {
                co = true;
                break;
            }
            cntFactor++;
        }
        if (co) mobius[i] = 0;
        else mobius[i] = (cntFactor % 2 ? -1 : 1);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    sieveBase(100000);
    cin >> n >> m;
    FOR(i,1,n) cin >> l[i] >> r[i];

    mi res = 0;
    FOR(x,1,m) {
        if (mobius[x] == 0) continue;
        res += mobius[x] * get(x);
    }
    cout << int(res);
    return 0;
}
