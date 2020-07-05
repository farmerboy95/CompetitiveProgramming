/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's sort the array descendantly by the absolute value of elements.
        - We pick first k numbers. There are several cases here:
            + There is a 0 in picked numbers. There is no way to get product > 0. Print 0.
            + Number of negative numbers is even. The product here >= 0. Print it.
        - Those are corner cases. So the number of negative ones is odd. Here we have some more cases:
            + We remove one negative number and choose one non-negative one to make the product >= 0.
            + We remove one positive number and choose one non-positive one to make the product >= 0.
        - If we one of the above cases is possible, choose it. If both are possible, use fraction to
        choose the better one. Otherwise, the array surely is full negative numbers. So we just choose
        the k biggest numbers and print the product.
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
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, k, a[MAXN];
bool choose[MAXN];
ll MOD = MODBASE;

bool cmp(int a, int b) {
    return abs(a) > abs(b);
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

ll mod(ll a) {
    return (a + MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,n) cin >> a[i];
    sort(a+1, a+n+1, cmp);

    bool have0 = false;
    int lastPos = 0, lastNeg = 0, pos = 0, neg = 0;
    FOR(i,1,k)
        if (a[i] > 0) {
            lastPos = i;
            pos++;
            choose[i] = true;
        } else if (a[i] < 0) {
            lastNeg = i;
            neg++;
            choose[i] = true;
        } else {
            have0 = true;
            choose[i] = true;
        }

    if (have0) {
        cout << 0;
        return 0;
    }

    if (neg % 2 == 0) {
        ll res = 1;
        FOR(i,1,k) res = mul(res, mod(a[i]));
        cout << res;
        return 0;
    }

    int denom1 = lastNeg, nume1 = 0;
    FOR(i,k+1,n)
        if (a[i] >= 0) {
            nume1 = i;
            break;
        }
    
    if (lastPos) {
        int denom2 = lastPos, nume2 = 0;
        FOR(i,k+1,n)
            if (a[i] <= 0) {
                nume2 = i;
                break;
            }
        if (nume1 && nume2) {
            if ((ll) abs(a[nume1]) * abs(a[denom2]) > (ll) abs(a[nume2]) * abs(a[denom1])) {
                choose[denom1] = false;
                choose[nume1] = true;
            } else {
                choose[denom2] = false;
                choose[nume2] = true;
            }
        } else if (nume2) {
            choose[denom2] = false;
            choose[nume2] = true;
        } else if (nume1) {
            choose[denom1] = false;
            choose[nume1] = true;
        } else {
            // full negative
            MS(choose, false);
            FORE(i,n,n-k+1) choose[i] = true;
        }
    } else {
        if (nume1) {
            choose[denom1] = false;
            choose[nume1] = true;
        } else {
            // full negative
            MS(choose, false);
            FORE(i,n,n-k+1) choose[i] = true;
        }
    }
    ll res = 1;
    FOR(i,1,n) 
        if (choose[i]) res = mul(res, mod(a[i]));
    cout << res;
    return 0;
}
