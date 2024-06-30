/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - As described in the code
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

struct Event {
    int y, l, r, type;

    Event(int y = 0, int l = 0, int r = 0, int type = 0) : y(y), l(l), r(r), type(type) {}
};

struct SegmentTreeLazy {
    public:
    int N;

    // 0-indexed
    SegmentTreeLazy(int n) {
        t.resize(4*n);
        lazy.resize(4*n);
        N = n;
        build(1, 0, N-1);
    }

    pi get(int k, int l, int r, int u, int v) {
        lazyUpdate(k, l, r);
        if (l > r || r < u || v < l) return {-1, 1000000001};
        if (u <= l && r <= v) return t[k];
        int m = (l + r) >> 1;
        pi lef = get(k*2, l, m, u, v);
        pi rig = get(k*2+1, m+1, r, u, v);
        return merge(lef, rig);
    }

    void lazyUpdate(int k, int l, int r) {
        if (l > r) return;
        if (lazy[k] == 0) return;
        t[k].FI += lazy[k];
        if (l < r) {
            lazy[k*2] += lazy[k];
            lazy[k*2+1] += lazy[k];
        }
        lazy[k] = 0;
    }

    void update(int k, int l, int r, int u, int v, int val) {
        lazyUpdate(k, l, r);
        if (l > r || r < u || v < l) return;
        if (u <= l && r <= v) {
            lazy[k] = val;
            lazyUpdate(k, l, r);
            return;
        }
        int m = (l + r) >> 1;
        update(k*2, l, m, u, v, val);
        update(k*2+1, m+1, r, u, v, val);
        t[k] = merge(t[k*2], t[k*2+1]);
    }

    private:
    vpi t; // value, position
    vi lazy;

    pi merge(pi &a, pi &b) {
        if (a.FI != b.FI) return max(a, b);
        return a;
    }

    void build(int k, int l, int r) {
        if (l > r) return;
        if (l == r) {
            t[k] = {0, l};
            return;
        }
        int m = (l + r) >> 1;
        build(k*2, l, m);
        build(k*2+1, m+1, r);
        t[k] = merge(t[k*2], t[k*2+1]);
    }
};

int n, l[MAXN], r[MAXN];

int getPos(int x, vi &c) {
    return lower_bound(ALL(c), x) - c.begin();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> l[i] >> r[i];

    // the set of answers of each segment falls into 2 separate rectangles on the plane
    // 1. x < l[i] < y < r[i]: rectangle with x from 0 to l[i], y from l[i] to r[i]
    // 2. l[i] < x < r[i] < y: rectangle with x from l[i] to r[i], y r[i] to 1000000000

    vi c;
    c.push_back(0);
    c.push_back(1000000000);
    FOR(i,1,n) {
        if (l[i] - 1 >= 0) {
            c.push_back(l[i] - 1);
        }
        c.push_back(l[i] + 1);
        c.push_back(r[i] - 1);
    }
    remDup(c);

    // x: 0 -> l[i] - 1, y: l[i] + 1 -> r[i] - 1
    // x: l[i] + 1 -> r[i] - 1, y: r[i] + 1 -> 1000000000

    // Enums:
    // 0: ADD
    // 1: REMOVE

    vector<Event> events;
    FOR(i,1,n) {
        // check conditions carefully here
        if (l[i] - 1 >= 0) {
            events.push_back(Event(
                l[i] + 1, getPos(0, c), getPos(l[i] - 1, c), 0
            ));
            events.push_back(Event(
                r[i] - 1, getPos(0, c), getPos(l[i] - 1, c), 1
            ));
        }

        // especially this one
        if (l[i] + 1 <= r[i] - 1) {
            events.push_back(Event(
                r[i] + 1, getPos(l[i] + 1, c), getPos(r[i] - 1, c), 0
            ));
            events.push_back(Event(
                1000000000, getPos(l[i] + 1, c), getPos(r[i] - 1, c), 1
            ));
        }
    }

    sort(ALL(events), [&](const Event &A, const Event &B) {
        if (A.y == B.y) return A.type < B.type;
        return A.y < B.y;
    });

    // do classical sweep line

    pi res = {0, 1};
    int kq = 0;
    SegmentTreeLazy seg(SZ(c));
    TRAV(x, events) {
        if (x.type == 0) {
            seg.update(1, 0, SZ(c) - 1, x.l, x.r, 1);
        } else {
            seg.update(1, 0, SZ(c) - 1, x.l, x.r, -1);
        }

        pi val = seg.get(1, 0, SZ(c) - 1, 0, SZ(c) - 1);
        if (val.FI > kq) {
            kq = val.FI;
            res = {c[val.SE], x.y};
        }
    }

    cout << res.FI << " " << res.SE;
    return 0;
}
