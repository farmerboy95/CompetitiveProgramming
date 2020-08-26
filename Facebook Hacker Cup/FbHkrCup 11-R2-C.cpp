/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/codingcompetitions/hacker-cup/2011/round-2/problems/C
    Status: AC
    Idea:
        - Let dp[l][r][k][hasA][hasB][isOneChar] is the number of different sequences
        of operations to perform on s[l...r] with k operations, then it becomes a string
        with hasA = 1 or 0 (has character a or not), hasB = 1 or 0 (has character b or not), and
        the string has one character or not (isOneChar = 1 or 0).
        - Let's imagine one operation is to put '[' and ']' covering the substring that we are 
        conducting the operation. So one operation will be either inside another operation or
        not inside any operation at all, no partially overlay.
        - We calculate from length = 1 to length = n.
        - More comments in code
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
const int MAXN = 65;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

string s;
int n;
ll dp[MAXN][MAXN][MAXN][2][2][2], c[MAXN][MAXN];
ll MOD = MODBASE;

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

void init() {
    n = SZ(s);
    MS(dp, 0);
}

ll solve() {
    init();
    FOR(len,1,n)
        FOR(l,0,n-len) {
            // get l, r, string s[l..r] is the string that we are considering
            int r = l + len - 1;
            if (len == 1) {
                int hasA = (s[l] == 'a') ? 1 : 0;
                int hasB = (s[r] == 'b') ? 1 : 0;
                // only one case here
                dp[l][r][0][hasA][hasB][1] = 1;
                continue;
            }

            // we add all dp[l+1][r] to dp[l][r] like below (based on cases hasA, hasB)
            FOR(operationCnt,0,len-1)
                FOR(hasA,0,1)
                    FOR(hasB,0,1)
                        FOR(isOneChar,0,1) {
                            int nextHasA = hasA | (s[l] == 'a' ? 1 : 0);
                            int nextHasB = hasB | (s[l] == 'b' ? 1 : 0);
                            dp[l][r][operationCnt][nextHasA][nextHasB][0] = add(dp[l][r][operationCnt][nextHasA][nextHasB][0], dp[l+1][r][operationCnt][hasA][hasB][isOneChar]);
                        }
            
            // dp[l][r] contains all dp[l+1][r], so we need to add operations involving s[l...mid]
            FOR(mid,l,r)
                FOR(lefOpCnt,0,mid-l)
                    FOR(lefHasA,0,1)
                        FOR(lefHasB,0,1) {
                            // as we want to add operations involving s[l...mid], isOneChar should be 0
                            ll lefWayNum = dp[l][mid][lefOpCnt][lefHasA][lefHasB][0];
                            if (lefWayNum == 0) continue;

                            // choose a or b to transform to
                            FOR(transformTo,0,1) {
                                if ((transformTo == 0 && lefHasA == 0) || (transformTo == 1 && lefHasB == 0)) continue;

                                if (mid != r) {
                                    // find the state of the remaining part
                                    FOR(rigOpCnt,0,r-mid-1)
                                        FOR(rigHasA,0,1)
                                            FOR(rigHasB,0,1)
                                                FOR(rigIsOneChar,0,1) {
                                                    ll rigWayNum = dp[mid+1][r][rigOpCnt][rigHasA][rigHasB][rigIsOneChar];
                                                    if (rigWayNum == 0) continue;

                                                    // nextOpCnt = (lefOpCnt + 1) + rigOpCnt
                                                    // the 2 operation sets are independent
                                                    // so we add lefWayNum * rigWayNum * c[nextOpCnt][rigOpCnt]
                                                    // as in one way there are nextOpCnt operations now, and there are rigOpCnt ways in those.
                                                    // isOneChar is 0 because we definitely have more than one character
                                                    int nextOpCnt = lefOpCnt + rigOpCnt + 1;
                                                    int nextHasA = ((transformTo == 0) ? 1 : 0) | rigHasA;
                                                    int nextHasB = ((transformTo == 1) ? 1 : 0) | rigHasB;

                                                    dp[l][r][nextOpCnt][nextHasA][nextHasB][0] = add(dp[l][r][nextOpCnt][nextHasA][nextHasB][0], mul(mul(lefWayNum, rigWayNum), c[nextOpCnt][rigOpCnt]));
                                                }
                                } else {
                                    // we do the operation on the whole s[l..r], isOneChar should be 1, obviously
                                    int nextOpCnt = lefOpCnt + 1;
                                    int nextHasA = (transformTo == 0) ? 1 : 0;
                                    int nextHasB = (transformTo == 1) ? 1 : 0;
                                    dp[l][r][nextOpCnt][nextHasA][nextHasB][1] = add(dp[l][r][nextOpCnt][nextHasA][nextHasB][1], lefWayNum);
                                }
                            }
                        }
        }

    // get the result
    ll res = 0;
    FOR(operationCnt,0,n-1)
        FOR(hasA,0,1)
            FOR(hasB,0,1)
                FOR(isOneChar,0,1) res = add(res, dp[0][n-1][operationCnt][hasA][hasB][isOneChar]);
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    // nCk
    FOR(i,0,60) FOR(j,0,i)
        if (i == j || j == 0) c[i][j] = 1;
        else c[i][j] = add(c[i-1][j], c[i-1][j-1]);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cin >> s;
        cout << "Case #" << o << ": " << solve() << "\n";
    }
    return 0;
}
