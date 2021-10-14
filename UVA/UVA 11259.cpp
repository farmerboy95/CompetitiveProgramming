/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Inclusion Exclusion Principle + DP Coin Change
        - Assuming that there are only two kinds of coins, we let 
            + N = the number of schemes that make up the total value of v
            + N1 = the number of schemes in which the first coin with face value c1 has 
            taken more than d1 times to make up the total value of v
            + N2 = the second kind the coin with face value c2 is taken more than d2 times 
            to get the total value of v
            + N12 = The first coin with face value c1 is taken more than d1 times and the 
            second coin with face value c2 is taken more than d2 times. 
        - The number of plans with a total value of v. Then for a set of queries d1, d2, v, 
        the number of legal solutions is N - N1 - N2 + N12.
        - In order to calculate these N, we use c1, c2, c3, c4 to make an infinite backpack 
        with a backpack capacity of 100,000, and use the dp array to record the number of plans.
        Then, to calculate N, just use dp[v].
        - How to calculate N1? Because the c1 coin has been taken more than d1 times, then we 
        assume that it has taken d1+1 times, and a total of (d1+1)*c1 value coins have been 
        taken away, then the number of plans is dp[v-(d1+1) * c1].
        - Similarly, the number of plans for N2 is dp[v-(d2+1)*c2], and the number of plans 
        for N12 is dp[v-(d1+1)*c1-(d2+1)*c2]. Then count N-N1-N2+N12 to get the answer.
        - Now there are 4 coin types in the question, and the same principle is used. At this 
        time, the answer is 
            N-N1-N2-N3-N4+N12+N13+N14+N23+N24+N34-N123-N124-N134-N234+N1234
            a total of 16 items.
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

const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int c[4], d[4];
ll dp[MAXN];

ll solve(int v) {
    ll res = 0;
    FOR(mask,0,15) {
        int tempV = v;
        int f = 1;
        FOR(i,0,3) {
            if (mask & (1<<i)) {
                f = -f;
                tempV -= (d[i] + 1) * c[i];
            }
        }
        if (tempV >= 0) {
            res += f * dp[tempV];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    while (te--) {
        FOR(i,0,3) cin >> c[i];
        MS(dp, 0);
        dp[0] = 1;
        FOR(i,0,3)
            FOR(j,c[i],100000) dp[j] += dp[j-c[i]];
        
        int q;
        cin >> q;
        while (q--) {
            FOR(i,0,3) cin >> d[i];
            int v;
            cin >> v;
            cout << solve(v) << "\n";
        }
    }
    return 0;
}
