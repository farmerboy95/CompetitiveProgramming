/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We need to find 3 non-overlapping rectangles so that their sum is the greatest.
        - So we can divide the initial area into 3 smaller areas then find the greatest-sum
        rectangle in each area.
        - There are 6 cases
            1. +-----------+
               |           |
               +-----------+
               |           |
               +-----------+
               |           |
               +-----------+
            2. +---+---+---+
               |   |   |   |
               |   |   |   |
               |   |   |   |
               |   |   |   |
               |   |   |   |
               +---+---+---+
            3. +-----------+
               |           |
               |           |
               +-----+-----+
               |     |     |
               |     |     |
               +-----+-----+
            4. +-----+-----+
               |     |     |
               |     |     |
               +-----------+
               |           |
               |           |
               +-----+-----+
            5. +-----+-----+
               |     |     |
               |     |     |
               |     +-----+
               |     |     |
               |     |     |
               +-----+-----+
            6. +-----+-----+
               |     |     |
               |     |     |
               +-----+     |
               |     |     |
               |     |     |
               +-----+-----+
        - Let dp[0][i][j] = the greatest sum retrieved in rectangle (1, 1) -> (i, j)
              dp[1][i][j] = the greatest sum retrieved in rectangle (1, m) -> (i, j)
              dp[2][i][j] = the greatest sum retrieved in rectangle (n, m) -> (i, j)
              dp[3][i][j] = the greatest sum retrieved in rectangle (n, 1) -> (i, j)
              dp[4][i][j] = the greatest sum retrieved in rectangle (1, i) -> (n, j)
              dp[5][i][j] = the greatest sum retrieved in rectangle (i, 1) -> (j, m)
        - Those can be calculated in O(n^4). Then get result from 6 above cases.
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

const int MAXN = 35;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int a[MAXN][MAXN], sum[MAXN][MAXN];
int dp[6][MAXN][MAXN];

class ThreeMines {
    public:
    inline int getSum(int x, int y, int u, int v) {
        int X = min(x, u), U = max(x, u);
        x = X; u = U;
        int Y = min(y, v), V = max(y, v);
        y = Y; v = V;
        return sum[u][v] - sum[x-1][v] - sum[u][y-1] + sum[x-1][y-1];
    }

    int maximumProfit(vs ss) {
        int n = SZ(ss), m = SZ(ss[0]);

        FOR(i,0,n-1) FOR(j,0,m-1) {
            if (ss[i][j] >= 'a' && ss[i][j] <= 'z') {
                a[i+1][j+1] = ss[i][j] - 'a';
            } else {
                a[i+1][j+1] = -(ss[i][j] - 'A');
            }
        }

        FOR(i,0,n+1)
            FOR(j,0,m+1)
                FOR(k,0,5) 
                    if (i == 0 || i == n+1 || j == 0 || j == m+1) dp[k][i][j] = -1000000;
                    else dp[k][i][j] = 0;

        FOR(i,1,n)
            FOR(j,1,m) sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + a[i][j];
        
        // 0
        FOR(i,1,n)
            FOR(j,1,m) {
                int Max = -1e9;
                FOR(u,1,i) FOR(v,1,j) ckmax(Max, getSum(u, v, i, j));
                dp[0][i][j] = max(dp[0][i-1][j], max(dp[0][i][j-1], Max));
            }

        // 1
        FOR(i,1,n)
            FORE(j,m,1) {
                int Max = -1e9;
                FOR(u,1,i) FORE(v,m,j) ckmax(Max, getSum(u, v, i, j));
                dp[1][i][j] = max(dp[1][i-1][j], max(dp[1][i][j+1], Max));
            }

        // 2
        FORE(i,n,1)
            FORE(j,m,1) {
                int Max = -1e9;
                FORE(u,n,i) FORE(v,m,j) ckmax(Max, getSum(u, v, i, j));
                dp[2][i][j] = max(dp[2][i+1][j], max(dp[2][i][j+1], Max));
            }

        // 3
        FORE(i,n,1)
            FOR(j,1,m) {
                int Max = -1e9;
                FORE(u,n,i) FOR(v,1,j) ckmax(Max, getSum(u, v, i, j));
                dp[3][i][j] = max(dp[3][i+1][j], max(dp[3][i][j-1], Max));
            }

        

        // vertical
        FORE(i,m,1)
            FOR(j,i,m) {
                int Max = -1e9;
                if (i != j) Max = max(Max, max(dp[4][i+1][j], dp[4][i][j-1]));
                int prefixSum = 0, minPrefixSum = 0;
                FOR(k,1,n) {
                    prefixSum += getSum(k, i, k, j);
                    Max = max(Max, prefixSum - minPrefixSum);
                    minPrefixSum = min(minPrefixSum, prefixSum);
                }
                dp[4][i][j] = Max;
            }

        // horizontal
        FORE(i,n,1)
            FOR(j,i,n) {
                int Max = -1e9;
                if (i != j) Max = max(Max, max(dp[5][i+1][j], dp[5][i][j-1]));
                int prefixSum = 0, minPrefixSum = 0;
                FOR(k,1,m) {
                    prefixSum += getSum(i, k, j, k);
                    Max = max(Max, prefixSum - minPrefixSum);
                    minPrefixSum = min(minPrefixSum, prefixSum);
                }
                dp[5][i][j] = Max;
            }

        

        int res = -1e9;
        // case 1
        FOR(i,1,m)
            FOR(j,i+1,m-1) ckmax(res, dp[0][n][i] + dp[1][n][j+1] + dp[4][i+1][j]);
        
        // case 2
        FOR(i,1,n)
            FOR(j,i+1,n-1) ckmax(res, dp[0][i][m] + dp[3][j+1][m] + dp[5][i+1][j]);
        
        // case 3, 4
        FOR(i,1,n-1)
            FOR(j,1,m-1) {
                ckmax(res, dp[0][i][m] + dp[3][i+1][j] + dp[2][i+1][j+1]);
                ckmax(res, dp[0][i][j] + dp[3][i+1][m] + dp[1][i][j+1]);
            }

        // case 5, 6
        FOR(j,1,m-1)
            FOR(i,1,n-1) {
                ckmax(res, dp[0][n][j] + dp[1][i][j+1] + dp[2][i+1][j+1]);
                ckmax(res, dp[0][i][j] + dp[3][i+1][j] + dp[1][n][j+1]);
            }

        return res;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    ThreeMines a;
    cout << a.maximumProfit({
"bbbb",
"bBBB",
"BBbb",
"BBBB"}) << endl;
    cout << a.maximumProfit({"cfCBDCbcdZb"}) << endl;
    cout << a.maximumProfit({"d", "c", "B", "m", "Z", "h", "g", "B", "z", "G", "H", "b", "Y"}) << endl;
    cout << a.maximumProfit({
"hBhh", 
"BBBB",
"BBBB", 
"hBhh", 
"hBhh"}) << endl;
    cout << a.maximumProfit({
"BB", 
"BB"}) << endl;
    cout << a.maximumProfit({
"ZcabcaacacabcbbbcababacaccbZaa",
"acaaccccacbccbaaccabaccaacbZbc",
"bcbaacbcbbccbbcbabbbbaZcbcbccb",
"cccacbabccbZbcbabaacbbZcbacbab",
"cacbabbcabbabbcacbcbbcaacaabbc",
"bacZcacaaccbabbcccccabcaacbaca",
"cbcccacabcabacaccacaZbbcbcacbb",
"cZbbbcaacbaacaabZcaccbcZccbbab",
"Zcababaacbbbbccbcbbaccacacbbcc",
"cZcccaaabbcbcbccccbcbaabbbccbb",
"bbcaacacabccababacbccacccbbaba",
"cccbbcaZabccacabbccccabbabbbab",
"bbbacbccbbcaabaaabccbcaabcacaa",
"cbbababbccccbcccbaacacccaabaac",
"aaccaccaccbabbccaaaacbacccacca",
"bbbcabcabZZcabcabbaacZbaaabaZb",
"aaabbabcabaaacbcccccbbcabcccbc",
"bbbaccbacacaccbbaccabacbbbaaac",
"acaaacccbabbccbcbabbcbaaaccabb",
"bcaaaaabcbabaaabccacccbaacbbbc",
"bZcbcbcccaabccaabbccbababbbcca",
"cbbbbcccabcabcbacaaaaabbbbbcac",
"ccbbcbacacbbcacacbaabcbbacbaba",
"cbbbaabaabbbbaccabbcbcaccaaaac",
"abZcabaacbbcacbaaabccbabacacaa",
"aabccacbabaacaccccbbbbcccccaca",
"aabcbaaacbabcaccbaabbbabbabbca",
"ababcabaccaaaacccacbcbcabacbcb",
"bcaaaacabcabbbaccccccacabccacb",
"cbbabbbccaaaaacbccaabcbbccbacc"}) << endl;
    cout << a.maximumProfit(
        {{
        "vZqZZuh", 
        "kbqnZlE", 
        "addvZax", 
        "ZZZZZbv", 
        "GuFwZqr", 
        "vEutZEq", 
        "pFckZkn"}}
    );
    return 0;
}
