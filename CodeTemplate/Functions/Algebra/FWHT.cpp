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
//      https://csacademy.com/blog/fast-fourier-transform-and-variations-of-it
//      https://codeforces.com/blog/entry/48417
//      https://codeforces.com/blog/entry/71899 (main idea)
// not tested yet
// --------------------------------------------------------------------------

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

void fwht(vector<ll> &P, bool inv, int op, ll mod) { // 1 xor 2 and 3 or
    int n = SZ(P);
    for (int len = 1; 2 * len <= n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            FOR(j,0,len-1) {
                int u = P[i + j];
                int v = P[i + len + j];
                if (!inv) {
                    if (op == 1) P[i + j] = (u + v) % mod, P[i + len + j] = (u - v + mod) % mod;
                    if (op == 2) P[i + j] = (u + v) % mod;
                    if (op == 3) P[i + len + j] = (u + v) % mod;
                }
                else {
                    if (op == 1) P[i + j] = (u + v) % mod, P[i + len + j] = (u - v + mod) % mod;
                    if (op == 2) P[i + j] = (u - v + mod) % mod;
                    if (op == 3) P[i + len + j] = (v - u + mod) % mod;
                }
            }
        }
    }
    if (inv && op == 1) {
        ll rev = binPowMod(n, mod-2, mod);
        FOR(i,0,n-1) P[i] = P[i] * rev % mod;
    }
}

vector<ll> multiply(vector<ll> &v, vector<ll> &w, int op, int mod) {
    int n = 1; 
    while (SZ(v) > n || SZ(w) > n) n <<= 1;
    v.resize(n);
    w.resize(n);
    fwht(v, 0, op, mod);
    fwht(w, 0, op, mod);

    vector<ll> res(n);
    FOR(i,0,n-1) res[i] = v[i] * w[i] % mod;
    fwht(res, 1, op, mod);
    return res;
}

// --------------------------------------------------------------------------

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    return 0;
}
