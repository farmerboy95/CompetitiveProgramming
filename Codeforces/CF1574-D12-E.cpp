/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/95188
        - Some explanation in the code
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

const int MAXN = 1000010;
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

int n, m, k, cntx[2];
map<pi, int> c;
set<int> badR, badC, uR, uC;
int cntR[MAXN][2], cntC[MAXN][2];
mi mu[MAXN];

void update2(int pos, int col, int add, int cnt[MAXN][2], set<int> &bad, set<int> &u) {
    cnt[pos][col] += add;

    if (cnt[pos][0] && cnt[pos][1]) {
        bad.insert(pos);
    } else {
        bad.erase(pos);
    }

    if (cnt[pos][0] > 0 || cnt[pos][1] > 0) {
        u.insert(pos);
    } else {
        u.erase(pos);
    }
}

void update(int x, int y, int t) {
    // color (x, y) in a checkerboard pattern 
    int mark = (x & 1) ^ (y & 1);
    if (c.count({x, y})) {
        // remove (x, y)
        int nMark = mark ^ c[{x, y}];
        cntx[nMark]--;
        update2(x, nMark, -1, cntR, badR, uR);
        update2(y, nMark, -1, cntC, badC, uC);
        c.erase({x, y});
    }

    // removed already, ok to quit
    if (t == -1) return;

    // add (x, y)
    int nMark = mark ^ t;
    cntx[nMark]++;
    update2(x, nMark, 1, cntR, badR, uR);
    update2(y, nMark, 1, cntC, badC, uC);
    c[{x, y}] = t;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    mu[0] = 1;
    FOR(i,1,1000000) mu[i] = mu[i-1] * 2;

    cin >> n >> m >> k;
    FOR(i,1,k) {
        int x, y, t;
        cin >> x >> y >> t;
        x--; y--;
        update(x, y, t);

        mi res = 0;
        if (SZ(badR) && SZ(badC)) {
            res = 0;
        } else if (SZ(badR)) {
            res = mu[m - SZ(uC)];
        } else if (SZ(badC)) {
            res = mu[n - SZ(uR)];
        } else {
            if (SZ(uR) == 0 && SZ(uC) == 0) {
                /*
                if there are no forced stripes (horizontal or vertical) and no rows or columns 
                have any cell coloured in them (they are not set in place) then the possible 
                number of colourings is:
                    Assume there are horizontal stripes, that gives 2^n different colourings.
                    Assume there are vertical stripes, that gives 2^m different colourings.
                But the two cases above share two colourings, which is the checkerboard 
                pattern and the anti-checkerboard pattern, which have to be subtracted from 
                the total.
                */
                res = mu[n] + mu[m] - 2;
            } else {
                // this is somewhat the same as the above explanation
                res += mu[m - SZ(uC)];
                res += mu[n - SZ(uR)];
                if (cntx[0] == 0 || cntx[1] == 0) {
                    res -= 1;
                }
            }
        }
        cout << int(res) << "\n";
    }
    return 0;
}
