/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        Unify the two operations. Since ceil(v/2) = floor((v+1)/2), every step is
            v -> floor((v + b) / 2),   b = 0 if this element is chosen, b = 1 otherwise.
        Unrolling T steps with bits b_1..b_T:
            v_T = floor( (a[i] + sum_{t=1..T} b_t * 2^(t-1)) / 2^T )
        so v_T = 0  <=>  a[i] + sum_{t not in S_i} 2^(t-1) < 2^T, where S_i = steps at which i
        was chosen. Complement using sum_{t=1..T} 2^(t-1) = 2^T - 1: the not-chosen sum is
        2^T - 1 - Sigma_i with Sigma_i = sum_{t in S_i} 2^(t-1). Substituting collapses to

            a[i] <= Sigma_i

        (Hand check a=5, T=3: S={3} gives Sigma=4 < 5, and 5->3->2->1 indeed fails;
         S={2,3} gives Sigma=6 >= 5, and 5->3->1->0 works.)

        Each step chooses exactly one index, so S_1..S_n partition {1..T}. The problem becomes:
            distribute the T distinct weights 2^0, 2^1, ..., 2^(T-1), each to exactly one
            element; element i is satisfied iff its weights sum to >= a[i]. Minimize T.
        No more floors/ceilings/simulation.

        Bounds: every a[i] >= 1 needs at least one weight => T >= n. And 2^30 > 1e9 >= a[i], so
        any weight 2^e with e >= 30 satisfies an element by itself ("big" weight); there are
        T-30 of them, so at T = n+30 every element gets its own big weight => T <= n+30.
        Feasibility is monotone in T (going to T+1 adds a weight to some element: sums only
        grow, requirements are unchanged), so binary search T over [n, n+30].

        Feasibility test for a fixed T. Let b = max(0, T-30) big weights and k = n - b.
        Claim: it is optimal to spend the big weights on the b LARGEST elements, leaving the k
        smallest to the 30 small weights 2^0..2^(min(T,30)-1). Proof from any feasible
        assignment, in two exchange phases:
          - If one element holds >= 2 big weights while another holds none, move one across:
            the donor keeps a big weight so stays satisfied, the receiver is satisfied by a
            single big weight. Repeat => each element holds at most one.
          - If a large element x has no big weight while a small element y does, swap their
            whole weight sets: x gets y's set which contains a big weight => satisfied;
            y gets x's set whose sum was >= a[x] >= a[y] => satisfied. Each swap moves a big
            weight onto a larger element, so this terminates.

        Subproblem: cover the k (<= 30) smallest requirements with the distinct weights
        2^0..2^(j_max). Greedy: process weights from largest down, giving each to the element
        with the largest remaining deficit (max-heap); drop an element once its deficit is met.
        Correctness by exchange: suppose an optimal assignment gives the current largest weight
        2^j to y while x has the largest requirement (a[x] >= a[y]). Let X, Y be the weight sets
        they receive. Every weight in X is < 2^j, so
            sum(X) <= 2^0 + ... + 2^(j-1) = 2^j - 1 < 2^j <= sum(Y).
        Swapping the two sets keeps both satisfied: x gets sum(Y) > sum(X) >= a[x], and y gets
        sum(X) >= a[x] >= a[y]. That strict inequality between sum(X) and sum(Y) is the whole
        proof - it is what powers of two buy us; without it the swap does not go through.

        Note there is no "which set of weights should this element get" decision to make - sets
        are never planned, they fall out of always feeding the current largest deficit.
        Sum of weights >= sum of requirements is NOT sufficient: r={3,3,1} with weights {1,2,4}
        has 7 >= 7 but is infeasible (4 covers a 3, then 2+1 covers the other 3, nothing left
        for the 1).

        Complexity: O(n log n) for the sort, then ~5 binary search steps, each doing <= 30 heap
        operations on a heap of size <= 30.
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

int n, a[MAXN];

bool check(int T) {
    int b = max(0, T - 30);
    int k = n - b;

    priority_queue<int> h;
    FOR(i,1,k) h.push(a[i]);

    FORE(i,T-b-1,0) {
        if (SZ(h)) {
            int r = h.top();
            h.pop();
            if (r > (1<<i)) {
                r -= (1<<i);
                h.push(r);
            }
        }
    }

    return SZ(h) == 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    while (te--) {
        cin >> n;
        FOR(i,1,n) cin >> a[i];
        sort(a+1, a+n+1);
        int l = n, r = n+30;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) r = mid - 1;
            else l = mid + 1;
        }
        cout << l << "\n";
    }
    return 0;
}
