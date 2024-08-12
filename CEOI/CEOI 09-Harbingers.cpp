/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Main idea from https://dmoj.ca/problem/ceoi09p2/editorial
        - Let dp[i] be the min cost to go from i to 1.
        - So dp[i] = min(dp[j] + s[i] + v[i] * |d[i] - d[j]|) for all j being ancestors of i
        and d[i] is the distance from 1 to i.
        - It means dp[i] = s[i] + min(dp[j] + v[i] * |d[i] - d[j]|), let a = |d[i] - d[j]|,
        b = dp[j], we have lines y = ax + b. These lines have decreasing slope so we can
        use convex hull trick to find the minimum value of y = ax + b for all lines.
        - When adding a new line, we need to remove all lines that are not useful in our
        convex hull. We can do this by binary search. Then fill the new line to the list of
        lines. But to restore the list of lines after we finish processing a node, we don't
        need to actually remove the lines from the list and add again, we can store something
        like a log to know what the value of the filled position was before we filled it.
        - When querying, again we use binary search to find the line that gives the minimum
        value of y = ax + b.
        - Complexity O(n log n)
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

const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct Line {
    // y = a * x + b
    ll a, b;
    Line(ll a = 0, ll b = 0) : a(a), b(b) {}
    ll getY(ll x) {
        return a * x + b;
    }
};

int n, curSize, lines[MAXN];
vpi a[MAXN];
ll s[MAXN], v[MAXN], dp[MAXN], d[MAXN];
vector<vi> logs;

inline ll getDist(int i, int j) {
    return abs(d[i] - d[j]);
}

inline bool isBad(int x, int y, int z, int u) {
    Line l1 = Line(getDist(x, u), dp[x]);
    Line l2 = Line(getDist(y, u), dp[y]);
    Line l3 = Line(getDist(z, u), dp[z]);
    // do not use multiplication to avoid overflow
    return (ld) (l3.b - l1.b) / (l1.a - l3.a) < (ld) (l2.b - l1.b) / (l1.a - l2.a);
}

void dfs(int u, int p) {
    if (u != 1) {
        // remove invalid lines
        int lef = 0, rig = curSize - 1;
        while (lef <= rig) {
            int mid = (lef + rig) >> 1;
            if (mid == 0) {
                if (dp[p] <= dp[lines[mid]]) {
                    rig = mid - 1;
                } else {
                    lef = mid + 1;
                }
            } else if (isBad(lines[mid-1], lines[mid], p, u)) {
                rig = mid - 1;
            } else {
                lef = mid + 1;
            }
        }

        // fill p to lef
        logs.push_back({u, lef, lines[lef], curSize});
        lines[lef] = p;
        curSize = lef + 1;

        // calculate dp[u]
        lef = 0, rig = curSize - 2;
        while (lef <= rig) {
            int mid = (lef + rig) >> 1;
            Line curLine = Line(getDist(lines[mid], u), dp[lines[mid]]);
            Line nextLine = Line(getDist(lines[mid+1], u), dp[lines[mid+1]]);
            if (curLine.getY(v[u]) < nextLine.getY(v[u])) {
                rig = mid - 1;
            } else {
                lef = mid + 1;
            }
        }

        dp[u] = s[u] + getDist(u, lines[lef]) * v[u] + dp[lines[lef]];
    }

    TRAV(x, a[u]) {
        int v = x.FI;
        if (v == p) continue;
        d[v] = d[u] + x.SE;
        dfs(v, u);
    }

    if (u != 1) {
        if (SZ(logs) && logs.back()[0] == u) {
            lines[logs.back()[1]] = logs.back()[2];
            curSize = logs.back()[3];
            logs.pop_back();
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n-1) {
        int u, v, c;
        cin >> u >> v >> c;
        a[u].push_back({v, c});
        a[v].push_back({u, c});
    }
    FOR(i,2,n) {
        cin >> s[i] >> v[i];
    }
    dp[1] = 0;
    curSize = 0;

    dfs(1, 0);

    FOR(i,2,n) cout << dp[i] << " ";
    cout << "\n";
    return 0;
}
