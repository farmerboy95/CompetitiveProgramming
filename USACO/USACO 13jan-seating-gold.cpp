/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Maintain the best empty segment length, the best left segment length and right segment
        length. 
        - Use segment tree with lazy propagation.
        - Finally, please make sure that one update the child node with lazy value before accessing
        the node values.
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
template<class T, class U> string ts(pair<T,U> p) { return "("+ts(p.f)+", "+ts(p.s)+")"; }

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
const ll MODBASE = 1000000007LL;
const int INF = 0x3f3f3f3f;

const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct Node {
    int best, lef, rig, range;
    Node(int _best = 0, int _lef = 0, int _rig = 0, int _range = 0) 
        : best(_best), lef(_lef), rig(_rig), range(_range) {}
};

struct SegmentTreeLazy {
    public:
    int N;

    // 0-indexed
    SegmentTreeLazy(int n) {
        t.resize(4*n);
        lazy.resize(4*n);
        N = n;
        FOR(i,0,SZ(t)-1) {
            t[i] = Node();
            lazy[i] = 0;
        }
    }

    int get(int k, int l, int r, int need) {
        lazyUpdate(k, l, r);
        if (l == r) {
            if (t[k].best >= need) return l;
            return -1;
        }
        int m = (l + r) >> 1;
        if (t[k].best < need) return -1;
        // lazy update the child nodes before accessing its values
        lazyUpdate(k*2, l, m);
        if (t[k*2].best >= need) return get(k*2, l, m, need);
        lazyUpdate(k*2+1, m+1, r);
        if (t[k*2].rig + t[k*2+1].lef >= need) return m - t[k*2].rig + 1;
        if (t[k*2+1].best >= need) return get(k*2+1, m+1, r, need);
        return -1;
    }

    void lazyUpdate(int k, int l, int r) {
        if (l > r) return;
        if (lazy[k] == 0) return;
        if (lazy[k] > 0) add(t[k]);
        else remove(t[k]);
        if (l < r) {
            lazy[k*2] = lazy[k];
            lazy[k*2+1] = lazy[k];
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

    void build(int k, int l, int r) {
        if (l > r) return;
        if (l == r) {
            t[k] = Node(1,1,1,1);
            return;
        }
        int m = (l + r) >> 1;
        build(k*2, l, m);
        build(k*2+1, m+1, r);
        t[k] = merge(t[k*2], t[k*2+1]);
    }

    vector<Node> t;
    vector<int> lazy;

    Node merge(Node &a, Node &b) {
        Node res;
        res.range = a.range + b.range;
        res.best = max(a.best, b.best);
        res.best = max(res.best, a.rig + b.lef);
        res.lef = a.lef;
        res.rig = b.rig;
        if (a.lef == a.range) res.lef = max(res.lef, a.lef + b.lef);
        if (b.rig == b.range) res.rig = max(res.rig, b.rig + a.rig);
        return res;
    }

    void remove(Node &node) {
        node.best = node.lef = node.rig = node.range;
    }

    void add(Node &node) {
        node.best = node.lef = node.rig = 0;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("seating.in", "r", stdin);
    freopen("seating.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    SegmentTreeLazy st(n);
    st.build(1,0,st.N-1);
    int res = 0;
    FOR(que,1,m) {
        char ch; int u, v;
        cin >> ch >> u;
        if (ch == 'A') {
            int x = st.get(1,0,st.N-1,u);
            if (x == -1) res++;
            else st.update(1,0,st.N-1,x,x+u-1,1);
        } else {
            cin >> v;
            u--; v--;
            st.update(1,0,st.N-1,u,v,-1);
        }
    }
    cout << res;
    return 0;
}
// 0 1 2 3 4 5 6 7 8 9
// 1 1 1 1 1 1 0 0 0 0
// 1 0 0 0 1 1 0 0 0 0
// 1 1 1 0 1 1 0 0 0 0
// 1 1 1 0 1 1 1 1 1 0
