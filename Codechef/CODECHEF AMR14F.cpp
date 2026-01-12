/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let m = 16.
        - The commented code shows how we can brute force to get the answer.
        Basically, we can choose any 2 substrings with at least one common
        character, like, if they both contain character A, it's a good pair
        of substrings, does not matter if those As are from different or the
        same position. This will take O(n^4).
        - There are only m characters in our alphabet, so each substring can
        make up a bitmask showing which character it contains.
        - Let's first count the number of substrings corresponding with each
        bitmask, putting in cnt[mask]. How? Let's fix a starting point i and
        extend our substring to the right. We notice that our bitmask only
        changes up to m times (when considering a new character, there are 
        2 possibilities, whether it's in our set, or not). We can easily get
        the positions where the bitmask changes, using binary search.
        - Then we can use SOS DP to have dp[mask] containing the number of
        bitmask being covered by mask.
        - For each count of the mask x we have, we need to count the number 
        of masks y that x & y > 0. How? It's the total number of possible 
        substrings excluding the number of masks z that x & z = 0. Multiply 
        2 values and add to the result.
        - Complexity O(n * m * logn + m * 2^m)
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

const int MAXN = 100000;
const int MAXM = 16;
const int MAXK = 16;
const int MAXQ = 200010;

template<int MOD> struct mint {
    static const int mod = MOD;
    int v; explicit operator int() const { return v; } // explicit -> don't silently convert to int
    mint() { v = 0; }
    mint(ll _v) { v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
        if (v < 0) v += MOD; }
    friend bool operator==(const mint& a, const mint& b) { 
        return a.v == b.v; }
    friend bool operator!=(const mint& a, const mint& b) { 
        return !(a == b); }
    friend bool operator<(const mint& a, const mint& b) { 
        return a.v < b.v; }
    friend string ts(mint a) { return ts(a.v); }

    mint& operator+=(const mint& m) { 
        if ((v += m.v) >= MOD) v -= MOD; 
        return *this; }
    mint& operator-=(const mint& m) { 
        if ((v -= m.v) < 0) v += MOD; 
        return *this; }
    mint& operator*=(const mint& m) { 
        v = int((ll) v * m.v % MOD); return *this; }
    mint& operator/=(const mint& m) { return (*this) *= inv(m); }
    friend mint pow(mint a, ll p) {
        mint ans = 1; assert(p >= 0);
        for (; p; p /= 2, a *= a) if (p&1) ans *= a;
        return ans; }
    friend mint inv(const mint& a) { assert(a.v != 0); 
        return pow(a,MOD-2); }
        
    mint operator-() const { return mint(-v); }
    mint& operator++() { return *this += 1; }
    mint& operator--() { return *this -= 1; }
    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }
};

typedef mint<MODBASE> mi;
typedef vector<mi> vmi;
typedef pair<mi,mi> pmi;
typedef vector<pmi> vpmi;

string s;
int n;
mi cnt[1<<MAXM], dp[1<<MAXM];
vi pos[MAXM];

inline int toInt(char ch) {
    if (ch >= '0' && ch <= '9') return ch - '0';
    return 10 + ch - 'A';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    while (te--) {
        cin >> s;
        n = SZ(s);
        // int f[100][100];
        // MS(f, 0);
        // FOR(i,0,n-1) {
        //     int mask = 0;
        //     FOR(j,i,n-1) {
        //         mask |= (1 << toInt(s[j]));
        //         f[i][j] = mask;
        //     }
        // }

        // int res = 0;
        // FOR(i,0,n-1) {
        //     FOR(j,i,n-1) {
        //         FOR(k,0,n-1) {
        //             FOR(l,k,n-1) {
        //                 if (f[i][j] & f[k][l]) {
        //                     res++;
        //                 }
        //             }
        //         }
        //     }
        // }
        // cout << res << "\n";

        FOR(i,0,MAXM-1) {
            pos[i].clear();
        }

        FOR(i,0,n-1) {
            int x = toInt(s[i]);
            pos[x].push_back(i);
        }

        FOR(mask,0,(1<<MAXM)-1) {
            cnt[mask] = dp[mask] = 0;
        }

        FOR(i,0,n-1) {
            int x = toInt(s[i]);
            vi ptrs(MAXM, 0);
            ptrs[x] = lower_bound(ALL(pos[x]), i) - pos[x].begin();
            FOR(j,0,MAXM-1) {
                if (j == x) continue;
                ptrs[j] = lower_bound(ALL(pos[j]), pos[x][ptrs[x]]) - pos[j].begin();
            }
            vpi w;
            FOR(j,0,MAXM-1) {
                if (ptrs[j] >= SZ(pos[j])) continue;
                w.push_back({pos[j][ptrs[j]], j});
            }
            sort(ALL(w));
            w.push_back({n, 0});
            int mask = (1<<x);
            FOR(i,1,SZ(w)-1) {
                cnt[mask] += w[i].FI - w[i-1].FI;
                mask |= (1<<w[i].SE);
            }
        }

        mi numSubstrings = mi(n) * (n+1) / 2;
        FOR(mask,0,(1<<MAXM)-1) {
            dp[mask] = cnt[mask];
        }

        FOR(i,0,MAXM-1) {
            FOR(mask,0,(1<<MAXM)-1) {
                if (mask & (1<<i)) {
                    dp[mask] += dp[mask ^ (1<<i)];
                }
            }
        }

        mi res = 0;
        FOR(mask,1,(1<<MAXM)-1) {
            if (cnt[mask] == 0) continue;
            int other = (1<<MAXM)-1 - mask;
            mi cntOther = dp[other];
            mi cntMask = numSubstrings - cntOther;
            res += cnt[mask] * cntMask;
        }

        cout << int(res) << "\n";
    }
    return 0;
}
