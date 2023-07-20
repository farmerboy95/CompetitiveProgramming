/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We need to calculate E[B * H * (B+H)], with B and H are number of bears and humans
        after the attack, respectively. This means that we need to find the sum of expected
        value when we choose 1 bear, 1 human and 1 of the alive soldiers, which is the same
        as the probability of choosing.
        - We try to define dp[one][two] as the probability to have "one" 1 HP soldiers, "two"
        2 HP soldiers. We can have some transition to dp[one-1][two] with the chance of
        one / (one+two), and to dp[one+1][two-1] with the chance of two / (one+two). However,
        at the end we cannot distinguish number of bears and number of humans, because in
        "one" soldiers, we cannot tell if one is a human or one is a wounded bear.
        - Consider a pair of human - bear, how do we calculate the probability that they
        are still alive after the attack? Define dp[one][two][hp1][hp2] as the probability
        to have "one" 1HP soldiers and "two" 2HP soldiers, and the pair has "hp1" HP and "hp2"
        2HP after the attack, respectively (0 <= hp1 <= 1 and 0 <= hp2 <= 2). The transition
        is the same as above. The result we need is X = dp[one][two][1][1] + dp[one][two][1][2]
        with "one" and "two" are after the attack. Since the bears and humans are symmetric,
        calculations for the next pair is not necessary. So the probability to choose 1 human
        1 bear is X * B * H, B and H are the initial number of bears and humans, respectively.
        - What about the number of soldiers after the attack? We know that number of soldiers
        left is one+two, so we need to multiply the result with one+two. To be more specific,
        since you reach the state of "one" 1HP soldiers and "two" 2HP soldiers, so the
        probability to choose one in this group is 1. We need to pick all of them, so we
        need one+two times.
        - Complexity O((B+H)^2)
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

const int MAXN = 4010;
const int MAXM = 1000;
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

mi dp[4010][2010][2][3];

class DoubleLive {
  public:
    int sumAfterBattle;

    int findEV(int B, int H, int T) {
        sumAfterBattle = B * 2 + H - T;
        if (sumAfterBattle == 0 || B == 0 || H == 0) {
            return 0;
        }

        // dp[one][two][HP1][HP2]
        FOR(i,0,B+H) {
            FOR(j,0,B) {
                FOR(hp1,0,1) {
                    FOR(hp2,0,2) {
                        dp[i][j][hp1][hp2] = 0;
                    }
                }
            }
        }

        dp[H][B][1][2] = 1;
        mi res = 0;

        FORE(sum,B*2+H,sumAfterBattle) {
            FOR(numTwo,0,B) {
                int numOne = sum - numTwo * 2;
                if (numOne > B + H) continue;
                if (numOne < 0) break;
                
                FOR(hp1,1,1) {
                    FOR(hp2,1,2) {
                        if (mi(dp[numOne][numTwo][hp1][hp2]) == 0) continue;
                        mi cur = dp[numOne][numTwo][hp1][hp2];

                        if (sum == sumAfterBattle) {
                            if (hp1 && hp2) {
                                res += dp[numOne][numTwo][hp1][hp2] * B * H * (numOne + numTwo);
                            }
                            continue;
                        }

                        int one = (hp1 == 1) + (hp2 == 1);
                        int two = (hp1 == 2) + (hp2 == 2);

                        mi preCalc = cur / mi(numOne + numTwo);

                        // numOne / (numOne + numTwo)
                        if (numOne > one) {
                            dp[numOne - 1][numTwo][hp1][hp2] += preCalc * mi(numOne - one);
                        }
                        if (one) {
                            if (hp1 == 1) {
                                dp[numOne - 1][numTwo][hp1 - 1][hp2] += preCalc;
                            }
                            if (hp2 == 1) {
                                dp[numOne - 1][numTwo][hp1][hp2 - 1] += preCalc;
                            }
                        }

                        // numTwo / (numOne + numTwo)
                        if (numTwo > two) {
                            dp[numOne + 1][numTwo - 1][hp1][hp2] += preCalc * mi(numTwo - two);
                        }
                        if (two) {
                            if (hp1 == 2) {
                                dp[numOne + 1][numTwo - 1][hp1 - 1][hp2] += preCalc;
                            }
                            if (hp2 == 2) {
                                dp[numOne + 1][numTwo - 1][hp1][hp2 - 1] += preCalc;
                            }
                        }
                    }
                }
            }
        }

        return int(res);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    DoubleLive sol;
    cout << sol.findEV(4, 3, 1) << "\n";
    cout << sol.findEV(3, 10, 0) << "\n";
    cout << sol.findEV(1, 2, 2) << "\n";
    cout << sol.findEV(1, 1, 1) << "\n";
    cout << sol.findEV(1, 1, 2) << "\n";
    cout << sol.findEV(3, 10, 16) << "\n";
    cout << sol.findEV(5, 2, 5) << "\n";
    cout << sol.findEV(1807, 1234, 4040) << "\n";
    cout << sol.findEV(20, 10, 7) << "\n";
    cout << sol.findEV(2000, 2000, 5998) << "\n";
    cout << sol.findEV(1987, 1701, 570) << "\n";
    cout << sol.findEV(2, 3, 2) << "\n";
    cout << sol.findEV(3, 2, 2) << "\n";
    cout << sol.findEV(5, 1, 4) << "\n";
    cout << sol.findEV(1, 5, 4) << "\n";
    cout << sol.findEV(1, 1, 0) << "\n";
    cout << sol.findEV(1,1,1) << "\n";
    cout << sol.findEV(1,1,2) << "\n";
    cout << sol.findEV(1,1,3) << "\n";
    cout << sol.findEV(5,1,0) << "\n";
    cout << sol.findEV(1,5,0) << "\n";
    cout << sol.findEV(5,1,11) << "\n";
    cout << sol.findEV(1,5,7) << "\n";
    cout << sol.findEV(1,5,5) << "\n";
    cout << sol.findEV(5,1,9) << "\n";
    cout << sol.findEV(2000,2000,0) << "\n";
    cout << sol.findEV(2000,2000,1) << "\n";
    cout << sol.findEV(2000,2000,3786) << "\n";
    cout << sol.findEV(2000,2000,5997) << "\n";
    cout << sol.findEV(2000,2000,5999) << "\n";
    cout << sol.findEV(2000,2000,6000) << "\n";
    cout << sol.findEV(2000,2000,5998) << "\n";
    cout << sol.findEV(2000,1970,5860) << "\n";
    cout << sol.findEV(	1981, 2000, 123) << "\n";
    cout << sol.findEV(1981, 2000, 5887) << "\n";
    cout << sol.findEV(1457, 1612, 3970) << "\n";
    cout << sol.findEV(1910, 1844, 4567) << "\n";
    return 0;
}
