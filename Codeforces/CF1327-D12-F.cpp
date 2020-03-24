/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Easily see that we can solve for each bit separately, then multiply results.
        - To solve for one bit, use DP ways[i] is the number of ways that we can put 0 at i and there
        is no conflict so far (i is from 0 to n, consider we have a 0 at position 0)
        - We only have two restrictions to deal with:
            + First of all, for given position P, we can't put 0 there if it is a part of some 1-segment.
            + In case you decide to put 0 there, the previous 0 can't be too far to the left so 
            we don't have some 0-segment being completely between those two 0s.
        - For each i, we maintain currentL and currentR; currentR is the furthest position of 1-segment
        from 1 to i, we can consider it initially is 0; currentL is the nearest position to the left of
        i that a 0-segment has.
        - When we come to new i, first we update currentR using segments that start from i. If
        currentR < i, it means we can put a zero there, so we get sum of ways[j] from currentL to i-1
        because if we get any ways[j] to the left of currentL, we expose at least one 0-segment in
        the range from j+1 to i-1, that's why we have to keep currentL. Finally, we update currentL
        for next i.
        - One final thing is that, when we get the result, we get sum(ways[j]) from max(l[i]) of 
        0-segments to n, as there is absolutely no more 0-segments to the right of max(l[i]) can be
        exposed.
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
const int MAXN = 500010;
const int MAXM = 500010;
const int MAXK = 16;
const int MAXQ = 200010;

int n, k, m, l[MAXM], r[MAXM], x[MAXM];
vector<int> startOne[MAXN], endZero[MAXN];
ll prefixSum[MAXN], ways[MAXN];
ll MOD = 998244353;

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

ll get(ll l, ll r) {
    if (l > r) return 0;
    ll res = prefixSum[r];
    if (l > 0) res = sub(res, prefixSum[l-1]);
    return res;
}

ll solve(int bit) {
    FOR(i,1,n) {
        startOne[i].clear();
        endZero[i].clear();
    }

    int shouldStartFrom = 0;
    FOR(i,1,m)
        if (x[i] & (1<<bit)) {
            // full 1
            startOne[l[i]].emplace_back(r[i]);
        }
        else {
            endZero[r[i]].emplace_back(l[i]);
            shouldStartFrom = max(shouldStartFrom, l[i]);
        }

    // ways[i] = number of ways to put 0 at i
    // prefixSum[i] = sum(ways[0..i])
    prefixSum[0] = 1;
    ways[0] = 1;
    int currentL = 0, currentR = 0;

    FOR(i,1,n) {
        FOR(j,0,SZ(startOne[i])-1) currentR = max(currentR, startOne[i][j]);
        ways[i] = 0;
        // i can be 0
        if (currentR < i) ways[i] = get(currentL, i-1);
        prefixSum[i] = add(prefixSum[i-1], ways[i]);
        FOR(j,0,SZ(endZero[i])-1) currentL = max(currentL, endZero[i][j]);
    }

    ll res = 0;
    FOR(i,shouldStartFrom,n) res = add(res, ways[i]);
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k >> m;
    FOR(i,1,m) cin >> l[i] >> r[i] >> x[i];
    ll res = 1;
    FOR(bit,0,k-1) res = mul(res, solve(bit));
    cout << res;
    return 0;
}
