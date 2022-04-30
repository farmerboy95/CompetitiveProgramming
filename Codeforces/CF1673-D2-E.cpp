/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Comments in code
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

const int MAXN = 1100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, k;
int b[MAXN], res[MAXN];
vi c[MAXN];

int getParityC(int n, int k) {
    // dbg(n, k);
    if (k < 0 || k > n) {
        return 0;
    }

    int dist = n - k;
    int res = c[n][SZ(c[n])-1-dist];

    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> k;
    FOR(i,1,n) cin >> b[i];

    // only need C(n, k) of about 25 n only
    FOR(i,max(n-25,0),n) {
        FOR(j,0,i) {
            // C(n, k) % 2 == 1 when (k & n) == k
            // We can show this using Kummer's theorem, Lucas's theorem or 
            // just staring at an image of a Sierpiński triangle
            if ((j & i) == j) {
                c[i].push_back(1);
            } else {
                c[i].push_back(0);
            }
        }

        // prefix sum
        FORE(j,i-1,0) {
            c[i][j] += c[i][j+1];
            c[i][j] %= 2;
        }
    }

    // divide into at least k+1 segments
    // each segment not having more than 20 elements

    FOR(i,1,n) {
        // 2^(b[i] * 2^(b[i+1] + b[i+2] + ...))
        int num = b[i];
        int sum = 0;
        FOR(j,i,i+19) {
            if (j > n) break;
            if (j > i) {
                sum += b[j];
            }
            if (sum >= 20) break;
            if ((ll) (1 << sum) * num >= (1 << 20)) break;

            int g = (1 << sum) * num;
            int remainingSlots = n - 1 - (j - i);
            int K = k;

            // left and right of segment should be XOR
            if (i - 1 >= 1) {
                remainingSlots--;
                K--;
            }

            if (j + 1 <= n) {
                remainingSlots--;
                K--;
            }

            // there will be no more than 25 different remaining slots

            ckmax(K, 0);

            // only need the parity of C(n, k) + C(n, k+1) + ... + C(n, n)
            int par = getParityC(remainingSlots, K);
            if (par) {
                res[g] = 1 - res[g];
            }
        }
    }

    int pos = 0;
    FORE(i,(1<<20)-1,0) {
        if (res[i]) {
            pos = i;
            break;
        }
    }
    FORE(i,pos,0) {
        cout << res[i];
    }
    return 0;
}
