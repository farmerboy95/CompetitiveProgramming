/*
    Keywords: dp
    Đề bài:
        - Cho một xâu độ dài n, gồm các ký tự 'O' và 'K' và một số nguyên k.
        - Gọi a là số lần xuất hiện của "OK" trong xâu, b là số lần xuất hiện của "KO" trong xâu.
        - Bạn được dùng k lần để đổi chỗ 2 ký tự bất kỳ trong xâu. In ra giá trị lớn nhất của a^2 - b^2.
    Lời giải:
        - Ta có một số nhận xét sau:
            + k nhỏ (k <= 10)
            + Khi ta đếm số lượng cặp "OK" và "KO", thực ra chênh lệch giữa số lượng cặp sẽ không 
            quá 1 đơn vị. Tức số cặp "OK" có thể nhiều hơn "KO" là 1 cặp, hoặc bằng nhau, hoặc ít 
            hơn 1 cặp. Và do k là số dương, tức ta được phép biến đổi ít nhất 1 lần, thì rõ ràng ta
            hoàn toàn có thể làm cho hiệu giữa số cặp OK và số cặp KO >= 0
            + Giá trị a^2 - b^2 = (a - b) * (a + b). Vậy a - b chính là hiệu giữa số cặp OK và KO, 
            và giá trị a - b này chỉ = -1, 0 hoặc 1. Như vậy nếu ta lưu trữ diff là giá trị a - b,
            vậy khi ta có diff, ta chỉ việc tính toán sao cho a + b lớn nhất.
        - Từ đó, ta sử dụng quy hoạch động như sau:
            + Gọi f[i][changeK][changeO][diff][state] là giá trị a + b lớn nhất có thể khi xét 
                + i ký tự đầu tiên của chuỗi s
                + changeK là số lượng vị trí từ O đổi sang K
                + changeO là số lượng vị trí từ K đổi sang O
                + diff là hiệu số cặp OK và KO
                + state = 1 nếu ký tự cuối là O, state = 2 nếu ký tự cuối là K
            + Khi xét i vị trí, xét lên vị trí i + 1,
                + Khi kí tự cuối là O (state = 1), khi thêm ký tự mới vào, ta có thể để nguyên hoặc
                đổi, nếu ở cuối là OK thì diff tăng thêm 1, tổng a+b tăng thêm 1, ngược lại nếu ở
                cuối là OO thì diff và a+b giữ nguyên.
                + Khi kí tự cuối là K (state = 2), khi thêm ký tự mới vào, ta có thể để nguyên hoặc
                đổi, nếu ở cuối là KO thì diff giảm đi 1, tổng a+b tăng thêm 1, ngược lại nếu ở cuối
                là KK thì diff và a+b giữ nguyên.
                + Nhớ là khi đổi ký tự thì thêm 1 vào changeK hoặc changeO
            + Bởi vì kết quả là (a - b) * (a + b), nên ta sẽ lấy Max(diff * f[n][change][change][diff][state]),
            change từ 0 đến k, vì ta sẽ ứng số thay đổi K và số thay đổi O với nhau.
            + Để tránh MLE, ta chỉ cần tính f[i+1] theo f[i], nên chỉ cần lưu 2 dòng f[i][] và f[i+1][]
        - Độ phức tạp O(n * k^2)
    Nguồn: 
        - https://oj.vnoi.info/problem/vnoicup24_r2_d
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

int n, k;
string s;
int dp[2][12][12][3][3];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    while (te--) {
        cin >> n >> k >> s;

        // init
        FOR(i,0,1) {
            FOR(changeK,0,k) {
                FOR(changeO,0,k) {
                    FOR(diff,0,2) {
                        FOR(ch,0,2) {
                            dp[i][changeK][changeO][diff][ch] = -INF;
                        }
                    }
                }
            }
        }

        dp[0][0][0][1][0] = 0;
        FOR(i,0,n-1) {
            int cur = i % 2;
            int nex = 1 - cur;
            FOR(changeK,0,k) {
                FOR(changeO,0,k) {
                    FOR(diff,0,2) {
                        FOR(ch,0,2) {
                            dp[nex][changeK][changeO][diff][ch] = -INF;
                        }
                    }
                }
            }

            FOR(changeK,0,k) {
                FOR(changeO,0,k) {
                    FOR(diff,0,2) {
                        FOR(ch,0,2) {
                            if (dp[cur][changeK][changeO][diff][ch] == -INF) continue;

                            // changeK = number of O that we have changed to K
                            // changeO = number of K that we have changed to O

                            // ch = 0 -> unknown, only when we haven't had any character
                            // ch = 1 -> end with O
                            // ch = 2 -> end with K
                            if (ch == 0) {
                                // first case, next character is O
                                ckmax(dp[nex][changeK][changeO + (s[i] == 'K')][diff][1], dp[cur][changeK][changeO][diff][ch]);
                                // second case, next character is K
                                ckmax(dp[nex][changeK + (s[i] == 'O')][changeO][diff][2], dp[cur][changeK][changeO][diff][ch]);
                            } else if (ch == 1) {
                                // previous character is O

                                // first case, next character is O
                                ckmax(dp[nex][changeK][changeO + (s[i] == 'K')][diff][1], dp[cur][changeK][changeO][diff][ch]);
                                // second case, next character is K
                                ckmax(dp[nex][changeK + (s[i] == 'O')][changeO][diff + 1][2], dp[cur][changeK][changeO][diff][ch] + 1);
                            } else {
                                // previous character is K

                                // first case, next character is O
                                ckmax(dp[nex][changeK][changeO + (s[i] == 'K')][diff - 1][1], dp[cur][changeK][changeO][diff][ch] + 1);
                                // second case, next character is K
                                ckmax(dp[nex][changeK + (s[i] == 'O')][changeO][diff][2], dp[cur][changeK][changeO][diff][ch]);
                            }
                        }
                    }
                }
            }
        }

        int res = -INF;
        FOR(change,0,k) {
            FOR(diff,0,2) {
                FOR(ch,1,2) {
                    if (dp[n % 2][change][change][diff][ch] == -INF) continue;
                    res = max(res, (diff - 1) * dp[n % 2][change][change][diff][ch]);
                }
            }
        }

        cout << res << "\n";
    }
    return 0;
}
