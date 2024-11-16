/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Idea shown in the code
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

int nt[1000010];
ld Log2[2][50];
ll Real[2][50];
ll q[2][4][50];
vi primes;

struct node {
    ld Log2;
    ll Real;
    int flag; // flag is formed by (state number in previous depth) * 100 + (prime number index)
};

node a[150];

ll mu(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MODBASE;
        a = a * a % MODBASE;
        b >>= 1;
    }
    return res;
}

void sieveBase(int n) {
    FOR(i,2,n) {
        if (nt[i] == 0) {
            nt[i] = i;
            for (ll j = (ll) i * i; j <= n; j += i) nt[j] = i;
            primes.push_back(i);
        }
    }
}

void dfs(int depth, int stateNum, vl &factors, ld &Min, ll &res) {
    int pre = depth % 2;
    int cur = 1 - pre;
    
    // stateNum is the number of states in the previous depth
    if (depth == SZ(factors)) {
        FOR(i,1,stateNum) {
            if (Log2[pre][i] < Min) {
                Min = Log2[pre][i];
                res = Real[pre][i];
            }
        }
        return;
    }

    ll fac = factors[depth];
    int t = 0;

    // for each state in the previous depth
    // we try to get the new state in the current depth
    // p ^ (x * y * z ... - 1) = p ^ (x-1) * p ^ (x * (y-1)) * p ^ (x * y * (z-1)) ...
    // so at each state, we can get the new value by multiplying the previous value with p ^ (x * y * (z-1))
    // z is the new exponent of the prime number that we want to add to the state
    // we also have q[] to store x*y... to serve the purpose of the above formula
    FOR(i,1,stateNum) {
        FOR(j,1,SZ(factors)) {
            t++;
            int flag = i * 100 + j;
            // real = previous real * prime[j] ^ (q[pre][i][j] * (fac-1))
            ld newLog2 = Log2[pre][i] + q[pre][i][j] * (fac-1) * log(primes[j] * 1.0);
            ll newReal = Real[pre][i] * mu(primes[j], q[pre][i][j] * (fac-1)) % MODBASE;
            a[t] = {newLog2, newReal, flag};
        }
    }

    sort(a+1, a+t+1, [](node a, node b) {
        // sort by log2 of the real value, increasing
        return a.Log2 < b.Log2;
    });

    int curStateNum = 0;
    for (int i = 1; i <= t && curStateNum < 3; i++) {
        // only add new state if the real value is different from the previous one
        // we can tell because we sort by log2 of the real value already
        // only takes the 3 smallest log2 of the real value to reduce the number of states
        if (i == 1 || a[i].Real != a[i-1].Real) {
            curStateNum++;
            Log2[cur][curStateNum] = a[i].Log2;
            Real[cur][curStateNum] = a[i].Real;
            int prevStateNum = a[i].flag / 100;
            int primeIndex = a[i].flag % 100;
            FOR(j,1,SZ(factors)) q[cur][curStateNum][j] = q[pre][prevStateNum][j];
            q[cur][curStateNum][primeIndex] *= fac;
        }
    }
    dfs(depth+1, curStateNum, factors, Min, res);
}

ll solve(ll P) {
    if (P == 0) return 1;
    P++;
    vl factors;
    TRAV(x, primes) {
        while (P % x == 0) {
            factors.push_back(x);
            P /= x;
        }
    }
    if (P > 1) factors.push_back(P);

    // up to 40 factors
    sort(ALL(factors));
    reverse(ALL(factors));

    dbg(factors);

    // log2(2^(P+1)) = P+1
    // we compare using log2 of the real value, not the real value
    ld Min = 1e40;
    ll res = 1;

    FOR(i,1,SZ(factors)) q[0][1][i] = 1;
    Log2[0][1] = 0;
    Real[0][1] = 1;
    dfs(0, 1, factors, Min, res);
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    // S = n * (2f + (n-1)) / 2 = n * (n + 2f - 1) / 2
    // 2S = n * (n + 2f - 1) (odd * even or even * odd)
    // f >= 1, n > 1, S odd
    // 90 = 1 * 90, 2 * 45, 3 * 30, 5 * 18, 6 * 15, 9 * 10
    // we have 12 divisors here, but n must be larger than 1 and n < n + 2f - 1 because f >= 1
    // so (P+1)*2 will be the number of divisors of 2S
    // => number of divisors of S must be P+1
    sieveBase(1000000);
    int te;
    cin >> te;
    FOR(o,1,te) {
        ll P;
        cin >> P;
        cout << "Case " << o << ": " << solve(P) << "\n";
    }
    return 0;
}
