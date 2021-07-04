/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Based on E1
        - Reduce the complexity of E1 by using accumulative sums of dp array. 
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

int n, mod;

inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return (x*1ll*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

int dp[501][124752], dpSum[501][124752], C[501][501], f[501];
int dpSumRange[124752], dpSumSum[124752], dpSumStair[124752];

int C2(int n) {
    return n * (n+1) / 2;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> mod;

    FOR(i,0,n)
        FOR(j,0,i)
            if (j == 0 || j == i) C[i][j] = 1 % mod;
            else C[i][j] = add(C[i-1][j-1], C[i-1][j]);
    f[0] = 1;
    FOR(i,1,n) f[i] = mul(f[i-1], i % mod);

    // dp[i][j] = num of permutations with length i and j inversions
    dp[1][0] = 1 % mod;
    FOR(i,2,n) {
        int invNum = C2(i-1);
        FOR(j,0,invNum) {
            if (j == 0) dpSumRange[j] = dp[i-1][j];
            else dpSumRange[j] = add(dpSumRange[j-1], dp[i-1][j]);
            if (j - i < 0) dp[i][j] = dpSumRange[j];
            else dp[i][j] = sub(dpSumRange[j], dpSumRange[j-i]);
        }
    }

    FOR(i,1,n) {
        int invNum = C2(i-1);
        dpSum[i][0] = dp[i][0];
        FOR(j,1,invNum) {
            dpSum[i][j] = add(dpSum[i][j-1], dp[i][j]);
        }
    }

    int res = 0;
    FOR(used,0,n-1) {
        int remain = n - used;
        int p = 0;
        int N = remain - 1;
        int invNum = C2(N-1);

        dpSumSum[0] = dpSum[N][0];
        dpSumStair[0] = dpSum[N][0];
        FOR(i,1,invNum) {
            dpSumSum[i] = add(dpSumSum[i-1], dpSum[N][i]);
            dpSumStair[i] = add(dpSumStair[i-1], mul((i+1) % mod, dpSum[N][i]));
        }

        // k : 0 -> invNum
        // i : k-remain -> k-2 { dpSum[N][i] } -> q
        // q * dp[N][k]

        FOR(k,2,invNum) {
            int z = 0;
            // FOR(i,2,remain) {
            //     if (k - i - 1 >= 0) z = add(z, mul(dp[N][k], sub(dpSumSum[k-2], dpSumSum[k-i-1])));
            //     else z = add(z, mul(dp[N][k], dpSumSum[k-2]));
            // }

            if (k - remain - 1 >= 0) {
                int hs = (k-remain) % mod;
                z = add(z, mul(dp[N][k], sub(sub(dpSumStair[k-2], dpSumStair[k-remain-1]), mul(hs, sub(dpSumSum[k-2], dpSumSum[k-remain-1])))));
            } else {
                int hs = (0 - (k - remain - 1) - 1) % mod;
                z = add(z, mul(dp[N][k], add(dpSumStair[k-2], mul(hs, dpSumSum[k-2]))));
            }

            p = add(p, z);
        }
        p = mul(p, mul(C[n][used], f[used]));
        res = add(res, p);
    }
    cout << res;
    return 0;
}
