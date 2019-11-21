/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use inclusion-exclusion principal
        - Remember: lcm(x, y, z) = lcm(lcm(x, y), z)
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
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 1010;
const int MAXM = 30010;
const int MAXK = 16;
const int MAXQ = 200010;

ll l, r, a, d, t, f[10];

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

ll solve(ll n) {
    if (n == 0) return 0;
    ll res = n;
    FOR(mask,1,(1<<5)-1) {
        ll lcm = 1;
        int cnt = 0;
        bool first = true;
        bool less = true;
        FOR(i,0,4)
            if (mask & (1<<i)) {
                if (first) {
                    first = false;
                    lcm = f[i];
                }
                else {
                    ll g = gcd(lcm, f[i]);
                    lcm /= g;
                    if (f[i] > n / lcm) {
                        less = false;
                        break;
                    }
                    lcm *= f[i];
                }
                cnt++;
            }
        
        if (!less) continue;
        
        ll sign = 1;
        if (cnt % 2) sign = -1;
        res += sign * n / lcm;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> l >> r >> a >> d;
        FOR(i,0,4) f[i] = a + i * d;
        cout << solve(r) - solve(l-1) << "\n";
    }
    return 0;
}
