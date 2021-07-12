/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codingcompetitions.withgoogle.com/kickstart/round/00000000004361e3/000000000082bcf4#analysis
        - The editorial seems to forget the case when a[i] < p => a[i]^s - (a[i] % p)^s = 0
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

const int MAXN = 500010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, q;
ll p, a[MAXN], v[MAXN], dem[MAXN], v1[MAXN], v2[MAXN];

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
 
    ll get(int u) {
        ll res = 0;
        while (u) {
            res += t[u];
            u = u - (u & (-u));
        }
        return res;
    }

    private:
    vector<ll> t;
    int N;
};

void input() {
    cin >> n >> q >> p;
    FOR(i,1,n) cin >> a[i];
}

void init() {
    FOR(i,1,n) v[i] = v1[i] = v2[i] = dem[i] = 0;
}

ll getV(ll u) {
    ll cnt = 0;
    if (u == 0) return cnt;
    while (u % p == 0) {
        u /= p;
        cnt++;
    }
    return cnt;
}

void solve() {
    input();
    init();

    BinaryIndexedTree bitNotDivSub(n), bitNotDivAdd(n), bitDiv(n), bitCntNotDiv(n);

    FOR(i,1,n) {
        ll x = a[i] % p;
        if (x != 0) {
            if (a[i] >= p) {
                v1[i] = getV(a[i] - x);
                v2[i] = getV(a[i] + x) - 1;
                bitNotDivSub.update(i, v1[i]);
                bitNotDivAdd.update(i, v2[i]);
                bitCntNotDiv.update(i, 1);
                dem[i] = 0;
            } else dem[i] = -1;
        } else {
            v[i] = getV(a[i]);
            dem[i] = 1;
            bitDiv.update(i, v[i]);
        }
    }

    FOR(o,1,q) {
        int ch, l, r, u;
        ll val, s;
        cin >> ch;
        if (ch == 1) {
            cin >> u >> val;

            if (dem[u] == 1) {
                bitDiv.update(u, -v[u]);
            } else if (dem[u] == 0) {
                bitNotDivSub.update(u, -v1[u]);
                bitNotDivAdd.update(u, -v2[u]);
                bitCntNotDiv.update(u, -1);
            }
            a[u] = val;

            ll x = a[u] % p;
            if (x != 0) {
                if (a[u] >= p) {
                    v1[u] = getV(a[u] - x);
                    v2[u] = getV(a[u] + x) - 1;
                    bitNotDivSub.update(u, v1[u]);
                    bitNotDivAdd.update(u, v2[u]);
                    bitCntNotDiv.update(u, 1);
                    dem[u] = 0;
                } else dem[u] = -1;
            } else {
                v[u] = getV(a[u]);
                dem[u] = 1;
                bitDiv.update(u, v[u]);
            }
        } else {
            cin >> s >> l >> r;
            ll res = (bitDiv.get(r) - bitDiv.get(l-1)) * s;
            ll num = getV(s);
            if (s % 2 == 0 && p == 2) {
                res += bitNotDivSub.get(r) - bitNotDivSub.get(l-1);
                res += bitNotDivAdd.get(r) - bitNotDivAdd.get(l-1);
            } else {
                res += bitNotDivSub.get(r) - bitNotDivSub.get(l-1);
            }
            res += (bitCntNotDiv.get(r) - bitCntNotDiv.get(l-1)) * num;
            cout << res << " ";
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        
        cout << "Case #" << o << ": ";
        solve();
        cout << "\n";
    }
    return 0;
}
