/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let f[i][j] be the number of sequences formed by A[1] -> A[i] and the last element is j
        - Then f[i][j] = sum(f[i-1][k]) (k != j and j <= A[i])
        - So we maintain a segment tree storing f[i] and we move from i-1 to i by:
            + Let sum be sum(f[i][j])
            + Multiply f[A[i]+1 ... MAX] by 0
            + Multiply f[1 ... A[i]] by -1
            + Add f[1 ... A[i]] by sum
        - We just need a lazy segment tree that supports range add and range multiply.
        - In the implementation, since A[i] <= 10^9, we renumber the input, then let len[k] = number
        of real numbers that the range [l, r] is managing.
        - Updating the segment tree is relatively easy.
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

const int MAXN = 500010;
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

struct SegmentTreeLazy {
    public:
    int N;

    // 0-indexed
    SegmentTreeLazy(vi &a) {
        t.resize(4*SZ(a));
        len.resize(4*SZ(a));
        lazySum.resize(4*SZ(a));
        lazyProd.resize(4*SZ(a));
        N = SZ(a);
        build(1, 0, N-1, a);
        FOR(i,0,SZ(t)-1) {
            lazySum[i] = 0;
            lazyProd[i] = 1;
        }
    }

    mi get(int k, int l, int r, int u, int v) {
        lazyUpdate(k, l, r);
        if (l > r || r < u || v < l) return 0;
        if (u <= l && r <= v) return t[k];
        int m = (l + r) >> 1;
        mi lef = get(k*2, l, m, u, v);
        mi rig = get(k*2+1, m+1, r, u, v);
        return lef + rig;
    }

    void lazyUpdate(int k, int l, int r) {
        if (l > r) return;
        if (int(lazySum[k]) == 0 && int(lazyProd[k]) == 1) return;
        t[k] = t[k] * lazyProd[k] + lazySum[k] * len[k];
        if (l < r) {
            lazySum[k*2] = lazySum[k] + lazyProd[k] * lazySum[k*2];
            lazyProd[k*2] = lazyProd[k] * lazyProd[k*2];
            lazySum[k*2+1] = lazySum[k] + lazyProd[k] * lazySum[k*2+1];
            lazyProd[k*2+1] = lazyProd[k] * lazyProd[k*2+1];
        }
        lazySum[k] = 0;
        lazyProd[k] = 1;
    }

    void add(int k, int l, int r, int u, int v, mi val) {
        lazyUpdate(k, l, r);
        if (l > r || r < u || v < l) return;
        if (u <= l && r <= v) {
            lazySum[k] = val;
            lazyUpdate(k, l, r);
            return;
        }
        int m = (l + r) >> 1;
        add(k*2, l, m, u, v, val);
        add(k*2+1, m+1, r, u, v, val);
        t[k] = t[k*2] + t[k*2+1];
    }

    void mul(int k, int l, int r, int u, int v, mi val) {
        lazyUpdate(k, l, r);
        if (l > r || r < u || v < l) return;
        if (u <= l && r <= v) {
            lazyProd[k] = val;
            lazyUpdate(k, l, r);
            return;
        }
        int m = (l + r) >> 1;
        mul(k*2, l, m, u, v, val);
        mul(k*2+1, m+1, r, u, v, val);
        t[k] = t[k*2] + t[k*2+1];
    }

    private:
    vector<mi> t, lazySum, lazyProd, len;

    void build(int k, int l, int r, vi &a) {
        if (l > r) return;
        if (l == r) {
            t[k] = 0;
            if (l > 0) len[k] = a[l] - a[l-1];
            else len[k] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(k*2, l, m, a);
        build(k*2+1, m+1, r, a);
        t[k] = t[k*2] + t[k*2+1];
        len[k] = len[k*2] + len[k*2+1];
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vi a(n);
    FOR(i,0,n-1) cin >> a[i];

    vi b;
    FOR(i,0,n-1) b.push_back(a[i]);
    remDup(b);
    
    FOR(i,0,n-1) a[i] = lower_bound(ALL(b), a[i]) - b.begin() + 1;
    int m = SZ(b);
    SegmentTreeLazy st(b);
    st.add(1,0,st.N-1,0,a[0]-1,1);

    FOR(i,1,n-1) {
        mi s = st.get(1,0,st.N-1,0,st.N-1);
        if (a[i] < m) {
            st.mul(1,0,st.N-1,a[i],st.N-1,0);
        }
        st.mul(1,0,st.N-1,0,a[i]-1,-1);
        st.add(1,0,st.N-1,0,a[i]-1,s);
    }
    mi res = st.get(1,0,st.N-1,0,st.N-1);
    cout << int(res);
    return 0;
}
