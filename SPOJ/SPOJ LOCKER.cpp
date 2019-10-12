/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use n/3 number 3
        - If n % 3 == 2, use 1 number 2
        - If n % 3 == 1, use 1 number 4, deduct 1 from number of 3
        - Proof: https://apps.topcoder.com/forums/?module=Thread&threadID=796977&start=0&mc=9
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
const int MAXN = 1010;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

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
    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        if (n <= 2) {
            cout << n << "\n";
            continue;
        }
        ll g = n / 3;
        ll h = n % 3;
        if (h == 1) {
            g--;
            h += 3;
        }
        else {
            if (h == 0) h = 1;
        }
        ll res = binPowMod(3, g, MODBASE);
        res = res * h % MODBASE;
        cout << res << "\n";
    }
    return 0;
}
