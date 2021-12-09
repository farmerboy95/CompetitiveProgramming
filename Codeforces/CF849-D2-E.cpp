/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's look at segment [l, r]. Let p1x < p2x < ... < pkx - positions of all occurences 
        of shape x at segment [l, r].
        - Then memory of shape x at segment [l, r] is 
            pkx - p1x = (pkx - p(k-1)x) + (p(k-1)x - p(k-2)x) + ... + (p2x - p1x)
        - Then we can build array of pairs b: b[i] = (prev(i), i - prev(i)), where prev(i) is 
        previous occurence of shape a[i]. Then a query transform to sum(b[i].second) (l <= i <= r and
        b[i].first >= l).
        - How can we manage a segment tree with this kind of query? After dividing query on log to 
        some nodes of segtree they transform to "get sum value of all b.first >= l from all elements 
        which are controlled by fixed node", so if you sort all b.first in fixed node you get query 
        on suffix.
        - At each node of the segment tree, we maintain a fenwick tree with all the related prev(i)
        (i inside the segment). We get through the input twice, the first time is for preparing the
        segment tree as well as the fenwick tree in each node of the segment tree. The second time
        we can solve the problem.
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
    int ch, x, y;
    Query(int ch = 0, int x = 0, int y = 0) : ch(ch), x(x), y(y) {}
};

int n, m, a[MAXN], A[MAXN], prv[MAXN];
Query q[MAXN];
set<int> id[MAXN];
vi vars[MAXN * 4];
vl bit[MAXN * 4];

void addBit(int k, int u, int val) {
    while (u) {
        bit[k][u] += val;
        u -= (u & (-u));
    }
}

ll getBit(int k, int u) {
    ll res = 0;
    while (u < SZ(bit[k])) {
        res += bit[k][u];
        u += (u & (-u));
    }
    return res;
}

void build(int k, int l, int r, int solveFlag = 0) {
    if (l > r) return;
    FOR(i,l,r) {
        if (!solveFlag) {
            vars[k].push_back(prv[i]);
        } else {
            int pos = lower_bound(ALL(vars[k]), prv[i]) - vars[k].begin() + 1;
            addBit(k, pos, i - prv[i]);
        }
    }
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(k*2, l, mid, solveFlag);
    build(k*2+1, mid+1, r, solveFlag);
}

void add(int k, int l, int r, int pos, int prvPos, int val, int solveFlag = 0) {
    if (l > r) return;
    if (!solveFlag) {
        vars[k].push_back(prvPos);
    } else {
        int tmpPos = lower_bound(ALL(vars[k]), prvPos) - vars[k].begin() + 1;
        addBit(k, tmpPos, val);
    }
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) add(k*2, l, mid, pos, prvPos, val, solveFlag);
    else add(k*2+1, mid+1, r, pos, prvPos, val, solveFlag);
}

ll get(int k, int l, int r, int u, int v, int leftBound) {
    if (l > r || r < u || v < l) return 0;

    if (u <= l && r <= v) {
        int pos = lower_bound(ALL(vars[k]), leftBound) - vars[k].begin() + 1;
        return getBit(k, pos);
    }
    
    int mid = (l + r) >> 1;
    return get(k * 2, l, mid, u, v, leftBound) + get(k * 2 + 1, mid+1, r, u, v, leftBound);
}

void eraseSets(int pos, int solveFlag = 0) {
    add(1,1,n,pos,prv[pos],-(pos - prv[pos]), solveFlag);
    id[A[pos]].erase(pos);
    auto it = id[A[pos]].lower_bound(pos);
    if (it != id[A[pos]].end()) {
        int pos2 = *it;
        add(1,1,n,pos2,prv[pos2],-(pos2 - prv[pos2]), solveFlag);
        prv[pos2] = prv[pos];
        add(1,1,n,pos2,prv[pos2],+(pos2 - prv[pos2]), solveFlag);
    }

    A[pos] = 0;
    prv[pos] = 0;
}

void insertSets(int pos, int val, int solveFlag = 0) {
    auto it = id[val].lower_bound(pos);
    if (it != id[val].end()) {
        int pos2 = *it;
        add(1,1,n,pos2,prv[pos2],-(pos2 - prv[pos2]), solveFlag);
        prv[pos2] = pos;
        add(1,1,n,pos2,prv[pos2],+(pos2 - prv[pos2]), solveFlag);
    }
    prv[pos] = 0;
    if (it != id[val].begin()) {
        it--;
        prv[pos] = *it;
    }
    add(1,1,n,pos,prv[pos],+(pos - prv[pos]), solveFlag);

    id[val].insert(pos);
    A[pos] = val;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    // input
    cin >> n >> m;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,m) cin >> q[i].ch >> q[i].x >> q[i].y;

    // prepare trees
    FOR(i,1,n) A[i] = a[i];
    vi latestPos(n+1, 0);
    FOR(i,1,n) {
        prv[i] = latestPos[A[i]];
        latestPos[A[i]] = i;
        id[A[i]].insert(i);
    }

    build(1,1,n);
    FOR(i,1,m) {
        if (q[i].ch == 1) {
            eraseSets(q[i].x);
            insertSets(q[i].x, q[i].y);
        }
    }

    // solve
    FOR(i,1,4*n) {
        remDup(vars[i]);
        bit[i].assign(SZ(vars[i])+1, 0);
    }
    FOR(i,1,n) id[i].clear();
    FOR(i,1,n) A[i] = a[i];
    latestPos.assign(n+1, 0);
    FOR(i,1,n) {
        prv[i] = latestPos[A[i]];
        latestPos[A[i]] = i;
        id[A[i]].insert(i);
    }
    build(1,1,n,1);
    FOR(i,1,m) {
        if (q[i].ch == 1) {
            eraseSets(q[i].x, 1);
            insertSets(q[i].x, q[i].y, 1);
        } else {
            cout << get(1,1,n,q[i].x,q[i].y,q[i].x) << "\n";
        }
    }

    return 0;
}
