/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - As it's more possible to get the square when increasing the result. We can binary
        search the result.
        - For each maximum moving distance, we can choose the corner and the direction (vertical - 0
        or horizontal - 1) for each point. There are 4! * 4^2 for each distance.
        - Let's assume the first point is the bottom-left, and we go clockwise order (the first
        point can be the top-right sometimes but it does not really matter).
        - Let range[i][0/1] be the Min/Max value of the x/y-coordinate where the side is considering
        on. As we are going clockwise, the first side is for x-coordinate, the second side is for
        y-coordinate, the third side is for x-coordinate again, the fourth side is for y-coordinate
        again.
        - Each side has 2 points, each point has one direction of moving, we can get the range 
        based on the direction of those points.
        - Now we have 4 ranges, 2 for x and 2 for y, now we need to check if the length of the sides
        can be the same (getSquareLengthRange function).

        - When getting the result (4 new points), we can choose a proper side length and find the
        x-coordinates and y-coordinates
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

int t, a[4][2], b[4][2], dir[4], range[4][2], resZ[4], resDir[4], c[4][2];

II common(int l, int r, int u, int v) {
    II res = II(max(l, u), min(r, v));
    if (res.FI <= res.SE) return res;
    return II(-1e9, -1e9);
}

bool process(int len) {
    // get the range of each side based on the directions.
    FOR(i,0,3) {
        int nex = (i + 1) % 4;
        int w = i % 2;
        if (dir[i] != dir[nex]) {
            if (dir[i] == 1-w) {
                int diff = abs(b[i][1-dir[i]] - b[nex][dir[nex]]);
                if (len < diff) return false;
                range[i][0] = range[i][1] = b[i][1-dir[i]];
            } else {
                int diff = abs(b[i][dir[i]] - b[nex][1-dir[nex]]);
                if (len < diff) return false;
                range[i][0] = range[i][1] = b[nex][1-dir[nex]];
            }
        } else {
            if (dir[i] == 1-w) {
                if (b[i][1-dir[i]] != b[nex][1-dir[nex]]) return false;
                range[i][0] = range[i][1] = b[i][1-dir[i]];
            } else {
                int diff = abs(b[i][dir[i]] - b[nex][dir[nex]]);
                if (len * 2 < diff) return false;
                range[i][0] = max(b[i][dir[i]], b[nex][dir[nex]]) - len;
                range[i][1] = min(b[i][dir[i]], b[nex][dir[nex]]) + len;
            }
        }
    }
    return true;
}

II getSquareLengthRange(int len) {
    int Min = 1e9, Max = 0;
    II q1 = common(range[0][0], range[0][1], range[2][0], range[2][1]);
    FOR(i,0,1) FOR(j,0,1) Max = max(Max, abs(range[0][i] - range[2][j]));
    if (q1.FI == -1e9) {
        FOR(i,0,1) FOR(j,0,1) Min = min(Min, abs(range[0][i] - range[2][j]));
    } else {
        Min = 0;
    }

    int Min2 = 1e9, Max2 = 0;
    II q2 = common(range[1][0], range[1][1], range[3][0], range[3][1]);
    FOR(i,0,1) FOR(j,0,1) Max2 = max(Max2, abs(range[1][i] - range[3][j]));
    if (q2.FI == -1e9) {
        FOR(i,0,1) FOR(j,0,1) Min2 = min(Min2, abs(range[1][i] - range[3][j]));
    } else {
        Min2 = 0;
    }
    return common(Min, Max, Min2, Max2);
}

bool solve(int len) {
    if (!process(len)) return false;
    
    II q = getSquareLengthRange(len);
    if (q.FI == -1e9) return false;
    if (q.SE == 0) return false;
    return true;
}

void solve2(int len) {
    process(len);

    II q = getSquareLengthRange(len);
    int p = q.FI;
    if (p == 0) p++;

    II x, y;
    int u = range[0][0] + p, v = range[0][1] + p;
    q = common(u, v, range[2][0], range[2][1]);
    if (q.FI != -1e9) {
        x.SE = q.FI;
        x.FI = q.FI - p;
    } else {
        u = range[0][0] - p; v = range[0][1] - p;
        q = common(u, v, range[2][0], range[2][1]);
        x.SE = q.FI;
        x.FI = q.FI + p;
    }

    u = range[1][0] + p; v = range[1][1] + p;
    q = common(u, v, range[3][0], range[3][1]);
    if (q.FI != -1e9) {
        y.SE = q.FI;
        y.FI = q.FI - p;
    } else {
        u = range[1][0] - p; v = range[1][1] - p;
        q = common(u, v, range[3][0], range[3][1]);
        y.SE = q.FI;
        y.FI = q.FI + p;
    }

    c[0][0] = x.FI; c[0][1] = y.SE;
    c[1][0] = x.FI; c[1][1] = y.FI;
    c[2][0] = x.SE; c[2][1] = y.FI;
    c[3][0] = x.SE; c[3][1] = y.SE;
}

bool check(int len) {
    int z[4];
    FOR(i,0,3) z[i] = i;
    do {
        FOR(i,0,3) {
            b[i][0] = a[z[i]][0];
            b[i][1] = a[z[i]][1];
        }
        FOR(i,0,1)
            FOR(j,0,1)
                FOR(k,0,1)
                    FOR(l,0,1) {
                        dir[0] = i;
                        dir[1] = j;
                        dir[2] = k;
                        dir[3] = l;
                        if (solve(len)) {
                            FOR(I,0,3) resZ[I] = z[I];
                            FOR(I,0,3) resDir[I] = dir[I];
                            return true;
                        }
                    }
    } while (next_permutation(z, z+4));
    return false;
}

void printResult(int res) {
    if (res > 2e8) {
        cout << -1 << "\n";
        return;
    }
    cout << res << "\n";
    check(res);
    FOR(i,0,3) {
        b[i][0] = a[resZ[i]][0];
        b[i][1] = a[resZ[i]][1];
        dir[i] = resDir[i];
    }
    solve2(res);
    FOR(i,0,3) 
        FOR(j,0,3)
            if (resZ[j] == i) cout << c[j][0] << ' ' << c[j][1] << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        FOR(i,0,3) cin >> a[i][0] >> a[i][1];
        // binary search the result
        int dau = 0, cuoi = 2e8;
        while (dau <= cuoi) {
            int mid = (dau + cuoi) >> 1;
            if (check(mid)) cuoi = mid-1;
            else dau = mid+1;
        }
        printResult(dau);
    }
    return 0;
}
