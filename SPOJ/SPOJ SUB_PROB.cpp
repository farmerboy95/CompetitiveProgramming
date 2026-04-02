/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Create suffix array on input array S, in this implementation takes
        about O(n log^2 n)
        - For each query string T, we binary search on suffix array to check 
        if T appears in S in O(m log n)
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

string s, t;
int n;
int RA[MAXN], SA[MAXN], PLCP[MAXN], LCP[MAXN], behind[MAXN], c[MAXN], tempSA[MAXN], tempRA[MAXN];

void countingSort(int k) {
    int sum = 0, maxi = max(300, n);
    memset(c, 0, sizeof(c));
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

void suffixArray() {
    int r;
    FOR(i,0,n-1) {
        SA[i] = i;
        RA[i] = s[i];
    }
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
        while (s[i+L] == s[behind[i]+L]) L++; PLCP[i] = L;
        L = max(L-1,0);
    }
    FOR(i,0,n-1) LCP[i] = PLCP[SA[i]];
}

bool matches() {
    if (SZ(t) > n-1) return false;
    int l = 0, r = n-1;

    while (l <= r) {
        int mid = (l + r) >> 1;
        int lef = SA[mid], rig = lef + SZ(t) - 1;
        int res = strncmp(&s[lef], &t[0], SZ(t));
        if (res == 0) return true;
        if (res > 0) r = mid - 1;
        else l = mid + 1;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> s;
    s = s + "$";
    n = SZ(s);
    suffixArray();
    buildLCP();

    int q;
    cin >> q;
    while (q--) {
        cin >> t;
        if (matches()) cout << "Y\n";
        else cout << "N\n";
    }
    return 0;
}
