/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/88677
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

int nt[10000010], a[MAXN], n, k, dp[MAXN][25], lef[MAXN][25];
 
void sieveBase(int N) {
    FOR(i,2,N) {
        if (nt[i] == 0) {
            nt[i] = i;
            for (ll j = (ll) i * i; j <= N; j += i) nt[j] = i;
        }
    }
}

struct BinaryIndexedTree {
    public:
    // 1-indexed
    BinaryIndexedTree(int n) {
        N = n;
        t.resize(N+1);
        FOR(i,0,N) t[i] = 0;
    }

    void update(int u, int val) {
        while (u <= N) {
            t[u] += val;
            u = u + (u & (-u));
        }
    }
 
    int get(int u) {
        int res = 0;
        while (u) {
            res += t[u];
            u = u - (u & (-u));
        }
        return res;
    }

    private:
    vector<int> t;
    int N;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    sieveBase(10000000);
    while (te--) {
        cin >> n >> k;
        FOR(i,1,n) cin >> a[i];

        FOR(i,1,n) {
            int x = a[i];
            int p = 1;
            while (x > 1) {
                int g = nt[x];
                int cnt = 0;
                while (x % g == 0) {
                    cnt++;
                    x /= g;
                }
                if (cnt % 2) {
                    p *= g;
                }
            }
            a[i] = p;
        }

        unordered_map<int, int> ma;
        BinaryIndexedTree bit(n);
        FOR(i,1,n) {
            if (ma.count(a[i])) {
                int pos = ma[a[i]];
                bit.update(pos, -1);
                bit.update(i, 1);
            } else {
                bit.update(i, 1);
            }
            ma[a[i]] = i;
            int g = bit.get(i);
            FOR(j,0,k) {
                int dau = 1, cuoi = i;
                
                while (dau <= cuoi) {
                    int mid = (dau + cuoi) >> 1;
                    if (g - bit.get(mid-1) + j < i - (mid-1)) dau = mid+1;
                    else cuoi = mid-1;
                }

                lef[i][j] = dau;
            }
        }

        FOR(j,0,k) dp[0][j] = 0;
        FOR(i,1,n)
            FOR(j,0,k) {
                dp[i][j] = 1e9;
                FOR(p,0,j) {
                    ckmin(dp[i][j], dp[lef[i][p]-1][j-p] + 1);
                }
            }
        cout << dp[n][k] << "\n";
    }
    return 0;
}
