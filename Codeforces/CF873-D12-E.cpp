/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's consider naive solution: make three loops to fix amounts of people 
        to get diplomas of each degree, take the best. Obviously, sorting the scores
        will regroup optimal blocks for each degree in such a way that they come in 
        segments of initial array.
        - To be honest, we just need to get rid of the last loop. Let diff[i] be the 
        difference between a[i] and a[i+1] (a is desc sorted, b[n-1] = a[n-1], indices
        start from 0). Then we choose ending point of the first and second diploma, let
        them be i and j, now we need to choose the ending point k of the third diploma.
        There are several factors here:
            + Let Min = min(number of students with first diploma, number of students
            with second diploma), Max = max(number of students with first diploma, 
            number of students with second diploma).
            + If Min * 2 < Max, we ignore i and j and continue with next ones
            + If the remaining student is 0, we ignore i and j and continue with 
            next ones
            + The number of students with third diploma is a range which is
                + [max(1, Max / 2 + Max % 2), min(remaining students, 2 * Min)]
            + Ignore when the above range is not an actual range
            + Get k using sparse table or segment tree, here I used sparse table
            + Then it can be compared to the current result to update result
        - Complexity O(n^2)
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

struct RMQ {
    vector<vi> preComp;
    vi a;

    int log2_floor(unsigned long long i) {
        return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
    }

    RMQ(vi &a) {
        int n = SZ(a);
        int k = log2_floor(n);
        preComp.resize(k+1, vi(n));
        this->a = a;

        FOR(i,0,n-1) {
            preComp[0][i] = i;
        }

        FOR(i,1,k) {
            for (int j = 0; j + (1<<i) - 1 < n; j++) {
                if (a[preComp[i-1][j]] >= a[preComp[i-1][j + (1<<(i-1))]]) {
                    preComp[i][j] = preComp[i-1][j];
                } else {
                    preComp[i][j] = preComp[i-1][j + (1<<(i-1))];
                }
            }
        }
    }

    int query(int l, int r) {
        int lg = log2_floor(r - l + 1);
        if (a[preComp[lg][l]] >= a[preComp[lg][r - (1<<lg) + 1]]) {
            return preComp[lg][l];
        }
        return preComp[lg][r - (1<<lg) + 1];
    }
};

void compare(vi &res, vi &diff, int i, int j, int k) {
    if (res[0] == -1) {
        res = {i, j, k};
    }
    vi cur = {i, j, k};
    FOR(x,0,2) {
        if (diff[res[x]] > diff[cur[x]]) {
            return;
        }
        if (diff[res[x]] < diff[cur[x]]) {
            res = cur;
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vpi a(n);
    FOR(i,0,n-1) {
        cin >> a[i].FI;
        a[i].SE = i;
    }
    sort(ALL(a));
    reverse(ALL(a));

    vi diff;
    FOR(i,0,n-2) {
        diff.push_back(a[i].FI - a[i+1].FI);
    }
    diff.push_back(a[n-1].FI);

    RMQ rmq(diff);
    vi res = {-1, -1, -1};

    FOR(i,0,n-1) {
        FOR(j,i+1,n-1) {
            int num1 = i + 1;
            int num2 = j - i;
            int Min = min(num1, num2), Max = max(num1, num2);
            if (Min * 2 < Max) {
                continue;
            }

            int remain = n - num1 - num2;
            if (remain == 0) {
                continue;
            }

            // k = j+1 -> n-1
            int num3L = max(1, Max / 2 + Max % 2);
            int num3R = min(remain, 2 * Min);
            if (num3L > num3R) {
                continue;
            }

            // num1 | num2 | num3L -> num3R
            int k = rmq.query(j + num3L, j + num3R);
            compare(res, diff, i, j, k);
        }
    }

    vi kq(n);
    FOR(i,0,n-1) {
        if (i <= res[0]) {
            kq[a[i].SE] = 1;
        } else if (i <= res[1]) {
            kq[a[i].SE] = 2;
        } else if (i <= res[2]) {
            kq[a[i].SE] = 3;
        } else {
            kq[a[i].SE] = -1;
        }
    }

    FOR(i,0,n-1) cout << kq[i] << ' ';
    return 0;
}
