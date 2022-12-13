/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://img.atcoder.jp/abc141/editorial.pdf
        - Since (a[1] ^ a[2] ^ ... ^ a[n]) <= (a[1]) + (a[2] ^ ... ^ a[n]) holds, it 
        can be assumed that you may paint all integers in the same color.
        - Let Xred, Xblue be the XOR of integers painted in red and in blue, respectively. 
        Obviously, Xred ^ Xblue = a[1] ^ ... ^ a[n] holds, and this value is constant. 
        Write the value in binary notation, and let's call its digits with value 0 as 
        "interesting".
        - The i-th bits of Xred and Xblue are
            + (0, 1) or (1, 0) if i-th bit is not interesting, in which case the sum is
            constant, and
            + (0, 0) or (1, 1) if i-th bit is interesting
        - Since 2^i > 2^(i-1) + 2^(i-2) + ... + 2^0, it appears that it's optimal to 
        greedily letting interesting bit (1, 1) from higher to the lower, so the problem
        can be rephrased as follows:
            + Let a'[i] be a sequence, each element's non-interesting bits being removed,
            and maximize X'red + X'blue. If you add the integer whose all the non-interesting
            bits are set to 1 to it, that would be the answer for the original problem.
        - In the problem above, X'red = X'blue holds, so maximizing X'blue will be sufficient.
        Eventually, we only need to paint some a'[1], a'[2], ..., a'[n] in blue and maximize
        their XOR. Solving this is trivial using vector basis technique
        - Since X'red = X'blue holds, there would be at least one element in each set.
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

struct VectorBasis {
    vl basis;
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

    void insertVector(ll mask, bool incCnt = true) {
        // insert mask to the basis
        if (incCnt) numVectors++;
        FORE(i,d-1,0) {
            if (!(mask & (1LL << i))) continue;

            if (!basis[i]) {
                basis[i] = mask;
                sz++;
                return;
            }

            mask ^= basis[i];
        }
    }

    bool checkXor(ll mask) {
        // check if mask is representable by the basis
        FOR(i,0,d-1) {
            if (!(mask & (1LL << i))) continue;
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

    ll getMax() {
        ll res = 0;
        dbg(basis);
        FORE(i,d-1,0) {
            if (!basis[i]) continue;
            if (res & (1LL << i)) continue;
            res ^= basis[i];
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vl a(n);

    ll xorSum = 0;
    FOR(i,0,n-1) {
        cin >> a[i];
        xorSum ^= a[i];
    }

    FORE(i,59,0) {
        if (xorSum & (1LL << i)) {
            FOR(j,0,n-1) {
                if (a[j] & (1LL << i)) {
                    a[j] -= (1LL << i);
                }
            }
        }
    }

    VectorBasis vb(60);
    FOR(i,0,n-1) {
        vb.insertVector(a[i]);
    }
    ll maxXor = vb.getMax();

    cout << maxXor + (xorSum ^ maxXor);
    return 0;
}
