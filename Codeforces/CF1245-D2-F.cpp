/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://codeforces.com/blog/entry/71039?#comment-555254
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
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 2010;
const int MAXM = 10010;
const int MAXK = 110;
const int MAXQ = 200010;

ll dp[35][2][2][2][2];
int L[35], R[35];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int l, r;
        cin >> l >> r;
        MS(dp, 0);
        // init dp
        dp[31][0][0][0][0] = 1;

        // get bit of L and R
        FOR(i,0,31) {
            L[i] = (l >> i) & 1;
            R[i] = (r >> i) & 1;
        }

        FORE(i,31,1)
            FOR(sm1,0,1)
                FOR(lg1,0,1)
                    FOR(sm2,0,1)
                        FOR(lg2,0,1) {
                            int nxt = i-1;
                            FOR(a,0,1)
                                FOR(b,0,1) {
                                    // not allow a == b == 1
                                    if (a && b) continue;
                                    // if A right now is not smaller than r but bit a is larger than R[nxt], then A is larger than r
                                    if (!sm1 && a && !R[nxt]) continue;
                                    // if B right now is not smaller than r but bit b is larger than R[nxt], then B is larger than r
                                    if (!sm2 && b && !R[nxt]) continue;
                                    // if A right now is not larger than l but bit a is smaller than L[nxt], then A is smaller than r
                                    if (!lg1 && !a && L[nxt]) continue;
                                    // if B right now is not larger than l but bit b is smaller than L[nxt], then B is smaller than r
                                    if (!lg2 && !b && L[nxt]) continue;

                                    // from now on, adding a and b doesn't cause overflow anymore
                                    // if a == b == 0, lg1 and lg2 will not change, we only need to find new sm1 and sm2
                                    if (!a && !b) {
                                        int nsm1 = sm1 | R[nxt], nsm2 = sm2 | R[nxt];
                                        dp[nxt][nsm1][lg1][nsm2][lg2] += dp[i][sm1][lg1][sm2][lg2];
                                    }
                                    // if a == 1 and b == 0, sm1 and lg2 will not change, we only need to find new lg1 and sm2
                                    else if (a) {
                                        int nlg1 = lg1 | (!L[nxt]), nsm2 = sm2 | R[nxt];
                                        dp[nxt][sm1][nlg1][nsm2][lg2] += dp[i][sm1][lg1][sm2][lg2];
                                    }
                                    // if a == 0 and b == 1, lg1 and sm2 will not change, we only need to find new sm1 and lg2
                                    else {
                                        int nsm1 = sm1 | R[nxt], nlg2 = lg2 | (!L[nxt]);
                                        dp[nxt][nsm1][lg1][sm2][nlg2] += dp[i][sm1][lg1][sm2][lg2];
                                    }
                                }
                        }

        ll res = 0;
        FOR(sm1,0,1)
            FOR(lg1,0,1)
                FOR(sm2,0,1)
                    FOR(lg2,0,1) res += dp[0][sm1][lg1][sm2][lg2];
        cout << res << "\n";
    }
    return 0;
}
