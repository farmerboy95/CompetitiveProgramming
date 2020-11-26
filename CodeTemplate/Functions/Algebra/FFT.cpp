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
using ll = long long;
using ld = long double;
typedef pair<int, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

// idea:
//      https://cp-algorithms.com/algebra/fft.html
//      https://codeforces.com/blog/entry/43499
//      https://codeforces.com/blog/entry/48417
//      CP4 book
// tested on: 
//      https://judge.yosupo.jp/problem/convolution_mod_1000000007 
//      https://judge.yosupo.jp/problem/convolution_mod
// slower than NTT_CRT.cpp if using mod
// --------------------------------------------------------------------------

void fft(vcd &a, int invert) {
    int n = SZ(a);

    int k = 0;
    while ((1<<k) < n) k++;
    vector<int> rev(n);
    // 10110 -> rev = 01101
    rev[0] = 0;
    int high1 = -1;
    FOR(i,1,n-1) {
        if ((i & (i-1)) == 0) high1++;
        rev[i] = rev[i ^ (1<<high1)];
        rev[i] |= (1 << (k-high1-1));
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }

    // roots of unity w(n) ^ k = cos(2pi * k / n) (+/-) i * sin(2pi * k / n)
    vcd roots(n/2);
    ld alpha = 2 * acos(-1) / n * (invert ? -1 : 1);
    FOR(i,0,n/2-1) roots[i] = cd(cos(alpha * i), sin(alpha * i));

    for (int len = 2; len <= n; len <<= 1) {
        int step = n / len;
        for (int i = 0; i < n; i += len) {
            FOR(j,0,len/2-1) {
                cd u = a[i+j], v = a[i+j+len/2] * roots[j * step];
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
            }
        }
    }

    if (invert) FOR(i,0,n-1) a[i] /= n;
}

vector<ll> multiply(vector<ll> &v, vector<ll> &w) {
    vcd fv(ALL(v)), fw(ALL(w));
    int n = 1;
    while (n < SZ(v) + SZ(w) - 1) n <<= 1;
    fv.resize(n); fw.resize(n);

    fft(fv, 0); fft(fw, 0);
    FOR(i,0,n-1) fv[i] *= fw[i];

    fft(fv, 1);
    n = SZ(v) + SZ(w) - 1;
    vector<ll> res(n);
    FOR(i,0,n-1) res[i] = (ll) round(fv[i].real());

    return res;
}

vector<ll> multiply(vector<ll> &v, vector<ll> &w, ll mod) {
    int n = 1;
    while (n < SZ(v) + SZ(w) - 1) n <<= 1;
    vcd v1(n), v2(n), r1(n), r2(n);
    FOR(i,0,SZ(v)-1) v1[i] = cd(v[i] >> 15, v[i] & 32767);
    FOR(i,0,SZ(w)-1) v2[i] = cd(w[i] >> 15, w[i] & 32767);
    fft(v1, 0);
    fft(v2, 0);

    FOR(i,0,n-1) {
        int j = (i ? (n-i) : i);
        cd ans1 = (v1[i] + conj(v1[j])) * cd(0.5, 0);
        cd ans2 = (v1[i] - conj(v1[j])) * cd(0, -0.5);
        cd ans3 = (v2[i] + conj(v2[j])) * cd(0.5, 0);
        cd ans4 = (v2[i] - conj(v2[j])) * cd(0, -0.5);
        r1[i] = (ans1 * ans3) + (ans1 * ans4) * cd(0, 1);
        r2[i] = (ans2 * ans3) + (ans2 * ans4) * cd(0, 1);
    }

    fft(r1, 1);
    fft(r2, 1);

    n = SZ(v) + SZ(w) - 1;
    vector<ll> res(n);
    FOR(i,0,n-1) {
        ll av = (ll) round(r1[i].real());
        ll bv = (ll) round(r1[i].imag()) + (ll) round(r2[i].real());
        ll cv = (ll) round(r2[i].imag());
        av %= mod, bv %= mod, cv %= mod;
        res[i] = (av << 30) + (bv << 15) + cv;
        res[i] %= mod;
        res[i] += mod;
        res[i] %= mod;
    }
    return res;
}

// --------------------------------------------------------------------------

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<ll> a, b;
    FOR(i,0,n-1) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    FOR(i,0,m-1) {
        int x;
        cin >> x;
        b.push_back(x);
    }
    vector<ll> res = multiply(a, b, 1000000007);
    FOR(i,0,SZ(res)-1) cout << res[i] << ' ';
    return 0;
}
