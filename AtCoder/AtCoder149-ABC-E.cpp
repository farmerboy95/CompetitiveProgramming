/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We find the minimum sum by binary search so that the number of sums that are greater than or
        equal to that sum is lower than m
        - Then we easily calculate the result using binary search again.
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
typedef pair<ll, ll> II;
typedef pair<II, ll> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN];
ll m, s[MAXN];

ll calc(int k) {
    int dau = 1, cuoi = n, mid;
    while (dau <= cuoi) {
        mid = (dau + cuoi) >> 1;
        if (a[mid] >= k) cuoi = mid-1;
        else dau = mid+1;
    }
    return n - cuoi;
}

ll calc2(int k) {
    int dau = 1, cuoi = n, mid;
    while (dau <= cuoi) {
        mid = (dau + cuoi) >> 1;
        if (a[mid] >= k) cuoi = mid-1;
        else dau = mid+1;
    }
    return s[n] - s[cuoi];
}

ll check(int u) {
    ll res = 0;
    FOR(i,1,n) {
        int k = u - a[i];
        res += calc(k);
    }
    return res;
}

ll tinh(int u) {
    ll res = 0;
    FOR(i,1,n) {
        int k = u - a[i];
        res += calc(k) * a[i] + calc2(k);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) cin >> a[i];
    sort(a+1, a+n+1);
    FOR(i,1,n) s[i] = s[i-1] + a[i];
    int dau = 2, cuoi = 200000, mid;
    while (dau <= cuoi) {
        mid = (dau + cuoi) >> 1;
        if (check(mid) >= m) dau = mid+1;
        else cuoi = mid-1;
    }
    ll p = m - check(dau);
    ll res = p * cuoi;
    res += tinh(dau);
    cout << res;
    return 0;
}
