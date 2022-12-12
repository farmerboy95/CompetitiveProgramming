/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Since there are only 26 lower English characters, and we need to create a 
        palindrome with a subset, it means we can use XOR operation on subset. We 
        can consider a 26-dimensional vector space and convert each input string 
        to a vector to add to the basis.
        - Let's say we have a basis of a segment, how can we find the result?
        - Let's consider another problem, we have a basis, how can we find the number of
        subsets that xor of the elements equal to x, including an empty subset? 
            + First we need to check if x is representable by the basis, if not, the result
            is 0, otherwise, the result is 2^(y-z), with y = number of vectors that we tried
            to add to the basis, z = the number of vectors in the basis.
            + This is because we can choose any subsets in the set of vectors not in the
            basis, to combine with a subset of basis to create x.
        - Assume that we have the size of basis (sz) and the number of vectors added
        to the basis (numVectors), let k = 2^(numVectors-sz), the result is the sum 
        of these numbers:
            + The number of non-empty subsets that can produce an even-length palindrome
            which means x = 0, we all know that 0 can always be representable by a basis
            according to the previous problem, but now we have to notice that we consider
            non-empty subsets only, so the empty subset is not applicable, so we add k-1
            to the result.
            + The number of non-empty subsets that can produce an odd-length palindrome,
            which means x = 2^i (i : 0 -> 25), empty subset cannot be a result here,
            so for each i, if x is representable, we simply add k to the result.
        - Alright, we have the idea, but how can we get the basis of a segment? As the
        basis size is small, we can use a segment tree to quickly get segment basis and
        update data of one element.
        - Note that although the statement did not give anything about modulo, we
        have to print result modulo 10^9+7
        - Complexity O(n log n * D^2), because merging 2 basis requires D^2 time, with
        D = number of dimensions = 26 in this problem.
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

const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;
const int MAXD = 26;

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

struct VectorBasis {
    vi basis;
    int d, sz;
    int numVectors;

    VectorBasis(int d) {
        this->d = d;
        this->sz = 0;

        // numVectors is the number of vectors inserted
        this->numVectors = 0;
        basis.resize(d);
        FOR(i,0,d-1) basis[i] = 0;
    }

    void insertVector(int mask, bool incCnt = true) {
        // insert mask to the basis
        if (incCnt) numVectors++;
        FOR(i,0,d-1) {
            if (!(mask & (1 << i))) continue;

            if (!basis[i]) {
                basis[i] = mask;
                sz++;
                return;
            }

            mask ^= basis[i];
        }
    }

    bool checkXor(int mask) {
        // check if mask is representable by the basis
        FOR(i,0,d-1) {
            if (!(mask & (1<<i))) continue;
            if (!basis[i]) return false;
            mask ^= basis[i];
        }
        return true;
    }

    void merge(VectorBasis &v) {
        // merge 2 basis with the same dimention
        numVectors += v.numVectors;
        FOR(i,0,d-1) {
            if (v.basis[i]) {
                insertVector(v.basis[i], false);
            }
        }
    }
};

int toInt(string &s) {
    int res = 0;
    FOR(i,0,SZ(s)-1) {
        res ^= (1 << (s[i] - 'a'));
    }
    return res;
}

struct SegmentTree {
    public:
    int N;

    SegmentTree(vi &a) {
        t.resize(4*SZ(a), VectorBasis(MAXD));
        N = SZ(a);
        build(1, 0, N-1, a);
    }

    VectorBasis get(int k, int l, int r, int u, int v) {
        if (l > r || r < u || v < l) return VectorBasis(MAXD);
        if (u <= l && r <= v) return t[k];
        int m = (l + r) >> 1;
        VectorBasis lef = get(k*2, l, m, u, v);
        VectorBasis rig = get(k*2+1, m+1, r, u, v);
        return merge(lef, rig);
    }

    void update(int k, int l, int r, int u, int val) {
        if (l > r || r < u || u < l) return;
        if (l == r) {
            VectorBasis newVB(MAXD);
            newVB.insertVector(val);
            t[k] = newVB;
            return;
        }
        int m = (l + r) >> 1;
        update(k*2, l, m, u, val);
        update(k*2+1, m+1, r, u, val);
        t[k] = merge(t[k*2], t[k*2+1]);
    }

    private:
    vector<VectorBasis> t;

    void build(int k, int l, int r, vi &a) {
        if (l > r) return;
        if (l == r) {
            t[k].insertVector(a[l]);
            return;
        }
        int m = (l + r) >> 1;
        build(k*2, l, m, a);
        build(k*2+1, m+1, r, a);
        t[k] = merge(t[k*2], t[k*2+1]);
    }

    VectorBasis merge(VectorBasis &a, VectorBasis &b) {
        VectorBasis res(MAXD);
        res.merge(a);
        res.merge(b);
        return res;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vi a;
    FOR(i,0,n-1) {
        string s;
        cin >> s;
        int num = toInt(s);
        a.push_back(num);
    }

    vmi mu(n+1);
    mu[0] = 1;
    FOR(i,1,n) {
        mu[i] = mu[i-1] * 2;
    }

    SegmentTree seg(a);

    while (m--) {
        int ch;
        cin >> ch;
        if (ch == 1) {
            int x;
            string y;
            cin >> x >> y;
            x--;
            seg.update(1, 0, seg.N-1, x, toInt(y));
        } else {
            int x, y;
            cin >> x >> y;
            x--; y--;
            VectorBasis vb = seg.get(1, 0, seg.N-1, x, y);
            int g = vb.numVectors - vb.sz;
            mi res = mu[g] - 1;
            FOR(i,0,MAXD-1) {
                if (vb.checkXor(1 << i)) {
                    res += mu[g];
                }
            }

            cout << int(res) << "\n";
        }
    }
    return 0;
}
