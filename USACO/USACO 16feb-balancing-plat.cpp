/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Same as http://www.usaco.org/current/data/sol_balancing_platinum_feb16.html
        - But doing in the reversed order, given the position of east-west gate, figure out
        where to put the north-south gate
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

    int getAtNode(int k) {
        return t[k];
    }

    private:
    vector<int> t;

    int merge(int &a, int &b) {
        return a + b;
    }
};

int n;

bool cmp(pi a, pi b) {
    if (a.SE == b.SE) return a.FI < b.FI;
    return a.SE < b.SE;
}

int query(SegmentTree &upper, SegmentTree &lower, int k, int l, int r, int sumUpperLeft, int sumUpperRight, int sumLowerLeft, int sumLowerRight) {
    if (l == r) {
        // here we are not very sure where we should put node k into (left part or right part)
        // so we just try both ways
        int U = upper.getAtNode(k), L = lower.getAtNode(k);
        int g = max(max(sumUpperLeft + U, sumLowerLeft + L), max(sumUpperRight, sumLowerRight));
        int h = max(max(sumUpperLeft, sumLowerLeft), max(sumUpperRight + U, sumLowerRight + L));
        return min(g, h);
    }
    // k = index of node in segment tree, [l,r] is the segment that the node is managing in both segment trees
    // as we are considering the sum of the whole left part and right part, dividing by line x=m, 
    // and k is managing only segment [l, r], we need to store the left part before l, right part before
    // for both upper and lower segment trees, that's why we need sum...Left, sum...Right
    // we are going to do it O(logn) here
    int m = (l + r) >> 1;
    // l -> m, m+1 -> r
    int upperLeft = upper.getAtNode(k*2) + sumUpperLeft, upperRight = upper.getAtNode(k*2+1) + sumUpperRight;
    int lowerLeft = lower.getAtNode(k*2) + sumLowerLeft, lowerRight = lower.getAtNode(k*2+1) + sumLowerRight;
    // we go down just like in the editorial, remember to update the sums properly
    if (max(upperLeft, lowerLeft) > max(upperRight, lowerRight)) {
        return query(upper, lower, k*2, l, m, sumUpperLeft, upperRight, sumLowerLeft, lowerRight);
    } else {
        return query(upper, lower, k*2+1, m+1, r, upperLeft, sumUpperRight, lowerLeft, sumLowerRight);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("balancing.in", "r", stdin);
    freopen("balancing.out", "w", stdout);
    cin >> n;
    vpi a(n);
    FOR(i,0,n-1) cin >> a[i].FI >> a[i].SE;
    sort(ALL(a));

    // compress the x-axis
    int now = 0, x = a[0].FI;
    FOR(i,0,n-1) {
        if (a[i].FI != x) {
            x = a[i].FI;
            now++;
        }
        a[i].FI = now;
    }

    // sort by the increasing order of y-axis
    sort(ALL(a), cmp);

    // fill upper part
    SegmentTree upper(now+1), lower(now+1);
    FOR(i,0,n-1) upper.update(1,0,upper.N-1,a[i].FI,1);
    int res = n;

    FOR(i,0,n-1) {
        // for each y-axis, remove points from upper part and add to lower part
        int k = 0;
        while (i + k < n && a[i].SE == a[i+k].SE) {
            upper.update(1,0,upper.N-1,a[i+k].FI,-1);
            lower.update(1,0,lower.N-1,a[i+k].FI,1);
            k++;
        }
        // find the north-south gate
        res = min(res, query(upper, lower, 1, 0, now, 0, 0, 0, 0));
        i += k - 1;
    }

    cout << res;
    return 0;
}
