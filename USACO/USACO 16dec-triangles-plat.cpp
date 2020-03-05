/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Mainly from http://usaco.org/current/data/sol_triangles_platinum_dec16.html
        - Separate the case that one point is under another, as it could lead to duplicate
        addition to the result.
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
const int MAXN = 310;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

using ftype = ll;
struct point {
    ftype x, y;
    point() {}
    point(ftype xx, ftype yy) : x(xx), y(yy) {}
    point& operator+=(const point &t) {
        x += t.x;
        y += t.y;
        return *this;
    }
    point& operator-=(const point &t) {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    point& operator*=(ftype t) {
        x *= t;
        y *= t;
        return *this;
    }
    point& operator/=(ftype t) {
        x /= t;
        y /= t;
        return *this;
    }
    point operator+(const point &t) const {
        return point(*this) += t;
    }
    point operator-(const point &t) const {
        return point(*this) -= t;
    }
    point operator*(ftype t) const {
        return point(*this) *= t;
    }
    point operator/(ftype t) const {
        return point(*this) /= t;
    }
};
point operator*(ftype a, point b) {
    return b * a;
}

ftype cross(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

ftype cross(point a, point b, point c) {
    return cross(b-a, c-a);
}

bool isBelow(point a, point b, point c) {
    if (a.x == b.x) return false;
    if (a.x > b.x) swap(a, b);
    return c.x > a.x && c.x < b.x && cross(a, b, c) < 0;
}

bool isBelow(point a, point b) {
    return a.x == b.x && a.y > b.y;
}

int n, cntBelow[MAXN][MAXN], res[MAXN];
point a[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);
    cin >> n;
    FOR(i,1,n) cin >> a[i].x >> a[i].y;
    FOR(i,1,n)
        FOR(j,1,n)
            if (a[i].x < a[j].x) {
                FOR(k,1,n)
                    if (k != i && k != j) {
                        // only add once if point k is under point i or j
                        if (isBelow(a[i], a[k])) cntBelow[i][j]++;
                        if (isBelow(a[j], a[k])) cntBelow[i][j]++;
                        // remaining case, add twice
                        if (isBelow(a[i], a[j], a[k])) cntBelow[i][j] += 2;
                    }
                cntBelow[j][i] = -cntBelow[i][j];
            }
    FOR(i,1,n)
        FOR(j,i+1,n)
            FOR(k,j+1,n) {
                // iterating in clockwise order or counterclockwise order will have the same absolute result
                int p = abs(cntBelow[i][j] + cntBelow[j][k] + cntBelow[k][i]) / 2;
                // remember to remove endpoints that is under triangle remaining edge.
                p -= isBelow(a[i], a[j], a[k]);
                p -= isBelow(a[j], a[k], a[i]);
                p -= isBelow(a[k], a[i], a[j]);
                res[p]++;
            }
    FOR(i,0,n-3) cout << res[i] << "\n";
    return 0;
}
