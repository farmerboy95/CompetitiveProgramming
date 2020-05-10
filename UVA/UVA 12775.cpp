/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Use Extended Euclid Algorithm
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
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

ll extendedEuclid(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll X1, Y1;
    ll d = extendedEuclid(b, a % b, X1, Y1);
    x = Y1;
    y = X1 - Y1 * (a / b);
    return d;
}

ll solve(ll a, ll b, ll c) {
    // a*x + b*y = gcd(a, b)
    ll x, y;
    ll g = extendedEuclid(a, b, x, y);
    if (c % g) return 0;
    a /= g; b /= g; c /= g;
    // a*x + b*y = 1
    // => a * cx + b * cy = c
    x *= c;
    y *= c;
    // x = x0 + bk >= 0 => k >= -x0 / b
    // y = y0 - ak >= 0 => k <= y0 / a
    ll l = -x / b;
    if (-x % b) {
        if (-x / b >= 0) l++;
        else {}
    }
    ll r = y / a;
    if (y % a) {
        if (y / a <= 0) r--;
        else {}
    }
    return max(0LL, r-l+1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        ll a, b, c, p;
        cin >> a >> b >> c >> p;
        ll g = gcd(a, gcd(b, c));
        if (p % g) {
            cout << "Case " << o << ": 0\n";
            continue;
        }
        a /= g; b /= g; c /= g; p /= g;
        // c / gcd(a,b,c) >= 200 => we can iterate through the number of c, and use euclid to solve the rest
        ll res = 0;
        for (ll i = 0; p - c * i >= 0; i++) res += solve(a, b, p - c * i);
        cout << "Case " << o << ": " << res << "\n";
    }
    return 0;
}
