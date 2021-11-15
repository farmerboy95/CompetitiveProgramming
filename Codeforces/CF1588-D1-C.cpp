/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/96953
        - Very messy and hard-to-implement problem
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

const int MAXN = 300010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN];
ll c[MAXN], C[2][MAXN], M[2][MAXN][20];
map<ll, vi> pos[2];

void RMQ() {
    FOR(i,1,n) {
        M[0][i][0] = C[0][i];
        M[1][i][0] = C[1][i];
    }
    for (int k = 1; (1<<k) <= n; k++) {
        for (int i = 1; i + (1<<k) - 1 <= n; i++) {
            M[0][i][k] = min(M[0][i][k-1], M[0][i+(1<<(k-1))][k-1]);
            M[1][i][k] = min(M[1][i][k-1], M[1][i+(1<<(k-1))][k-1]);
        }
    }
}

ll get(int idx, int u, int v) {
    int k = log2(v - u + 1);
    return min(M[idx][u][k], M[idx][v-(1<<k)+1][k]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    while (te--) {
        cin >> n;
        FOR(i,1,n) cin >> a[i];
        
        c[0] = 0;
        FOR(i,1,n) c[i] = a[i] - c[i-1];

        FOR(i,1,n) {
            C[1 - i % 2][i] = (ll) INF * INF;
            C[i % 2][i] = c[i];
        }
        RMQ();
        pos[0].clear();
        pos[1].clear();

        FOR(i,1,n) pos[i % 2][c[i]].push_back(i);

        ll res = 0;
        FORE(l,n,1) {
            ll prv = c[l-1];
            // c[l+i-1] + (-1) ^ (i-1) * prv < 0
            // => c[l+i-1] < - (-1) ^ (i-1) * prv
            
            // c[l+i-1] + (-1) ^ (i-1) * prv = 0
            // => c[l+i-1] = - (-1) ^ (i-1) * prv

            // - on l, l+2, l+4 ...
            // find the first l+x that is smaller than posPrv
            // + on l+1, l+3, l+5 ...
            // find the first l+x that is smaller than negPrv
            ll posPrv = prv;
            ll negPrv = -prv;

            int dau = l, cuoi = n;
            while (dau <= cuoi) {
                int mid = (dau + cuoi) >> 1;
                if (l % 2 == 0) {
                    if (get(1, l, mid) < posPrv || get(0, l, mid) < negPrv) cuoi = mid-1;
                    else dau = mid+1;
                } else {
                    if (get(0, l, mid) < posPrv || get(1, l, mid) < negPrv) cuoi = mid-1;
                    else dau = mid+1;
                }
            }

            // find all "==" from l to cuoi
            if (cuoi >= l) {
                if (l % 2 == 0) {
                    if (pos[1].count(posPrv)) {
                        vi &v = pos[1][posPrv];
                        res += upper_bound(ALL(v), cuoi) - lower_bound(ALL(v), l);
                    }
                    if (pos[0].count(negPrv)) {
                        vi &v = pos[0][negPrv];
                        res += upper_bound(ALL(v), cuoi) - lower_bound(ALL(v), l);
                    }
                } else {
                    if (pos[0].count(posPrv)) {
                        vi &v = pos[0][posPrv];
                        res += upper_bound(ALL(v), cuoi) - lower_bound(ALL(v), l);
                    }
                    if (pos[1].count(negPrv)) {
                        vi &v = pos[1][negPrv];
                        res += upper_bound(ALL(v), cuoi) - lower_bound(ALL(v), l);
                    }
                }
            }
        }
        cout << res << "\n";
    }
    return 0;
}
