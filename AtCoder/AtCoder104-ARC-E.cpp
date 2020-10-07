/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Notice that n <= 6. First, when we consider the length of the LIS, it is only the state 
        after "compression" of the elements that matters. The number of ways to divide m objects 
        into some number of groups and ordering them is called the Ordered Bell number or Fubini 
        number, and there are 4683 such ways for n=6.
        - We will have at most n groups and n value segments. For example if n=6, a=[5,9,13,4,2,7].
        We will have these value segments [1,2], [3,4], [5,5], [6,7], [8,9], [10,13]. The reason why
        we divide it into value segments because the group with an index can have a value of the group
        that has smaller index. To make it simple we are going to describle the value segments in a
        one-dimentional array [1,3,5,6,7,10,14], one segment i contains values from a[i] to a[i+1]-1.
        - Basically, expected value = probability * value, so for each compressed array in 4683 ways 
        above, we are going to calculate the number of ways to retrieve it. The "value" would be the
        LIS of the compressed array, should be very easy to get.
        - Let 2-dimentional array idx, with idx[i] contains the indices of the compressed value i.
        Let upperBound[i] is the largest value possible that compressed value i can get, this one can
        be retrieved by min of value of input array, with the help of idx[i].
        - Let dp[i][j] is the number of ways that we can form up to i groups, with all the values lower
        than valueSegment[j]. At each step, we can choose the next value segment and the number of groups
        we can use the values in value segment. The binomial coefficient nCk here is quite easy to calculate
        as k is small.
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

ll MOD = MODBASE;
int group[10], val[10];
ll dp[10][10];
vector<int> valueSegment;

ll binPowMod(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1LL;
    }
    return res;
}

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

ll inv(ll a) {
    return binPowMod(a, MOD-2);
}

ll divi(ll a, ll b) {
    return mul(a, inv(b));
}

ll calc(int n, vector<vector<int> > &idx) {
    int numGroup = SZ(idx);
    vector<int> upperBound(numGroup, 2000000000);
    FOR(i,0,numGroup-1)
        for (int j : idx[i]) upperBound[i] = min(upperBound[i], val[j]);
    
    MS(dp, 0);
    dp[0][0] = 1;

    FOR(i,0,numGroup-1)
        FOR(j,0,SZ(valueSegment)-2) {
            if (!dp[i][j]) continue;
            FOR(nex,j,SZ(valueSegment)-2) {
                int minInSeg = valueSegment[nex];
                int num = valueSegment[nex+1] - valueSegment[nex];
                int now = 1;
                ll ways = 1;
                FOR(k,i,numGroup-1) {
                    // there is no case that upperBound is in the middle of 2 bounds as
                    // upperBound and minInSeg are all from the input
                    if (upperBound[k] < minInSeg) break;
                    ways = mul(ways, mul(num, inv(now)));
                    now++;
                    num--;
                    dp[k+1][nex+1] = add(dp[k+1][nex+1], mul(dp[i][j], ways));
                }
            }
        }

    ll res = 0;
    FOR(i,0,SZ(valueSegment)-1) res = add(res, dp[numGroup][i]);
    return res;
}

ll handle(int n, int Max) {
    vector<vector<int> > idx(Max);
    FOR(i,0,n-1) idx[group[i]].push_back(i);
    ll res = 0;

    do {
        vector<int> a(n), lis(n);
        FOR(i,0,SZ(idx)-1)
            for (int j : idx[i]) a[j] = i;
        int LIS = 0;
        FOR(i,0,n-1) {
            lis[i] = 1;
            FOR(j,0,i-1)
                if (a[j] < a[i]) lis[i] = max(lis[i], lis[j] + 1);
            LIS = max(LIS, lis[i]);
        }
        res = add(res, mul(calc(n, idx), LIS));
    } while (next_permutation(ALL(idx)));

    return res;
}

ll solve(int n, int u, int Max) {
    if (u == n) return handle(n, Max);
    ll res = 0;
    FOR(i,0,Max) {
        group[u] = i;
        res = add(res, solve(n, u+1, max(Max, i+1)));
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n;
    cin >> n;
    FOR(i,0,n-1) cin >> val[i];
    ll tot = 1;
    valueSegment.push_back(1);
    FOR(i,0,n-1) {
        tot = mul(tot, val[i]);
        valueSegment.push_back(val[i] + 1);
    }
    sort(ALL(valueSegment));
    cout << divi(solve(n, 0, 0), tot);
    return 0;
}
