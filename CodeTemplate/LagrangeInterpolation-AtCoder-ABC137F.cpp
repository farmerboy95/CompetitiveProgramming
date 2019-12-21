// http://webcache.googleusercontent.com/search?q=cache:ORgozBYxbWYJ:vuontoanblog.blogspot.com/2012/10/polynomial-interpolation-lagrange.html+&cd=1&hl=en&ct=clnk&gl=vn
// https://codeforces.com/blog/entry/68998?#comment-533822
// https://codeforces.com/blog/entry/68998?#comment-533849
#include <bits/stdc++.h>
#define FI first
#define SE second
#define EPS 1e-9
#define ALL(a) a.begin(),a.end()
#define SZ(a) int((a).size())
#define MS(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define WHATIS(x) cout << #x << " is " << x << endl;
#define ERROR(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x

using namespace std;
using ll = long long;
using ld = double;
typedef pair<int, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll MODBASE = 1000000007LL;
const int MAXN = 3010;
const int MAXM = 200010;
const int MAXK = 110;
const int MAXQ = 200010;

int mod;

void plusle(int &a, int b){
    a += b;
    if (a >= mod) a -= mod;
}

int mul(int a, int b) {
    return (int)((ll) a * b % mod);
}

int power(int a,int b) {
    int res=1;
    while (b>0) {
        if (b&1) res = mul(res,a);
        a = mul(a,a);
        b >>= 1;
    }
    return res;
}
int inv(int x) {
    return power(x,mod-2);
}

vector<int> mul(const vector<int> &p,int j) {
    /// c[0]+(c[1]*x)+(c[2]*(x^2)+...)c[n-1]*(x^(n-1))
    /// multiply
    /// (x-j)
    int n = SZ(p);
    vector<int> s(n+1,0); // 0 -> n
    FOR(i,0,n-1) plusle(s[i+1], p[i]);
    FOR(i,0,n-1) plusle(s[i], mul(p[i], j));
    return s;
}

vector<int> div(vector<int> p,int j) {
    /// c[0]+c[1]*x+...+c[n-1]*(x^(n-1))
    /// divide
    /// x-j
    int n = SZ(p);
    vector<int> s(n-1,0);
    FORE(i,n-1,1) {
        plusle(p[i-1], mul(j,p[i]));
        s[i-1]=p[i];
    }
    return s;
}

int get(const vector<int> &g,int x){
    int res=0;
    int now=1;
    FOR(i,0,SZ(g)-1) {
        plusle(res, mul(g[i], now));
        now = mul(now, x);
    }
    return res;
}

int p, a[MAXN];
vector<int> t = {0,1}; // x

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> p;
    mod = p;
    FOR(i,0,p-1) cin >> a[i];
    FOR(i,1,p-1) t = mul(t,i);
    vector<int> res(p, 0);

    FOR(i,0,p-1) {
        if (!a[i]) continue;
        vector<int> s = div(t,i);
        int cur = get(s,i);
        cur = inv(cur);
        FOR(j,0,SZ(s)-1) plusle(res[j], mul(s[j], cur));
    }

    FOR(i,0,p-1) cout << res[i] << ' ';
    return 0;
}
