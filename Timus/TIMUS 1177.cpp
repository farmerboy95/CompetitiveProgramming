/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Parse the strings then use dp to match them.
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

string s, s1, s2;
int n, m, r[MAXN], l[MAXN];
int dp[MAXN][MAXN];
vector<vs> v2;

void parseStrings() {
    s1 = s2 = "";
    s = s + " ";
    int i = 1;
    while (i < SZ(s)) {
        if (s[i] == '\'') {
            if (s[i+1] == '\'') {
                s1 += "'";
                i += 2;
            } else {
                i++;
                break;
            }
        } else {
            s1 += s[i];
            i++;
        }
    }

    i += 7;
    while (i < SZ(s)) {
        if (s[i] == '\'') {
            if (s[i+1] == '\'') {
                s2 += "'";
                i += 2;
            } else {
                i++;
                break;
            }
        } else {
            s2 += s[i];
            i++;
        }
    }
}

int match(int i, int j) {
    if (SZ(v2[j]) == 1) {
        char ch = v2[j][0][0];
        if (s1[i] == ch) return 1;
        if (ch == '_') return 1;
        return 0;
    }

    if (v2[j][0][0] == '^') {
        FOR(k,1,SZ(v2[j])-1) {
            string &cur = v2[j][k];
            if (SZ(cur) == 1) {
                if (s1[i] == cur[0]) return 0;
            } else {
                if (cur[0] <= s1[i] && s1[i] <= cur[2]) return 0;
            }
        }
        return 1;
    } else {
        FOR(k,1,SZ(v2[j])-1) {
            string &cur = v2[j][k];
            if (SZ(cur) == 1) {
                if (s1[i] == cur[0]) return 1;
            } else {
                if (cur[0] <= s1[i] && s1[i] <= cur[2]) return 1;
            }
        }
        return 0;
    }
}

int solve(int i, int j) {
    if (i < 0 && j < 0) return 1;
    if (i < 0) {
        if (SZ(v2[j]) == 1 && v2[j][0][0] == '%') {
            return solve(i, j-1);
        } else {
            return 0;
        }
    }
    if (j < 0) return 0;

    if (dp[i][j] != -1) return dp[i][j];

    int &res = dp[i][j];
    res = 0;

    if (SZ(v2[j]) == 1 && v2[j][0][0] == '%') {
        res |= solve(i, j-1);
        res |= solve(i-1, j);
        res |= solve(i-1, j-1);
    } else {
        if (match(i, j)) res |= solve(i-1, j-1);
    }

    return res;
}

int ok() {
    stack<int> st;
    FOR(i,0,m-1) {
        if (s2[i] == '[') {
            if (SZ(st)) continue;
            st.push(i);
        } else if (s2[i] == ']') {
            if (SZ(st) == 0) continue;
            l[i] = st.top();
            r[st.top()] = i;
            st.pop();
        }
    }

    int i = 0;
    v2.clear();
    while (i < m) {
        if (s2[i] == '[') {
            int lef = i+1, rig = r[i]-1;
            i = r[i]+1;
            vs cur;
            if (s2[lef] == '^') {
                cur.push_back("^");
                lef++;
            } else {
                cur.push_back("+");
            }
            int j = lef;
            while (j <= rig) {
                if (j + 2 <= rig && s2[j+1] == '-') {
                    string x = string() + s2[j] + '-' + s2[j+2];
                    cur.push_back(x);
                    j += 3;
                } else {
                    string x = string() + s2[j];
                    cur.push_back(x);
                    j++;
                }
            }
            dbg(cur);
            v2.push_back(cur);
        } else {
            string x = string() + s2[i];
            v2.push_back({x});
            i++;
        }
    }

    m = SZ(v2);
    dbg(v2);

    FOR(i,0,n-1) FOR(j,0,m-1) dp[i][j] = -1;
    return solve(n-1, m-1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    getline(cin, s);
    while (te--) {
        getline(cin, s);
        parseStrings();

        n = SZ(s1);
        m = SZ(s2);

        if (ok()) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
