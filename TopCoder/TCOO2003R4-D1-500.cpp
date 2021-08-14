/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We only need to care about difference between sum of numbers of 2 groups
        - Let dp[i][j] = number of ways to get diff j after considering first i
        numbers.
        - We choose the largest number of group 1 first, then calculate the dp above
        for each largest number. As there maybe duplicate numbers, after we have the
        largest number x and number of that number y, we try to choose a from y for
        group 1 and b from y-a for group 2, note that a > 0 and b >= 0. We can make
        it faster by taking the difference of a and b only.
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

const int MAXN = 60010;
const int MAXM = 1010;
const int MAXK = 16;
const int MAXQ = 200010;

class Jewelry {
    public:
    int n, cnt[MAXM];
    ll dp[MAXN], nex[MAXN], C[31][31];

    ll howMany(vi a) {
        n = SZ(a);
        sort(ALL(a));

        FOR(i,0,30)
            FOR(j,0,i)
                if (j == 0 || j == i) C[i][j] = 1;
                else C[i][j] = C[i-1][j-1] + C[i-1][j];

        MS(cnt, 0);

        FOR(i,0,n-1) cnt[a[i]]++;
        vpi w;
        FOR(i,1,1000)
            if (cnt[i]) w.push_back({i, cnt[i]});

        int offset = 30000;
        ll res = 0;

        FOR(p,0,SZ(w)-1) {
            int root = w[p].FI, dem = w[p].SE;

            // left - right = diff
            // left >= 1
            // right >= 0
            MS(dp, 0);
            FOR(diff,-dem,dem) {
                int l = 0, r = 0;
                if (diff < 0) r = -diff;
                else if (diff > 0) l = diff;
                if (l == 0) {
                    l++;
                    r++;
                }
                ll numInitWays = 0;
                while (l + r <= dem) {
                    numInitWays += C[dem][l] * C[dem - l][r];
                    l++;
                    r++;
                }
                dp[diff * root + offset] = numInitWays;
            }

            FOR(i,0,n-1) {
                MS(nex, 0);
                if (a[i] == root) continue;
                if (a[i] < root) {
                    FOR(sum,0,60000) {
                        nex[sum] += dp[sum];
                        if (sum + a[i] <= 60000) nex[sum + a[i]] += dp[sum];
                    }
                } else {
                    FOR(sum,0,60000) {
                        nex[sum] += dp[sum];
                        if (sum - a[i] >= 0) nex[sum - a[i]] += dp[sum];
                    }
                }
                FOR(sum,0,60000) dp[sum] = nex[sum];
            }
            res += dp[offset];
        }

        return res;
    } 
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    Jewelry sol;
    cout << sol.howMany({1,2,5,3,4,5}) << "\n";
    cout << sol.howMany({1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000}) << "\n";
    cout << sol.howMany({1,2,3,4,5}) << "\n";
    cout << sol.howMany({7,7,8,9,10,11,1,2,2,3,4,5,6}) << "\n";
    cout << sol.howMany({123,217,661,678,796,964,54,111,417,526,917,923}) << "\n";
    return 0;
}
