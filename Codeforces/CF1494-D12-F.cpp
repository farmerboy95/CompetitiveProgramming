/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/88344
        - Split the graph into 2 graphs G1 and G2, the first graph contains the edges we delete
        before mode shift, the second graph contains the edges we delete after mode shift.
        - G1 has an eulerian path, G2 is a star graph.
        - Choose the center of G2, let's construct G2 in such a way that we minimize the number 
        of odd vertices in G1
        - If there is an eulerian path in G1 that ends in the center, we are done. Otherwise,
        we should iterate on some edge adjacent to the center and change its status. Notice that
        we can't flip 2 edges, so we flip each one and check for the eulerian path in G1.
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

const int MAXN = 3010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m;
set<int> a[MAXN], b[MAXN];
vi res;

// hierholzer's algorithm from CP4 book
void hierholzer(int start) {
    stack<int> st;
    st.push(start);
    while (SZ(st)) {
        int u = st.top();
        if (SZ(b[u])) {
            int v = *b[u].begin();
            st.push(v);
            b[u].erase(v);
            b[v].erase(u);
        } else {
            res.push_back(u);
            st.pop();
        }
    }
    reverse(ALL(res));
}

bool check(int center) {
    FOR(i,1,n) b[i] = a[i];
    res.clear();
    hierholzer(center);
    reverse(ALL(res));

    // number of edge + 1 should be equal to the length of the path
    int numOfEdge = 0;
    FOR(i,1,n) numOfEdge += SZ(a[i]);
    numOfEdge /= 2;

    FOR(i,1,n) b[i] = a[i];
    FOR(i,1,SZ(res)-1) {
        int u = res[i-1], v = res[i];
        // there should be an edge (u, v)
        if (!b[u].count(v)) return false;
        b[u].erase(v);
        b[v].erase(u);
    }
    return numOfEdge + 1 == SZ(res);
}

void printResult() {
    cout << SZ(res) << "\n";
    TRAV(x, res) cout << x << ' ';
    exit(0);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        a[u].insert(v);
        a[v].insert(u);
    }

    FOR(center,1,n) {
        set<int> tmp = a[center];
        set<int> G2;
        // let's construct G2 in such a way that we minimize the number of odd vertices in G1
        TRAV(v, tmp)
            if (SZ(a[v]) % 2) {
                a[v].erase(center);
                a[center].erase(v);
                G2.insert(v);
            }
        
        // if the graph G1 has an eulerian path, we are done
        if (check(center)) {
            res.push_back(-1);
            TRAV(x, G2) {
                res.push_back(x);
                res.push_back(center);
            }
            printResult();
        }
        
        // flip each edge
        TRAV(v, tmp) {
            if (a[center].count(v)) {
                a[center].erase(v);
                a[v].erase(center);
                G2.insert(v);
            } else {
                a[center].insert(v);
                a[v].insert(center);
                G2.erase(v);
            }

            if (check(center)) {
                res.push_back(-1);
                TRAV(x, G2) {
                    res.push_back(x);
                    res.push_back(center);
                }
                printResult();
            }

            if (a[center].count(v)) {
                a[center].erase(v);
                a[v].erase(center);
                G2.insert(v);
            } else {
                a[center].insert(v);
                a[v].insert(center);
                G2.erase(v);
            }
        }

        // remember to merge G1 and G2 to go to consider the next center
        TRAV(v, G2) {
            a[center].insert(v);
            a[v].insert(center);
        }
    }
    cout << 0;
    return 0;
}
