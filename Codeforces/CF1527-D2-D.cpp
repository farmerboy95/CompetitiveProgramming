/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let our root be 0.
        - Let x = number of paths in total
        - Easily see that the number of mex-0 paths are the paths that not going through 0.
        We can calculate this easily. Remember to remove this result from x
        - What about mex-1? The path should go through 0 but not through 1. We can find
        a node 1 and calculate number of mex-larger-than-1 and get the remaining result from x.
        - In general, to get mex-k, we need to maintain a path that going through 0 to k-1. In that
        path, it may contain some other nodes that can affect our k (could increase our k). Let lef
        and rig are the endpoints of the path. Initially lef = rig = 0.
        - We have some cases, considering node i:
            + If the new node that we add is not creating a path with the current path => res[i] = x
            and get out of the loop as there would be no result from i+1 to n
            + If the new node can extend left or right endpoint, calculate res[i] carefully, then extend
            our endpoint, get new mex (we can maintain a BIT to calculate mex with binary search) and
            move i to the new mex.
            + Remember to remove the calculated result from x
            + Checking the above cases can be done by using LCA.
        - If x is still larger than 0 after the loop, it should be in res[n]
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

int n, d[MAXN], parent[MAXN][20], num[MAXN];
vi a[MAXN];
ll res[MAXN];

void dfs(int u, int p) {
    num[u] = 1;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (v == p) continue;
        d[v] = d[u]+1;
        parent[v][0] = u;
        dfs(v, u);
        num[u] += num[v];
    }
}

int lca(int u, int v) {
    if (d[v] < d[u]) FORE(i,17,0) if (d[parent[u][i]] >= d[v]) u = parent[u][i];
    if (d[u] < d[v]) FORE(i,17,0) if (d[parent[v][i]] >= d[u]) v = parent[v][i];
    FORE(i,17,0) if (parent[u][i] != parent[v][i]) { u = parent[u][i]; v = parent[v][i]; }
    while (u != v) { u = parent[u][0]; v = parent[v][0]; }
    return u;
}

ll getSum(ll u) {
    return u * (u-1) / 2;
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

int getMEX(BinaryIndexedTree &bit) {
    int dau = 1, cuoi = n;
    while (dau <= cuoi) {
        int mid = (dau + cuoi) >> 1;
        if (bit.get(mid) == mid) dau = mid+1;
        else cuoi = mid-1;
    }
    return cuoi;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    while (te--) {
        cin >> n;
        FOR(i,0,n-1) a[i].clear();
        FOR(i,1,n-1) {
            int u, v;
            cin >> u >> v;
            a[u].push_back(v);
            a[v].push_back(u);
        }
        parent[0][0] = 0;
        dfs(0, -1);
        FOR(j,1,17)
            FOR(i,1,n) parent[i][j] = parent[parent[i][j-1]][j-1];
        
        FOR(i,0,n) res[i] = 0;

        ll remain = getSum(n);
        TRAV(v, a[0]) {
            res[0] += getSum(num[v]);
        }
        remain -= res[0];
        BinaryIndexedTree bit(n);
        bit.update(1, 1);

        int lef = 0, rig = 0, highestLef = 0, highestRig = 0;
        FOR(i,1,n-1) {
            int checkLef = lca(i, lef);
            int checkRig = lca(i, rig);

            if (checkLef == lef) {
                int u = i, near = -1;
                while (u != lef) {
                    bit.update(u+1, 1);
                    near = u;
                    u = parent[u][0];
                }
                if (lef == 0) highestLef = near;
                ll leftSide = num[i], rightSide = 0;
                if (rig != 0) rightSide = num[rig];
                else rightSide = n - num[highestLef];

                res[i] = remain - leftSide * rightSide;
                remain -= res[i];
                lef = i;
                int mex = getMEX(bit);
                i = mex-1;
            } else if (checkRig == rig && lca(i, highestLef) != highestLef) {
                int u = i, near = -1;
                while (u != rig) {
                    bit.update(u+1, 1);
                    near = u;
                    u = parent[u][0];
                }
                if (rig == 0) highestRig = near;
                ll leftSide = 0, rightSide = num[i];
                if (lef != 0) leftSide = num[lef];
                else leftSide = n - num[highestRig];

                res[i] = remain - leftSide * rightSide;
                remain -= res[i];
                rig = i;
                int mex = getMEX(bit);
                i = mex-1;
            } else {
                // outer node
                res[i] = remain;
                remain = 0;
                break;
            }
        }
        res[n] = remain;

        FOR(i,0,n) cout << res[i] << ' ';
        cout << "\n";
    }
    return 0;
}
