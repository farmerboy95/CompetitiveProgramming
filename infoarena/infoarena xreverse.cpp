/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let dp[n][i][j] = pair<sum, numberOfWays> contains sum of all numbers W with length n, 
        W % k = i and reverse(W) % k = j, and number of ways to get those numbers.
        - So at each state (n, i, j), we can choose next number x, attach x to the end of i and
        the beginning of j, we can go to new state (n+1, (i*10+x) % k, j+x*10^n). 
        - dp[new state].second += dp[old state].second
        - dp[new state].first += dp[old state].first * 10 + dp[old state].second * x (because we
        have to attach x to the end of each number of old state)
        => It takes O(k^2 * 9) to move one step from n to n+1
        => So it takes O(n * k^2 * 9) overall => TLE
        - Hmm... What if we have dp[n] and dp[m], can we create dp[n+m]? YES, WE CAN.
        - So we use divide and conquer to solve this problem: dp[n] = merge(dp[n/2], dp[n/2]),
        we may need to merge one more time with dp[1] if n is odd (This is NOT matrix multiplication)
        - The merging part is somewhat the same as how we move one step forward.
        - It takes about O(k^4) to merge, so overall the complexity is O(k^4 * logn)
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
const int MAXK = 40;
const int MAXQ = 200010;
 
int n, k, m, pw[MAXN], pwm[MAXN];
II dp[MAXK][MAXK], dp2[MAXK][MAXK];

vector<vector<II> > zero;
map<int, vector<vector<II> > > ma;

void calc(int n) {
    // base case: n = 1
    if (n == 1) {
        vector<vector<II> > dp = zero;
        FOR(x,1,9) {
            int e = x % k;
            dp[e][e].FI = (dp[e][e].FI + x) % m;
            dp[e][e].SE = (dp[e][e].SE + 1) % m;
        }
        ma[n] = dp;
        return;
    }
    calc(n / 2);
    // move n/2 one step forward if n is odd
    if (n % 2) {
        vector<vector<II> > dp = ma[n/2];
        vector<vector<II> > dp2 = zero;
        FOR(i,0,k-1)
            FOR(j,0,k-1) {
                if (dp[i][j] == II(0,0)) continue;
                FOR(x,1,9) {
                    int I = (i * 10 + x) % k;
                    int J = (j + x * pw[n/2]) % k;
                    dp2[I][J].FI = (dp2[I][J].FI + dp[i][j].FI * 10 + dp[i][j].SE * x) % m;
                    dp2[I][J].SE = (dp2[I][J].SE + dp[i][j].SE) % m;
                }
            }
        ma[n/2+n%2] = dp2;
    }
    
    vector<vector<II> > dp = ma[n/2 + n%2];
    int len = n/2 + n%2;
    vector<vector<II> > dp2 = ma[n/2];
    int len2 = n/2;

    // merge dp and dp2
    vector<vector<II> > dp3 = zero;
    FOR(i,0,k-1)
        FOR(j,0,k-1) {
            if (dp[i][j] == II(0,0)) continue;
            FOR(I,0,k-1)
                FOR(J,0,k-1) {
                    if (dp2[I][J] == II(0,0)) continue;
                    int p = (i * pw[len2] + I) % k;
                    int q = (J * pw[len] + j) % k;
                    // for calculating sum, after mul with 10^len2, remember to multiply 
                    // sum of left part with the number of numbers in right part and do
                    // the similar thing with the right part
                    dp3[p][q].FI = (dp3[p][q].FI + dp[i][j].FI * pwm[len2] % m * dp2[I][J].SE + dp2[I][J].FI * dp[i][j].SE) % m;
                    dp3[p][q].SE = (dp3[p][q].SE + dp[i][j].SE * dp2[I][J].SE) % m;
                }
        }
    ma[n] = dp3;
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("xreverse.in", "r", stdin);
    freopen("xreverse.out", "w", stdout);
    cin >> n >> k >> m;
    pw[0] = 1 % k;
    FOR(i,1,n) pw[i] = (pw[i-1] * 10) % k;

    // we need powers of 10 modulo m, not only k
    pwm[0] = 1 % m;
    FOR(i,1,n) pwm[i] = (pwm[i-1] * 10) % m;

    FOR(i,0,k-1) zero.push_back(vector<II> (k, II(0,0)));

    calc(n);
    cout << ma[n][0][0].FI;
    return 0;
}