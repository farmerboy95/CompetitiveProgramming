/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - This is a very interesting problem about expected value of a square of sum of some
        values.
        - The result is sum(E[X[i]]), X[i] = expected fatigue of Alex on the i-th day. Since
        some subject may start late, maybe on the M-th day, i may reach M + 500 - 1.
        - E[X[i]] = E[(F[1] + F[2] + F[3] + ... F[n]) ^ 2], F[j] is the fatigue of Alex on the
        i-th day for the j-th subject.
        - E[X[i]] = E[(F[1] + F[2] + F[3] + ... F[n]) * (F[1] + F[2] + F[3] + ... F[n])]
                  = E[F[1] * F[1] + F[1] * F[2] + ... + F[1] * F[n] + F[2] * F[1] + 
                  F[2] * F[2] + ... + F[2] * F[n] + ... + F[n] * F[n]]
                  = E[F[1] * F[1]] + ... + E[F[1] * F[n]] + E[F[2] * F[1]] + ... + 
                  E[F[2] * F[n]] + ... + E[F[n] * F[1]] + ... + E[F[n] * F[n]]
        - For i-th day and j-th subject, you need to get the range of lessons that Alex can
        study, for example, on the first day, there is a chance of 1/M that Alex can study
        the first lesson, but no chance for second, third or more, so the range here is [1, 1].
        Similarly, on the second day, the chance for the first lesson is 1/M and the chance
        for the second lesson is also 1/M, no chance for third or more to fall on this day,
        so the range here is [1, 2]. Of course there are days that no valid range exists.
        - There are 2 cases here
            + E[F[j] * F[j]] = E[F[j] ^ 2]. You get the range mentioned above, then for each
            lesson, the chance is 1/M, and the value is square of fatigue, so add 1/M * sum
            of square of fatigue on range.
            + E[F[j] * F[k]]. Since the events of one subject and another subject to have first
            days are independent, the expected value will be E[F[j]] * E[F[k]]. Similarly, 
            E[F[j]] = 1/M * sum of fatigue on range, we can get sum of E[F[k]] as sum of all
            E[F[]] - E[F[j]] because k != j.
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

const int MAXN = 510;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m;
vi a[MAXN], s[MAXN], ss[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) {
        int k;
        cin >> k;
        a[i].push_back(0);
        s[i].push_back(0);
        ss[i].push_back(0);
        while (k--) {
            int x;
            cin >> x;
            a[i].push_back(x);
            s[i].push_back(s[i].back() + x);
            ss[i].push_back(ss[i].back() + x * x);
        }
    }

    ld res = 0;

    int M = m + 500 - 1;
    FOR(day,1,M) {
        vpi f(n+1);
        FOR(i,1,n) {
            int len = SZ(a[i]) - 1;
            int l1 = day - len + 1, r1 = day, l2 = day, r2 = day + len - 1;
            if (l1 < 1) {
                l1 = 1;
                r1 = len;
            }
            if (l2 > m) {
                l2 = m;
                r2 = m - len + 1;
            }

            int r = day - l1 + 1;
            int l = day - l2 + 1;
            f[i] = {l, r};
        }

        ld sum = 0;
        FOR(i,1,n) {
            if (f[i].FI > f[i].SE) continue;
            sum += (ld) (s[i][f[i].SE] - s[i][f[i].FI-1]) / m;
        }

        FOR(i,1,n) {
            if (f[i].FI > f[i].SE) continue;
            // 1/m * sum of square of fatigue on range.
            res += (ld) (ss[i][f[i].SE] - ss[i][f[i].FI-1]) / m;

            ld A = (ld) (s[i][f[i].SE] - s[i][f[i].FI-1]) / m;
            res += A * (sum - A);
        }
    }

    setPrec(9);
    cout << res;
    return 0;
}
