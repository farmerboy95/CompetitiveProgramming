/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We can see that F[87] is the greatest Fibonacci number which is lower than 
        or equal to 10^18
        - The first observation is that we can create a set of Fibonacci numbers 
        that have sum equal to n, by greedily choosing the largest number that 
        is <= n, remove it from n, then continue to choose. Then we store the indices
        of chosen numbers in an array A. For example 16 = 13 + 3 => A = [7, 4], let its size be m
        - It can be proved by induction that we can generate all numbers from 1 to F[x]
        using the numbers in F[1..x] and A contains all the largest indices of the position
        if the sum elements are sorted decreasingly.
        - One thing to notice is that there is no A[i] - A[i-1] = 1, because if that happens,
        there should be A[i]+1 in A, as the property of Fibonacci sequence.
        - Ok, let's represent a number in the Fibonacci code. We can use a simple binary
        representation for this, for example, 16 = 13+3 wll be written as 1001000.
        - How can we generate a new sum, it would be like this:
            +  100000000000000000...
            => 011000000000000000...
            => 010110000000000000...
            => 010101100000000000...
        - So when can this stop? When the last 1 of the previous one touch the current 1
        or overlap that one.
            + Case 1: 
               100000010000000000...
            => 011000010000000000...
            => 010110010000000000...
            => 010101110000000000...
            + Case 2
               100000100000000000...
            => 011000100000000000...
            => 010110100000000000...
            => 010101111000000000... (it forces the current 1 to become 2 1s)
        - The last observation, we don't use F[1] at all, if we need a 1, we use F[2].
        - So A will not contain 1, we can put it to the end of A and do a dp
            dp[i][0] = number of sums that does not overlap A[i]
            dp[i][1] = number of sums that overlaps A[i]
        - Clearly we print dp[m][0]
        - So how is the transition? Let dist = A[i-1] - A[i]
            dp[i][0] += dp[i-1][0] * (1 + number of separations)
            dp[i][0] += dp[i-1][1] * number of separations
            dp[i][1] += dp[i-1][0] + dp[i-1][1] when dist % 2 == 0 because only in this
            case, the last 1 will overlap the current one
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

ll n, f[MAXN], dp[MAXN][2];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    f[1] = f[2] = 1;
    FOR(i,3,87) {
        f[i] = f[i-1] + f[i-2];
    }

    int te;
    cin >> te;
    while (te--) {
        cin >> n;
        vi a;
        FORE(i,87,2)
            if (n - f[i] >= 0) {
                n -= f[i];
                a.push_back(i);
            }
        int m = SZ(a);
        a.push_back(1);
        // dbg(a);
        MS(dp, 0);
        dp[0][0] = 1;
        dp[0][1] = 0;

        FOR(i,1,m) {
            int dist = a[i-1] - a[i];
            int middleOK = (dist - 1) / 2;
            // dp[i][0]
            dp[i][0] += dp[i-1][0] * (1 + middleOK);
            dp[i][0] += dp[i-1][1] * middleOK;

            // dp[i][1]
            if (dist % 2 == 0) {
                dp[i][1] += dp[i-1][0] + dp[i-1][1];
            }
        }
        // FOR(i,0,m) dbg(i, dp[i][0], dp[i][1]);

        // print dp[m][0]
        cout << dp[m][0] << "\n";
    }
    return 0;
}
