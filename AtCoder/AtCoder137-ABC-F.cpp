/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use Lagrange's interpolation
        - http://vuontoanblog.blogspot.com/2012/10/polynomial-interpolation-lagrange.html
        - https://codeforces.com/blog/entry/68998?#comment-533822
        - https://codeforces.com/blog/entry/68998?#comment-533849
*/

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
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x

using namespace std;
using ll = int;
using ld = double;
typedef pair<int, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 3010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int p, MOD, a[MAXN];
vector<int> t = {0, 1}; // x

ll binPowMod(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1LL;
    }
    return res;
}

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

ll inv(ll x) {
    return binPowMod(x, MOD-2);
}

vector<int> mul(const vector<int> &p, int j) {
    // p[0] + p[1] * x + p[2] * x^2 + ... + p[n-1] * x^(n-1)
    // multiply
    // x - j
    int n = SZ(p);
    vector<int> res(n+1,0); // 0 -> n
    FOR(i,0,n-1) res[i+1] = add(res[i+1], p[i]);
    FOR(i,0,n-1) res[i] = add(res[i], mul(p[i], j));
    return res;
}

vector<int> div(vector<int> p, int j) {
    // p[0] + p[1] * x + ... + p[n-1] * x^(n-1)
    // divide
    // x - j
    int n = SZ(p);
    vector<int> res(n-1,0);
    FORE(i,n-1,1) {
        p[i-1] = add(p[i-1], mul(j, p[i]));
        res[i-1] = p[i];
    }
    return res;
}

int get(const vector<int> &p, int x) {
    // f(x) = p[0] + p[1] * x + ... + p[n-1] * x^(n-1)
    // now = x^y
    int res = 0, now = 1;
    FOR(i,0,SZ(p)-1) {
        res = add(res, mul(p[i], now));
        now = mul(now, x);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> p;
    FOR(i,0,p-1) cin >> a[i];
    MOD = p;
    FOR(i,1,p-1) t = mul(t, i);
    vector<int> res(p, 0);

    FOR(i,0,p-1) {
        if (!a[i]) continue;
        vector<int> s = div(t,i);
        int cur = get(s,i);
        cur = inv(cur);
        FOR(j,0,SZ(s)-1) res[j] = add(res[j], mul(s[j], cur));
    }

    FOR(i,0,p-1) cout << res[i] << ' ';
    return 0;
}
