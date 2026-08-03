/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        Let R = sum of all r[j], and G(t) = sum of r[j] over p[j] <= t (prefix sum + binary search).

        A single run of s consecutive ones is worth
            val(s) = d*s + floor(s/n)*R + G(s mod n)
        so f(I(a)) = val(|a|), and for a general array a = runs of ones separated by zeros,
        f(a) = sum of val(s_i) over the runs (a zero scores nothing: c becomes 0 and every
        p[j] >= 1, so no checkpoint can fire; it only destroys the streak).

        With k runs of lengths s_1..s_k and z zeros, |a| = sum(s_i) + z. Increasing z only
        inflates the RHS, so take z = k-1 (one zero per gap, none at the ends). Target:
            val(s_1) + ... + val(s_k) > val(s_1 + ... + s_k + k - 1)

        Merge-down to k = 2: merging two adjacent runs into one of length s_1 + s_2 + 1 absorbs
        exactly one zero, so |a| is INVARIANT => RHS is fixed, while the LHS weakly grows.
        Induct downwards => it suffices to check k = 2.

        Write x = q1*n + t1, y = q2*n + t2 with 0 <= t1, t2 < n. Expanding
        val(x) + val(y) - val(x+y+1) makes q1 and q2 cancel entirely, leaving
            G(t1) + G(t2) > d + H(t1 + t2 + 1),   H(T) = floor(T/n)*R + G(T mod n)
        Since t1, t2 <= n-1 we have T <= 2n-1, so floor(T/n) is 0 or 1 (the two cases in H()).

        H is non-decreasing (boundary check: H(n-1) = G(n-1) <= R = H(n)) and G is a step
        function jumping only at checkpoints. So snapping t1 down to the largest p[j] <= t1
        leaves the LHS UNCHANGED (G is constant on [p[j], p[j+1])) and weakly DECREASES the RHS
        (monotone H) => the inequality is preserved. Hence only the checkpoints are candidates.

        Answer YES iff some pair of checkpoints satisfies the inequality. O(m^2 log m).

        Pitfalls:
        - m = 0: G == 0, condition becomes 0 > d, and d >= 1 => always NO.
        - R can reach 2000 * 1e9 = 2e12, so use long long.
        - Do not drop the -G(t1+t2+1) term when T < n; the merged run collects checkpoints too.
        - t = n is not a valid candidate (a run of length n resets c), but feeding it in is
          harmless: G(n) = R and H(t+n+1) = R + G(t+1) >= R + G(t), so the check can never
          spuriously pass.
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
const int MAXM = 2010;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, d, p[MAXM], r[MAXM];
ll sum[MAXM];

ll G(int s) {
    int l = 1, r = m;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (p[mid] > s) r = mid-1;
        else l = mid + 1;
    }
    return sum[r];
}

ll H(int s) {
    if (s <= n) return G(s);
    return G(n) + G(s - n);
}

bool check(int t1, int t2) {
    ll left = G(t1) + G(t2);
    ll right = d + H(t1 + t2 + 1);
    return left > right;
}

bool check() {
    FOR(i,1,m) {
        if (p[i] == n) break;
        FOR(j,1,m) {
            if (check(p[i], p[j])) return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    while (te--) {
        cin >> n >> m >> d;
        FOR(i,1,m) cin >> p[i] >> r[i];
        FOR(i,1,m) sum[i] = sum[i-1] + r[i];

        if (check()) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
