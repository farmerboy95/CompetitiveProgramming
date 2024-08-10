/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - For each connected component, there are 2 ways of putting the animals, first is
        to put a cow and second is to put a bull in one node. The distribution of animals
        in the rest of the nodes in the connected component is determined by that filled node,
        as we can't put 2 animals of the same type in adjacent nodes.
        - So for each connected component, we can put x cows and y bulls in it, or y cows
        and x bulls in it, x+y = number of nodes in the connected component. But we have many
        connected components, which settings should we choose in those two in each connected
        component?
        - Let dp[i][j] = 1 if we can put i cows and j bulls in the connected components we have
        visited so far. The more connected components we visit, the larger sum of i and j we
        can have. So we can have a set of states in the previous connected components, and for
        each new connected component, we can update the set of states based on one of the two
        settings, meaning dp[i+x][j+y] = 1 or dp[i+y][j+x] = 1, and update the set of states.
        Note that we cannot ignore a component, so we cannot update the current set of states
        but to switch to a new set of states.
        - There's also a case when we cannot fill in a connected component at all, for example
        1-2, 2-3, 3-1. In this case we print "no".
        - At the end, if we see a state (b, c) in the set of states, we print "yes"
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

const int MAXN = 2010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int b, c, x, visited[MAXN], mark[MAXN];
vi a[MAXN];

void dfs(int u, vi &gr) {
    visited[u] = 1;
    gr.push_back(u);
    TRAV(v, a[u]) {
        if (!visited[v]) {
            dfs(v, gr);
        }
    }
}

pi tryOut(vi &gr, int x1, int x2) {
    queue<int> q;
    q.push(gr[0]);
    mark[gr[0]] = x1;
    while (SZ(q)) {
        int u = q.front();
        q.pop();
        TRAV(v, a[u]) {
            if (mark[v] != x1 && mark[v] != x2) {
                mark[v] = (mark[u] == x1) ? x2 : x1;
                q.push(v);
            } else {
                if (mark[v] == mark[u]) {
                    return {-1, -1};
                }
            }
        }
    }

    pi res = {0, 0};
    TRAV(u, gr) {
        if (mark[u] == x1) res.FI++;
        else res.SE++;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        cin >> b >> c >> x;
        FOR(i,1,b+c) {
            a[i].clear();
            visited[i] = 0;
            mark[i] = 0;
        }
        while (x--) {
            int u, v;
            cin >> u >> v;
            a[u].push_back(v);
            a[v].push_back(u);
        }

        set<pi> states;
        states.insert({0, 0});
        bool co = true;
        FOR(i,1,b+c) {
            if (!visited[i]) {
                vi gr;
                dfs(i, gr);
                pi tr = tryOut(gr, 1, 2);

                if (tr.FI == -1) {
                    co = false;
                    break;
                }

                set<pi> newStates;
                TRAV(s, states) {
                    if (s.FI + tr.FI <= b && s.SE + tr.SE <= c) {
                        newStates.insert({s.FI + tr.FI, s.SE + tr.SE});
                    }

                    if (s.FI + tr.SE <= b && s.SE + tr.FI <= c) {
                        newStates.insert({s.FI + tr.SE, s.SE + tr.FI});
                    }
                }

                swap(states, newStates);
            }
        }

        if (co && states.count({b, c})) cout << "yes\n";
        else cout << "no\n";
    }
    return 0;
}
