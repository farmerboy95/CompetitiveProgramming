/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/97350
        - DP + Segment tree
        - Let's maintain the following informaton for each segment: dp[node][mask] stores 
        the minimal number of characters that have to be replaced to make the string only 
        contain subsequences equal to mask.
        - Next let's define what mask is. Let the first bit of the mask correspond to 
        subsequence a, the second bit correspond to subsequence b, the third bit correspond 
        to subsequence c, the fourth bit correspond to subsequence ab, the fifth bit correspond 
        to subsequence bc. Then mask contains those subsequences, which have a number 
        corresponding to the number of 1 bits in them.
        - Let's define the value merge(leftMask, rightMask) as a resulting mask which contains 
        the subsequences from both masks and the subsequences that are created as a result of 
        their merge.
        - Now we have the sufficient function for our segment tree.
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

const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, q;
string s;
int m[32][32];
vpi v;

struct Data {
    int cost[32]; // a, b, c, ab, bc
    Data() {
        MS(cost, 63);
    }
};

struct SegmentTree {
    public:
    int N;

    // 0-indexed
    SegmentTree(int n) {
        t.resize(4*n);
        N = n;
        FOR(i,0,SZ(t)-1) t[i] = Data();
    }

    SegmentTree(string &s) {
        t.resize(4*SZ(s));
        N = SZ(s);
        build(1, 0, N-1, s);
    }

    Data get(int k, int l, int r, int u, int v) {
        if (l > r || r < u || v < l) return Data();
        if (u <= l && r <= v) return t[k];
        int m = (l + r) >> 1;
        Data lef = get(k*2, l, m, u, v);
        Data rig = get(k*2+1, m+1, r, u, v);
        return merge(lef, rig);
    }

    void update(int k, int l, int r, int u, char val) {
        if (l > r || r < u || u < l) return;
        if (l == r) {
            t[k].cost[1] = t[k].cost[2] = t[k].cost[4] = 1;
            if (val == 'a') {
                t[k].cost[1] = 0;
            } else if (val == 'b') {
                t[k].cost[2] = 0;
            } else {
                t[k].cost[4] = 0;
            }
            return;
        }
        int m = (l + r) >> 1;
        update(k*2, l, m, u, val);
        update(k*2+1, m+1, r, u, val);
        t[k] = merge(t[k*2], t[k*2+1]);
    }

    private:
    vector<Data> t;

    void build(int k, int l, int r, string &s) {
        if (l > r) return;
        if (l == r) {
            t[k].cost[1] = t[k].cost[2] = t[k].cost[4] = 1;
            if (s[l] == 'a') {
                t[k].cost[1] = 0;
            } else if (s[l] == 'b') {
                t[k].cost[2] = 0;
            } else {
                t[k].cost[4] = 0;
            }
            return;
        }
        int m = (l + r) >> 1;
        build(k*2, l, m, s);
        build(k*2+1, m+1, r, s);
        t[k] = merge(t[k*2], t[k*2+1]);
    }

    Data merge(Data &a, Data &b) {
        Data res;
        TRAV(x, v) {
            ckmin(res.cost[m[x.FI][x.SE]], a.cost[x.FI] + b.cost[x.SE]);
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> q >> s;
    FOR(i,0,31) {
        FOR(j,0,31) {
            // has ab but no a or b
            if ((i & 8) && (i & 3) != 3) continue;
            if ((j & 8) && (j & 3) != 3) continue;
            // has bc but no b or c
            if ((i & 16) && (i & 6) != 6) continue;
            if ((j & 16) && (j & 6) != 6) continue;

            m[i][j] = i | j;
            // left has a and right has b => include ab
            if ((i & 1) && (j & 2)) m[i][j] |= (1<<3);
            // left has b and right has c => include bc
            if ((i & 2) && (j & 4)) m[i][j] |= (1<<4);

            // left has ab and right has c => no
            if ((i & 8) && (j & 4)) m[i][j] = -1;
            // left has a and right has bc => no
            if ((i & 1) && (j & 16)) m[i][j] = -1;

            if (m[i][j] != -1) v.push_back({i, j});
        }
    }
    SegmentTree seg(s);

    while (q--) {
        int u;
        char ch;
        cin >> u >> ch;
        seg.update(1,0,seg.N-1,u-1,ch);
        Data x = seg.get(1,0,seg.N-1,0,seg.N-1);
        int res = INF;
        FOR(i,0,31) ckmin(res, x.cost[i]);
        cout << res << "\n";
    }
    return 0;
}
