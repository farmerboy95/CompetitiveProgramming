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
using ld = double;
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
//      https://cp-algorithms.com/algebra/chinese-remainder-theorem.html
//      https://codeforces.com/blog/entry/48798
// tested on: 
//      https://judge.yosupo.jp/problem/convolution_mod_1000000007 
//      https://judge.yosupo.jp/problem/convolution_mod
// based on: https://judge.yosupo.jp/submission/18618
// update MOD to use, remember to mod coefficients first before using the func
// faster than FFT.cpp
// --------------------------------------------------------------------------

int MOD = 998244353;

ll binPowMod(ll a, ll b, ll mod) {
    a %= mod;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % mod;
        a = a * a % mod;
        b >>= 1LL;
    }
    return res;
}

template <ll primitiveRoot, int LN, ll mod>
struct NTT {
    vector<ll> root;
    int N;
    
    NTT() {
        N = 1 << LN;
        root.assign(N, 1);

        ll unity = binPowMod(primitiveRoot, (mod - 1) >> LN, mod);
        FOR(i,1,N-1) root[i] = unity * root[i-1] % mod;
    }

    void ntt(vector<ll> &a, int invert) {
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

        for (int len = 2; len <= n; len <<= 1) {
            ll wlen = invert ? root[N - N/len] : root[N/len];
            for (int i = 0; i < n; i += len) {
                ll w = 1;
                FOR(j,0,len/2-1) {
                    ll u = a[i+j], v = a[i+j+len/2] * w % mod;
                    a[i+j] = (u+v) % mod;
                    a[i+j+len/2] = (u-v + mod) % mod;
                    w = w * wlen % mod;
                }
            }
        }

        if (invert) {
            ll inv = binPowMod(n, mod-2, mod);
            FOR(i,0,n-1) a[i] = a[i] * inv % mod;
        }
    }

    vector<ll> multiply(vector<ll> &v, vector<ll> &w) {
        vector<ll> fv(ALL(v)), fw(ALL(w));
        int n = 1;
        while (n < SZ(v) + SZ(w) - 1) n <<= 1;
        fv.resize(n); fw.resize(n);

        ntt(fv, 0); ntt(fw, 0);
        FOR(i,0,n-1) fv[i] = fv[i] * fw[i] % mod;

        ntt(fv, 1);
        fv.resize(SZ(v) + SZ(w) - 1);
        return fv;
   }
};

// increasing order
const ll M1 = 7340033,  M2 = 1051721729,  M3 = 1053818881;

NTT<3, 20, M1>  NTT1;
NTT<6, 20, M2>  NTT2;
NTT<7, 20, M3>  NTT3;

static const ll MM1 = binPowMod(M1, M2-2, M2);
static const ll MM2 = binPowMod(M1, M3-2, M3);
static const ll MM3 = binPowMod(M2, M3-2, M3);
static const ll MM4 = MM2 * MM3 % M3;
static const ll MM5 = M1 % MOD;
static const ll MM6 = MM5 * M2 % MOD;

ll garner(ll a1, ll a2, ll a3) {
    ll x1 = a1;
    ll x2 = (a2 - x1 + M2) * MM1 % M2;
    ll x3 = ((a3 - x1 + M3) * MM4 + (M3 - x2) * MM3) % M3;
    return (x1 + x2 * MM5 + x3 * MM6) % MOD;
}

vector<ll> multiply(vector<ll> &v, vector<ll> &w) {
    int n = SZ(v) + SZ(w) - 1;
    if (n <= 0) return {};

    vector<ll> p = NTT1.multiply(v, w);
    vector<ll> q = NTT2.multiply(v, w);
    vector<ll> r = NTT3.multiply(v, w);

    FOR(i,0,n-1) p[i] = garner(p[i], q[i], r[i]);

    return p;
}

// --------------------------------------------------------------------------

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;

    vector<ll> a(n), b(m); 
    FOR(i,0,n-1) cin >> a[i];
    FOR(i,0,m-1) cin >> b[i];

    a = multiply(a, b);

    for (int x : a) cout << x << ' ';
    return 0;
}
