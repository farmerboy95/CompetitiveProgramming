/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Put masks that produce first person's happiness larger than h in array A
        - Put masks that produce second person's happiness larger than h in array B
        - A mask "b" in B can pair with a mask "a" in A if and only if b & ((2^n-1) ^ a) == ((2^n-1) ^ a)
        - Or ((2^n-1) ^ a) is a submask of b
        - Use SOS DP dp[x] to count number of masks that x is submask of those masks
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
const int MAXN = 25;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, dp[1<<20][25];
ll h, a[MAXN], b[MAXN], sum1[1<<20], sum2[1<<20];
vector<int> A, B;

int rightMostSetBit(int u) {
    return (u & ~(u-1));
}

int toPosition(int u) {
    return int(log2(u));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n >> h;
        FOR(i,0,n-1) cin >> a[i];
        FOR(i,0,n-1) cin >> b[i];
        A.clear();
        B.clear();
        // get A and B
        FOR(mask,0,(1<<n)-1) {
            if (mask == 0) {
                sum1[mask] = sum2[mask] = 0;
            }
            else {
                int e = rightMostSetBit(mask);
                int pos = toPosition(e);
                int mask2 = mask - e;

                sum1[mask] = sum1[mask2] + a[pos];
                sum2[mask] = sum2[mask2] + b[pos];
            }
            if (sum1[mask] >= h) A.emplace_back(mask);
            if (sum2[mask] >= h) B.emplace_back(mask);
        }

        // sos dp part
        FOR(i,0,(1<<n)-1) dp[i][0] = 0;
        FOR(i,0,SZ(B)-1) dp[B[i]][0]++;

        FOR(i,0,n-1)
            FOR(mask,0,(1<<n)-1)
                if (mask & (1<<i)) {
                    dp[mask][i+1] = dp[mask][i];
                }
                else {
                    dp[mask][i+1] = dp[mask][i] + dp[mask + (1<<i)][i];
                }

        // get result
        ll res = 0;
        FOR(i,0,SZ(A)-1) {
            int x = A[i];
            int mask = ((1<<n)-1) ^ x;
            res += dp[mask][n];
        }
        cout << res << "\n";
    }
    return 0;
}
