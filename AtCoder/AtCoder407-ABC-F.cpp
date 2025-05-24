/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - For each i, find the nearest indices that has value larger than a[i] to the
        left and to the right, put them to l[i] and r[i], respectively.
        - Then for each i, we know that we can expand to the left and to the right, as
        long as they don't exceed l[i]+1 and r[i]-1, and for each of them, add a[i] to
        res[length]. But this would cause TLE right?
        - Let Min = min(i - l[i], r[i] - i), Max = max(i - l[i], r[i] - i), and the full
        length is Total = r[i] - l[i] - 1. Let's maintain a dx + c expression for each
        length, x is the length
            + For length from 1 to Min, a[i] can be added once to res[1], twice to res[2],
            and so on, so we just need to add 1 to d[1..Min]
            + For length from Min+1 to Max, a[i] can be added Min times to res[Min+1],
            Min times to res[Min+2] and so on, so we need to add Min * a[i] to c[Min+1..Max]
            + For length from Max+1 to Total, a[i] can be added Min-1 times to res[Max+1],
            Min-2 times to res[Max+2] and so on, so we need to add (Total - length + 1) * a[i]
            = Total * a[i] + a[i] - a[i] * length, so add Total * a[i] + a[i] to c[Max+1..Total]
            and add -a[i] to d[Max+1..Total]
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

int n, l[MAXN], r[MAXN];
ll a[MAXN], c[MAXN], d[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];

    a[0] = INF;
    a[n+1] = INF;

    deque<int> dq;
    dq.push_back(0);
    FOR(i,1,n) {
        while (SZ(dq) && a[dq.back()] < a[i]) dq.pop_back();
        l[i] = dq.back();
        dq.push_back(i);
    }

    while (SZ(dq)) dq.pop_back();
    dq.push_back(n+1);
    FORE(i,n,1) {
        while (SZ(dq) && a[dq.back()] <= a[i]) dq.pop_back();
        r[i] = dq.back();
        dq.push_back(i);
    }

    // dx + c
    FOR(i,1,n) {
        int leftSide = i - l[i];
        int rightSide = r[i] - i;
        int Min = min(leftSide, rightSide);
        int Max = max(leftSide, rightSide);
        int total = r[i] - l[i] - 1;

        // j : 1 -> Min, add a[i] to d[j]
        d[1] += a[i];
        d[Min+1] -= a[i];

        // j : Min+1 -> Max, add Min*a[i] to c[j]
        if (Min + 1 <= Max) {
            c[Min+1] += Min * a[i];
            c[Max+1] -= Min * a[i];
        }

        // j : Max+1 -> total, add total * a[i] + a[i] to c[j], add -a[i] to d[j]
        if (Max + 1 <= total) {
            c[Max+1] += total * a[i] + a[i];
            c[total+1] -= total * a[i] + a[i];
            d[Max+1] -= a[i];
            d[total+1] += a[i];
        }
    }

    FOR(i,1,n) {
        d[i] += d[i-1];
        c[i] += c[i-1];
    }

    FOR(i,1,n) {
        cout << d[i] * i + c[i] << "\n";
    }
    return 0;
}
