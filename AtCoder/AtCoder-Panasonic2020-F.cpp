/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Consider the largest black rectangular area in the grid. We have 8 moveable areas
        like this
            A B C
            D   E
            F G H
        - Let's consider (X1, Y1) in D and (X2, Y2) in E, we have 2 cases
            + First: D-A-B-C-E
            + Second: D-F-G-H-E
        - These 2 paths are similar (because of the symmetric of the grid), within one path,
        for example, the first one, D-A-B is similar to B-C-E. So let's consider path from D
        to A. After all, we want to go from D to E, so the optimal path is to go to top right 
        of D, then go up one step to A, then go through B to C to the right, then go down to
        reach top left of E. So within minor grid D, can we go from one cell to a corner cell
        using Manhattan distance? Yes, we can. We easily see that there is always a path with
        Manhattan distance from one random cell to a corner cell as at each step, we can always 
        move closer to the destination (unlike the case with black retangular in the middle). 
        So we can find the distanceof 2 above paths and get min of them. One trick is that 
        the number of right steps is Y2-Y1, you just have to get min of up-steps + down-steps 
        in each case.
        - What about other cases? We have B-G is a similar case to that one. Other cases'
        result is simply Manhattan distance iff they don't have a big black rectangular in 
        the middle
        - So we check for every size of black rectangular, if it's located in the middle
        of 2 points, we get the result right away, otherwise, result is just Manhattan distance.
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

int q;
ll p3[35];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int q;
    cin >> q;
    p3[0] = 1;
    FOR(i,1,30) p3[i] = p3[i-1] * 3;
    while (q--) {
        ll X1, Y1, X2, Y2;
        cin >> X1 >> Y1 >> X2 >> Y2;
        X1--; X2--; Y1--; Y2--;
        ll res = abs(X1 - X2) + abs(Y1 - Y2);
        FORE(i,29,0) {
            ll x1 = X1 / p3[i];
            ll y1 = Y1 / p3[i];
            ll x2 = X2 / p3[i];
            ll y2 = Y2 / p3[i];
            if (x1 == x2 && x1 % 3 == 1 && abs(y1 - y2) >= 2) {
                res = abs(Y1 - Y2) + min(X1 % p3[i] + 1 + X2 % p3[i] + 1, p3[i] - X1 % p3[i] + p3[i] - X2 % p3[i]);
                break;
            }
            if (y1 == y2 && y1 % 3 == 1 && abs(x1 - x2) >= 2) {
                res = abs(X1 - X2) + min(Y1 % p3[i] + 1 + Y2 % p3[i] + 1, p3[i] - Y1 % p3[i] + p3[i] - Y2 % p3[i]);
                break;
            }
        }
        cout << res << "\n";
    }
    return 0;
}
