/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Mainly from https://github.com/quangloc99/CompetitiveProgramming/blob/master/olympiad/IZhO/2017/subsequence.cpp
        - I use f[u][v][k] as a trace array.
        - More comments in the code
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

int n, a[MAXN], k[MAXN], f[1<<10][1<<10][11];
II dp[MAXN];
vector<int> kq;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n) cin >> k[i];

    // init array f
    FOR(i,0,(1<<10)-1)
        FOR(j,0,(1<<10)-1)
            FOR(bits,0,10) f[i][j][bits] = -1;

    II res = II(0,0);
    FOR(i,1,n) {
        // get first half (lower 10 bits) and second half (higher 10 bits) of number a[i]
        int firstHalf = a[i] & ((1 << 10) - 1), secondHalf = a[i] >> 10;
        // init dp[i] = the length of longest beautiful subsequence that contains i
        // store the position of the previous element as well 
        dp[i] = II(1, -1);
        // now we start to calculate dp[i]
        // iterate through all possible previous first half
        FOR(prevFirstHalf,0,(1<<10)-1) {
            int firstHalfSetBits = __builtin_popcount(prevFirstHalf & firstHalf);
            // then we can find the number of set bits of the second half
            int secondHalfSetBits = k[i] - firstHalfSetBits;
            if (secondHalfSetBits < 0 || secondHalfSetBits > 10) continue;
            // f[u][v][k] is the position of the last element of the longest beautiful subsequence so far
            // that last element has u as the first half, (second half & v) == k
            // so here the prevPos = the last element that has prevFirstHalf as the first half
            // (second half & secondHalf) == secondHalfSetBits
            int prevPos = f[prevFirstHalf][secondHalf][secondHalfSetBits];
            if (prevPos == -1) continue;
            // update dp[i]
            dp[i] = max(dp[i], II(dp[prevPos].FI + 1, prevPos));
        }
        // res contains the max length and the position of last element
        res = max(res, II(dp[i].FI, i));
        // now we update f, iterate through new second halves
        FOR(nextSecondHalf,0,(1<<10)-1) {
            // as the possible last element is secondHalf, v = nextSecondHalf, k = secondHalfSetBits
            // and u = firstHalf
            int secondHalfSetBits = __builtin_popcount(nextSecondHalf & secondHalf);
            int &trace = f[firstHalf][nextSecondHalf][secondHalfSetBits];
            // only update when the new length is larger than the available one.
            if (trace != -1 && dp[trace].FI > dp[i].FI) continue;
            trace = i;
        }
    }

    // now simply trace back and print the result.
    cout << res.FI << "\n";
    kq.push_back(res.SE);
    while (dp[kq.back()].SE != -1) kq.push_back(dp[kq.back()].SE);
    reverse(ALL(kq));
    for (int x : kq) cout << x << ' ';
    return 0;
}
