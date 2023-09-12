/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's assume a = b for simplicity.
        - To get the expected number of attacked cells, we can get sum of expected value of
        a cell being attack, meaning it's the probability of a cell being attacked.
        - When a = b, a cell (x, y) is attacked when there is a knight right at (x, y) or
        there is a knight at (x + a, y + a) or (x + a, y - a) or (x - a, y + a) or (x - a, y - a),
        meaning 4 other cells. But some of the cells may not have all 4 other cells inside the
        board.
        - Let x be the number of cells that from those cells, we can go to the current cell with
        one move. The probability of the current cell being attacked is 
            (x+1) / n^2 + (n^2 - x) / n^2 * (x+1) / (n^2 - 1)
        - Why do we have x+1? Because we need to consider the case when there is a knight at the
        current cell as well.
        - So if we can count the number of cells that have x cells covering them (let it be cnt[x]),
        the result would be sum of cnt[x] * (x+1) / n^2 + (n^2 - x) / n^2 * (x+1) / (n^2 - 1), x is
        from 0 to 4 (when a = b, we are still considering this case).
        - How to count cnt[x]? We know that only cells from (a+1, a+1) to (n, n) can go to (x-a, y-a) 
        right? Similarly, only cells from (n-a+1, a+1) to (1, n) can go to (x+a, y-a). If you draw
        a square with 4 areas like that, it will divide the board into 9 parts.
            -------
            |1|2|1|
            -------
            |2|4|2|
            -------
            |1|2|1|
            -------
        - The number in the square is the number of cells that can go to the current cell with one move.
        We also have the border coordination already, so we can count cnt[x] very easily.
        - What about the case when a != b? This is harder but similar. We can do the same thing as above
        to split the board into many parts, and since cells in the same part have the same number of covering
        cells, we can update count in each part and get cnt easily.
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

class TheKnights {
    public:
    bool isInside(pi rangeX, pi rangeY, pi rangeX2, pi rangeY2) {
        if (rangeX.first > rangeX2.second || rangeX.second < rangeX2.first) return false;
        if (rangeY.first > rangeY2.second || rangeY.second < rangeY2.first) return false;
        return true;
    }

    ld find(int n, int a, int b) {
        vl cnt(9, 0);
        vi x, y;
        x.push_back(1);
        y.push_back(1);
        vi DX, DY;
        if (a == b) {
            if (a+1 <= n+1) x.push_back(a+1);
            if (n-a+1 >= 1) x.push_back(n-a+1);
            x.push_back(n+1);

            if (a+1 <= n+1) y.push_back(a+1);
            if (n-a+1 >= 1) y.push_back(n-a+1);
            y.push_back(n+1);

            DX = {-a, -a, a, a};
            DY = {-a, a, -a, a};
        } else {
            if (a+1 <= n+1) x.push_back(a+1);
            if (b+1 <= n+1) x.push_back(b+1);
            if (n-a+1 >= 1) x.push_back(n-a+1);
            if (n-b+1 >= 1) x.push_back(n-b+1);
            x.push_back(n+1);

            if (a+1 <= n+1) y.push_back(a+1);
            if (b+1 <= n+1) y.push_back(b+1);
            if (n-a+1 >= 1) y.push_back(n-a+1);
            if (n-b+1 >= 1) y.push_back(n-b+1);
            y.push_back(n+1);

            DX = {-a, -a, a, a, -b, -b, b, b};
            DY = {-b, b, -b, b, -a, a, -a, a};
        }
        remDup(x);
        remDup(y);
        vector<vi> dem(SZ(x)-1, vi(SZ(y)-1, 0));
        FOR(i,0,SZ(dem)-1) {
            FOR(j,0,SZ(dem[0])-1) {
                pi rangeX = {x[i], x[i+1] - 1};
                pi rangeY = {y[j], y[j+1] - 1};
                if (rangeX.first > rangeX.second || rangeY.first > rangeY.second) continue;

                FOR(k,0,SZ(DX)-1) {
                    pi rangeX2 = {rangeX.first + DX[k], rangeX.second + DX[k]};
                    pi rangeY2 = {rangeY.first + DY[k], rangeY.second + DY[k]};
                    if (isInside(rangeX2, rangeY2, {1, n}, {1, n})) dem[i][j]++;
                }
            }
        }

        FOR(i,0,SZ(dem)-1) {
            FOR(j,0,SZ(dem[0])-1) {
                cnt[dem[i][j]] += (ld) (x[i+1] - x[i]) * (y[j+1] - y[j]);
            }
        }

        ll nn = (ll) n * n;
        ld res = 0;
        FOR(i,0,8) {
            res += (ld) cnt[i] * ((ld) (i + 1) / nn + (ld) (nn - (i + 1)) / nn * (ld) (i + 1) / (nn - 1));
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    TheKnights solver;
    setPrec(9);
    cout << solver.find(2, 1, 1) << "\n";
    cout << solver.find(47, 7, 74) << "\n";
    cout << solver.find(3, 2, 1) << "\n";
    cout << solver.find(9999, 999, 99) << "\n";
    cout << solver.find(10, 1, 6) << "\n";
    cout << solver.find(5, 5, 4) << "\n";
    cout << solver.find(4, 4, 5) << "\n";
    cout << solver.find(124823342, 45386564, 100951687) << "\n";
    cout << solver.find(183856503, 102695213, 60284295) << "\n";
    cout << solver.find(558782248, 558463543, 381881321) << "\n";
    cout << solver.find(925404249, 438144414, 800016186) << "\n";
    cout << solver.find(921115693, 689349088, 202813053) << "\n";
    cout << solver.find(633986483, 186837751, 425941920) << "\n";
    cout << solver.find(428649871, 95595700, 196624736) << "\n";
    cout << solver.find(330167461, 327554576, 20514242) << "\n";
    cout << solver.find(899169639, 472435499, 680900359) << "\n";
    cout << solver.find(903943749, 588260565, 302934536) << "\n";
    cout << solver.find(551344169, 182448637, 414844903) << "\n";
    cout << solver.find(800051864, 651969236, 179379089) << "\n";
    cout << solver.find(807648924, 432243241, 379393432) << "\n";
    cout << solver.find(999999048, 999999924, 999999452) << "\n";
    cout << solver.find(999999234, 999999550, 999999873) << "\n";
    cout << solver.find(999999245, 999999839, 999999540) << "\n";
    cout << solver.find(999999750, 999999818, 999999760) << "\n";
    cout << solver.find(999999409, 999999572, 999999921) << "\n";
    cout << solver.find(703191760, 145374404, 145374404) << "\n";
    cout << solver.find(219470790, 114967900, 114967900) << "\n";
    cout << solver.find(129333615, 60861281, 60861281) << "\n";
    cout << solver.find(968295264, 605815983, 605815983) << "\n";
    cout << solver.find(591907600, 58565539, 58565539) << "\n";
    cout << solver.find(1000000000, 583526549, 123155129) << "\n";
    cout << solver.find(999999999, 304781299, 330392701) << "\n";
    cout << solver.find(1000000000, 12556648, 541681559) << "\n";
    cout << solver.find(1000000000, 630812393, 15410460) << "\n";
    cout << solver.find(999999999, 817504650, 227186913) << "\n";
    cout << solver.find(999999999, 757598303, 532893574) << "\n";
    cout << solver.find(999999999, 890695666, 122069938) << "\n";
    cout << solver.find(999999999, 281698010, 168402490) << "\n";
    cout << solver.find(1000000000, 266151066, 348129641) << "\n";
    cout << solver.find(999999999, 702171433, 280562118) << "\n";
    cout << solver.find(2, 1, 1) << "\n";
    cout << solver.find(3, 1, 1) << "\n";
    cout << solver.find(4, 1, 2) << "\n";
    cout << solver.find(3, 2, 2) << "\n";
    cout << solver.find(1000000000, 1000000000, 1000000000	) << "\n";
    cout << solver.find(1000000000, 1, 1) << "\n";
    cout << solver.find(1000000000, 1, 2) << "\n";
    cout << solver.find(1000000000, 2, 2) << "\n";
    cout << solver.find(100000, 300, 200) << "\n";
    cout << solver.find(999999999, 523, 11337) << "\n";
    cout << solver.find(238293583, 2374, 48569) << "\n";
    cout << solver.find(1000000000, 2, 3) << "\n";
    cout << solver.find(1000000000, 268435456, 268435456) << "\n";
    cout << solver.find(1000000000, 1230, 2131) << "\n";
    cout << solver.find(1000000000, 3, 2) << "\n";
    cout << solver.find(1000000000, 500000000, 400000000) << "\n";
    return 0;
}
