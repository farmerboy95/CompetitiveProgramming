/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let x is a set of number (a1, a2, ..., an) that sum(a[i]) = n and a[i] >= 0
        - So our problem is to count the number of set x after k moves.
        - Let z[p] is a group of set x that sum(a[i]-1) = p (a[i] > 0). So after a move, z[p] can become
        z[p+1] and z[p-1]. For example n=5, (3 0 2 0 0) belongs to z[3]
        - Let res[p] is our result, the number of set x after p moves.
        - Clearly res[0] = numOf(z[0]), res[1] = numOf(z[1])
        - So res[2] = numOf(z[0]) + numOf(z[2]) + numOf(z[1]) (because z[1] can become itself after
        1 move, you can draw some cases to see)
        => res[3] = numOf(z[0]) + ... + numOf(z[3]) and so on.
        - Everything will stop at k = n-1 because max(p) <= n-1. So if k >= n-1 => 
        res[k] = res[n-1] = all cases = C(2*n-1, n-1)
        - What about k < n-1? We can count numOf(z[p]) (p <= k) like this: We got sum(a[i]-1) = p (a[i] > 0)
        so we would have p number 0, so first we choose p number 0 from n number: C(n, p). Then we put
        those p number into n-p group, number of ways is C(p + n-p-1, n-p-1) = C(n-1, n-p-1).
        - Overall, numOf(z[p]) = C(n, p) * C(n-1, n-p-1)
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
const int MAXN = 400010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, k;
ll f[MAXN], rev[MAXN];

ll mul(ll a, ll b) {
    return a * b % MODBASE;
}

ll add(ll a, ll b) {
    return (a + b) % MODBASE;
}

ll sub(ll a, ll b) {
    return (a - b + MODBASE) % MODBASE;
}

ll binPowMod(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % MODBASE;
        a = a * a % MODBASE;
        b >>= 1LL;
    }
    return res;
}

ll C(int n, int k) {
    if (k > n || k < 0) return 0;
    return mul(f[n], mul(rev[n-k], rev[k]));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    f[0] = 1;
    rev[0] = binPowMod(f[0], MODBASE-2);
    FOR(i,1,400000) {
        f[i] = mul(f[i-1], i);
        rev[i] = binPowMod(f[i], MODBASE-2);
    }
    if (k >= n-1) {
        cout << C(2*n-1, n-1);
        return 0;
    }
    ll res = 1;
    FOR(i,1,k) res = add(res, mul(C(n,i), C(n-1, n-i-1)));
    cout << res;
    return 0;
}
