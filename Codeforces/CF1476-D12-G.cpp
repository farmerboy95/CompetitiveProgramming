/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/87356
        - Mo's algorithm with updates (SQRT decomposition)
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

struct Query {
    int l, r, k, t, id;
    Query(int l = 0, int r = 0, int k = 0, int t = 0, int id = 0) : l(l), r(r), k(k), t(t), id(id) {}
};

int n, m, pos[MAXN], before[MAXN], after[MAXN], block[MAXN], res[MAXN], cnt[MAXN], ord[MAXN], c[MAXN];
vector<Query> qu;
vpi bounds;

bool cmp(const Query &a, const Query &b) {
    if (block[a.l] == block[b.l]) {
        if (block[a.r] == block[b.r]) return a.t < b.t;
        return block[a.r] < block[b.r];
    }
    return block[a.l] < block[b.l];
}

void del(int u) {
    int c = cnt[u];
    // decrease the right most element in ord which is equal to c -> c-1
    ord[bounds[c].SE]--;
    // if there is no c-1 in ord, create one for bounds
    if (bounds[c-1].FI == n) bounds[c-1].SE = bounds[c].SE;
    // update bounds[c-1]
    bounds[c-1].FI = bounds[c].SE;
    // if there is no c in ord after updating, clear in bounds[c]
    if (bounds[c].FI == bounds[c].SE) bounds[c].FI = n;
    // clear one c in bounds
    bounds[c].SE--;
    // update cnt
    cnt[u]--;
}

void add(int u) {
    int c = cnt[u];
    // increase the left most element in ord which is equal to c -> c+1
    ord[bounds[c].FI]++;
    // update bounds[c+1]
    bounds[c+1].SE = bounds[c].FI;
    // if there is no c+1 in ord, create one for bounds
    if (bounds[c+1].FI == n) bounds[c+1].FI = bounds[c].FI;
    // if there is no c in ord after updating, clear in bounds[c] (n-1 to make it fit with the below assignment)
    if (bounds[c].FI == bounds[c].SE) bounds[c].FI = n-1;
    // clear one c in bounds
    bounds[c].FI++;
    // update cnt
    cnt[u]++;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    // indicate block size, should be n^(2/3)
    int sz = 2154;
    vi a(n);
    FOR(i,0,n-1) {
        cin >> a[i];
        // get block idx of pos i
        block[i] = i / sz;
        // c is for recovering the array a later
        c[i] = a[i];
    }

    // bounds[x] contains left and right bounds of x in array ord where all numbers are equal to x
    // note that ord is array cnt sorted in descending order
    FOR(i,0,n-1) bounds.push_back({n, 0});
    // we initially have 0s in array ord, from 0 to n-1
    bounds[0] = {0, n-1};

    int numUpdates = 0, numQueries = 0;
    FOR(i,0,m-1) {
        int ch, u, v, c;
        cin >> ch;
        if (ch == 1) {
            cin >> u >> v >> c;
            u--; v--;
            numQueries++;
            qu.push_back(Query(u, v, c, numUpdates, numQueries));
        } else {
            cin >> u >> c;
            u--;
            numUpdates++;
            // get position, value before and after update
            pos[numUpdates] = u;
            before[numUpdates] = a[u];
            after[numUpdates] = c;
            a[u] = c;
        }
    }
    // recover array a
    FOR(i,0,n-1) a[i] = c[i];

    // sort query array
    sort(ALL(qu), cmp);
    // start to move
    int L = 0, R = -1, T = 0;
    for (Query x : qu) {
        while (T > x.t) {
            if (L <= pos[T] && pos[T] <= R) {
                del(after[T]);
                add(before[T]);
            }
            a[pos[T]] = before[T];
            T--;
        }
        while (T < x.t) {
            T++;
            if (L <= pos[T] && pos[T] <= R) {
                del(before[T]);
                add(after[T]);
            }
            a[pos[T]] = after[T];
        }
        while (L > x.l) add(a[--L]);
        while (R < x.r) add(a[++R]);
        while (L < x.l) del(a[L++]);
        while (R > x.r) del(a[R--]);
        int kq = n;

        // use 2-pointer to get the result, it's O(sqrt(n)) here, as there are no more than the 
        // same amount of different values in ord
        for (int i = 0, j = 0, sum = 0; i < n && ord[i] > 0; i = bounds[ord[i]].SE + 1) {
            while (j < n && ord[j] > 0 && sum < x.k) {
                sum += bounds[ord[j]].SE - bounds[ord[j]].FI + 1;
                j = bounds[ord[j]].SE + 1;
            }
            if (sum >= x.k) kq = min(kq, ord[i] - ord[j - 1]);
            sum -= bounds[ord[i]].SE - bounds[ord[i]].FI + 1;
        }

        if (kq == n) kq = -1;
        res[x.id] = kq;
    }

    FOR(i,1,numQueries) cout << res[i] << "\n";
    return 0;
}
