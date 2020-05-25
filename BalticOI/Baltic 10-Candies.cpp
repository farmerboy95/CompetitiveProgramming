/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Same as editorial: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2010_solutions/candies-sol.pdf
        - Used the big prime modulo method for storing the number of ways to form a specific sum
        - Comments are in the implementation
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
const int MAXM = 700010;
const int MAXK = 16;
const int MAXQ = 200010;

int MOD = 1000000007;
int n, a[MAXN];
int dp[MAXM], dp2[MAXM];
bool dp3[MAXM * 2];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];

    // remove
    // dp[i] is the number of ways to form the sum equals to i
    // the real value of dp[i] is really big (2^100) but we can use modulo as the chance that
    // dp[i] mod P = 0 and dp[i] > 0 is very low
    dp[0] = 1;
    FOR(i,1,n)
        FORE(j,700000,0) {
            if (j - a[i] < 0) break;
            dp[j] += dp[j - a[i]];
            if (dp[j] > MOD) dp[j] -= MOD;
        }

    int Max = -1, pos = -1;
    FOR(i,1,n) {
        // reverse the above flow to eliminate one number from the set
        FOR(j,0,700000) dp2[j] = dp[j];
        FOR(j,a[i],700000) {
            dp2[j] -= dp2[j - a[i]];
            if (dp2[j] < 0) dp2[j] += MOD;
        }

        // count the number of distinct sums, get max
        int cnt = 0;
        FOR(j,0,700000) cnt += (dp2[j] > 0);
        if (cnt > Max || (cnt == Max && a[pos] > a[i])) {
            Max = cnt;
            pos = i;
        }
    }
    // put the first result to the end of the array
    swap(a[pos], a[n]);
    n--;

    // add
    // now we have a set of candy bags a1 ... an, we should add a smallest size of candy bag C,
    // that we can double the number of different possible sum of candies afterward.
    // suppose that we can form sums x1, x2, x3, ..., then adding one more candy bag C doubles the number
    // of possible distinct sums iff C is not equal to any of x[i] - x[j]. Why?
    // We have X + a[j1] + a[j2] + a[j3] != a[i1] + a[i2] + a[i3]
    // => X != a[i1] + a[i2] + a[i3] - (a[j1] + a[j2] + a[j3])
    // => X != x[i] - x[j]
    // now we do the knapsack again but in the array of a1, ... an and -a1, ... -an to cover the above case.
    int offset = 700000;
    dp3[offset] = true;
    FOR(i,1,n) {
        FORE(j,1400000,0) {
            if (j - a[i] < 0) break;
            dp3[j] |= dp3[j - a[i]];
        }
        FOR(j,0,1400000) {
            if (j + a[i] > 1400000) break;
            dp3[j] |= dp3[j + a[i]];
        }
    }
    // finally get the res = the smallest non-checked number.
    int res = 0;
    FOR(i,700000,1400000)
        if (!dp3[i]) {
            res = i;
            break;
        }
    cout << a[n+1] << ' ' << res - offset;
    return 0;
}
