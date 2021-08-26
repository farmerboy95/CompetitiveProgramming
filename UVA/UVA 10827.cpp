/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Special case: if all are negative, result = largest element
        - Max sum rectangle in 2d grid but top and bottom are adjacent, left border and
        right border are adjacent.
        - Fix 2 rows then use Kadane
        - For the case that the result has 2 parts, one on the left and one on the right
        for example, we can use Kadane again to find the min sum, then get result = sum - min.
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

int n, a[MAXN][MAXN], b[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    while (te--) {
        cin >> n;
        bool co = true;
        int elem = -INF;
        FOR(i,1,n) FOR(j,1,n) {
            cin >> a[i][j];
            if (a[i][j] >= 0) {
                co = false;
            }
            elem = max(elem, a[i][j]);
            a[i][j] += a[i-1][j];
        }

        if (co) {
            cout << elem << "\n";
            continue;
        }

        int res = -INF;
        FOR(l,1,n)
            FOR(r,l,n) {
                FOR(j,1,n) b[j] = a[r][j] - a[l-1][j];

                int sum = 0;
                FOR(j,1,n) {
                    sum += b[j];
                    res = max(res, sum);
                    if (sum < 0) sum = 0;
                }

                int s = 0;
                FOR(j,1,n) s += b[j];

                sum = 0;
                FOR(j,1,n) {
                    sum += b[j];
                    res = max(res, s - sum);
                    if (sum > 0) sum = 0;
                }

                res = max(res, s - sum);

                if (!(l == 1 && r == n)) {
                    FOR(j,1,n) b[j] = a[n][j] - b[j];

                    int sum = 0;
                    FOR(j,1,n) {
                        sum += b[j];
                        res = max(res, sum);
                        if (sum < 0) sum = 0;
                    }

                    int s = 0;
                    FOR(j,1,n) s += b[j];

                    sum = 0;
                    FOR(j,1,n) {
                        sum += b[j];
                        res = max(res, s - sum);
                        if (sum > 0) sum = 0;
                    }

                    res = max(res, s - sum);
                }
            }
        cout << res << "\n";
    }
    return 0;
}
