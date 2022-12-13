/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status:
    Idea:
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

const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, level[MAXN];
vector<vl> a[MAXN];
ll prefXor[MAXN];

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
        FORE(i,d-1,0) {
            if (!basis[i]) continue;
            if (res & (1LL << i)) continue;
            res ^= basis[i];
        }
        return res;
    }
};

void dfs(int u, int edgeIdx, VectorBasis &vb) {
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i][0];
        ll c = a[u][i][1];
        int idx = a[u][i][2];
        if (idx == edgeIdx) continue;
        if (!level[v]) {
            // span edge
            level[v] = level[u] + 1;
            prefXor[v] = prefXor[u] ^ c;
            dfs(v, u, vb);
        } else {
            // back edge
            if (level[v] <= level[u]) {
                ll cycleXor = prefXor[u] ^ prefXor[v] ^ c;
                vb.insertVector(cycleXor);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> m;
    FOR(i,1,m) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        a[u].push_back({v, c, i});
        a[v].push_back({u, c, i});
    }

    VectorBasis vb(61);
    level[1] = 1;
    prefXor[1] = 0;
    dfs(1, 0, vb);

    cout << vb.getMax();
    return 0;
}
