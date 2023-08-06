/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let E[i] = the expected number of shuffles to have i different dices chosen.
        - First we have E[n] = 0 and E[0] = 1 + E[k]
        - We calculate E[i] from n-1 to k, in each shuffle, we have a chance to get
        more dices in total, from 1 to k more dices, we also have a chance that the number
        of dices remains
        - E[i] = iCk * (n-i)C0 / nCk * (1 + E[i]) 
               + iC(k-1) * (n-i)C1 / nCk * (1 + E[i+1])
               + iC(k-2) * (n-i)C2 / nCk * (1 + E[i+2])
               + ...
               + iC0 * (n-i)Ck / nCk * (1 + E[i+k])
        - E[i] = 1 
               + iCk / nCk * E[i]
               + iC(k-1) * (n-i)C1 / nCk * E[i+1]
               + iC(k-2) * (n-i)C2 / nCk * E[i+2]
               + ...
               + iC0 * (n-i)Ck / nCk * E[i+k]
        - E[i] = (1
               + iC(k-1) * (n-i)C1 / nCk * E[i+1]
               + iC(k-2) * (n-i)C2 / nCk * E[i+2]
               + ...
               + iC0 * (n-i)Ck / nCk * E[i+k]) / (1 - iCk / nCk)
        - We try to calculate these probabilities with 1 / x to make use of the small
        precision.
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
using ll = long long; using ld = long double; 
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

const int MAXN = 1010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, k;
ld E[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    E[n] = 0;

    // f = 1 / nCk
    ld f = 1;
    FOR(i,0,k-1) {
        f *= (ld) (k - i) / (n - i);
    }

    FORE(i,n-1,k) {
        // denom = 1 - iCk / nCk
        ld denom = 1;
        FOR(j,1,k) {
            denom *= (ld) (i - j + 1) / (n - j + 1);
        }
        denom = 1 - denom;

        // numerator = 1 + ...
        ld numerator = 1;

        FOR(j,i+1,min(n,i+k)) {
            int y = j - i;
            int x = k - y;

            // choose x dices in i dices, and y = k-x dices in n-i dices
            // prob = 1 / (iCx * (n-i)Cy) = 1 / iCx * 1 / (n-i)Cy
            ld prob = 1;

            FOR(w,0,x-1) {
                prob *= (ld) (x - w) / (i - w);
            }

            FOR(w,0,y-1) {
                prob *= (ld) (y - w) / (n - i - w);
            }

            numerator += f / prob * E[j];
        }

        E[i] = numerator / denom;
    }

    E[0] = 1 + E[k];
    setPrec(9);
    cout << E[0];
    return 0;
}
