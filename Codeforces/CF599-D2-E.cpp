/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let dp[root][mask] be the number of ways to build a tree with root in vertex "root"
        using vertices from the mask "mask" and all restrictions are satisfied. For convenience,
        we shall number the vertices from zero.
        - The result is dp[0][(1 << n) - 1].
        - Base cases are dp[i][1 << i] = 1, obviously.
        - Let's solve this task recursively with memorization. To make the transition, we need 
        to choose some kind of mask "newMask", which is necessarily is the submask of mask "mask".
        Then we should try to find new root "newRoot" in mask "newMask". To avoid duplicates, we
        should always include the first set bit in "mask" in "newMask".
        - We then pick a "newRoot" in the set bits of "newMask", then check if all edges and LCAs
        satisfy the conditions. We shall check if edges are in input but cannot be in the current
        tree that we are building. We also check if the LCA requirements are satisfied.
            1. There should be no edge from current root to any of the nodes in "newMask", of course
            skipping the "newRoot".
            2. There should be no edge from any node in "newMask" to any node in "mask" ^ ("newMask" ^ root).
            3. There should be no LCA(u, v, w) with u and v in "mask" but w not in "mask".
            4. If u or v is root, w should be root.
            5. If u is in "mask" and v is in "mask" ^ ("newMask" ^ root) (or vice versa), w should be root.
            6. If u and v are in "newMask", w should be in "newMask".
        - Time: O(3^n * n * q)
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
string ts(bool b) { return (b ? "true" : "false"); }

template<class T> using V = vector<T>;
template<class T> string ts(complex<T> c);
string ts(V<bool> v);
template<size_t sz> string ts(bitset<sz> b);
template<class T> string ts(T v);
template<class T, class U> string ts(pair<T,U> p);
template<class ...U> string ts(tuple<U...> u);

template<class T> string ts(complex<T> c) { stringstream ss; ss << c; return ss.str(); }
string ts(V<bool> v) {string res = "{"; FOR(i,0,SZ(v)-1) res += char('0'+v[i]); res += "}"; return res; }
template<size_t sz> string ts(bitset<sz> b) { string res = ""; FOR(i,0,SZ(b)-1) res += char('0'+b[i]); return res; }
template<class T> string ts(T v) { // containers with begin(), end()
    bool fst = 1; string res = "";
    for (const auto& x: v) { if (!fst) res += " "; fst = 0; res += ts(x); }
    return res;
}
template<class T, class U> string ts(pair<T,U> p) { return "(" + ts(p.FI) + ", " + ts(p.SE) + ")"; }
template<size_t i, class T> string print_tuple_utils(const T& tup) { if constexpr(i == tuple_size<T>::value) return ")"; else return (i ? ", " : "(") + ts(get<i>(tup)) + print_tuple_utils<i + 1, T>(tup); }
template<class ...U> string ts(tuple<U...> u) { return print_tuple_utils<0, tuple<U...>>(u); }

// OUTPUT
template<class T> void pr(T x) { cout << ts(x); }
template<class T, class ...U> void pr(const T& t, const U&... u) { pr(t); pr(u...); }
void ps() { pr("\n"); } // print w/ spaces
template<class T, class ...U> void ps(const T& t, const U&... u) { pr(t); if (sizeof...(u)) pr(" "); ps(u...); }

// DEBUG
void DBG() { cerr << "]" << endl; }
template<class T, class ...U> void DBG(const T& t, const U&... u) { cerr << ts(t); if (sizeof...(u)) cerr << ", "; DBG(u...); }

#ifdef LOCAL_DEBUG
#define CONCAT(x, y) x##y
#define with_level setw(__db_level * 2) << setfill(' ') << "" << setw(0)
#define dbg(...) cerr << with_level << "Line(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#define chk(...) if (!(__VA_ARGS__)) cerr << setw(__db_level * 2) << setfill(' ') << "" << setw(0) << "Line(" << __LINE__ << ") -> function(" << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\n", exit(0);
#define db_block() debug_block CONCAT(dbbl, __LINE__)
int __db_level = 0;
struct debug_block {
    debug_block() { cerr << with_level << "{" << endl; ++__db_level; }
    ~debug_block() { --__db_level; cerr << with_level << "}" << endl; }
};
#else
#define dbg(...) 0
#define chk(...) 0
#define db_block() 0
#endif

const ld PI = acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
const ld EPS = 1e-9;
const ll MODBASE = 1000000007LL;
const int INF = 0x3f3f3f3f;

const int MAXN = 13;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, q, edgeMask[MAXN];
vpi edges;
vector<tuple<int, int, int>> lcaRequirements;
ll dp[MAXN][1<<MAXN];

ll solve(int root, int mask) {
    if (dp[root][mask] != -1) {
        return dp[root][mask];
    }

    ll &res = dp[root][mask];
    res = 0;

    int maskWithoutRoot = mask ^ (1<<root);
    int firstActive = -1;
    FOR(i,0,n-1) {
        if (maskWithoutRoot & (1<<i)) {
            firstActive = i;
            break;
        }
    }

    for (int submask = maskWithoutRoot; submask; submask = (submask-1) & maskWithoutRoot) {
        // must have firstActive to avoid duplicate
        if (!(submask & (1<<firstActive))) {
            continue;
        }

        FOR(i,0,n-1) {
            if (submask & (1<<i)) {
                int newRoot = i;

                // we have edge (root, newRoot)
                // but don't have edge (root, the other node in submask)
                if (edgeMask[root] & (submask ^ (1<<i))) {
                    continue;
                }

                bool co = true;
                FOR(j,0,SZ(edges)-1) {
                    int u, v;
                    tie(u, v) = edges[j];
                    if ((submask & (1<<u)) && ((maskWithoutRoot ^ submask) & (1<<v))) {
                        co = false;
                        break;
                    }
                    if ((submask & (1<<v)) && ((maskWithoutRoot ^ submask) & (1<<u))) {
                        co = false;
                        break;
                    }
                }

                if (!co) {
                    continue;
                }

                FOR(j,0,SZ(lcaRequirements)-1) {
                    int u, v, w;
                    tie(u, v, w) = lcaRequirements[j];
                    
                    if (!(mask & (1<<u))) continue;
                    if (!(mask & (1<<v))) continue;

                    if (!(mask & (1<<w))) {
                        co = false;
                        break;
                    }

                    if (u == root || v == root) {
                        if (w != root) {
                            co = false;
                            break;
                        }
                    } else {
                        if ((submask & (1<<u)) && ((maskWithoutRoot ^ submask) & (1<<v))) {
                            if (w != root) {
                                co = false;
                                break;
                            }
                        } else if ((submask & (1<<v)) && ((maskWithoutRoot ^ submask) & (1<<u))) {
                            if (w != root) {
                                co = false;
                                break;
                            }
                        } else if ((submask & (1<<v)) && (submask & (1<<u))) {
                            if (!(submask & (1<<w))) {
                                co = false;
                                break;
                            }
                        }
                    }
                }

                if (!co) {
                    continue;
                }

                res += solve(newRoot, submask) * solve(root, mask ^ submask);
            }
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> q;

    FOR(i,0,m-1) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        edgeMask[u] |= (1<<v);
        edgeMask[v] |= (1<<u);
        edges.push_back({u, v});
    }

    FOR(i,0,q-1) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        w--;
        if (u == v) {
            if (w != v) {
                cout << 0;
                return 0;
            }
            continue;
        }
        lcaRequirements.push_back({u, v, w});
    }

    FOR(i,0,n-1) FOR(j,0,(1<<n)-1) dp[i][j] = -1;
    FOR(i,0,n-1) dp[i][1<<i] = 1;

    cout << solve(0, (1<<n)-1) << "\n";
    return 0;
}
