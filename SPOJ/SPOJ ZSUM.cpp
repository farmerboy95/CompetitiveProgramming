/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: 
        Zn = Zn-1 + n^n + n^k
        => Zn + Zn-1 - 2 * Zn-2 = 2 * (n-1)^k + 2 * (n-1)^(n-1) + n^n + n^k
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

ll MOD = 10000007;

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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, k;
    while (cin >> n >> k && !(n == 0 && k == 0)) {
        cout << (2 * binPowMod(n-1, k, MOD) + 2 * binPowMod(n-1, n-1, MOD) + binPowMod(n, n, MOD) + binPowMod(n, k, MOD)) % MOD << endl;
    }
    return 0;
}
