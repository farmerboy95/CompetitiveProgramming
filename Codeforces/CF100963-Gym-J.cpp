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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    ll n, m, a, k;
    while (cin >> n >> m >> a >> k) {
        if (!n && !m && !a && !k) break;
        // n + mx = k + ay
        // as y >= 1 => k += a
        k += a;
        if (k == n) {
            cout << k << "\n";
            continue;
        }
        // make sure that k - n >= 0
        if (k < n) {
            swap(k, n);
            swap(m, a);
        }
        // now it is mx + (-a)y = k - n
        k -= n;
        a = -a;
        ll x, y;
        ll g = extendedEuclid(m, a, x, y);
        if (k % g) {
            cout << "Impossible\n";
            continue;
        }
        m /= g;
        a /= g;
        k /= g;
        x *= k;
        y *= k;
        // m, a, k may change the sign after dividing by g, we flip it
        bool absed = false;
        if (m < 0) {
            absed = true;
            m = -m;
            a = -a;
            k = -k;
        }
        // x = x0 + a * t, y = y0 - m * t
        // but now a < 0, m > 0
        // => x = x0 - abs(a) * t, y = y0 - m * t
        // x, y >= 0 => t <= min(x0 / abs(a), y0 / m);
        ll t = min(x / -a, y / m);
        ll xx = x + a * t;
        ll yy = y - m * t;
        // check again for sure
        while (xx < 0 || yy < 0) {
            xx -= a;
            yy += m;
        }
        // remember to recover m before getting result
        if (absed) m = -m;
        cout << n + m * g * xx << "\n";
    }
    return 0;
}
