/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Submitted at: https://www.e-olymp.com/en/problems/5650
        - https://blog.csdn.net/weixin_30767921/article/details/99328332
        - https://www.csc.kth.se/~austrin/icpc/finals2013solutions.pdf
        - The main idea is to realize that because both rotations and reflections of 
        pieces are allowed, the geometry of the problem is completely irrelevant. 
        That is, it suffices to check if there is an infinite chain of pieces P1, 
        P2, . . . such that Pi can be connected to Pi+1. If such a chain exists then
        using rotations and reflections it can always be laid out in such a way that 
        only the adjacent pieces touch each other (e.g. you can make it so that you 
        always go upwards or to the right). If such a chain doesn’t exist then clearly 
        the answer is “bounded”.
        - This reduces the problem to checking for cycles in a graph that consists 
        of the n <= 40 000 pieces. This is however still too much, but there is one 
        small additional trick: only the connections matter, so you can consider the 
        graph consisting only of 2 x 26 nodes A+, A−, ..., Z+, Z−.
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

const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int A[52][52], visited[52];

void connect(char a, char b, char c, char d) {
    if (a == '0' || c == '0') return;
    int u = (a - 'A') * 2 + (b == '+' ? 1 : 0);
    int v = (c - 'A') * 2 + (d == '+' ? 1 : 0);
    A[u][v^1] = 1;
}

bool dfs(int u) {
    visited[u] = 2;
    FOR(v,0,51)
        if (A[u][v]) {
            if (visited[v] == 2) return 1;
            else if (!visited[v] && dfs(v)) return 1;
        }
    visited[u] = 1;
    return 0;
}

bool cycle() {
    FOR(i,0,51) visited[i] = 0;
    FOR(i,0,51)
        if (!visited[i])
            if (dfs(i)) return 1;
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n;
    cin >> n;
    FOR(i,1,n) {
        string s;
        cin >> s;
        FOR(i,0,3)
            FOR(j,0,3)
                if (i != j) connect(s[i*2], s[i*2+1], s[j*2], s[j*2+1]);
    }
    if (cycle()) cout << "unbounded";
    else cout << "bounded";
    return 0;
}
