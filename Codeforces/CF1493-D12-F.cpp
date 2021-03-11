/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/88422
        - Check if x consecutive blocks are equal to each other using ceil(log2(x)) queries.
        - Let's suppose we want to check the equality of x blocks, then we will check if the first 
        and second floor(x/2) blocks are equal. If they are not equal, then x blocks are not equal 
        to each other, otherwise we need to check if the last ceil(x/2) blocks are equal.
        - Let's solve the problem for n rows and let's find all r such that the matrix can be split 
        into equal rectangles of r rows. If r is the answer, then the numbers that are divisible by 
        r are also the answers. If r is not the answer, then all divisors of r are not the answers. 
        If r1 and r2 are the answers, then gcd(r1,r2) is the answer as well.
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

const int MAXN = 1010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, dp[MAXN];
vector<vector<int> > a;

int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int ask(int h, int w, int x, int y, int u, int v) {
    cout << "? " << h << ' ' << w << ' ' << x << ' ' << y << ' ' << u << ' ' << v << endl;
    int res;
    cin >> res;
    return res;
}

bool isOK(int l, int r) {
    if (l == r) return 1;

    int mid = (l + r) >> 1;
    if ((r - l + 1) % 2 == 0) mid++;

    int h = a[mid][0] - a[l][0];
    if (h == 0) h = n;
    int w = a[mid][1] - a[l][1];
    if (w == 0) w = m;

    if (ask(h, w, a[l][0], a[l][1], a[mid][0], a[mid][1])) return isOK(mid, r);

    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    // dp[r] = 1 then the matrix can be divided into blocks with r rows in each block.
    // otherwise dp[r] = -1
    FORE(i,n,1)
        if (n % i == 0 && dp[i] == 0) {
            // dp[i] == 0 => still have the chance to be ok
            // if dp[i] = 1 => every x that are divisors of n and are divisible by r, dp[x] = 1
            // take the smallest x (because dp[x] is already 1, if dp[x] = 0 => dp[i] = 0 => we can't reach here)
            // check the range 1 -> x, divide it to blocks with i rows in each block
            for (int j = 2 * i; j <= n; j += i) {
                if (n % j == 0 && j % i == 0) {
                    a.clear();
                    for (int k = 1; k <= j; k += i) {
                        a.push_back({k, 1, k + i - 1, m});
                    }
                    if (isOK(0, SZ(a)-1)) dp[i] = 1;
                    else dp[i] = -1;
                    break;
                }
            }
            if (dp[i] == -1) {
                // update the lower ones
                FOR(j,1,n)
                    if (i % j == 0) dp[j] = -1;
            } else {
                dp[i] = 1;
                // use gcd to update the other lower ones
                FOR(j,i,n)
                    if (dp[j] == 1) {
                        int g = gcd(i, j);
                        for (int w = g; w <= n; w += g) dp[w] = 1;
                    }
            }
        }
    
    int resN = 0;
    FOR(i,1,n)
        if (n % i == 0 && dp[i] == 1) resN++;
    MS(dp, 0);

    // do the same thing with the columns
    FORE(i,m,1)
        if (m % i == 0 && dp[i] == 0) {
            for (int j = 2 * i; j <= m; j += i) {
                if (m % j == 0 && j % i == 0) {
                    a.clear();
                    for (int k = 1; k <= j; k += i) {
                        a.push_back({1, k, n, k+i-1});
                    }
                    if (isOK(0, SZ(a)-1)) dp[i] = 1;
                    else dp[i] = -1;
                    break;
                }
            }
            if (dp[i] == -1) {
                FOR(j,1,m)
                    if (i % j == 0) dp[j] = -1;
            } else {
                dp[i] = 1;
                FOR(j,i,m)
                    if (dp[j] == 1) {
                        int g = gcd(i, j);
                        for (int w = g; w <= m; w += g) dp[w] = 1;
                    }
            }
        }

    int resM = 0;
    FOR(i,1,m)
        if (m % i == 0 && dp[i] == 1) resM++;
    
    cout << "! " << resN * resM << endl;
    return 0;
}
