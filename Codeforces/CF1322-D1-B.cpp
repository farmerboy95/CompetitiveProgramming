/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/74148
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
const int MAXN = 400010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN], b[MAXN];

int get(II range) {
    int res = 0;
    // there is a case that range.FI > range.SE (at k == 0)
    if (range.FI > range.SE) return res;
    FOR(i,1,n) {
        int l = -1, r = -1;
        int dau = i+1, cuoi = n, mid;
        // binary search to find segments in b that b[x] + b[i] in range
        while (dau <= cuoi) {
            mid = (dau + cuoi) >> 1;
            if (b[mid] >= range.FI - b[i]) cuoi = mid-1;
            else dau = mid+1;
        }
        l = dau;
        dau = i+1; cuoi = n;
        while (dau <= cuoi) {
            mid = (dau + cuoi) >> 1;
            if (b[mid] <= range.SE - b[i]) dau = mid+1;
            else cuoi = mid-1;
        }
        r = cuoi;

        if (l >= i+1 && l <= n && r >= i+1 && r <= n && l <= r) res ^= (r-l+1)%2;
    }
    return res;
}

int solve(int k) {
    // 2 ranges that we are considering
    II range1 = II(1<<k, (1<<(k+1)) - 1);
    II range2 = II((1<<(k+1)) + (1<<k), (1<<(k+2)) - 2);
    int mask = (1<<(k+1))-1;
    // consider only first k bits
    FOR(i,1,n) b[i] = a[i] & mask;
    sort(b+1, b+n+1);
    return get(range1) ^ get(range2);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    int res = 0;
    FOR(bit,0,24) res ^= (solve(bit) << bit);
    cout << res;
    return 0;
}
