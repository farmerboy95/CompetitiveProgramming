/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/87598?#comment-758870
        - Let dp[i][x] = largest number of groups that can be achieved after coloring a[1] .. a[i]
        such that 2 elements at the end of the subsequences are a[i] and x.
        - There are 2 cases:
            + Put a[i] to the sequence with x: dp[i][a[i-1]] = dp[i-1][x] + (a[i] != x)
            + Put a[i] to the sequence with a[i-1]: dp[i][x] = dp[i-1][x] + (a[i] != a[i-1]) (with x != a[i])
        - Easily see that this dp is calculated in O(n^2), which is TLE, but we can maintain the last
        row of this dp in a segment tree with lazy propagation.
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
template<class T, class U> string ts(pair<T,U> p) { return "("+ts(p.FI)+", "+ts(p.SE)+")"; }

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

const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN];

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

    SegmentTreeLazy(vi &a) {
        t.resize(4*SZ(a));
        lazy.resize(4*SZ(a));
        N = SZ(a);
        build(1, 0, N-1, a);
        FOR(i,0,SZ(t)-1) lazy[i] = 0;
    }

    int get(int k, int l, int r, int u, int v) {
        lazyUpdate(k, l, r);
        if (l > r || r < u || v < l) return -INF;
        if (u <= l && r <= v) return t[k];
        int m = (l + r) >> 1;
        ll lef = get(k*2, l, m, u, v);
        ll rig = get(k*2+1, m+1, r, u, v);
        return max(lef, rig);
    }

    void lazyUpdate(int k, int l, int r) {
        if (l > r) return;
        if (lazy[k] == 0) return;
        if (t[k] + lazy[k] >= -INF) t[k] += lazy[k];
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
        t[k] = max(t[k*2], t[k*2+1]);
    }

    private:
    vi t, lazy;

    void build(int k, int l, int r, vi &a) {
        if (l > r) return;
        if (l == r) {
            t[k] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(k*2, l, m, a);
        build(k*2+1, m+1, r, a);
        t[k] = max(t[k*2], t[k*2+1]);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];

    vi b(100001);
    b[0] = 1;
    FOR(i,1,100000) b[i] = -INF;
    SegmentTreeLazy st(b);

    FOR(i,2,n) {
        int pre = a[i-1], now = a[i];

        // x == a[i]
        int w = st.get(1,0,st.N-1,now,now);
        // x != a[i]
        int rem = max(st.get(1,0,st.N-1,0,now-1), st.get(1,0,st.N-1,now+1,st.N-1)) + 1;

        // update dp[i][a[i]-1]
        int g = st.get(1,0,st.N-1,pre,pre);
        st.update(1,0,st.N-1,pre,pre,max(w, rem) - g);

        // update dp[i][x]
        int add = (now != pre);
        if (add) {
            st.update(1,0,st.N-1,0,pre-1,add);
            st.update(1,0,st.N-1,pre+1,st.N-1,add);
        }
    }
    cout << st.get(1,0,st.N-1,0,st.N-1);
    return 0;
}
