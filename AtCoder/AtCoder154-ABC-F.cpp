/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We can easily prove that f(r,c) = f(r-1,0) + f(r-1,1) + ... + f(r-1,c)
        (Because f(r,c) = f(r-1,c) + f(r,c-1) and do the same thing with f(r,c-1)...)
        - So we can easily calculate sum of f(r,x) (0 <= x <= c), f(r,x) = f(r+1,c)
        - As limit is 10^6, we can iterate through r1 and r2, use prefix sum to calculate 
        sum of f(i,c1) + ... + f(i,c2)
        - Finally, how to calculate f(r, c)? It would be C(r+c, c) = C(r+c, r)
        => f(r+1,c) = C(r+c+1, r+1)
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
const int MAXN = 3000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ll f[MAXN], rev[MAXN];
int r1, c1, r2, c2;

ll binPowMod(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % MODBASE;
        a = a * a % MODBASE;
        b >>= 1LL;
    }
    return res;
}

ll add(ll a, ll b) {
    return (a + b) % MODBASE;
}

ll mul(ll a, ll b) {
    return a * b % MODBASE;
}

ll sub(ll a, ll b) {
    return (a - b + MODBASE) % MODBASE;
}

ll C(ll n, ll k) {
    if (k > n || k < 0) return 0;
    return mul(f[n], mul(rev[n-k], rev[k]));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    f[0] = 1;
    rev[0] = binPowMod(f[0], MODBASE-2);
    FOR(i,1,3000000) {
        f[i] = mul(f[i-1], i);
        rev[i] = binPowMod(f[i], MODBASE-2);
    }
    cin >> r1 >> c1 >> r2 >> c2;
    ll res = 0;
    FOR(i,r1,r2) res = add(res, sub(C(c2+i+1, i+1), C(c1-1+i+1, i+1)));
    cout << res;
    return 0;
}
