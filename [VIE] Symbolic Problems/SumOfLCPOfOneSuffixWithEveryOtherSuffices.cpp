/*
    Keywords: suffix array, LCP sum, nearest smaller element
    Đề bài:
        - Cho 1 string, với mỗi hậu tố bắt đầu ở i, tìm tổng LCP của hậu tố đó với tất cả
        các hậu tố khác
    Lời giải:
        - Nhìn vào bài này thì ta biết ngay cần phải build suffix array cho string.
        - Dễ dàng nhận ra LCP(suffix i, suffix j) khi rank[i] < rank[j] sẽ là 
        min(LCP[rank[i]+1], LCP[rank[i]+2], ..., LCP[rank[j]])
        - Gọi fromLeft[i] = tổng LCP của suffix ở rank i với các suffix ở rank phía trên nó
        - Gọi fromRight[i] = tổng LCP của suffix ở rank i với các suffix ở rank phía dưới nó
        - Tại suffix ở rank i, ta tìm thằng gần nhất rank trên nó (j) có LCP nhỏ hơn hoặc bằng
        LCP ở i (dùng stack preprocessing trong O(n)) khi đó ta có thể cộng fromLeft[j] vào
        fromLeft[i] và thêm đoạn j đến i-1 vào fromLeft[i]
        - Làm tương tự với fromRight, có thể sửa mảng LCP cho phù hợp và dễ làm hơn.
        - Cuối cùng res[i] = fromLeft[i] + fromRight[i] + độ dài của hậu tố ở rank i (vì ta
        chưa tính thằng này)
        - Độ phức tạp: O(n + SA(n)), trong đó SA(n) là độ phức tạp cần để build suffix array.
    Nguồn: 
        - https://atcoder.jp/contests/abc213/tasks/abc213_f
        - https://atcoder.jp/contests/abc213/editorial/2412
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
string ts(bool b) { return ts((int)b); }
template<class T> string ts(complex<T> c) { stringstream ss; ss << c; return ss.str(); }
template<class T> using V = vector<T>;
string ts(V<bool> v) {string res = "{"; FOR(i,0,SZ(v)-1) res += char('0'+v[i]); res += "}"; return res; }
template<size_t sz> string ts(bitset<sz> b) { string res = ""; FOR(i,0,SZ(b)-1) res += char('0'+b[i]); return res; }
template<class T, class U> string ts(pair<T,U> p);
template<class T> string ts(T v) { // containers with begin(), end()
    bool fst = 1; string res = "";
    for (const auto& x: v) { if (!fst) res += " "; fst = 0; res += ts(x); }
    return res;
}
template<class T, class U> string ts(pair<T,U> p) { return "("+ts(p.FI)+", "+ts(p.SE)+")"; }

// OUTPUT
template<class T> void pr(T x) { cout << ts(x); }
template<class T, class ...U> void pr(const T& t, const U&... u) { pr(t); pr(u...); }
void ps() { pr("\n"); } // print w/ spaces
template<class T, class ...U> void ps(const T& t, const U&... u) { pr(t); if (sizeof...(u)) pr(" "); ps(u...); }

// DEBUG
void DBG() { cerr << "]" << endl; }
template<class T, class ...U> void DBG(const T& t, const U&... u) { cerr << ts(t); if (sizeof...(u)) cerr << ", "; DBG(u...); }
#define dbg(...) cerr << "Line(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#define chk(...) if (!(__VA_ARGS__)) cerr << "Line(" << __LINE__ << ") -> function(" \
        << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\n", exit(0);

const ld PI = acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
const ld EPS = 1e-9;
const ll MODBASE = 1000000007LL;
const int INF = 0x3f3f3f3f;

const int MAXN = 1000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int t, SA[MAXN], RA[MAXN], c[MAXN], tempRA[MAXN], tempSA[MAXN];
int n, behind[MAXN], LCP[MAXN], PLCP[MAXN];
ll fromLeft[MAXN], fromRight[MAXN];
string s;

void countingSort(int k) {
    int sum = 0, maxi = max(300, n);
    memset(c, 0, sizeof(c));
    FOR(i,0,n-1)
        if (i+k < n) c[RA[i+k]]++;
        else c[0]++;
    FOR(i,0,maxi-1) {
        int t = c[i];
        c[i] = sum;
        sum += t;
    }
    FOR(i,0,n-1) {
        int a = 0;
        if (SA[i]+k < n) a = RA[SA[i]+k];
        tempSA[c[a]++] = SA[i];
    }
    FOR(i,0,n-1) SA[i] = tempSA[i];
}

void suffixArray() {
    int r;
    FOR(i,0,n-1) SA[i] = i; FOR(i,0,n-1) RA[i] = s[i];
    for (int k = 1; k < n; k <<= 1) {
        countingSort(k);
        countingSort(0);
        tempRA[SA[0]] = r = 0;
        FOR(i,1,n-1) {
            if (RA[SA[i]] != RA[SA[i-1]]) {
                tempRA[SA[i]] = ++r;
                continue;
            }
            int a, b;
            if (SA[i]+k >= n) a = 0;
            else a = RA[SA[i]+k];
            if (SA[i-1]+k >= n) b = 0;
            else b = RA[SA[i-1]+k];
            if (a == b) tempRA[SA[i]] = r;
            else tempRA[SA[i]] = ++r;
        }
        FOR(i,0,n-1) RA[i] = tempRA[i];
        if (r == n-1) break;
    }
}

void buildLCP() {
    behind[SA[0]] = -1;
    FOR(i,1,n-1) behind[SA[i]] = SA[i-1];
    int L = 0;
    FOR(i,0,n-1) {
        if (behind[i] == -1) {
            PLCP[i] = 0;
            continue; 
        }
        while (s[i+L] == s[behind[i]+L]) L++; PLCP[i] = L;
        L = max(L-1,0);
    }
    FOR(i,0,n-1) LCP[i] = PLCP[SA[i]];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    cin >> s;

    s = s + "$";
    n++;

    suffixArray();
    buildLCP();

    stack<int> st;
    FOR(i,0,n-1) {
        while (SZ(st) && LCP[st.top()] > LCP[i]) st.pop();
        int ok = -1;
        if (SZ(st)) ok = st.top();
        st.push(i);

        if (ok != -1) {
            int range = i - ok;
            fromLeft[SA[i]] += (ll) range * LCP[i];
            fromLeft[SA[i]] += fromLeft[SA[ok]];
        }
    }

    while (SZ(st)) st.pop();
    FOR(i,0,n-2) LCP[i] = LCP[i+1];
    LCP[n-1] = 0;

    FORE(i,n-1,0) {
        while (SZ(st) && LCP[st.top()] > LCP[i]) st.pop();
        int ok = -1;
        if (SZ(st)) ok = st.top();
        st.push(i);

        if (ok != -1) {
            int range = ok - i;
            fromRight[SA[i]] += (ll) range * LCP[i];
            fromRight[SA[i]] += fromRight[SA[ok]];
        }
    }

    FOR(i,0,n-2) cout << fromLeft[i] + fromRight[i] + n-1-i << "\n";
    return 0;
}
