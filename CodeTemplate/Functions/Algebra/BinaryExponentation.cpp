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
#define WHATIS(x) cout << #x << " is " << x << endl;
#define ERROR(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x

using namespace std;
using ll = long long;
using ld = double;
typedef pair<int, int> II;
typedef pair<ll, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

// https://cp-algorithms.com/algebra/binary-exp.html
// function part ------------------------------------------------------------------------------------

ll binPow(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a;
        a = a * a;
        b >>= 1LL;
    }
    return res;
}

ll binPowMod(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % m;
        a = a * a % m;
        b >>= 1LL;
    }
    return res;
}

// base on Little Fermat's theorem: a ^ (m-1) = 1 (mod m) (m is a prime number)
ll binPowModPrime(ll a, ll b, ll m) {
    a %= m;
    b %= (m-1);
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % m;
        a = a * a % m;
        b >>= 1LL;
    }
    return res;
}

ll binAddModPrime(ll a, ll b, ll m) {
    a %= m;
    b %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = (res + a) % m;
        a = (a + a) % m;
        b >>= 1LL;
    }
    return res;
}

// end of function part -----------------------------------------------------------------------------

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    return 0;
}
