/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Change the state of the problem from at most m to exactly m by adding one more a[i] = 0
        - The result = C(m+n, sum(a)+n)
        - Reason:  the problem is equivalent to placing sum(a)+n bars between m-sum(a) stars, after 
        this we consider the bars number a[1]+1, a[1]+a[2]+2, etc a[1]+...+a[n]+n as the real bars, 
        and the other "bars" between them being the chosen objects (there are a[1] of them before 
        the first real bar, a[2] between the first and the second and so on). All stars after the 
        last bar are the unchosen objects from b[i] (or we can say that we choose for the newly added
        a[i] above, but it does not matter anyway).
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
const int MAXN = 2010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, a[MAXN];

ll MOD = MODBASE;

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
    ll res = 1;
    FOR(i,n-k+1,n) res = mul(res, i);
    FOR(i,2,k) res = mul(res, binPowMod(i, MOD-2));
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) cin >> a[i];
    // C(m + n, sum(a) + n)
    int sum = 0;
    FOR(i,1,n) sum += a[i];
    
    cout << C(m + n, sum + n);
    return 0;
}
