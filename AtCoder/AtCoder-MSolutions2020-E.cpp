/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - First idea is: let's brute force which subset of points will have a horizontal line 
        closest to it and which will have vertical.
        - This way we reduce to 1D problem: given some set of points and number of people in 
        each of them, for each k from 0 to number of points find minimum possible sum of distances 
        for each people to nearest marked point/origin.
        - First we can observe, that there is an optimal solution, where marked points coincide 
        with some subset of input points (if not, we can choose some marked point which doesn't 
        and if total number of people for whom current point is the closest is more on its left 
        we can move the marked point to the closest input point on the left and if not then to 
        the closest on the right without increasing the answer).
        - Let bestx[mask][num] = the best answer if we consider "num" vertical lines going through
        "num" points in the total of numBit(mask) points (we consider answer with vertical lines only,
        including the line x = 0).
        - Let besty[mask][num] = the best answer if we consider "num" horizontal lines going through
        "num" points in the total of numBit(mask) points (we consider answer with horizontal lines only,
        including the line y = 0).
        - So res[i + j] = min(ans[i + j], bestx[mask1][i] + besty[mask2][j]) when we divide all points
        into 2 sets mask1 and mask2, in mask1 we choose i points and in mask2 we choose j points.
        - How to calculate bestx and besty? We start at bestx[mask][num] when numBit[mask] = num, the
        answer here is surely 0. Then we add new points into mask and update new state, only num unchanges
        in the whole process.
        - Complexity O(3^n)
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
const int MAXN = 16;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ll bestx[1 << MAXN][MAXN], besty[1 << MAXN][MAXN], score[MAXN], subScore[1 << MAXN], ans[MAXN];
int x[MAXN], y[MAXN], p[MAXN], n;

void calc(int pos[], int val[], ll res[1 << MAXN][MAXN]) {
    // marked points
    FOR(mask,0,(1<<n)-1) {
        // calculate score of each points => score[i]
        FOR(i,0,n-1)
            if (mask & (1<<i)) score[i] = 0;
            else {
                int x = abs(pos[i]);
                FOR(j,0,n-1) 
                    if (mask & (1<<j)) x = min(x, abs(pos[i] - pos[j]));
                score[i] = (ll) x * val[i];
            }
        int cntMarked = __builtin_popcount(mask);
        // consider new set of points to add to mask
        int rest = ((1<<n)-1) ^ mask;
        for (int subOfRest = rest;; subOfRest = (subOfRest-1) & rest) {
            // we are getting subOfRest from the largest to smallest, we prefer the reversed
            int s = rest ^ subOfRest;

            // basic case
            if (s == 0) subScore[s] = 0;
            else {
                // simply get number of trailing zeroes of s and update subScore
                int i = __builtin_ctz(s);
                subScore[s] = subScore[s ^ (1<<i)] + score[i];
            }
            // update res
            res[s | mask][cntMarked] = min(res[s | mask][cntMarked], subScore[s]);
            // stop when subOfRest == 0, means s == rest
            if (subOfRest == 0) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,0,n-1) cin >> x[i] >> y[i] >> p[i];
    
    FOR(mask,0,(1<<n)-1) FOR(i,0,n) bestx[mask][i] = besty[mask][i] = 1e18;
    calc(x, p, bestx);
    calc(y, p, besty);
    FOR(i,0,n) ans[i] = 1e18;
    FOR(mask1,0,(1<<n)-1) {
        int mask2 = ((1<<n)-1) ^ mask1;
        int n1 = __builtin_popcount(mask1), n2 = n - n1;
        FOR(i,0,n1)
            FOR(j,0,n2) ans[i + j] = min(ans[i + j], bestx[mask1][i] + besty[mask2][j]);
    }
    FOR(i,0,n) cout << ans[i] << "\n";
    return 0;
}
