/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/hackercup/problem/143461485714593/
    Status: AC
    Idea:
        - Mainly from: https://aholzner.wordpress.com/2011/02/08/facebook-hacker-cup-round-2-problem-3-%E2%80%93-some-discussion/
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

int nt[1000010], mobius[1000010];
int n, A, B, C, D;
ll MOD = MODBASE;

void sieveBase(int n) {
    FOR(i,2,n) {
        if (nt[i] == 0) {
            nt[i] = i;
            for (ll j = (ll) i * i; j <= n; j += i) nt[j] = i;
        }
    }
    mobius[1] = 1;
    FOR(i,2,n) {
        int p = i, cntFactor = 0;
        bool co = false;
        while (p > 1) {
            int k = nt[p], cnt = 0;
            while (p % k == 0) {
                p /= k;
                cnt++;
            }
            if (cnt >= 2) {
                co = true;
                break;
            }
            cntFactor++;
        }
        if (co) mobius[i] = 0;
        else mobius[i] = (cntFactor % 2 ? -1 : 1);
    }
    // do the mobius reverse first
    FOR(i,1,n) mobius[i] = -mobius[i];
    FOR(i,1,n) mobius[i] = (mobius[i] + MOD) % MOD;
}

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

ll g(int r) {
    ll res = 0;
    FOR(i,2,1000000) {
        ll x = mul(mobius[i], r / i);
        x = binPowMod(x, n);
        res = add(res, x);
    }
    return res;
}

ll f(int l, int r) {
    if (l > r) return 0;
    ll res = binPowMod(r - l + 1, n);
    ll z = 0;
    FOR(i,2,1000000) {
        ll x = mul(mobius[i], binPowMod(sub(r / i, (l-1) / i), n));
        z = add(z, x);
    }
    res = sub(res, z);
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    sieveBase(1000000);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n >> A >> B >> C >> D;
        ll res = 0;
        res = add(res, f(A, D));
        res = sub(res, f(A, C-1));
        res = sub(res, f(B+1, D));
        res = add(res, f(B+1, C-1));
        cout << res << "\n";
    }
    return 0;
}
