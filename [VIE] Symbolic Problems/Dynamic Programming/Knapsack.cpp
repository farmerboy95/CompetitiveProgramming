/*
    Keywords: dp
    Đề bài:
        - Cho n món đồ, mỗi món có khối lượng w[i] và giá trị v[i]. Có một cái túi có thể chứa
        tối đa W đơn vị khối lượng.
        - Tìm giá trị lớn nhất mà túi có thể chứa sao cho tổng khối lượng của các món đồ
        được chứa không vượt quá W.
    Lời giải:
        - Gọi dp[i][j] = giá trị lớn nhất mà túi có thể chứa khi chỉ xét i món đồ đầu tiên
        và tổng khối lượng không vượt quá j.
        - Ban đầu ta có dp[0][0] = 0, vì chưa có món đồ nào. Còn lại dp[i][j] = -1 vì chưa
        có các trạng thái đó.
        - Với mỗi món đồ i, ta cập nhật dp[i][j] bằng cách thử chọn hoặc không chọn món đồ i.
        Nếu không chọn món đồ i, dp[i][j] = dp[i-1][j]. Nếu chọn món đồ i, dp[i][j] = dp[i-1][j-w[i]] + v[i].
        Kết quả là dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i]] + v[i]). Tất nhiên là ta chỉ
        sử dụng dp[i-1][] nếu nó khác -1.
        - Đáp án là giá trị lớn nhất trong các dp[n][j] với j = 0, 1, ..., W.
        - Tuy nhiên ta thấy là giá trị dp[i][] chỉ phụ thuộc vào dp[i-1][], nên ta chỉ cần
        mảng một chiều dp[].
        - Gọi dp[j] = giá trị lớn nhất mà túi có thể chứa khi tổng khối lượng không vượt quá j.
        - Ban đầu ta có dp[0] = 0, vì chưa có món đồ nào. Còn lại dp[j] = -1 vì chưa
        có các trạng thái đó.
        - Với mỗi món đồ i, nếu không chọn nó thì ta đã có sẵn dp[j], còn nếu chọn nó thì
        dp[j] = dp[j-w[i]] + v[i]. Kết quả là dp[j] = max(dp[j], dp[j-w[i]] + v[i]). Tuy
        nhiên ở đây, nếu ta duyệt j từ 0 đến W, ta có thể sẽ sử dụng v[i] nhiều lần, nên
        ta phải duyệt j từ W về 0 để tránh trường hợp trùng lặp.
        - Đáp án là giá trị lớn nhất trong các dp[j] với j = 0, 1, ..., W.
        - Độ phức tạp O(n*W).
    Nguồn: 
        - https://atcoder.jp/contests/dp/tasks/dp_d
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
const int MAXW = 100010;
const int MAXK = 16;
const int MAXQ = 200010;

int n, W, w[MAXN], v[MAXN];
ll dp[MAXW];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> W;
    FOR(i,1,n) cin >> w[i] >> v[i];

    FOR(i,0,W) dp[i] = -1;
    dp[0] = 0;

    FOR(i,1,n) {
        FORE(j,W,w[i]) {
            if (dp[j-w[i]] == -1) continue;
            dp[j] = max(dp[j], dp[j-w[i]] + v[i]);
        }
    }

    ll res = 0;
    FOR(i,0,W) res = max(res, dp[i]);
    cout << res;
    return 0;
}
