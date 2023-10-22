/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - For a specific topic, we know that the paths are all starting from the leaves,
        going towards the root. If 2 paths intersect, only one of them can move forward,
        the other one has to stop.
        - The topic now should be able to cover all the paths, so the number of nodes containing
        the topic should be equal or more to the number of leaves in the tree, or you
        can say, subtree. But it's not enough, we have to find if one leaf node can be
        covered by one node that contains the topic.
        - We iterate through nodes from the deepest ones to the root, count the number of
        unpaired leaves in the subtree of the node. If such number is more than 1, we
        can't cover the subtree. Otherwise, we can cover the subtree. We can use segment
        tree to do this, with the help of tree flattening. When we need to pair, just add
        -1 to the node. If the number of unpaired leaves is 0, we don't need to pair.
        - Remember to check the root node even when it does not contain the topic.
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

const int MAXN = 1000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, N, st[MAXN], en[MAXN], leaves[MAXN], depth[MAXN];
vi a[MAXN];
map<string, vi> ma;

struct SegmentTree {
    public:
    int N;

    // 0-indexed
    SegmentTree(int n) {
        t.resize(4*n);
        N = n;
        FOR(i,0,SZ(t)-1) t[i] = 0;
    }

    int get(int k, int l, int r, int u, int v) {
        if (l > r || r < u || v < l) return 0;
        if (u <= l && r <= v) return t[k];
        int m = (l + r) >> 1;
        int lef = get(k*2, l, m, u, v);
        int rig = get(k*2+1, m+1, r, u, v);
        return merge(lef, rig);
    }

    void update(int k, int l, int r, int u, int val) {
        if (l > r || r < u || u < l) return;
        if (l == r) {
            t[k] += val;
            return;
        }
        int m = (l + r) >> 1;
        update(k*2, l, m, u, val);
        update(k*2+1, m+1, r, u, val);
        t[k] = merge(t[k*2], t[k*2+1]);
    }

    private:
    vector<int> t;

    int merge(int &a, int &b) {
        return a + b;
    }
};

void dfs(int u) {
    N++;
    st[u] = N;
    leaves[u] = 0;
    TRAV(v, a[u]) {
        depth[v] = depth[u] + 1;
        dfs(v);
        leaves[u] += leaves[v];
    }
    if (SZ(a[u]) == 0) leaves[u] = 1;
    en[u] = N;
}

bool isOK(SegmentTree &seg, vi &v, vi &updated) {
    int has1 = 0;
    TRAV(x, v) {
        if (x == 1) has1 = 1;
        int numUnpair = seg.get(1, 0, seg.N-1, st[x], en[x]);
        if (numUnpair > 1) return false;
        if (numUnpair == 0) continue;
        updated.push_back(x);
        seg.update(1, 0, seg.N-1, st[x], -1);
    }

    if (has1) {
        return true;
    }

    int num = seg.get(1, 0, seg.N-1, st[1], en[1]);
    return num == 0;
}

int solve() {
    N = 0;
    dfs(1);
    SegmentTree seg(n+1);
    FOR(i,1,n)
        if (SZ(a[i]) == 0) seg.update(1, 0, seg.N-1, st[i], 1);
    int res = 0;
    for (auto it = ma.begin(); it != ma.end(); it++) {
        vi &v = it->SE;
        sort(ALL(v), [&](int x, int y) {
            return depth[x] > depth[y];
        });

        vi updated;
        if (isOK(seg, v, updated)) {
            res++;
        }

        TRAV(x, updated) seg.update(1, 0, seg.N-1, st[x], 1);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case #" << o << ": ";
        cin >> n;
        FOR(i,1,n) a[i].clear();
        FOR(i,2,n) {
            int p;
            cin >> p;
            a[p].push_back(i);
        }

        ma.clear();
        FOR(i,1,n) {
            int k;
            cin >> k;
            FOR(j,1,k) {
                string x;
                cin >> x;
                ma[x].push_back(i);
            }
        }

        cout << solve() << "\n";
    }
    return 0;
}
