/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let dp[i] = min price to divide trees from 0 to i into different groups satisfying
        the condition in the problem.
        - dp[i] = min(dp[j] + max(h[j+1], h[j+2], ..., h[i])) for all j < i that types in the
        maximum group are different. Doing like this would take O(n^2) time.
        - We might wanna use segment tree with lazy propagation to have some states when reaching i:
            + At each seg[j] (0 <= j < i), we want to have the sum dp[j-1] + max(h[j], h[j+2], ..., h[i])
            note that dp[-1] = 0
            + We can maintain a stack to keep track of the max height of each interval, the heights
            would be in decreasing order in the stack, then we can use segment tree to add or remove
            the height of the last element in the stack.
            + With an i, we can get the furthest j with 2-pointer technique, then dp[i] = min of
            segment tree from j to i, then update segment tree from i+1 to i+1 with dp[i], matching
            with our definition
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

const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

// Example: SegmentTreeLazy<mi, op, e, Expression, mapping, composition, id> seg(a);
// Define functions like this: inline mi op(mi a, mi b) { return a + b; }
template<
    typename S, 
    S (*op)(S, S), // merge 2 segments
    S (*e)(), // initial value of a segment
    S (*invalid)(), // value for invalid queries
    typename F,
    S (*mapping)(F, S, int, int), // apply lazy value to a segment
    F (*composition)(F, F), // merge later lazy value to earlier lazy value
    F (*id)() // initial value of a lazy value
>
struct SegmentTreeLazy {
    public:
    int N;

    // 0-indexed
    SegmentTreeLazy(int n) {
        t.resize(4*n, e());
        lazy.resize(4*n, id());
        N = n;
    }

    SegmentTreeLazy(vector<S> &a) {
        t.resize(4*SZ(a));
        lazy.resize(4*SZ(a), id());
        N = SZ(a);
        build(1, 0, N-1, a);
    }

    S get(int k, int l, int r, int u, int v) {
        lazyUpdate(k, l, r);
        if (l > r || r < u || v < l) return invalid();
        if (u <= l && r <= v) return t[k];
        int m = (l + r) >> 1;
        S lef = get(k*2, l, m, u, v);
        S rig = get(k*2+1, m+1, r, u, v);
        return op(lef, rig);
    }

    void lazyUpdate(int k, int l, int r) {
        if (l > r) return;
        if (lazy[k] == id()) return;
        t[k] = mapping(lazy[k], t[k], l, r);
        if (l < r) {
            lazy[k*2] = composition(lazy[k*2], lazy[k]);
            lazy[k*2+1] = composition(lazy[k*2+1], lazy[k]);
        }
        lazy[k] = id();
    }

    void update(int k, int l, int r, int u, int v, F val) {
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
        merge(k);
    }

    void print(int k, int l, int r, int u, int v) {
        lazyUpdate(k, l, r);
        if (l > r || r < u || v < l) return;
        if (l == r) {
            cout << t[k] << ' ';
            return;
        }
        int m = (l + r) >> 1;
        print(k*2, l, m, u, v);
        print(k*2+1, m+1, r, u, v);
    }

    private:
    vector<S> t;
    vector<F> lazy;

    void build(int k, int l, int r, vector<S> &a) {
        if (l > r) return;
        if (l == r) {
            t[k] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(k*2, l, m, a);
        build(k*2+1, m+1, r, a);
        merge(k);
    }

    void merge(int k) {
        t[k] = op(t[k*2], t[k*2+1]);
    }
};

struct DpAdd {
    int l, r, val;
};

int n, ty[MAXN], h[MAXN];
int last[MAXN], pre[MAXN];

ll op(ll a, ll b) {
    return min(a, b);
}

ll e() {
    return 0;
}

ll invalid() {
    return (ll) INF * INF;
}

ll mapping(ll f, ll x, int l, int r) {
    return x + f;
}

ll composition(ll f, ll g) {
    return f + g;
}

ll id() {
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case " << o << ": ";
        cin >> n;

        FOR(i,1,200000) {
            last[i] = -1;
        }

        FOR(i,0,n-1) {
            pre[i] = -1;
        }

        FOR(i,0,n-1) {
            cin >> ty[i] >> h[i];
            pre[i] = last[ty[i]];
            last[ty[i]] = i;
        }

        vector<DpAdd> st;
        st.push_back({-1, -1, INF});
        int l = 0, r = -1;
        ll res = 0;

        SegmentTreeLazy seg = SegmentTreeLazy<ll, op, e, invalid, ll, mapping, composition, id>(n+1);

        FOR(i,0,n-1) {
            r++;
            ckmax(l, pre[i] + 1);
            while (st.back().val < h[i]) {
                DpAdd x = st.back();
                st.pop_back();
                seg.update(1, 0, n, x.l, x.r, -x.val);
            }
            st.push_back({st.back().r+1, r, h[i]});
            seg.update(1, 0, n, st.back().l, st.back().r, st.back().val);
            res = seg.get(1, 0, n, l, r);
            seg.update(1, 0, n, r+1, r+1, res);
        }

        cout << res << "\n";
    }
    return 0;
}
