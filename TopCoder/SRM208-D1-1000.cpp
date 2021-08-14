/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Stated in code
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

class StarAdventure {
    public:
    int dp[55][55][55];

    int mostStars(vs level) {
        // - The problem reduced to most stars collected after 3 paths from top-left 
        // to bottom-right corner (left path, middle path and right path)
        // - Idea: https://www.topcoder.com/thrive/articles/Dynamic%20Programming:%20From%20Novice%20to%20Advanced
        // - dp[i][x][y][z] = most stars collected at a[i][x], a[i][y] and a[i][z]
        // x <= y <= z
        // - After moving down, we try to move each to the right. As they don't intersect,
        // we try to move all x to y, y to z, and z to m-1

        int n = SZ(level), m = SZ(level[0]);
        MS(dp, 0);
        FOR(i,0,m-1)
            FOR(j,i,m-1)
                FOR(k,j,m-1) {
                    if (i == 0 && j == 0) {
                        if (k == 0) dp[i][j][k] = level[0][k] - '0';
                        else dp[i][j][k] = dp[i][j][k-1] + level[0][k] - '0';
                    } else {
                        dp[i][j][k] = dp[0][0][k];
                    }
                }
        

        FOR(row,1,n-1) {
            FOR(i,0,m-1)
                FOR(j,i,m-1)
                    FOR(k,j,m-1) {
                        dp[i][j][k] += level[row][i] - '0';
                        if (j != i) dp[i][j][k] += level[row][j] - '0';
                        if (k != j) dp[i][j][k] += level[row][k] - '0';
                    }
            
            // i
            FOR(i,0,m-1)
                FOR(j,i,m-1)
                    FOR(k,j,m-1)
                        if (i - 1 >= 0) ckmax(dp[i][j][k], dp[i-1][j][k] + (i != j ? level[row][i] - '0' : 0));

            // j
            FOR(i,0,m-1)
                FOR(j,i,m-1)
                    FOR(k,j,m-1)
                        if (j - 1 >= i) ckmax(dp[i][j][k], dp[i][j-1][k] + (j != k ? level[row][j] - '0' : 0));

            // k
            FOR(i,0,m-1)
                FOR(j,i,m-1)
                    FOR(k,j,m-1)
                        if (k - 1 >= j) ckmax(dp[i][j][k], dp[i][j][k-1] + level[row][k] - '0');
        }

        return dp[m-1][m-1][m-1];
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    StarAdventure sol;
    cout << sol.mostStars({"01", "11"}) << "\n";
    cout << sol.mostStars({"0999999999"
,"9999999999"
,"9999999999"
,"9999999999"
,"9999999999"
,"9999999999"
,"9999999999"
,"9999999999"
,"9999999999"
,"9999999999"}) << "\n";
    cout << sol.mostStars({"012"
,"012"
,"012"
,"012"
,"012"
,"012"
,"012"}) << "\n";
    cout << sol.mostStars({"0123456789",
 "1123456789",
 "2223456789",
 "3333456789",
 "4444456789",
 "5555556789",
 "6666666789",
 "7777777789",
 "8888888889",
 "9999999999"}) << "\n";
    return 0;
}
