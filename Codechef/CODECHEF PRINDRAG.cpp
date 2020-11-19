/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://discuss.codechef.com/t/prindrag-editorial/19793
        - https://ideone.com/oOh8X3
        - The main difference here is that I used one-based index for the given array
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
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int a[MAXN], minPrefix[MAXN*3], dp[MAXN], gp[MAXN];

void solve(int n, int W) {
    sort(a+1, a+n+1);
    reverse(a+1, a+n+1);

    if (a[1] >= W) {
        FOR(i,1,n) cout << n << ' ';
        cout << "\n";
        return;
    }

    W -= a[1];

    MS(minPrefix, 0);

    int sum = 0;
    FOR(i,1,n) {
        if (i > 1) sum += a[i];
        if (sum + 1 >= 300000) break;
        minPrefix[sum + 1] = i;
    }

    FOR(i,1,300000) minPrefix[i] = max(minPrefix[i], minPrefix[i-1]);

    int res = n;

    FOR(i,0,W-1) dp[i] = 0;
    dp[0] = 1;

    int p = 2;
    while (p <= n) {
        if (p-1 >= res) break;
        int p1 = p + 1;
        while (p1 <= n && a[p1] == a[p]) p1++;


        FOR(j,max(0LL, W - (ll) a[p] * (p1 - p)), W-1) {
            if (!dp[j]) continue;

            int cnt = (W - j) / a[p] + ((W - j) % a[p] > 0);
            if (cnt > p1-p) continue;
            int needSum = (j + a[p] * cnt) + W;
            
            int pos = minPrefix[needSum];
            pos = max(pos, p-1 + cnt);
            
            res = min(res, pos);
        }

        FOR(j,0,W-1) {
            if (dp[j]) gp[j] = 0;
            else {
                gp[j] = 1e9;
                if (j >= a[p]) gp[j] = min(gp[j], dp[j - a[p]] + 1);
            }
            if (!dp[j]) dp[j] = (gp[j] <= (p1 - p));
        }

        p = p1;
    }

    int pos = minPrefix[W];
    FOR(i,1,n) {
        int case1 = res == n ? 0 : n-1 - (res-2);
        int case2 = max(i-1, n-i) - (pos - 1);
        cout << max(case1, case2) << ' ';
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, W;
        cin >> n >> W;
        FOR(i,1,n) cin >> a[i];
        solve(n, W);
    }
    return 0;
}
