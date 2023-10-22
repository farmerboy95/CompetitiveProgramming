/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Note that over time, a pair of dots that are next to each other will always stay
        next to each other, meaning A[1] and B[1] will always be next to each other, A[2] and
        B[2] will always be next to each other, and so on.
        - If N is even and A[i] == B[i] for any i, then the answer is -1 by defnition. If N is
        odd, then there can be only one place were A[i] == B[i] (the midpoint of the metalike
        logo), so we can find it and get the answer in O(N), or return -1 if there is no or more
        than one such i.
        - Otherwise, we are left with even N and no A[i] == B[i], and we can first just think 
        about each i as the lower vs higher dot. For a meta-like logo, the relationship always
        look like this:
            3 2 3 5 6 4  -> LLLHHH
            4 6 5 3 2 3  -> HHHLLL
        - Let's first consider even N by simulating the first pattern in reverse:
            (t)     (t-1)   (t-2)   (t-N/2)                 (t-N)
            LLLHHH  LLLLHH  LLLLLH  LLLLLL  HLLLLL  HHLLLL  HHHLLL
            HHHLLL  HHHHLL  HHHHHL  HHHHHH  LHHHHH  LLHHHH  LLLHHH

            (t-N-1)                                 (t-2N)
            HHHHLL  HHHHHL  HHHHHH  LHHHHH  LHHHHH  LLHHHH  LLLHHH
            LLLLHH  LLLLLH  LLLLLL  HLLLLL  HLLLLL  HHLLLL  HHHLLL
        - Thus, the pattern repeats after 2N steps. If the answer exists, then at any given time:
        there is at most one place when A[i] < B[i] inverts to A[i+1] > B[i+1] (or the reverse).
        - Therefore, the midpoint of the metalike logo either be this inversion point, or the 
        first/last element. Either way, there are O(1) possible candidates for the midpoints. After
        we've found these candidates, we can simulate 2N steps on the input arrays using a double-ended
        queue (updating the positions of the midpoint candidates at each step). If at any time a midpoint 
        candidate actually shifts to the midpoint, we can do a check to see if A equals the reverse of B.
        - There are O(1) midpoint candidates, and each can only reach the midpoint twice in our 2N 
        simulated time steps. Thus, the reverse condition is checked at most O(1) times. The overall 
        running time is O(N).
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

const int MAXN = 2000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN], b[MAXN];

void move(deque<int> &A, deque<int> &B, int &middleCdd) {
    int x = A.front(); A.pop_front();
    B.push_back(x);
    x = B.front(); B.pop_front();
    A.push_back(x);
    middleCdd--;
    if (middleCdd == -1) middleCdd = n-1;
}

bool isOK(deque<int> &A, deque<int> &B) {
    vi aa, bb;
    TRAV(x, A) aa.push_back(x);
    TRAV(x, B) bb.push_back(x);

    int l = 0, r = n-1;
    int half = n / 2;
    int lefMid = l + half - 1, rigMid = r - half + 1;

    FOR(i,l,lefMid)
        if (aa[i] >= bb[i]) return false;
    
    FOR(i,rigMid,r)
        if (aa[i] <= bb[i]) return false;
    
    reverse(ALL(bb));
    return aa == bb;
}

int solve() {
    int numEqual = 0;
    FOR(i,0,n-1) numEqual += (a[i] == b[i]);
    if (n % 2 == 0 && numEqual) return -1;
    if (n % 2 == 1 && numEqual != 1) return -1;
    int middleCdd = -1;
    if (n % 2 == 1) {
        FOR(i,0,n-1)
            if (a[i] == b[i]) {
                middleCdd = i;
                break;
            }
    } else {
        FOR(i,0,n-1) {
            if (a[i] < b[i]) {
                if (i == n-1) {
                    if (a[0] < b[0]) {
                        middleCdd = i;
                        break;
                    }
                } else {
                    if (a[i+1] > b[i+1]) {
                        middleCdd = i;
                        break;
                    }
                }
            } else if (a[i] > b[i]) {
                if (i == n-1) {
                    if (a[0] > b[0]) {
                        middleCdd = i;
                        break;
                    }
                } else {
                    if (a[i+1] < b[i+1]) {
                        middleCdd = i;
                        break;
                    }
                }
            }
        }
    }

    if (middleCdd == -1) return -1;

    deque<int> A, B;
    FOR(i,0,n-1) {
        A.push_back(a[i]);
        B.push_back(b[i]);
    }

    int desired = n / 2;
    if (n % 2 == 0) desired--;
    FOR(i,0,2*n-1) {
        if (desired == middleCdd) {
            if (isOK(A, B)) return i;
        }
        move(A, B, middleCdd);
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case #" << o << ": ";
        cin >> n;
        FOR(i,0,n-1) cin >> a[i];
        FOR(i,0,n-1) cin >> b[i];

        cout << solve() << "\n";
    }
    return 0;
}
