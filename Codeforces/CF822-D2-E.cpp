/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let dp[i][j] be the maximum length of the prefix of string t after processing
            + first i characters of string s
            + found first j groups
        - Initially, dp[0][0] = 0, others are -INF
        - dp[i+1][j] = max(dp[i+1][j], dp[i][j]) when we don't add a new group
        - Otherwise, we find the longest common prefix of s[i...] and t[dp[i][j]...], how?
        We can use a suffix array of the string s + "$" + t + "#, then use RMQ to find the 
        longest common prefix of two suffixes. Let the longest common prefix be lcp, so
        dp[i+lcp][j+1] = max(dp[i+lcp][j+1], dp[i][j] + lcp) when i+lcp <= n and j+1 <= x
        - But what if the new group does not take the whole LCP? It should take because if
        we take a prefix of that LCP, the rest can be found possibly in the next group and
        the result can only be worse.
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

struct SuffixArray {
    int n;
    vi SA, RA, tempRA, tempSA, c, LCP, PLCP, behind;
    string str;
    vector<vi> Min;

    SuffixArray(string &s) {
        n = SZ(s);
        str = s;
        SA.resize(n, 0);
        RA.resize(n, 0);
        tempRA.resize(n, 0);
        tempSA.resize(n, 0);
        c.resize(max(300, n), 0);
        LCP.resize(n, 0);
        PLCP.resize(n, 0);
        behind.resize(n, 0);
        Min.resize(n, vi(int(log2(n))+1, 0));
        build();
        buildLCP();
        buildRMQ();
    }

    void countingSort(int k) {
        int sum = 0, maxi = max(300, n);
        FOR(i,0,maxi-1) c[i] = 0;
        FOR(i,0,n-1)
            if (i+k < n) c[RA[i+k]]++;
            else c[0]++;
        FOR(i,0,maxi-1) {
            int t = c[i];
            c[i] = sum;
            sum += t;
        }
        FOR(i,0,n-1) {
            int a = 0;
            if (SA[i]+k < n) a = RA[SA[i]+k];
            tempSA[c[a]++] = SA[i];
        }
        FOR(i,0,n-1) SA[i] = tempSA[i];
    }

    void build() {
        int r;
        FOR(i,0,n-1) SA[i] = i;
        FOR(i,0,n-1) RA[i] = str[i];
        for (int k = 1; k < n; k <<= 1) {
            countingSort(k);
            countingSort(0);
            tempRA[SA[0]] = r = 0;
            FOR(i,1,n-1) {
                if (RA[SA[i]] != RA[SA[i-1]]) {
                    tempRA[SA[i]] = ++r;
                    continue;
                }
                int a, b;
                if (SA[i]+k >= n) a = 0;
                else a = RA[SA[i]+k];
                if (SA[i-1]+k >= n) b = 0;
                else b = RA[SA[i-1]+k];
                if (a == b) tempRA[SA[i]] = r;
                else tempRA[SA[i]] = ++r;
            }
            FOR(i,0,n-1) RA[i] = tempRA[i];
            if (r == n-1) break;
        }
    }

    void buildLCP() {
        behind[SA[0]] = -1;
        FOR(i,1,n-1) behind[SA[i]] = SA[i-1];
        int L = 0;
        FOR(i,0,n-1) {
            if (behind[i] == -1) {
                PLCP[i] = 0;
                continue; 
            }
            while (str[i+L] == str[behind[i]+L]) L++;
            PLCP[i] = L;
            L = max(L-1,0);
        }
        FOR(i,0,n-1) LCP[i] = PLCP[SA[i]];
    }

    void print() {
        FOR(i,0,n-1) cout << SA[i] << ' ' << str.substr(SA[i]) << ' ' << LCP[i] << "\n";
    }

    void buildRMQ() {
        FOR(i,0,n-1) Min[i][0] = LCP[i];
        
        for (int k = 1; (1<<k) <= n; k++)
            for (int i = 0; i + (1<<k) - 1 < n; i++) {
                Min[i][k] = min(Min[i][k-1], Min[i+(1<<(k-1))][k-1]);
            }
    }

    int getLCP(int u, int v) {
        if (u == v) return n - u;
        u = RA[u];
        v = RA[v];
        if (u > v) swap(u, v);

        int l = u+1, r = v;
        int k = log2(r-l+1);

        return min(Min[l][k], Min[r-(1<<k)+1][k]);
    }
};

int n, m, x;
string s, t;
int dp[MAXN][31];
// dp[i][j] = max length of prefix of string t after processing
// - first i characters of string s
// - found first j groups

int solve() {
    string S = s + "$" + t + "#";
    SuffixArray sa(S);

    FOR(i,0,n) FOR(j,0,x) dp[i][j] = -INF;
    dp[0][0] = 0;

    FOR(i,0,n-1) {
        FOR(j,0,x) {
            if (dp[i][j] == -INF) continue;
            dp[i+1][j] = max(dp[i+1][j], dp[i][j]);

            int posS = i;
            int posT = n + 1 + dp[i][j];

            int lcp = sa.getLCP(posS, posT);

            if (lcp && i+lcp <= n && j+1 <= x) {
                dp[i+lcp][j+1] = max(dp[i+lcp][j+1], dp[i][j] + lcp);
            }
        }
    }

    FOR(i,0,n) FOR(j,0,x)
        if (dp[i][j] == m) return 1;
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> s >> m >> t >> x;

    if (solve()) cout << "YES";
    else cout << "NO";
    return 0;
}
