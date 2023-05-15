/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Given two animals, we want to be able to look up whether we know the relationship 
        between them. Let's say R(x, y) = 1 if x can eat y, 0 if x and y are of the same 
        kind, or -1 if y can eat x. For a given pair (x, y), we may or may not know R(x, y). 
        What you should observe is that:
            + Each edge we're given in the input tells us the value of R(x, y) for the two 
            vertices x, y.
            + If we know R(a, b) and R(b, c), then we automatically know R(a, c). In fact, 
            its value is R(a, b) + R(b, c), modulo 3.
            + Therefore, when we add a new edge, if it joins together two components into 
            a single component, then it gives us information about the relationship between 
            every vertex in one component and every vertex in the other.
        - The way we can keep track of all this information efficiently is as follows: we 
        remember for each node u not only its parent pointer but also the value R(u, p[u]) 
        where p[u] is the parent of u. We can get the value R(u, r) by adding up all the 
        R values along parent edges as we climb from u to the root r. 
        - For any two u, v in the same component, we can get the value R(u, v) using the 
        formula R(u, v) = R(u, r) - R(v, r). 
        - When we get a new edge (u, v), we can first of all calculate whether the value 
        given for R(u, v) contradicts our already known value. If not, then let u's root 
        be r, and v's root be s. Then R(r, s) = R(u, v) - R(u, r) + R(v, s), so if you 
        choose to make s the parent of r, you can set R(r, p[r]) using this formula 
        (or set R(s, p[s]) to the negative of this, if you want to join the other way).
        - The mod 3 is necessary because R values are not really integers, but rather 
        equivalence classes mod 3. If A can eat B, B can eat C, and C can eat D, you know 
        that A and D are really the same type. So an R value of 3 is the same as an R value 
        of 0.
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

const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct DisjointSetUnion {
  public:
    // creates an undirected graph with n vertices and 0 edges.
    DisjointSetUnion() : _n(0) {}
    DisjointSetUnion(int n) : _n(n), parent_or_size(n, -1), sum_to_parent(n, 0) {}

    // add an edge (u, v)
    // If the vertices u and v were in the same connected component, 
    // it returns the representative of this connected component. 
    // Otherwise, it returns the representative of the new connected component.
    int merge(int u, int v, int distRUtoRV) {
        assert(0 <= u && u < _n);
        assert(0 <= v && v < _n);
        int x = leader(u), y = leader(v);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) {
            swap(x, y);
        } else {
            // relationship is from root u to root v, so it we merge v to u, need to reverse the relationship
            distRUtoRV = (3 - distRUtoRV) % 3;
        }
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        sum_to_parent[y] = distRUtoRV;
        return x;
    }

    // It returns whether the vertices u and v are in the same connected component
    bool same(int u, int v) {
        assert(0 <= u && u < _n);
        assert(0 <= v && v < _n);
        return leader(u) == leader(v);
    }

    // It returns the representative of the connected component that contains the vertex u
    int leader(int u) {
        assert(0 <= u && u < _n);
        if (parent_or_size[u] < 0) {
            return u;
        }
        int curSum = sum_to_parent[u];
        int par = parent_or_size[u];
        parent_or_size[u] = leader(parent_or_size[u]);
        sum_to_parent[u] = (curSum + sum_to_parent[par]) % 3;
        return parent_or_size[u];
    }

    int getDistanceToLeader(int u) {
        assert(0 <= u && u < _n);
        leader(u);
        return sum_to_parent[u];
    }

    // It returns the size of the connected component that contains the vertex u
    int size(int u) {
        assert(0 <= u && u < _n);
        return -parent_or_size[leader(u)];
    }

    // It divides the graph into connected components and returns the list of them
    vector<vector<int>> groups() {
        vector<int> leader_buf(_n), group_size(_n);
        FOR(i,0,_n-1) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        vector<vector<int>> result(_n);
        FOR(i,0,_n-1) result[i].reserve(group_size[i]);
        FOR(i,0,_n-1) result[leader_buf[i]].push_back(i);
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

  private:
    int _n;
    vector<int> parent_or_size, sum_to_parent;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    while (te--) {
        int n, k;
        cin >> n >> k;
        int res = 0;
        DisjointSetUnion dsu(n);
        FOR(i,1,k) {
            int ch, x, y;
            cin >> ch >> x >> y;
            if (x > n || y > n) {
                res++;
                continue;
            }

            x--;
            y--;

            if (ch == 1) {
                // x and y are the same
                if (dsu.same(x, y)) {
                    int distX = dsu.getDistanceToLeader(x);
                    int distY = dsu.getDistanceToLeader(y);
                    // R(u, v) = R(u, r) - R(v, r)
                    int relationship = (distX - distY + 3) % 3;
                    // x and y are the same, so R(u, v) should be 0
                    if (relationship) {
                        res++;
                    }
                } else {
                    int distX = dsu.getDistanceToLeader(x);
                    int distY = dsu.getDistanceToLeader(y);
                    // root u = r, root v = s
                    // R(r, s) = R(u, v) - R(u, r) + R(v, s)
                    // R(u, v) = 0
                    int distRXtoRY = (distY - distX + 3) % 3;
                    dsu.merge(x, y, distRXtoRY);
                }
            } else {
                if (x == y) {
                    res++;
                    continue;
                }
                // x can eat y
                if (dsu.same(x, y)) {
                    int distX = dsu.getDistanceToLeader(x);
                    int distY = dsu.getDistanceToLeader(y);
                    // R(u, v) = R(u, r) - R(v, r)
                    int relationship = (distX - distY + 3) % 3;
                    // x can eat y, so R(u, v) should be 1
                    if (relationship != 1) {
                        res++;
                    }
                } else {
                    int distX = dsu.getDistanceToLeader(x);
                    int distY = dsu.getDistanceToLeader(y);
                    // root u = r, root v = s
                    // R(r, s) = R(u, v) - R(u, r) + R(v, s)
                    // R(u, v) = 1
                    int distRXtoRY = ((1 + distY) % 3 - distX + 3) % 3;
                    dsu.merge(x, y, distRXtoRY);
                }
            }
        }
        cout << res << "\n";
    }
    return 0;
}
