/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Firstly, let's consider 2 nodes u, v that val[u] = val[v]. Consider a path from u
        to v that reach u and v only once. All nodes lying on that path would possibly be the
        distinctive roots (we can call those nodes lying between u and v).
        - So we can have some corner cases:
            + If there is an edge (u, v) that val[u] = val[v], there would be no solution. Indeed,
            there is no node lying between u and v.
            + If the path from u to v above exists a node k that val[k] = val[u] = val[v]. There
            would be no solution. There is no node both lying between u - k and k - v.
        - That's it. Otherwise, we need to count the number of distinctive roots.
        - The first corner case can be easily solved but the second one requires a bit more effort.
        - We don't need to care about values that have less than 2 nodes. For the other values,
        we flatten the tree using DFS and maintain a segment tree on it. We add 1 to each node with
        that same value. For each of these nodes, we need to check if it's "between" any pair of
        nodes with the same value (to match with corner case 2). So we get the sum of each child node
        (it's easy to calculate the parent node as well), if we have more than one sum > 0, we return
        0 immediately.
        - For child nodes that have sum == 0, the subtree of child nodes has all ineligible nodes.
        So we try to remove them from the result (by maintaining another segment tree, add 1 to nodes
        that we need to remove from the result). Don't forget to remove the current node itself. It's
        not eligible by the way.
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

const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, val[MAXN], N=-1, st[MAXN], en[MAXN], par[MAXN];
vector<int> a[MAXN], nodes[MAXN];

void dfs(int u, int p) {
    N++;
    st[u] = N;
    TRAV(v, a[u]) {
        if (v == p) continue;
        par[v] = u;
        dfs(v, u);
    }
    en[u] = N;
}

struct SegmentTreeLazy {
    public:
    int N;

    // 0-indexed
    SegmentTreeLazy(int n) {
        t.resize(4*n);
        lazy.resize(4*n);
        N = n;
        FOR(i,0,SZ(t)-1) {
            t[i] = 0;
            lazy[i] = 0;
        }
    }

    ll get(int k, int l, int r, int u, int v) {
        lazyUpdate(k, l, r);
        if (l > r || r < u || v < l) return 0;
        if (u <= l && r <= v) return t[k];
        int m = (l + r) >> 1;
        ll lef = get(k*2, l, m, u, v);
        ll rig = get(k*2+1, m+1, r, u, v);
        return merge(lef, rig);
    }

    void lazyUpdate(int k, int l, int r) {
        if (l > r) return;
        if (lazy[k] == 0) return;
        t[k] += (r - l + 1) * lazy[k];
        if (l < r) {
            mergeLazy(lazy[k*2], lazy[k]);
            mergeLazy(lazy[k*2+1], lazy[k]);
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
    vector<ll> t;
    vector<ll> lazy;

    ll merge(ll &a, ll &b) {
        return a+b;
    }

    void mergeLazy(ll &ol, ll &ne) {
        ol += ne;
    }
};

void output(int x) {
    cout << x;
    exit(0);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> val[i];
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        if (val[u] == val[v]) output(0);
        a[u].push_back(v);
        a[v].push_back(u);
    }
    dfs(1, 0);
    vector<int> z;

    // compress
    FOR(i,1,n) z.push_back(val[i]);
    remDup(z);
    FOR(i,1,n) val[i] = lower_bound(ALL(z), val[i]) - z.begin();

    FOR(i,1,n) nodes[val[i]].push_back(i);

    SegmentTreeLazy tree(n), tree2(n);

    FOR(i,0,SZ(z)-1) {
        if (SZ(nodes[i]) < 2) continue;

        TRAV(u, nodes[i]) {
            tree.update(1,0,tree.N-1,st[u],st[u],1);
            tree2.update(1,0,tree2.N-1,st[u],st[u],1);
        }

        TRAV(u, nodes[i]) {
            int cnt = 0;
            TRAV(v, a[u]) {
                if (v == par[u]) {
                    int x = SZ(nodes[i]) - tree.get(1,0,tree.N-1,st[u],en[u]);
                    if (x > 0) cnt++;
                    else {
                        tree2.update(1,0,tree2.N-1,st[1],en[1],1);
                        tree2.update(1,0,tree2.N-1,st[u],en[u],-1);
                    }
                } else {
                    int x = tree.get(1,0,tree.N-1,st[v],en[v]);
                    if (x > 0) cnt++;
                    else {
                        tree2.update(1,0,tree2.N-1,st[v],en[v],1);
                    }
                }
                if (cnt > 1) output(0);
            }
        }

        TRAV(u, nodes[i]) {
            tree.update(1,0,tree.N-1,st[u],st[u],-1);
        }
    }

    int res = 0;
    FOR(i,1,n) {
        int x = tree2.get(1,0,tree2.N-1,i-1,i-1);
        res += (x == 0);
    }
    cout << res;
    return 0;
}
