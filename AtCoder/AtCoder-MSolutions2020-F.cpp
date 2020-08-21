/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - As the planes move 0.1 per second, we multiply all coordinates by 10, then the planes
        would move 1 per second.
        - Let's consider one example, one plane goes right and one plane goes up. We can easily see
        that they will collide with each other when those 2 are on the same diagonal line (the line
        x + y, with x, y are coordinates).
        - So we can put the planes into lines and sort them by a factor (x or y, increasing or
        decreasing), then check if 2 adjacent planes in the line will collide, watch out the case
        that they go away from each other instead of colliding.
        - R-U Collision: x+y lines
        - L-D Collision: x+y lines
        - R-D Collision: x-y lines
        - L-U Collision: x-y lines
        - What about U-D and L-R? Because of the problem condition, there is no case that 2 planes
        head-to-head but no colliding, so we can ignore some annoying cases. Then we create x lines
        or y lines and do the same as above. Remember that the way to calculate result here is a bit
        different from above.
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
const int MAXN = 4000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

vector<II> u, d, l, r;
vector<II> b[MAXN];
int n;

void solve(int &res) {
    FOR(i,0,4000000) {
        if (SZ(b[i]) < 2) continue;
        sort(ALL(b[i]));
        FOR(j,1,SZ(b[i])-1) {
            II now = b[i][j], pre = b[i][j-1];
            if (now.SE == 0 && pre.SE == 1) res = min(res, abs(now.FI - pre.FI));
        }
    }
}

void solve2(int &res) {
    FOR(i,0,2000000) {
        if (SZ(b[i]) < 2) continue;
        sort(ALL(b[i]));
        FOR(j,1,SZ(b[i])-1) {
            II now = b[i][j], pre = b[i][j-1];
            if (now.SE == 0 && pre.SE == 1) res = min(res, abs((now.FI - pre.FI) / 2));
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        int U, V;
        char D;
        cin >> U >> V >> D;
        U *= 10;
        V *= 10;
        if (D == 'U') u.push_back(II(U, V));
        if (D == 'D') d.push_back(II(U, V));
        if (D == 'L') l.push_back(II(U, V));
        if (D == 'R') r.push_back(II(U, V));
    }

    int res = 1e9;

    // R U
    FOR(i,0,4000000) b[i].clear();
    for (II x : r) {
        int g = x.FI + x.SE;
        b[g].push_back(II(x.SE, 0));
    }
    for (II x : u) {
        int g = x.FI + x.SE;
        b[g].push_back(II(x.SE, 1));
    }
    solve(res);

    // L D
    FOR(i,0,4000000) b[i].clear();
    for (II x : l) {
        int g = x.FI + x.SE;
        b[g].push_back(II(x.SE, 1));
    }
    for (II x : d) {
        int g = x.FI + x.SE;
        b[g].push_back(II(x.SE, 0));
    }
    solve(res);

    // U L
    FOR(i,0,4000000) b[i].clear();
    for (II x : u) {
        int g = x.FI - x.SE + 2000000;
        b[g].push_back(II(x.SE, 1));
    }
    for (II x : l) {
        int g = x.FI - x.SE + 2000000;
        b[g].push_back(II(x.SE, 0));
    }
    solve(res);

    // D R
    FOR(i,0,4000000) b[i].clear();
    for (II x : d) {
        int g = x.FI - x.SE + 2000000;
        b[g].push_back(II(x.SE, 0));
    }
    for (II x : r) {
        int g = x.FI - x.SE + 2000000;
        b[g].push_back(II(x.SE, 1));
    }
    solve(res);

    // U D
    FOR(i,0,2000000) b[i].clear();
    for (II x : d) {
        int g = x.FI;
        b[g].push_back(II(x.SE, 0));
    }
    for (II x : u) {
        int g = x.FI;
        b[g].push_back(II(x.SE, 1));
    }
    solve2(res);

    // L R
    FOR(i,0,2000000) b[i].clear();
    for (II x : l) {
        int g = x.SE;
        b[g].push_back(II(x.FI, 0));
    }
    for (II x : r) {
        int g = x.SE;
        b[g].push_back(II(x.FI, 1));
    }
    solve2(res);

    if (res == 1e9) cout << "SAFE";
    else cout << res;
    return 0;
}
