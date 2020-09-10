/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's define x1 = s2 - s1, x2 = n2 - n1, x3 = u2 - u1, x4 = k2 - k1, x5 = e2 - e1
        - So s1 + s2 + n1 + n2 + u1 + u2 + k1 + k2 + e1 + e2 <= n
         <=> 2 * (s1 + n1 + u1 + k1 + e1) + x1 + x2 + x3 + x4 + x5 <= n
         <=> x1 + x2 + x3 + x4 + x5 <= n - 2 * (s1 + n1 + u1 + k1 + e1) (1)
        - Since s2 > s1 => s2 - s1 > 0 => x1 > 0, the same thing applies to x2, x3, x4, x5
        - Let's solve another problem first, count the number of tuples satisfying
            x1 + x2 + x3 + x4 + x5 <= n
            + To solve this, let's solve the problem with x1 + x2 + x3 + x4 + x5 = n first
            + The number of tuples here is C(n+4, 4) (using stars and bars trick)
            + What about x1 + x2 + x3 + x4 + x5 <= n? We can just assume that there is an
            additional variable x6 that x1 + x2 + x3 + x4 + x5 + x6 = n => The number of
            tuples here is C(n+5, 5)
        - But we need the product x1 * x2 * x3 * x4 * x5, right? We only count the number of
        ways. Let's suppose our stars and bars looks like ooo|oo|ooo, we want to count this as
        3*2*3, we can put additional 3 bars, each representing the "count" of x_i.
        - Here we put 5 more bars into the stars (we don't care about the x6 because we simply
        just don't count it) => the answer is C(n+10, 10)
        - One more thing, as x1, x2, x3, x4, x5 > 0, each part has at least one star, we simply 
        deduct 5 from n => C(n+5, 10)
        - Let s1 + n1 + u1 + k1 + e1 = x (number of ways is C(x+4, 4)), 
        (1) <=> x1 + x2 + x3 + x4 + x5 <= n - 2x
        => For each fixed x, our result is C(n-2x+5, 10)
        => Our answer overall is sum(C(n-2x+5, 10) * C(x+4, 4)) with x from 0 to floor((n-5)/2)
        - Note that the above sum can actually be represented as a polynomial P(n) degree 15 
        (sum of x^14 is x^15)
        - So to get the P(n) with n from input, we can pre calculate P(n) with 16 different n and
        use Lagrange Interpolation to get the value of P(n) with n in input without having to find
        the exact polynomial.
        - As x runs from 0 to floor((n-5)/2), we have to divide it into cases with n odd and even.
        For example n is odd, set N = (n-5) / 2 => n = 2*N+5. Then there is no floor in the formula
        and we can use the Lagrange Interpolation on it. If n is even, set N = (n-6) / 2 and do the
        same thing.

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
const int MAXN = 210;
const int MAXM = 20;
const int MAXK = 16;
const int MAXQ = 200010;

ll MOD = MODBASE;
ll f[MAXN], rev[MAXN];

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

ll sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

ll C(int n, int k) {
    if (k > n || k < 0) return 0;
    return mul(f[n], mul(rev[n-k], rev[k]));
}

ll calc(int n) {
    ll res = 0;
    for (int i = 0; 2 * i + 5 <= n; i++) res = add(res, mul(C(i+4, 4), C(n+5-2*i, 10)));
    return res;
}

ll inv(ll x) {
    return binPowMod(x, MOD-2);
}

ll LagrangeInterpolation(vector<ll> &y, int n) {
    if (n <= 15) return y[n];
    ll numerator = 1, denominator = 1;
    FOR(i,0,15) {
        numerator = mul(numerator, n - i);
        ll x = (0 - i + MOD) % MOD;
        if (i > 0) denominator = mul(denominator, x);
    }
    ll res = 0;
    FOR(i,0,15) {
        res = add(res, mul(y[i], mul(mul(numerator, inv(n - i)), inv(denominator))));
        ll last = (i - 15 + MOD) % MOD;
        denominator = mul(denominator, inv(last));
        ll newFirst = (i+1) - 0;
        denominator = mul(denominator, newFirst);
    }
    return res;
}

ll solve(int n) {
    if (n < 5) return 0;
    vector<ll> y(16);
    int r = (n - 5) % 2, N = (n - 5) / 2;
    FOR(i,0,15) y[i] = calc(2*i + 5 + r);
    return LagrangeInterpolation(y, N);
}

void init() {
    f[0] = 1;
    rev[0] = inv(f[0]);
    FOR(i,1,200) {
        f[i] = mul(f[i-1], i);
        rev[i] = inv(f[i]);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    init();
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << solve(n) << "\n";
    }
    return 0;
}
