/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/87356
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

const int MAXN = 300010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, p[MAXN], dp[MAXN], par[MAXN], lef[MAXN], rig[MAXN];

struct SegmentTree {
    public:
    int N, mx;

    // 0-indexed
    SegmentTree(int n, int mx) {
        this->mx = mx;
        t.resize(4*n);
        N = n;
        FOR(i,0,SZ(t)-1) t[i] = mx ? -INF : INF;
    }

    int get(int k, int l, int r, int u, int v) {
        if (l > r || r < u || v < l) return mx ? -INF : INF;
        if (u <= l && r <= v) return t[k];
        int m = (l + r) >> 1;
        int lef = get(k*2, l, m, u, v);
        int rig = get(k*2+1, m+1, r, u, v);
        return merge(lef, rig);
    }

    void update(int k, int l, int r, int u, int val) {
        if (l > r || r < u || u < l) return;
        if (l == r) {
            t[k] = mx ? max(t[k], val) : min(t[k], val);
            return;
        }
        int m = (l + r) >> 1;
        update(k*2, l, m, u, val);
        update(k*2+1, m+1, r, u, val);
        t[k] = merge(t[k*2], t[k*2+1]);
    }

    private:
    vi t;

    int merge(int &a, int &b) {
        return mx ? max(a, b) : min(a, b);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    while (te--) {
        cin >> n;
        FOR(i,1,n) cin >> p[i];

        // dp[i] = the maximum prefix we can fully cover with first i lanterns
        dp[0] = 0;
        // par[i] = -1 if lantern i turns right
        // par[i] >= 0 if lantern i turns left
        // par[i] = minimum j that dp[j] >= i - p[i] - 1
        par[0] = -1;

        // lef[i] = the left endpoint of lantern i if it turns left
        // rig[i] = the right endpoint of lantern i if it turns right
        FOR(i,1,n) {
            lef[i] = max(1, i - p[i]);
            rig[i] = min(n, i + p[i]);
        }

        // maintain 2 segment tree
        // Min = store value i at position dp[i]
        // Max = store value of array rig
        SegmentTree Min(n+1, 0), Max(n+1, 1);

        // dp[0] = 0, add it to Min segment tree
        Min.update(1,0,n,0,0);

        // add array rig to Max
        FOR(i,1,n) Max.update(1,0,n,i,rig[i]);

        FOR(i,1,n) {
            dp[i] = -INF;
            par[i] = -2;
            // we need to find the minimum j that dp[j] >= "connect"
            // so just query the range [connect, n] in the Min tree to find such j
            int connect = lef[i] - 1;
            int minJ = Min.get(1,0,n,connect,n);

            if (minJ != INF) {
                // since i turns left, we turn all the lanterns from minJ + 1 to i-1 to right
                // get max with i-1 (because i turn left)
                int rigVal = max(i-1, Max.get(1,0,n,minJ+1,i-1));
                if (rigVal > dp[i]) {
                    // update dp and par
                    dp[i] = rigVal;
                    par[i] = minJ;
                }
            }

            // if dp[i-1] >= i, we can turn lantern i right
            if (dp[i-1] >= i && max(dp[i-1], rig[i]) > dp[i]) {
                dp[i] = max(dp[i-1], rig[i]);
                par[i] = -1;
            }

            // if dp[i-1] > dp[i], we simply take dp[i-1]
            if (dp[i-1] > dp[i]) {
                dp[i] = dp[i-1];
                par[i] = -1;
            }

            // update i to position dp[i] of Min tree
            Min.update(1,0,n,dp[i],i);
        }

        if (dp[n] != n) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        string res = "";
        int cur = n;
        while (cur) {
            if (par[cur] == -1) {
                cur--;
                res += "R";
            } else {
                int pcur = par[cur];
                int diff = cur - pcur;
                res += "L";
                // turn the middle right
                FOR(i,1,diff-1) res += "R";
                // go to par
                cur = pcur;
            }
        }
        // remember to reverse the string
        reverse(ALL(res));
        cout << res << "\n";
    }
    return 0;
}
