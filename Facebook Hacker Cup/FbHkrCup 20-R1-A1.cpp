/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/codingcompetitions/hacker-cup/2020/round-1/problems/A1
    Status: AC
    Idea:
        - We notice that the width of rooms is the same and small (W <= 20). So we can maintain
        an array "height" of W+1 (i from 0 to W) contains the height at x = i.
        - Define latestX as the max x-coordinate that has been occupied by a room, we can use this 
        because L1 < L2 < ... < Ln
        - If latestX < L[i], the new room does not overlap with the ones before, so we add 2 * (h[i] + w)
        to p and update "height".
        - Otherwise, the current one overlaps with some rooms before, first we move the array "height"
        forward to the point L[i].
        - For the width, only need to add 2 * (l[i] + w - latestX), the rest of width does not change 
        in value, only be moved higher.
        - For the height, only need to add 2 * (h[i] - height[0]) (if h[i] > height[0])
        - Complexity O(NW)
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

int n, k, w;
ll l[MAXN], h[MAXN], height[25];

void init() {

}

void input() {
    ll A, B, C, D;
    cin >> n >> k >> w;

    FOR(i,1,k) cin >> l[i];
    cin >> A >> B >> C >> D;
    FOR(i,k+1,n) l[i] = (A * l[i-2] + B * l[i-1] + C) % D + 1;

    FOR(i,1,k) cin >> h[i];
    cin >> A >> B >> C >> D;
    FOR(i,k+1,n) h[i] = (A * h[i-2] + B * h[i-1] + C) % D + 1;
}

ll handle() {
    ll res = 1;

    FOR(i,0,w) height[i] = 0;
    ll latestX = 0;
    ll p = 0;

    FOR(i,1,n) {
        if (latestX < l[i]) {
            p = (p + 2 * w + 2 * h[i]) % MODBASE;
            FOR(j,0,w) height[j] = h[i];
        } else {
            ll pos = w - (latestX - l[i]);
            FOR(j,0,w)
                if (j + pos > w) height[j] = 0;
                else height[j] = height[j + pos];
            p = (p + 2 * (l[i] + w - latestX)) % MODBASE;
            if (height[0] < h[i]) p = (p + 2 * (h[i] - height[0])) % MODBASE;
            FOR(j,0,w) height[j] = max(height[j], h[i]);
        }
        latestX = l[i] + w;
        res = res * p % MODBASE;
    }

    return res;
}

ll solve() {
    input();
    init();
    return handle();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case #" << o << ": ";
        cout << solve() << "\n";
    }
    return 0;
}
