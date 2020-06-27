/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's assume the sequence A is 1, 2, ... N. We find the number of sequences B and then multiple
        the result with C(M, N) * N! (because when we change sequence A to another set, the way to find
        sequence B is still the same, and there are C(M, N) * N! sequences A)
        - In total we have C(M, N) * N! sequence B (initially), we need to remove some of the wrong
        sequences here. Let's consider p[j] as the number of sequences B that have at least j positions
        i that B[i] == i, so the result would be C(M, N) * N! - p[1] + p[2] - p[3] + .... (inclusion-exclusion
        principle)
        - There are C(N, j) ways to choose those j positions. Then, it doesn't matter what we put in 
        the remaining positions, so there are C(M-j, N-j) ways to choose the numbers and (N-j)! ways to
        rearrange them. So p[j] = C(N, j) * C(M-j, N-j) * (N-j)!
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
using ll = long long;
using ld = double;
typedef pair<int, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 500010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ll binPowMod(ll a, ll b) {
    a %= MODBASE;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % MODBASE;
        a = a * a % MODBASE;
        b >>= 1LL;
    }
    return res;
}

ll add(ll a, ll b) {
    return (a+b) % MODBASE;
}

ll mul(ll a, ll b) {
    return (a*b) % MODBASE;
}

ll sub(ll a, ll b) {
    return (a-b+MODBASE) % MODBASE;
}

ll f[MAXN], inv[MAXN];
int n, m;

ll C(int N, int K) {
    if (K > N || K < 0) return 0;
    return mul(f[N], mul(inv[N-K], inv[K]));
}

void init() {
    f[0] = 1;
    inv[0] = binPowMod(f[0], MODBASE-2);
    FOR(i,1,500000) {
        f[i] = mul(f[i-1], i);
        inv[i] = binPowMod(f[i], MODBASE-2);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    init();
    cin >> n >> m;
    ll res = mul(C(m, n), f[n]);
    FOR(i,1,n) {
        ll k = mul(C(n,i), mul(C(m-i, n-i), f[n-i]));
        if (i % 2) res = sub(res, k);
        else res = add(res, k);
    }
    res = mul(res, mul(C(m, n), f[n]));
    cout << res;
    return 0;
}
