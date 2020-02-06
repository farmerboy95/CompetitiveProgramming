/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Based on the method of finding convex hull.
        - A convex hull contains upper convex line and lower convex line. To determine that
        a point is inside a convex hull, that point should lie below upper convex line and
        above lower convex line.
        - We only consider upper convex line. For lower convex line, we simply reflect the
        convex hull over the x-axis, lower line will become upper one and we consider the point
        (x, -y) instead of (x, y) as we reflect that point as well.
        - For each point p and the convex line, we find the nearest points (by x) to the left (a) and
        right (b) of p, then if a, p, b make a counter-clockwise rotation, point p lies below the line.
        - For adding point p into the convex line, p should not lie under the line, then consider pairs
        of consecutive points (a, b) to the right of p on the convex line and check if we should keep
        point a on the convex line or not (just like how we build convex hull), do the same thing to 
        the left of p.
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

struct point {
    int x, y;
    point() {}
    point(int x, int y) : x(x), y(y) {}
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
    point& operator*=(int t) {
        x *= t;
        y *= t;
        return *this;
    }
    point& operator/=(int t) {
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
    point operator*(int t) const {
        return point(*this) *= t;
    }
    point operator/(int t) const {
        return point(*this) /= t;
    }
};
point operator*(int a, point b) {
    return b * a;
}

ll cross(point a, point b) {
    return (ll) a.x * b.y - (ll) a.y * b.x;
}

ll cross(point a, point b, point c) {
    return cross(b-a, c-a);
}

map<int, int> upper, lower;

bool check(map<int, int> &ma, point p) {
    auto pos = ma.lower_bound(p.x);
    if (pos == ma.end()) return 0;
    if (pos->FI == p.x) return p.y <= pos->SE;
    if (pos == ma.begin()) return 0;
    auto pre = pos;
    pre--;
    point pointPre = point(pre->FI, pre->SE);
    point pointPos = point(pos->FI, pos->SE);
    return cross(pointPre, p, pointPos) >= 0;
}

void add(map<int, int> &ma, point p) {
    if (check(ma, p)) return;
    ma[p.x] = p.y;
    auto pos = ma.lower_bound(p.x);
    auto nex = pos; nex++;
    while (nex != ma.end()) {
        pos = nex;
        nex++;
        if (nex == ma.end()) break;
        point pointNex = point(nex->FI, nex->SE);
        point pointPos = point(pos->FI, pos->SE);
        if (cross(p, pointPos, pointNex) <= 0) break;
        ma.erase(pos);
    }

    pos = ma.lower_bound(p.x);
    if (pos == ma.begin()) return;
    auto pre = pos; pre--;
    while (pre != ma.begin()) {
        pos = pre;
        pre--;
        point pointPre = point(pre->FI, pre->SE);
        point pointPos = point(pos->FI, pos->SE);
        if (cross(p, pointPos, pointPre) >= 0) break;
        ma.erase(pos);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int q;
    cin >> q;
    while (q--) {
        int ch, u, v;
        cin >> ch >> u >> v;
        if (ch == 1) {
            add(upper, point(u, v));
            add(lower, point(u, -v));
        }
        else {
            if (check(upper, point(u, v)) && check(lower, point(u, -v))) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}
