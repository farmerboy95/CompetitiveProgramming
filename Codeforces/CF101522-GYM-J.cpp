/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let dp[x][y][z][p] = number of ways to form a string with x B, y R, z S and starting with B/R/S
        (0/1/2 respectively). Here we need to handle some cases that the dp > 10^18, we can use -2 as
        such value.
        - Then the problem would just be a simple counting problem. First we check if we can put B
        into the result by checking if k > dp[x][y][z][0], if yes, we move to the next character and
        reduce k, if not, we can tell B is the first character. Do like that till the end.
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

const int MAXN = 210;
const int MAXM = 1000;
const int MAXK = 16;
const ll MAXQ = 1000000000000000000LL;

ll dp[MAXN][MAXN][MAXN][3];
string alp = "BRS";

ll solve(int x, int y, int z, int p) {
    if (p == 0 && x == 0) return 0;
    if (p == 1 && y == 0) return 0;
    if (p == 2 && z == 0) return 0;
    if (x + y + z == 1) return 1;
    ll &res = dp[x][y][z][p];
    if (res != -1) return res;
    int newX = x, newY = y, newZ = z;
    if (p == 0) newX--;
    if (p == 1) newY--;
    if (p == 2) newZ--;
    ll g = solve(newX, newY, newZ, (p+1) % 3);
    ll h = solve(newX, newY, newZ, (p+2) % 3);
    if (g == -2 || h == -2) return res = -2;
    res = g+h;
    if (res > MAXQ) res = -2;
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int x, y, z;
    ll k;
    cin >> x >> y >> z >> k;
    MS(dp, -1);
    FOR(i,0,2) solve(x, y, z, i);
    int n = x + y + z;
    string res = "";
    int pre = -1;
    FOR(i,1,n) {
        bool co = false;
        FOR(j,0,2) {
            if (j == pre) continue;
            ll g = solve(x, y, z, j);
            if (g == -2) {
                pre = j;
                res += alp[j];
                co = true;
                if (j == 0) x--;
                if (j == 1) y--;
                if (j == 2) z--;
                break;
            }
            if (g >= k) {
                pre = j;
                res += alp[j];
                co = true;
                if (j == 0) x--;
                if (j == 1) y--;
                if (j == 2) z--;
                break;
            }
            // g <= k
            k -= g;
        }
        if (!co) {
            cout << "None";
            return 0;
        }
    }
    cout << res;
    return 0;
}
