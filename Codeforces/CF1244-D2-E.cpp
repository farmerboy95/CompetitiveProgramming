/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Binary search the maximum difference in the initial array
        - Then ternary search the allowed segment to get the minimum number of operation
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
const int MAXN = 100010;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, a[MAXN];
ll k;

ll calc(ll st, ll en) {
    ll cnt = 0;
    FOR(i,1,n)
        if (a[i] < st) cnt += st - a[i];
        else if (a[i] > en) cnt += a[i] - en;
    return cnt;
}

bool check(int maxDiff) {
    ll LL = a[1];
    ll RR = a[n] - maxDiff;
    ll ML = (LL + LL + RR) / 3;
    ll MR = (LL + RR + RR) / 3;
    while ((LL != ML) && (ML != MR) && (MR != RR)) {
        if (calc(ML, ML + maxDiff) > calc(MR, MR + maxDiff)) LL = ML;
        else RR = MR;
        ML = (LL + LL + RR) / 3;
        MR = (LL + RR + RR) / 3;
    }
    ll res = 1e18;
    while (LL != RR) {
        res = min(res, calc(LL, LL + maxDiff));
        LL++;
    }
    res = min(res, calc(LL, LL + maxDiff));
    if (res > k) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,n) cin >> a[i];
    sort(a+1, a+n+1);
    int maxDiff = a[n] - a[1];
    int dau = 0, cuoi = maxDiff, mid;
    while (dau <= cuoi) {
        mid = (dau + cuoi) >> 1;
        if (check(mid)) cuoi = mid-1;
        else dau = mid+1;
    }
    cout << dau;
    return 0;
}
