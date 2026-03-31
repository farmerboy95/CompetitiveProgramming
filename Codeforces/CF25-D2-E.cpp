/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - There are a few cases:
            - If 2 of the strings are substrings of the last string, return length of that
            last string
            - If one string is substring of one of the two other strings, try to place those
            two remaining strings next to each other, find the longest suffix of the left
            string that matches the prefix of the right string.
            - Otherwise, we try all permutations of placing 3 strings next to each other and 
            find the minimum length by that prefix / suffix matching logic.
        - We can use hashing for string matching.
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

struct HashModule {
    ll mod;
    vl pw, h;
    int n;

    void init(string &s, ll bas, ll p) {
        mod = p;
        n = SZ(s);
        pw.resize(n+1);
        h.resize(n);
        pw[0] = 1;
        FOR(i,1,n) pw[i] = (pw[i-1] * bas) % mod;
        h[0] = s[0] - 'a' + 1;
        FOR(i,1,n-1) h[i] = (h[i-1] * bas + s[i] - 'a' + 1) % mod;
    }

    ll query(ll l, ll r) {
        if (!l) return h[r];
        return (h[r] - h[l-1] * pw[r-l+1] + mod * mod) % mod; 
    }
};

struct SingleHash {
    HashModule hm;
    void init(string &s, ll base1, ll mod1) {
        hm.init(s, base1, mod1);
    }
    ll query(ll l, ll r) {
        return hm.query(l,r);
    } 
};

string s[3];
bool subs[3][3];
vector<SingleHash> hs(3);

int check(int x, int y) {
    int minSz = min(SZ(s[x]), SZ(s[y]));
    FORE(len,minSz,1) {
        if (hs[x].query(SZ(s[x])-len, SZ(s[x])-1) == hs[y].query(0, len-1)) {
            return SZ(s[x]) + SZ(s[y]) - len;
        }
    }

    return SZ(s[x]) + SZ(s[y]);
}

int solve() {
    // find the shortest length of the string that has s0, s1, s2 as substrings
    int res = INF;
    vi order = {0, 1, 2};
    FOR(i,0,2) hs[i].init(s[i], 31, 1000000007);
    do {
        int L = check(order[0], order[1]);
        int R = check(order[1], order[2]);
        int len = L + R - SZ(s[order[1]]);
        ckmin(res, len);
    } while (next_permutation(ALL(order)));

    FOR(i,0,2) {
        FOR(j,0,2) {
            subs[i][j] = 0;
            if (SZ(s[i]) > SZ(s[j])) continue;
            int len = SZ(s[i]);
            FOR(k,0,SZ(s[j])-len) {
                if (hs[i].query(0, len-1) == hs[j].query(k, k+len-1)) {
                    subs[i][j] = 1;
                    break;
                }
            }
        }
    }

    if (subs[1][0] && subs[2][0]) ckmin(res, SZ(s[0]));
    if (subs[0][1] && subs[2][1]) ckmin(res, SZ(s[1]));
    if (subs[0][2] && subs[1][2]) ckmin(res, SZ(s[2]));

    if (subs[0][1] || subs[0][2]) {
        ckmin(res, check(1, 2));
        ckmin(res, check(2, 1));
    }
    if (subs[1][0] || subs[1][2]) {
        ckmin(res, check(0, 2));
        ckmin(res, check(2, 0));
    }
    if (subs[2][0] || subs[2][1]) {
        ckmin(res, check(0, 1));
        ckmin(res, check(1, 0));
    }
    
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    while (cin >> s[0]) {
        cin >> s[1] >> s[2];
        cout << solve() << "\n";
    }
    return 0;
}
