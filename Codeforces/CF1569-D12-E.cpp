/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/94721
        - Meet in the middle technique, use when k = 5
        - Choose the winning half and try to calculate the hash
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

const int MAXN = 110;
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

vi eval(int n, int mask) {
    int curPlace = n / 2 + 1;
    int curBit = 0;
    vi a(n);
    vi p(n);
    FOR(i,0,n-1) a[i] = i;
    while (SZ(a) > 1) {
        vi tmp;
        for (int i = 0; i < SZ(a); i += 2) {
            if (mask & (1<<curBit)) {
                p[a[i+1]] = curPlace;
                tmp.push_back(a[i]);
            } else {
                p[a[i]] = curPlace;
                tmp.push_back(a[i+1]);
            }
            curBit++;
        }
        swap(tmp, a);
        curPlace /= 2;
        curPlace += 1;
    }
    p[a[0]] = 1;
    return p;
}

vi adjust(vi p, bool win) {
    FOR(i,0,SZ(p)-1)
        if (p[i] == 1) {
            if (!win) p[i]++;
        } else {
            p[i] = p[i] * 2 - 1;
        }
    return p;
}

mi getHash(vi p, mi A, bool partial = false, bool win = false, int shift = 0) {
    if (partial) p = adjust(p, win);
    mi res = 0;
    FOR(i,0,SZ(p)-1) res += (i+1+shift) * pow(A, p[i]);
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int k, A, h;
    cin >> k >> A >> h;
    if (k <= 4) {
        int numMatches = (1 << k) - 1;
        FOR(mask,0,(1<<numMatches)-1) {
            vi p = eval(1<<k, mask);
            mi hash = getHash(p, A);
            if (int(hash) == h) {
                TRAV(x, p) cout << x << ' ';
                cout << "\n";
                return 0;
            }
        }
    } else {
        int maskLeft = -1, maskRight = -1;
        bool leftWin = false;

        FOR(x,0,1) {
            map<int, int> leftMap;
            FOR(mask,0,(1<<15)-1) {
                vi p = eval(16, mask);
                leftMap[int(getHash(p, A, true, x == 0, 0))] = mask;
            }
            FOR(mask,0,(1<<15)-1) {
                vi p = eval(16, mask);
                mi rightHash = getHash(p, A, true, x == 1, 16);
                mi leftHash = h - rightHash;
                if (leftMap.count(int(leftHash))) {
                    maskLeft = leftMap[int(leftHash)];
                    maskRight = mask;
                    leftWin = (x == 0);
                }
            }
        }

        if (maskLeft != -1) {
            vi p1 = eval(16, maskLeft), p2 = eval(16, maskRight);
            vi resLeft = adjust(p1, leftWin);
            vi resRight = adjust(p2, !leftWin);
            TRAV(x, resLeft) cout << x << ' ';
            TRAV(x, resRight) cout << x << ' ';
            return 0;
        }
    }
    cout << -1;
    return 0;
}
