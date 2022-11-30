/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://discuss.codechef.com/t/tutorial-disjoint-sparse-table/17404
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

struct DisjointSparseTable {
    vi a;
    int size, x;
    ll p;
    vector<vi> table;

    DisjointSparseTable(vi &a, int p) {
        // all 0-indexed
        this->a = a;
        this->p = p;

        // size = 2^x = 2^floor(log_2(n))
        size = SZ(a);
        x = __builtin_clz(SZ(a)) ^ 31;
        if( (1<<x) != SZ(a)) size = (1<<(++x));
        this->a.resize(size);

        table.resize(x+1, vi(size));
        
        build();
    }

    void build() {
        int len = 1;
        FORE(level,x,0) {
            for (int l = 0; l < size; l += len) {
                // [l, r)
                int r = l + len;
                int mid = (l + r) >> 1;
                table[level][mid] = a[mid] % p;
                FORE(i,mid-1,l) table[level][i] = (ll) table[level][i+1] * a[i] % p;

                if (mid + 1 < r) {
                    table[level][mid+1] = a[mid+1] % p;
                    FOR(i,mid+2,r-1) table[level][i] = (ll) table[level][i-1] * a[i] % p;
                }
            }
            len <<= 1;
        }
    }

    int query(int l, int r) {
        // [l, r]
        if (l == r) {
            return a[l] % p;
        }

        int k2 = __builtin_clz(l ^ r) ^ 31;
        int lev = x - 1 - k2;
        int ans = table[lev][l];
        if (r & ((1<<k2) - 1)) {
            // y % (1<<k2)
            ans = (ll) ans * table[lev][r] % p;
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    while (te--) {
        int n, q;
        ll p;
        cin >> n >> p >> q;
        vi a(n);
        FOR(i,0,n-1) {
            cin >> a[i];
        }

        vi b(q/64+2);
        FOR(i,0,q/64+1) {
            cin >> b[i];
        }

        DisjointSparseTable dst(a, p);

        ll res = 0;
        vi l(q), r(q);
        FOR(i,0,q-1) {
            if (i % 64 == 0) {
                l[i] = (b[i / 64] + res) % n;
                r[i] = (b[i / 64 + 1] + res) % n;
            } else {
                l[i] = (l[i-1] + res) % n;
                r[i] = (r[i-1] + res) % n;
            }

            if (l[i] > r[i]) {
                swap(l[i], r[i]);
            }

            res = dst.query(l[i], r[i]);
            res = (res + 1) % p;
        }
        cout << res << "\n";
    }
    return 0;
}
