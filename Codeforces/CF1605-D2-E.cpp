/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/96866
        - Quite hard to understand the official editorial code, so i divided the 1 and -1
        mobius func to 2 cases as described in the implementation
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

const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN], b[MAXN];
ll c[MAXN];
ll coeff[MAXN], noCoeff[MAXN];

void init() {
    coeff[1] = 1;
    FOR(i,1,200000) {
        for (int j = i + i; j <= 200000; j += i) {
            coeff[j] -= coeff[i];
        }
    }
}

ll get(vl &pref, int l, int r) {
    if (l > r) return 0;
    if (r > SZ(pref)-1) return 0;
    if (l < 0) return 0;
    ll res = pref[r];
    if (l - 1 >= 0) res -= pref[l-1];
    return res;
}

ll getNum(vl &pref, int l, int r) {
    if (l > r) return 0;
    if (r > SZ(pref)-1) return 0;
    if (l < 0) return 0;
    return r - l + 1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    init();
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n) cin >> b[i];

    c[1] = 0;
    FOR(i,2,n) c[i] = b[i] - a[i];

    FOR(i,1,n) {
        int d = c[i];
        for (int j = i; j <= n; j += i) {
            c[j] -= d;
        }
        noCoeff[i] = d;
    }

    ll kq = 0;
    vl z1, z2;
    FOR(i,1,n) {
        if (coeff[i] == 0) kq += abs(noCoeff[i]);
        // |A - x| = 
        // A - x when x <= A
        // x - A when x > A
        else if (coeff[i] == -1) z2.push_back(noCoeff[i]);
        // |A + x| = 
        // A + x when x >= -A
        // -A - x when x < -A
        else z1.push_back(-noCoeff[i]);
    }
    sort(ALL(z1));
    sort(ALL(z2));

    vl prefSum1 = z1;
    vl prefSum2 = z2;
    FOR(i,1,SZ(z1)-1) prefSum1[i] += prefSum1[i-1];
    FOR(i,1,SZ(z2)-1) prefSum2[i] += prefSum2[i-1];


    int q;
    ll x;
    cin >> q;
    while (q--) {
        cin >> x;
        x -= a[1];
        ll res = 0;
        
        int dau = 0, cuoi = SZ(z1) - 1;
        while (dau <= cuoi) {
            int mid = (dau + cuoi) >> 1;
            if (z1[mid] > x) cuoi = mid-1;
            else dau = mid+1;
        }
        // dau -> SZ(z1)-1
        res += get(prefSum1, dau, SZ(z1)-1) - getNum(prefSum1, dau, SZ(z1)-1) * x;
        // 0 -> cuoi
        res += -get(prefSum1, 0, cuoi) + getNum(prefSum1, 0, cuoi) * x;

        dau = 0; cuoi = SZ(z2) - 1;
        while (dau <= cuoi) {
            int mid = (dau + cuoi) >> 1;
            if (z2[mid] <= x) dau = mid+1;
            else cuoi = mid-1;
        }
        // dau -> SZ(z2)-1
        res += get(prefSum2, dau, SZ(z2)-1) - getNum(prefSum2, dau, SZ(z2)-1) * x;
        // 0 -> cuoi
        res += -get(prefSum2, 0, cuoi) + getNum(prefSum2, 0, cuoi) * x;

        cout << kq + res << "\n";
    }
    return 0;
}
