/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let dp[i][j] = The minimum result we got when considering the first j numbers and
        divide them into i parts
        - Then we can easily get the result when i = 1
        - From 2 to k, dp[i][j] = min(dp[i-1][x] + result of the part (x+1 ... j)) (x = 0 -> j-1)
        - So it seems that the result of current i completely depends on i-1
        - This would be O(n^2) in short, but not enough for our problem.
        - So let's notice that in the new i, when we consider a specific j, we can try to
        add (x+1 ... j) to dp[i-1][x]. 
        - Let val[x] = dp[i-1][x] + result of the part (x+1 ... j), so we can simply add a[j] 
        into a list of previous val[x] (x < j) to update them. And when we add a[j], we actually
        just add a number into it, so we can consider the previous appearances of a[j] to calculate.
        - Finally get min(0 ... j-1) of val to get the result of dp[i][j]. We can use segment tree
        to solve
        - But how to add a[j] into a list of previous val[x] (x < j)?
        - Consider this example: 
            + Let b1 b2 b3 b4 b5 is the positions of a number p in the list, we currently need 
            to add b3.
            + Add -p to [b2 ... b3-1] as in these position, there was no p. (Why not b2+1, because
            we are considering the result of the part x+1...j)
            + Add p to [0 ... b3-1], of course
            + Add -p to [0 ... b2-1] to remove the added part when we add b2
        - After having dp[i][0 ... n], create a new segment tree based on that dp[i] and continue
        with new i.
        - Complexity O(nklogn)
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

const int MAXN = 40000;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;


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

    SegmentTreeLazy(vector<int> &a) {
        t.resize(4*SZ(a));
        lazy.resize(4*SZ(a));
        N = SZ(a);
        build(1, 0, N-1, a);
        FOR(i,0,SZ(t)-1) lazy[i] = 0;
    }

    int get(int k, int l, int r, int u, int v) {
        lazyUpdate(k, l, r);
        if (l > r || r < u || v < l) return 1e7;
        if (u <= l && r <= v) return t[k];
        int m = (l + r) >> 1;
        int lef = get(k*2, l, m, u, v);
        int rig = get(k*2+1, m+1, r, u, v);
        return min(lef, rig);
    }

    void lazyUpdate(int k, int l, int r) {
        if (l > r) return;
        if (lazy[k] == 0) return;
        t[k] += lazy[k];
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
        t[k] = min(t[k*2], t[k*2+1]);
    }

    void build(int k, int l, int r, vector<int> &a) {
        if (l > r) return;
        if (l == r) {
            t[k] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(k*2, l, m, a);
        build(k*2+1, m+1, r, a);
        t[k] = min(t[k*2], t[k*2+1]);
    }

    private:
    vector<int> t, lazy;
};


int n, k, a[MAXN], ptr[MAXN];
vector<int> dp;
vector<int> occ[MAXN];

void calc1() {
    dp = vector<int> (n+1, 0); 
    dp[0] = 0;
    FOR(i,1,n) {
        dp[i] = dp[i-1];
        if (SZ(occ[a[i]])) dp[i] -= occ[a[i]].back() - occ[a[i]][0];
        occ[a[i]].push_back(i);
        dp[i] += occ[a[i]].back() - occ[a[i]][0];
    }
    dp[0] = 1e7;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,n) cin >> a[i];

    calc1();
    SegmentTreeLazy seg(dp);

    FOR(j,2,k) {
        FOR(i,1,n) ptr[i] = -1;
        dp[0] = 1e7;
        FOR(i,1,n) {
            int num = a[i];
            ptr[num]++;

            int l = ptr[num]-1;
            if (l < 0) l = 0;
            else l = occ[num][ptr[num]-1];
            int r = i;

            seg.update(1,0,seg.N-1,l,r-1,-occ[num][ptr[num]]);

            if (l > 0) {
                seg.update(1,0,seg.N-1,0,l-1,-occ[num][ptr[num]-1]);
            }
            seg.update(1,0,seg.N-1,0,r-1,occ[num][ptr[num]]);
            if (j > i) dp[i] = 1e9;
            else dp[i] = seg.get(1,0,seg.N-1,0,r-1);
        }

        SegmentTreeLazy seg2(dp);
        seg = seg2;
    }
    cout << dp[n];
    return 0;
}
