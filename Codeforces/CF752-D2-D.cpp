/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's split this problem into 2 parts, palindromes and non-palindromes
        - For non-palindromes, they can be on the sides of the final palindrome only.
        So what we can do is to find matching pairs and take sum when it's positive.
        - For palindromes, they can be both on the sides and the middle. For each string,
        we take even number of such string to be on the sides, of course values must
        be positive. There are 2 cases left if there are odd positive values here:
            + The min positive value is the only value left, this can only be the middle
            part candidate, we put it in an "alone" list.
            + There are some non-positive values here, we take max of them to form a pair
            (with the min positive value), these can either be middle (min positive value) 
            or on sides (both of them if sum is positive). Put these 2 in "pairs" list.
        - Then there are 2 further cases:
            + If there is anything in "alone", the largest value should be the middle.
            The "pairs" can be used on sides if their sums are positive.
            + Then we can try with one of the "pairs" being the middle part (just the
            min positive value in that pair), then other pairs can be used on sides if 
            their sums are positive.
        - Result will be sum of non-palindromes and palindromes cases.
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

const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

string s[MAXN], rev[MAXN];
int k, n, a[MAXN];

int getResPalin(vi &idx) {
    map<string, vi> mp;
    TRAV(i, idx) {
        mp[s[i]].push_back(i);
    }
    int res = 0;
    vi alone;
    vpi pairs;
    FORALL(it, mp) {
        sort(ALL(it->SE), [&](int x, int y) {
            return a[x] > a[y];
        });
        vi &arr = it->SE;
        int sum = 0, cnt = 0;
        TRAV(x, arr) {
            if (a[x] <= 0) break;
            cnt++;
            sum += a[x];
        }
        if (cnt % 2 == 0) {
            res += sum;
        } else {
            // odd
            sum -= a[arr[cnt-1]];
            res += sum;
            if (cnt == SZ(arr)) {
                alone.push_back(a[arr[cnt-1]]);
            } else {
                pairs.push_back({a[arr[cnt-1]], a[arr[cnt]]});
            }
        }
    }
    sort(ALL(alone));
    reverse(ALL(alone));

    // mid in alone, take all pairs
    int Max = 0;
    if (SZ(alone)) {
        int cur = alone[0];
        TRAV(p, pairs) {
            if (p.FI + p.SE > 0) cur += p.FI + p.SE;
        }
        ckmax(Max, cur);
    }
    
    // mid in one of the pairs
    int cur = 0;
    TRAV(p, pairs) {
        if (p.FI + p.SE > 0) cur += p.FI + p.SE;
    }
    TRAV(p, pairs) {
        int w = cur;
        if (p.FI + p.SE > 0) w -= p.FI + p.SE;
        w += p.FI;
        ckmax(Max, w);
    }
    
    res += Max;
    return res;
}

int getResNonPalin(vi &idx) {
    map<string, vi> mp;
    TRAV(i, idx) {
        mp[s[i]].push_back(i);
    }
    FORALL(it, mp) {
        sort(ALL(it->SE), [&](int x, int y) {
            return a[x] > a[y];
        });
    }
    int res = 0;
    FORALL(it, mp) {
        string cur = s[it->SE[0]];
        string revCur = rev[it->SE[0]];
        vi &arr = it->SE;
        if (mp.count(revCur)) {
            vi &arr2 = mp[revCur];
            FOR(i,0,min(SZ(arr), SZ(arr2))-1) {
                if (a[arr[i]] + a[arr2[i]] <= 0) break;
                res += a[arr[i]] + a[arr2[i]];
            }
        }
    }
    return res / 2;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> k >> n;
    vi palin, nonPalin;
    FOR(i,1,k) {
        cin >> s[i] >> a[i];
        rev[i] = string(s[i].rbegin(), s[i].rend());
        if (s[i] == rev[i]) {
            palin.push_back(i);
        } else {
            nonPalin.push_back(i);
        }
    }
    int res = getResNonPalin(nonPalin) + getResPalin(palin);
    cout << res;
    return 0;
}
