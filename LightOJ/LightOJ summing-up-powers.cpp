/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Matrix exponentiation, steps in the code
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
using ll = unsigned long long; using ld = double; 
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
const ll MODBASE = (1LL << 32);
const int INF = 0x3f3f3f3f;

ll add(ll a, ll b) {
    return (a + b) % MODBASE;
}

ll mul(ll a, ll b) {
    return a * b % MODBASE;
}

struct Matrix {
    vector<vector<ll> > a;
    int n;
    Matrix(int N) {
        this->n = N;
        a.clear();
        vector<ll> b(N, 0);
        FOR(i,0,N-1) a.emplace_back(b);
    }
    Matrix operator * (Matrix &to) {
        Matrix ans(n);
        FOR(i,0,n-1)
            FOR(j,0,n-1)
                FOR(k,0,n-1) ans.a[i][j] = add(ans.a[i][j], mul(a[i][k], to.a[k][j]));
        return ans;
    }
    vector<ll> operator * (vector<ll> to) { 
        vector<ll> ans(n);
        FOR(i,0,n-1)
            FOR(j,0,n-1) ans[i] = add(ans[i], mul(a[i][j], to[j]));
        return ans;
    }
};

Matrix mu(Matrix A, ll n, Matrix B) {
    while (n) {
        if (n&1) B = B*A;
        A = A*A;
        n >>= 1;
    }
    return B;
}

ll C[55][55];

ll solve(ll n, int k) {
    // dp[n] - 1^k + 2^k + ... + n^k
    // => dp[n+1] = dp[n] + (n+1)^k
    // => dp[n+1] = dp[n] + kC0 * n^k + kC1 * n^(k-1) + ... + kCk * n^0
    // A x [dp[n], n^k ... n^0] = [dp[n+1], (n+1)^k ... 1]
    // A = 
    // [1, kC0, kC1, ..., kCk]
    // [0, kC0, kC1, ..., kCk]
    // [0, 0, (k-1)C0, ..., (k-1)C(k-1)]
    // [...]
    // [0, 0, ..., 1C0, 1C1]
    // [0, 0, ..., 0, 0C0]

    Matrix ONE(k+2);
    FOR(i,0,k+1) ONE.a[i][i] = 1;

    Matrix now(k+2);
    now.a[0][0] = 1;
    FOR(i,1,k+1) now.a[0][i] = C[k][i-1];
    FOR(i,1,k+1) {
        FOR(j,i,k+1) now.a[i][j] = C[k-i+1][j-i];
    }

    vl fi(k+2, 0);
    fi[k+1] = 1;
    fi = mu(now, n, ONE) * fi;
    return fi[0];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    FOR(i,0,50) {
        C[i][0] = C[i][i] = 1;
        FOR(j,1,i-1) C[i][j] = add(C[i-1][j-1], C[i-1][j]);
    }

    int te;
    cin >> te;
    FOR(o,1,te) {
        ll n;
        int k;
        cin >> n >> k;
        cout << "Case " << o << ": " << solve(n, k) << "\n";
    }
    return 0;
}
