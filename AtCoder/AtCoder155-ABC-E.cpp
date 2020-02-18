/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let n = length of given input, digits are indexed from 0 to n-1
        - Let dp[i][j] = minimum number of notes used from i to n-1 digit and we have j carry (j = 0 or 1)
        - Base case dp[n][0] = 0, dp[n][1] = MAX (obviously)
        - We simulate the subtraction process, subtract from n-1 to 0, at each digit, we choose k as the
        number of notes we pay and calculate the number of change notes
        - Let x is the current digit of input, we should add the carry to x if we have one.
        - If k >= x, there would be no carry here => dp[i][0] = min(dp[i][0], dp[i+1][j] + k + k - x), k
        is num of notes we pay, k - x is the change.
        - If k < x, there would be a carry => dp[i][1] = min(dp[i][1], dp[i+1][j] + k + 10 + k - x), k
        is num of notes we pay, 10 + k - x is the change (as we need one from digit i-1).
        - Finally, result = min(dp[0][0], dp[0][1] + 1) (a bit greedy here but ok)
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
const int MAXN = 1000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

string s;
int n, dp[MAXN][2];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> s;
    n = SZ(s);
    dp[n][0] = 0;
    dp[n][1] = 1000000000;
    FORE(i,n-1,0) {
        dp[i][0] = dp[i][1] = 1000000000;
        FOR(j,0,1) {
            int x = s[i] - '0' + j;
            FOR(k,0,9) {
                if (k >= x) dp[i][0] = min(dp[i][0], dp[i+1][j] + 2*k - x);
                else dp[i][1] = min(dp[i][1], dp[i+1][j] + 10 + 2*k - x);
            }
        }
    }
    cout << min(dp[0][0], dp[0][1] + 1);
    return 0;
}
