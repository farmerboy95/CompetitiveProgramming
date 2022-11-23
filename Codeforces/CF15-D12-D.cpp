/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - First, you get all axb rectangles with their number of removals, you can
        do it with 2D RMQ and 2D prefix sum, please note that we only query on a fixed
        axb size, so you don't really need the whole O(logN * logM * N * M) sparse table.
        Instead, you just need to calculate min of all 2 ^ (logA) * 2 ^ (logB) sized
        rectangles only, to avoid MLE.
        - Then sort all the rectangles with most priority on the number of removals,
        then row index and finally column index. Then iterate through all axb rectangles,
        we need some way to check if the current rectangle has all cell not chosen by any
        previous rectangle, we can use 2D BIT to mark 4 corners of satisfied rectangles.
        This is correct because all rectangles have the same size, so we only need to
        mark 4 corners.
        - Complexity O(logN * logM * N * M)
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

struct Data {
    int x, y;
    ll diff;
};

bool cmp(Data a, Data b) {
    if (a.diff != b.diff) return a.diff < b.diff;
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

struct RMQ2D {
    vector<vi> preComp, tmp;
    vector<vl> prefixSum;
    int kN, kM;

    int log2_floor(unsigned long long i) {
        return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
    }

    RMQ2D(vector<vi> &a, int A, int B) {
        int n = SZ(a);
        int m = SZ(a[0]);
        kN = log2_floor(A); kM = log2_floor(B);
        preComp.resize(n, vi(m));
        tmp.resize(n, vi(m));
        prefixSum.resize(n, vl(m));

        FOR(i,0,n-1) {
            FOR(j,0,m-1) {
                preComp[i][j] = a[i][j];
                prefixSum[i][j] = a[i][j];
                if (i > 0) {
                    prefixSum[i][j] += prefixSum[i-1][j];
                }
                if (j > 0) {
                    prefixSum[i][j] += prefixSum[i][j-1];
                }
                if (i > 0 && j > 0) {
                    prefixSum[i][j] -= prefixSum[i-1][j-1];
                }
            }
        }

        FOR(k,1,kN) {
            swap(preComp, tmp);
            FOR(i,0,n-1) {
                if (i + (1<<(k-1)) >= n) break;
                FOR(j,0,m-1) {
                    preComp[i][j] = min(tmp[i][j], tmp[i + (1<<(k-1))][j]);
                }
            }
        }

        FOR(k,1,kM) {
            swap(preComp, tmp);
            FOR(i,0,n-1) {
                FOR(j,0,m-1) {
                    if (j + (1<<(k-1)) >= m) break;
                    preComp[i][j] = min(tmp[i][j], tmp[i][j + (1<<(k-1))]);
                }
            }
        }
    }

    int query(int x, int y, int u, int v) {
        return min(
            min(preComp[x][y], preComp[x][v - (1<<kM) + 1]),
            min(preComp[u - (1<<kN) + 1][y], preComp[u - (1<<kN) + 1][v - (1<<kM) + 1])
        );
    }

    ll getSum(int x, int y, int u, int v) {
        ll res = prefixSum[u][v];
        if (x > 0) {
            res -= prefixSum[x-1][v];
        }
        if (y > 0) {
            res -= prefixSum[u][y-1];
        }
        if (x > 0 && y > 0) {
            res += prefixSum[x-1][y-1];
        }
        return res;
    }
};

struct BIT2D {
    vector<vi> t;
    int n, m;

    BIT2D(int n, int m) {
        t.resize(n+1, vi(m+1));
        this->n = n;
        this->m = m;
    }

    void add(int x, int y, int gt) {
        for (int i = x; i <= n; i += (i & (-i)))
            for (int j = y; j <= m; j += (j & (-j))) t[i][j] += gt;
    }

    int get(int x, int y) {
        int res = 0;
        for (int i = x; i > 0; i -= (i & (-i)))
            for (int j = y; j > 0; j -= (j & (-j))) res += t[i][j];
        return res;
    }

    int query(int X1, int Y1, int X2, int Y2) {
        return get(X2, Y2) - get(X2, Y1-1) - get(X1-1, Y2) + get(X1-1, Y1-1);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, m, A, B;
    cin >> n >> m >> A >> B;
    vector<vi> a(n, vi(m));
    FOR(i,0,n-1) {
        FOR(j,0,m-1) {
            cin >> a[i][j];
        }
    }

    RMQ2D rmq2d(a, A, B);
    vector<Data> b;
    FOR(i,0,n-A) {
        FOR(j,0,m-B) {
            int Min = rmq2d.query(i, j, i+A-1, j+B-1);
            ll sum = rmq2d.getSum(i, j, i+A-1, j+B-1);
            ll cut = sum - (ll) Min * A * B;
            b.push_back({i+1, j+1, cut});
        }
    }
    sort(ALL(b), cmp);
    
    BIT2D bit2d(n, m);
    vi res;
    FOR(i,0,SZ(b)-1) {
        int ok = (bit2d.query(b[i].x, b[i].y, b[i].x+A-1, b[i].y+B-1) == 0);
        if (ok) {
            res.push_back(i);
            bit2d.add(b[i].x, b[i].y, 1);
            bit2d.add(b[i].x+A-1, b[i].y, 1);
            bit2d.add(b[i].x, b[i].y+B-1, 1);
            bit2d.add(b[i].x+A-1, b[i].y+B-1, 1);
        }
    }

    cout << SZ(res) << "\n";
    TRAV(x, res) {
        cout << b[x].x << ' ' << b[x].y << ' ' << b[x].diff << "\n";
    }
    return 0;
}
