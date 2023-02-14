/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use sqrt tree: https://cp-algorithms.com/data_structures/sqrt-tree.html
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

inline int log2Up(int n) {
    int res = 0;
    while ((1 << res) < n) {
        res++;
    }
    return res;
}

struct SqrtTree {
    int n, lg, indexSz;
    vi v;
    vi clz, layers, onLayer;
    vector<vi> pref, suf, between;
    int p;

    int op(const int &a, const int &b) {
        return (ll) a * b % p;
    }

    inline void buildBlock(int layer, int l, int r) {
        // block [l, r)
        // calculate prefix and suffix arrays
        pref[layer][l] = v[l];
        FOR(i,l+1,r-1) {
            pref[layer][i] = op(pref[layer][i-1], v[i]);
        }
        suf[layer][r-1] = v[r-1];
        FORE(i,r-2,l) {
            suf[layer][i] = op(v[i], suf[layer][i+1]);
        }
    }

    inline void buildBetween(int layer, int lBound, int rBound, int betweenOffs) {
        // log of block size
        int bSzLog = (layers[layer]+1) >> 1;
        // log of number of blocks
        int bCntLog = layers[layer] >> 1;
        // block size
        int bSz = 1 << bSzLog;
        // number of blocks, it's basically ceilDiv(r - l, bSz)
        int bCnt = (rBound - lBound + bSz - 1) >> bSzLog;

        // fill in "between"
        for (int i = 0; i < bCnt; i++) {
            int ans = 1;
            for (int j = i; j < bCnt; j++) {
                int add = suf[layer][lBound + (j << bSzLog)];
                ans = (i == j) ? add : op(ans, add);
                // between[i][j]
                between[layer-1][betweenOffs + lBound + (i << bCntLog) + j] = ans;
            }
        }
    }

    inline void buildBetweenZero() {
        int bSzLog = (lg+1) >> 1;
        // put values of blocks to the "index" sqrt tree and build it
        for (int i = 0; i < indexSz; i++) {
            v[n+i] = suf[0][i << bSzLog];
        }
        build(1, n, n + indexSz, (1 << lg) - n);
    }

    inline void updateBetweenZero(int bid) {
        int bSzLog = (lg+1) >> 1;
        // update block value of "index" sqrt tree
        v[n+bid] = suf[0][bid << bSzLog];
        // update the "index" sqrt tree
        update(1, n, n + indexSz, (1 << lg) - n, n+bid);
    }

    void build(int layer, int lBound, int rBound, int betweenOffset) {
        if (layer >= SZ(layers)) {
            // return if layer index is larger than the number of layers
            return;
        }

        // block size
        int bSz = 1 << ((layers[layer]+1) >> 1);
        for (int l = lBound; l < rBound; l += bSz) {
            int r = min(l + bSz, rBound);
            buildBlock(layer, l, r);
            build(layer+1, l, r, betweenOffset);
        }

        // build "index" sqrt tree on layer 0, otherwise build "between"
        if (layer == 0) {
            buildBetweenZero();
        } else {
            buildBetween(layer, lBound, rBound, betweenOffset);
        }
    }

    void update(int layer, int lBound, int rBound, int betweenOffset, int x) {
        if (layer >= (int)layers.size()) {
            // return if layer index is larger than the number of layers
            return;
        }

        // log of block size
        int bSzLog = (layers[layer]+1) >> 1;
        // block size
        int bSz = 1 << bSzLog;
        // block index containing x
        int blockIdx = (x - lBound) >> bSzLog;
        // [l, r) of the block containing x
        int l = lBound + (blockIdx << bSzLog);
        int r = min(l + bSz, rBound);
        // update the pref and suf
        buildBlock(layer, l, r);

        // update "index" sqrt tree on layer 0, otherwise update "between"
        if (layer == 0) {
            updateBetweenZero(blockIdx);
        } else {
            buildBetween(layer, lBound, rBound, betweenOffset);
        }
        // update till the leaf
        update(layer+1, l, r, betweenOffset, x);
    }

    inline int query(int l, int r, int betweenOffset, int base) {
        // segment [l, r]
        // length 1
        if (l == r) {
            return v[l];
        }
        // length 2
        if (l + 1 == r) {
            return op(v[l], v[r]);
        }

        // find the layer number which covers [l, r]
        int layer = onLayer[clz[(l - base) ^ (r - base)]];
        // block size of blocks on this layer
        int bSzLog = (layers[layer]+1) >> 1;
        // number of blocks on this layer
        int bCntLog = layers[layer] >> 1;
        // lBound = number of elements in the blocks before block containing l
        int lBound = (((l - base) >> layers[layer]) << layers[layer]) + base;
        // lBlock and rBlock are the most left and right blocks that are lying inside the query
        // not counting the left most or right most in the case they satisfy the above condition
        int lBlock = ((l - lBound) >> bSzLog) + 1;
        int rBlock = ((r - lBound) >> bSzLog) - 1;

        // get answer of the left most block
        int ans = suf[layer][l];
        if (lBlock <= rBlock) {
            int add = (layer == 0) ? (
                // if it's on the root of the tree, we query using "index", which stored
                // all blocks of the first layer already
                query(n + lBlock, n + rBlock, (1 << lg) - n, n)
            ) : (
                // if layer is not on the root of the tree, we easily use "between" to get the result
                between[layer-1][betweenOffset + lBound + (lBlock << bCntLog) + rBlock]
            );
            // add the block to the answer
            ans = op(ans, add);
        }
        // get answer of the right most block
        ans = op(ans, pref[layer][r]);
        return ans;
    }

    inline int query(int l, int r) {
        return query(l, r, 0, 0);
    }

    inline void update(int x, const int &item) {
        v[x] = item;
        update(0, 0, n, 0, x);
    }

    SqrtTree(const vi &a, int p) : n(SZ(a)), lg(log2Up(n)), v(a), clz(1 << lg), onLayer(lg+1) {
        // n = size of the initial array
        // lg = ceil(log2(n))
        this->p = p;

        // clz[i] = lowest set bit
        clz[0] = 0;
        FOR(i,1,SZ(clz)-1) clz[i] = clz[i >> 1] + 1;

        // layers[i] is the block length on layer i
        // onLayer[i] = x means that if the block length is 2^i, it should be on layer x
        int tlg = lg;
        while (tlg > 1) {
            onLayer[tlg] = SZ(layers);
            layers.push_back(tlg);
            // sqrt(2^x) = 2^(x / 2)
            tlg = (tlg + 1) >> 1;
        }
        FORE(i,lg-1,0) ckmax(onLayer[i], onLayer[i+1]);

        int betweenLayers = max(0, SZ(layers) - 1);
        int bSzLog = (lg + 1) >> 1;
        int bSz = (1 << bSzLog);
        // indexSz is number of bSz-length blocks separating n
        // it's basically ceilDiv(n, bSz)
        indexSz = (n + bSz - 1) >> bSzLog;

        v.resize(n + indexSz);
        pref.assign(layers.size(), vi(n + indexSz));
        suf.assign(layers.size(), vi(n + indexSz));
        between.assign(betweenLayers, vi((1 << lg) + bSz));

        build(0, 0, n, 0);
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

        SqrtTree sq = SqrtTree(a, p);

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

            res = sq.query(l[i], r[i]);
            res = (res + 1) % p;
        }
        cout << res << "\n";
    }
    return 0;
}
