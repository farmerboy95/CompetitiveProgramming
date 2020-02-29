/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's assume that we don't have the constraint which does not allow people to use the ticket
        at the same exit where the ticket is issued. We can see that it's optimal to sort all the 
        entrance and all the exit and we give tickets to drivers in order (case 1).
        - So what if after reordering, one driver received a forbidden ticket? He can swap it with
        the adjacent driver and everything will be fine (case 2). But there is a case of 3 drivers (case 3), 
        2 drivers are happy with their tickets but the last one isn't, ok, we can try permutations of 3 
        to make all 3 happy eventually. But what about 4 drivers? This case can become twice of case 2
        (we can draw this case on paper and see it's optimal to transform it to case 2).
        - So we only have 3 cases when considering a driver. Let dp[i] is the result when we consider
        first i drivers. Transitions are in the code. The final result is dp[n].
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

int n;
ll a[MAXN], b[MAXN];
ll dp[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i] >> b[i];
    sort(a+1, a+n+1);
    sort(b+1, b+n+1);
    dp[0] = 0;
    FOR(i,1,n) {
        dp[i] = 1e18;
        if (a[i] != b[i]) dp[i] = min(dp[i], dp[i-1] + abs(a[i]-b[i]));
        if (i > 1) {
            if (a[i-1] != b[i] && a[i] != b[i-1]) {
                dp[i] = min(dp[i], dp[i-2] + abs(a[i-1] - b[i]) + abs(a[i] - b[i-1]));
            }
        }
        if (i > 2) {
            if (a[i] != b[i-1] && a[i-1] != b[i-2] && a[i-2] != b[i]) {
                dp[i] = min(dp[i], dp[i-3] + abs(a[i] - b[i-1]) + abs(a[i-1] - b[i-2]) + abs(a[i-2] - b[i]));
            }
            if (a[i] != b[i-2] && a[i-1] != b[i] && a[i-2] != b[i-1]) {
                dp[i] = min(dp[i], dp[i-3] + abs(a[i] - b[i-2]) + abs(a[i-1] - b[i]) + abs(a[i-2] - b[i-1]));
            }
        }
    }
    cout << dp[n];
    return 0;
}
