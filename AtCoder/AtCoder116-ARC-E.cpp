/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We binary search the result, for each max depth x, we try to separate the tree
        into minimum number of subtrees so that the max of min depth of each tree <= x,
        finally we compare the number of subtrees with k to see where we should go next
        in the binary search.
        - So we are going to do it from the root of the big tree in O(n), in each subtree 
        of u, we store the following information:
            + The closest root of one of the subtree from u (as closest)
            + The furthest uncovered node (as furthest)
            + The number of roots that we have chosen.
        - Note that the subtree v that has a closest node can also have a furthest node too,
        as the closest node cannot cover the furthest node
        - This seems to be a dp solution but it's just that we fill in the root of the subtree
        whenever we must do and update closest and furthest info of the current node.
        - Finally at the root of the big tree, if there is any uncovered node, take it
        as the root of the subtree.
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

int n, k, closest[MAXN], furthest[MAXN], num;
vi a[MAXN];

inline void setSpecial(int u) {
    num++;
    closest[u] = 0;
    furthest[u] = -1;
}

void dfs(int u, int p, int x) {
    closest[u] = -1; furthest[u] = -1;

    // get closest special vertex
    TRAV(v, a[u]) {
        if (v == p) continue;
        dfs(v, u, x);
        if (closest[v] != -1) {
            if (closest[u] == -1 || closest[u] > closest[v] + 1) {
                closest[u] = closest[v] + 1;
            }
        }
    }

    // get furthest non-special vertex
    TRAV(v, a[u]) {
        if (v == p) continue;
        if (furthest[v] != -1) {
            if (furthest[u] == -1 || furthest[u] < furthest[v] + 1) {
                furthest[u] = furthest[v] + 1;
            }
        }
    }

    // no furthest? so it should be the current node u as we don't know if it's covered yet
    if (furthest[u] == -1) {
        furthest[u] = 0;
    }

    if (closest[u] == -1) {
        // no special vertex in the subtree of u so far
        if (furthest[u] == x) {
            setSpecial(u);
        }
    } else {
        if (furthest[u] == x || closest[u] == 2 * x + 1) {
            // set special when it reaches the limit
            setSpecial(u);
        } else if (closest[u] > x) {
            // update furthest
            ckmax(furthest[u], closest[u] - x - 1);
        } else {
            // check if the closest special node can cover the furthest node
            int remain = x - closest[u];
            if (remain >= furthest[u]) {
                furthest[u] = -1;
            }
        }
    }

    // check if there is leftover at root of big tree
    if (u == 1 && furthest[u] != -1) {
        num++;
    }
}

bool check(int x) {
    num = 0;
    dfs(1, 0, x);
    return num <= k;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    int dau = 0, cuoi = n;
    while (dau <= cuoi) {
        int mid = (dau + cuoi) >> 1;
        if (check(mid)) cuoi = mid-1;
        else dau = mid+1;
    }
    cout << dau;
    return 0;
}
