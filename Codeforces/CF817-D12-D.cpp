/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - For each segment, we want to know its maximum element (Max) and its minimum element (Min).
        Then we add Max - Min to the result. Doing the same thing with all the segments we will get
        the final result in possibly O(n^2).
        - But that's too slow. So we approach the problem in another way. How many time a specific
        a[i] is Max? To be more exact, how many segments are there that i-th element can be their
        maximum element? If we can solve this problem, the same thing applies to finding Min.
        - Assume all the elements are distinct. For i-th element to be the largest value of a
        segment, we need to find how much we can extend the segment to the left and to the right
        so that i-th still be the largest value. So to the left, we can extend until we meet a
        larger value or we reach the left side of the whole array. Similarly, we can extend to
        the right until we meet a larger value or we reach the right side of the whole array.
        Denote those position as l and r. So a[i] can contribute (r - i) * (i - l) * a[i] to
        the final result. Doing similar to the smallest value, the different is that we extend
        until we meet a smaller value or reach side of the whole array. Then a[i] can contribute
        -(r - i) * (i - l) * a[i] to the final result.
        - Finding the nearest lower / higher value of i-th element to the left / right can be
        done using Sliding Window in O(n), then we can store the positions in 4 different arrays.
        - What if elements are not distinct? If we do the same, we may count duplicates. The
        best approach is to:
            - find the nearest position to the left in which value is larger than or EQUAL to a[i].
            - find the nearest position to the right in which value is larger than a[i]. (same as above)
            - find the nearest position to the left in which value is smaller than or EQUAL to a[i].
            - find the nearest position to the right in which value is smaller than a[i]. (same as above)
        - Overall, we can solve the problem in O(n).
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

const int MAXN = 1000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN], leftHigher[MAXN], rightHigher[MAXN], leftLower[MAXN], rightLower[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    
    cin >> n;
    FOR(i,1,n) cin >> a[i];

    deque<int> dq;
    FOR(i,1,n) {
        while (SZ(dq) && a[i] > a[dq.back()]) dq.pop_back();
        leftHigher[i] = (SZ(dq) == 0 ? 0 : dq.back());
        dq.push_back(i);
    }

    dq.clear();
    FOR(i,1,n) {
        while (SZ(dq) && a[i] < a[dq.back()]) dq.pop_back();
        leftLower[i] = (SZ(dq) == 0 ? 0 : dq.back());
        dq.push_back(i);
    }

    dq.clear();
    FORE(i,n,1) {
        while (SZ(dq) && a[i] >= a[dq.back()]) dq.pop_back();
        rightHigher[i] = (SZ(dq) == 0 ? n+1 : dq.back());
        dq.push_back(i);
    }

    dq.clear();
    FORE(i,n,1) {
        while (SZ(dq) && a[i] <= a[dq.back()]) dq.pop_back();
        rightLower[i] = (SZ(dq) == 0 ? n+1 : dq.back());
        dq.push_back(i);
    }

    ll res = 0;
    FOR(i,1,n) {
        int l = leftHigher[i], r = rightHigher[i];
        res += (ll) (i - l) * (r - i) * a[i];

        l = leftLower[i]; r = rightLower[i];
        res -= (ll) (i - l) * (r - i) * a[i];
    }

    cout << res;
    return 0;
}
