/*
    Keywords: shortest path, ford bellman, inequalities
    Đề bài:
        - Cho một số bất phương trình dạng x[j] - x[i] <= b[ij]
        - Tìm một lời giải cho nó
    Lời giải:
        - Mỗi biến x[i] ứng với 1 node v[i]
        - Mỗi điều kiện x[j] - x[i] <= b[ij] ứng với 1 cạnh từ v[i] đến v[j] với trọng
        số b[ij]
        - Thêm 1 node v[0] và thêm cạnh từ node này đến tất cả các node, trọng số là 0
        (không dùng cho lời giải bên dưới)
        - Nếu Ford Bellman cho ra chu trình âm, ta khẳng định rằng không có đáp án, 
        ngược lại x[i] = dist[v[i]] (chứng minh trong file pdf) (dist[w] <= dist[v] + c(v, w))
        - Ở dưới là bài giải cho task AtCoder216-ABC-G
    Nguồn: 
        - https://www.cs.huji.ac.il/course/2002/dast/slides/BellmanFord.pdf
        - https://codeforces.com/blog/entry/94366
        - https://atcoder.jp/contests/abc216/tasks/abc216_g
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

struct Data {
    int l, r, x;
    Data(int l = 0, int r = 0, int x = 0) : l(l), r(r), x(x) {}
};

int n, m, res[MAXN];
Data a[MAXN];
vpi g[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    // B[i] = sum(A[i]), the prefix sum
    // 1. B[R[j]] - B[L[j]-1] >= X[j] for all j
    // 2. B[i] - B[i-1] >= 0
    // 3. B[i] - B[i-1] <= 1

    // x[j] - x[i] <= b[ij] -> edge from v[i] to v[j] with weight b[ij]

    cin >> n >> m;
    FOR(i,1,n) {
        g[i].push_back({i-1, 0});
    }
    FOR(i,1,m) {
        int l, r, x;
        cin >> l >> r >> x;
        g[r].push_back({l-1, -x});
    }

    vi d(n+1);
    bool changed = true;
    while (changed) {
        changed = false;
        FORE(i,n,0) {
            for (auto& [u,to] : g[i]) {
                if (d[u] > d[i] + to) changed = true;
                ckmin(d[u], d[i] + to);
            }
        }
        FOR(i,0,n-1) {
            if (d[i] + 1 < d[i+1]) changed = true;
            ckmin(d[i+1], d[i] + 1);
        }
    }
    FOR(i,1,n) {
        int x = d[i] - d[i-1];
        cout << x << ' ';
    }
    return 0;
}
