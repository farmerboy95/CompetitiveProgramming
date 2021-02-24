/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/87294
        - https://codeforces.com/blog/entry/87294?#comment-756075
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

struct Info {
    int idx,val;
    friend bool operator<(Info u, Info v) {
        return u.val == v.val ? u.idx < v.idx : u.val < v.val;
    }
};

struct Star {
    int root;
    vi leaves;
};

int n, m, deg[MAXN], perm1[MAXN], perm2[MAXN];
set<int> a[MAXN], b[MAXN];
set<int> s;
set<Info> d;
vector<Star> res;

void dfs(int u) {
    // mark u visited by removing it from set
    s.erase(u);
    int x = 0;
    while (1) {
        // check the non-visited node
        auto it = s.upper_bound(x);
        if (it == s.end()) break;
        int v = *it;
        x = v;
        // if there is an edge (u, v) in graph G, check the next node
        if (a[u].find(v) != a[u].end()) continue;
        // add edge to DFS tree
        b[u].insert(v);
        b[v].insert(u);
        dfs(v);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    while (te--) {
        cin >> n >> m;
        FOR(i,1,n) {
            a[i].clear();
            b[i].clear();
        }
        // build graph G
        FOR(i,1,m) {
            int u, v;
            cin >> u >> v;
            a[u].insert(v);
            a[v].insert(u);
        }

        // build DFS tree
        // we are not going to build the graph G' but to create the DFS tree based on G' directly
        s.clear();
        FOR(i,1,n) s.insert(i);
        while (SZ(s)) {
            int u = *s.begin();
            dfs(u);
        }

        // d stores node and number of nodes adjacent to it in the tree
        d.clear();
        int remain = n;
        FOR(i,1,n) {
            deg[i] = SZ(b[i]);
            if (deg[i]) {
                // add it to d
                d.insert((Info) {i, deg[i]});
            } else {
                // deg[i] = 0 => the case p[i] = q[i]
                perm1[i] = perm2[i] = remain;
                remain--;
            }
        }

        res.clear();
        while (SZ(d)) {
            // choose an arbitrary leaf in the tree (idx)
            int idx = (*d.begin()).idx;
            // find its neighbor vertice f
            int f = *b[idx].begin();
            vi leaves;
            d.erase((Info) {f, deg[f]});
            TRAV(c, b[f]) {
                d.erase((Info) {c, deg[c]});
                // choose all neighbor vertices c of f with degree 1 to form a star
                if (deg[c] == 1) leaves.push_back(c);
                else {
                    // otherwise remove edge (c, f)
                    deg[c]--;
                    d.insert((Info) {c, deg[c]});
                    b[c].erase(f);
                }
            }
            // It can be shown that the remaining graph after deletion of this chosen star 
            // is still a tree with more than 1 vertices or empty
            // Therefore, we could decompose tree into stars applying this method recursively
            res.push_back((Star) {f, leaves});
        }

        // finally fill in numbers to each star
        // (1, k+1) (2, 1) (3, 2) (4, 3) ... for the first star
        // then continue with the same pattern with the next stars
        int l = 0, r = 0;
        TRAV(c, res) {
            perm1[c.root] = ++l;
            TRAV(c1, c.leaves) {
                perm1[c1] = ++l;
                perm2[c1] = ++r;
            }
            perm2[c.root] = ++r;
        }

        FOR(i,1,n) cout << perm1[i] << ' '; cout << "\n";
        FOR(i,1,n) cout << perm2[i] << ' '; cout << "\n";
    }
    return 0;
}
