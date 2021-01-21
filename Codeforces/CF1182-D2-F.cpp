/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/67614
        - We can easily see that the problem is to find minimum possible number x that 2px mod 2q
        is the closest to q.
        - Go step by step in implementation.
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

const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ll solve(ll l, ll r, ll p, ll q) {
    // set interval with length seg = sqrt(r-l+1)
    ll seg = 1;
    while (seg * seg < r - l) seg++;

    // let g(x) = 2px mod 2q
    // construct a list [(g(a),a), (g(a+1),a+1), (g(a+2),a+2), ..., (g(a+seg-1),a+seg-1)]
    vpl firstSeg;
    for (ll i = l; i < l + seg; i++) {
        ll x = 2 * p * i % (2 * q);
        firstSeg.push_back({x, i});
    }
    // remove the larger x with duplicate g(x) values from the sorted list
    sort(ALL(firstSeg));
    vpl tmp = firstSeg;
    firstSeg.clear();
    firstSeg.push_back(tmp[0]);
    FOR(i,1,SZ(tmp)-1)
        if (tmp[i].FI != tmp[i-1].FI) firstSeg.push_back(tmp[i]);
    
    // now we check O(seg) segments, val is the minimum distance from q to g(res)
    ll res = -1, val = (ll) INF * INF, itr = 0;
    for (itr = 0; l + (itr + 1) * seg <= r; itr++) {
        // ideally, we need 2px = q (mod 2q)
        //              <=> 2p(X + itr * seg) = q (mod 2q) (X is a number in the first segment)
        //              <=> 2pX + 2p * itr * seg = q (mod 2q)
        //              <=> 2pX = q - 2p * itr * seg (mod 2q)
        // so we just need to find g(X) = q - 2p * itr * seg in the first segment
        // of course we mostly cannot find any X with that exact value as it's ideal case.
        // But we cam still find its near values, left and right
        ll z = q - 2 * p * itr * seg;
        z %= 2 * q;
        if (z < 0) z += 2 * q;

        // check baseIdx and baseIdx-1 (right and left respectively)
        ll baseIdx = lower_bound(ALL(firstSeg), pl(z, (ll) -INF * INF)) - firstSeg.begin();
        FORE(j,0,-1) {
            // baseIdx can be SZ(firstSeg) sometimes, remember to take the modulo first
            ll checkIdx = (baseIdx + j) % SZ(firstSeg);
            if (checkIdx < 0) checkIdx += SZ(firstSeg);
            // get the number
            ll thisNum = firstSeg[checkIdx].SE + itr * seg;
            // value is the difference of the ideal value and its value
            ll w = z - firstSeg[checkIdx].FI;
            if (w < 0) w = -w;
            if (w > q) w = 2 * q - w;

            // get the result
            if (w < val) {
                val = w;
                res = thisNum;
            } else if (w == val && thisNum < res) {
                val = w;
                res = thisNum;
            }
        }

    }

    // brute force the rest of numbers, this will take O(seg)
    for (ll i = l + itr * seg; i < r; i++) {
        ll w = 2 * p * i % (2 * q) - q;
        if (w < 0) w = -w;
        if (w < val) {
            val = w;
            res = i;
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
        ll a, b, p, q;
        cin >> a >> b >> p >> q;
        cout << solve(a, b+1, p, q) << "\n";
    }
    return 0;
}
