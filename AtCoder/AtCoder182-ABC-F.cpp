/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - First of all notice that any number X has unique minimal representation. 
        This can be proved by greedy exchange (using the fact that each successive number 
        is a multiple of the previous number).
        - Now, notice the isomorphism (structure equivalence) between the number bases and 
        the (minimal) representation of each number in the system of Yens. There are two 
        properties which are maintained:
            + If highest bit of A is greater than B in our Yen-system, then A > B.
            + Each number has unique representation.
        - So we can think of an equivalent problem: given a number X, how many numbers b 
        are there such that X + b = a and a and b have no bit in common?
        - Array b[] represents the representation of X in Yen-system
        - Let dp[i][j] is the number of b when we consider first i digits and whether we have
        a carry (j = 0 or 1)
        - The transition is quite easy.
            + For i < n, if the digit i of X is 0, we have only one choice to make b and a not
            having bit i in common, it's to fill in 0 for b. Otherwise, if the digit i of X is not
            0, we have 2 choices, to fill in 0 and go forward without carry, and to fill a number
            that make the sum is 0 and go forward with a carry. Things would be the same if we
            move from a carry-ed state, we just need to add 1 to the current digit and do as above.
            + For i = n, there is no upper bound for the digit here. So there is only one case,
            which is that we fill 0 (because if we fill 1, the sum will definitely not be 0).
        - Complexity O(n)
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

int n;
ll a[MAXN], dp[MAXN][2], x, b[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> x;
    FOR(i,1,n) cin >> a[i];
    dp[0][0] = 1;
    dp[0][1] = 0;
    ll k = x;
    FOR(i,2,n) {
        ll p = a[i] / a[i-1];
        b[i-1] = k % p;
        k /= p;
    }
    b[n] = k;

    FOR(i,1,n) {
        ll g = b[i];
        ll p = a[i+1] / a[i];

        if (dp[i-1][0]) {
            if (i == n) {
                dp[i][0] += dp[i-1][0];
            } else if (g == 0) {
                dp[i][0] += dp[i-1][0];
            } else {
                dp[i][0] += dp[i-1][0];
                dp[i][1] += dp[i-1][0];
            }
        }
        if (dp[i-1][1]) {
            g++;
            if (i == n) {
                dp[i][0] += dp[i-1][1];
            } else if (g == p) {
                dp[i][1] += dp[i-1][1];
            } else {
                dp[i][0] += dp[i-1][1];
                dp[i][1] += dp[i-1][1];
            }
        }
    }

    cout << dp[n][0];
    return 0;
}
