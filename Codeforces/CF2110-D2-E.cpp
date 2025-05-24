/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's construct a bipartite graph, where all possible volumes of sounds are 
        on the left and pitches are on the right. Then a pair of vertices (p, v) will 
        be connected by an edge if the musical instrument can produce the sound (p, v)
        - Notice that each path in such a graph represents beautiful music. This is 
        because any two adjacent edges share a common vertex, meaning they either 
        have the same volume or the same pitch. Also, this music is not boring, as no 
        three consecutive edges share any common vertices, meaning they cannot have a 
        common volume or pitch.
        - Now, notice that music consisting of all sounds is an Eulerian path in our 
        graph. Thus, we have reduced our problem to the standard problem of finding 
        an Eulerian path.
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

const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n;
set<pi> adj[MAXN*2];
pi a[MAXN];
map<pi, int> f;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    while (te--) {
        cin >> n;
        f.clear();
        FOR(i,1,n) {
            int x, y;
            cin >> x >> y;
            a[i] = {x, y+1000000000};
            f[a[i]] = i;
        }

        // create a bipartite graph to connect volumes and pitches for each sound
        // first we need to re-index the values to make the number of nodes small
        vi c;
        FOR(i,1,n) {
            c.push_back(a[i].FI);
            c.push_back(a[i].SE);
        }
        remDup(c);
        int m = SZ(c);
        FOR(i,1,n) {
            a[i].FI = lower_bound(ALL(c), a[i].FI) - c.begin();
            a[i].SE = lower_bound(ALL(c), a[i].SE) - c.begin();
        }
        FOR(i,0,m-1) {
            adj[i].clear();
        }
        // add edges with the index
        FOR(i,1,n) {
            adj[a[i].FI].insert({a[i].SE, i});
            adj[a[i].SE].insert({a[i].FI, i});
        }

        // find eulerian path
        // first we need to take out odd-degree nodes
        vi odd;
        FOR(i,0,m-1) {
            if (SZ(adj[i]) % 2 == 1) odd.push_back(i);
        }

        // to find eulerian path, the graph should have 0 or 2 odd-degree nodes
        if (SZ(odd) != 2 && SZ(odd) != 0) {
            cout << "NO\n";
            continue;
        }

        // start at one of the odd-degree node when there are some
        // otherwise start at one of the nodes with edges
        int start = 0, en = -1;
        if (SZ(odd) == 2) {
            start = odd[0];
            en = odd[1];
        } else {
            FOR(i,0,m-1) {
                if (SZ(adj[i]) > 0) {
                    start = i;
                    break;
                }
            }
        }

        if (SZ(adj[start]) == 0) {
            cout << "NO\n";
            continue;
        }

        // add one more edge to find eulerian cycle
        if (SZ(odd) == 2) {
            adj[odd[0]].insert({odd[1], 0});
            adj[odd[1]].insert({odd[0], 0});
        }

        // start to find eulerian path
        stack<int> st;
        st.push(start);
        vi res;
        while (!st.empty()) {
            int v = st.top();
            if (SZ(adj[v]) == 0) {
                res.push_back(v);
                st.pop();
            } else {
                int u = adj[v].begin()->FI;
                int id = adj[v].begin()->SE;
                adj[v].erase(adj[v].begin());
                adj[u].erase({v, id});
                st.push(u);
            }
        }

        // if there is any edge left, we can't find eulerian path
        bool co = true;
        FOR(i,0,m-1) {
            if (SZ(adj[i]) > 0) {
                co = false;
                break;
            }
        }
        if (!co) {
            cout << "NO\n";
            continue;
        }

        // otherwise, yes, we can find an eulerian path
        cout << "YES\n";
        vi e;
        // remove the last node because it's the same as first node
        res.pop_back();

        // there would be an edge we would not use when there are odd-degree nodes
        int s = 0;
        FOR(i,0,SZ(res)-1) {
            int x = res[i], y = res[(i+1) % SZ(res)];
            if ((x == start && y == en) || (x == en && y == start)) {
                s = (i+1) % SZ(res);
                break;
            }
        }
        vi kq;
        for (int i = s; i != (s - 1 + SZ(res)) % SZ(res); i = (i + 1) % SZ(res)) {
            kq.push_back(res[i]);
        }
        kq.push_back(res[(s - 1 + SZ(res)) % SZ(res)]);

        // if there are odd-degree nodes, we would not use the last edge
        FOR(i,0,SZ(kq)-1-(SZ(odd)==2)) {
            int x = kq[i], y = kq[(i+1) % SZ(kq)];
            int realNumX = c[x], realNumY = c[y];
            if (realNumX > realNumY) swap(realNumX, realNumY);
            int id = f[{realNumX, realNumY}];
            e.push_back(id);
        }

        FOR(i,0,SZ(e)-1) cout << e[i] << " ";
        cout << "\n";
    }
    return 0;
}
