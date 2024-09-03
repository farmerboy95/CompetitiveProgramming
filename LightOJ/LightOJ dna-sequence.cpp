/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Remove all strings that are substrings of other strings
        - For the rest, we use DP bitmask to find the minimum length of the shortest
        string that contains all strings, with dp top-down approach, starting from
        the first string.
        - Print the result by tracing from the first to the last string, always choose
        the lexicographically smallest string that can be added to the current string
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

const int MAXN = 15;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n;
string s[MAXN];
int dp[1<<MAXN][MAXN], f[MAXN][MAXN];

int solve(int mask, int cur) {
    if (mask == (1<<n)-1) return 0;
    if (dp[mask][cur] != INF) return dp[mask][cur];
    int &res = dp[mask][cur];

    FOR(i,0,n-1) {
        if (mask & (1<<i)) continue;
        res = min(res, solve(mask | (1<<i), i) + SZ(s[i]) - f[cur][i]);
    }

    return res;
}

void print(int mask, int cur) {
    if (mask == (1<<n)-1) {
        cout << "\n";
        return;
    }
    int res = dp[mask][cur];

    string minStr = "Z";
    int pos = -1;
    FOR(i,0,n-1) {
        if (mask & (1<<i)) continue;
        if (res == solve(mask | (1<<i), i) + SZ(s[i]) - f[cur][i]) {
            string tmpStr = s[i].substr(f[cur][i]);
            if (tmpStr < minStr) {
                minStr = tmpStr;
                pos = i;
            }
        }
    }

    cout << minStr;
    print(mask | (1<<pos), pos);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cin >> n;
        vs t;
        FOR(i,0,n-1) {
            string str;
            cin >> str;
            FOR(j,0,SZ(t)-1) {
                if (t[j].find(str) != string::npos) {
                    str = "";
                    break;
                }
            }
            if (str != "") t.push_back(str);
        }
        n = SZ(t);
        FOR(i,0,n-1) s[i] = t[i];
        sort(s, s+n);

        FOR(i,0,n-1) {
            FOR(j,0,n-1) {
                if (i == j) {
                    f[i][j] = SZ(s[i]);
                    continue;
                }
                int len = min(SZ(s[i]), SZ(s[j]));
                f[i][j] = 0;
                FOR(k,0,len-1) {
                    if (s[i].substr(SZ(s[i])-len+k) == s[j].substr(0,len-k)) {
                        f[i][j] = len-k;
                        break;
                    }
                }
            }
        }

        FOR(mask,0,(1<<n)-1) {
            FOR(i,0,n-1) {
                dp[mask][i] = INF;
            }
        }

        int res = INF, pos = 0;
        FOR(i,0,n-1) {
            int cur = solve(1<<i, i) + SZ(s[i]);
            if (cur < res) {
                res = cur;
                pos = i;
            }
        }

        cout << "Case " << o << ": ";
        cout << s[pos];
        print(1<<pos, pos);
    }
    return 0;
}