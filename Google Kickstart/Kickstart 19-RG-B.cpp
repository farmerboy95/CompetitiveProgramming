/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: 
        - Let dp[x] is the smallest sum that can be produced when using first x bits of all numbers
        - For each x from 49 to 0:
            + Try to fill 1 in x-th bit of k: If number of unset x-th bits of all numbers * 2^x + dp[x-1] <= m, we choose 1
            + Otherwise, we must choose 0
        - Easily prove that it would maximize result k
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

int n;
ll m, a[MAXN], dp[60];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n >> m;
        FOR(i,1,n) cin >> a[i];
        // calculate dp
        FOR(x,0,49) {
            ll cnt0 = 0, cnt1 = 0;
            FOR(i,1,n)
                if (a[i] & (1LL << x)) cnt1++;
                else cnt0++;
            dp[x] = min(cnt0, cnt1) * (1LL << x);
            if (x > 0) dp[x] += dp[x-1];
        }

        // corner case
        if (dp[49] > m) {
            cout << "-1\n";
            continue;
        }

        ll k = 0;

        FORE(x,49,0) {
            // recalculate cnt0 and cnt1
            ll cnt0 = 0, cnt1 = 0;
            FOR(i,1,n)
                if (a[i] & (1LL << x)) cnt1++;
                else cnt0++;
            
            ll dpprev = 0;
            if (x > 0) dpprev = dp[x-1];

            if (cnt0 * (1LL << x) + dpprev <= m) {
                // choose 1
                m -= cnt0 * (1LL << x);
                k += (1LL << x);
            }
            else {
                // choose 0
                m -= cnt1 * (1LL << x);
            }
        }

        cout << k << "\n";
    }
    return 0;
}
