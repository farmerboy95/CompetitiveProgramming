/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Transform pos[i] and h[i] into points with x = pos[i], y = h[i]
        - Consider pair of points i and i+1, if we draw a vector from point i to point i+1,
        the list of points that could oversee the whole vector is located to the left of 
        that vector (even on the line(point[i], point[i+1])), we have n-1 planes like that
        - So the list of points that could oversee the whole landscape will be located in a
        convex plane (intersection of n-1 planes).
        - We can easily see that the minimum height could be achieved when we calculate 
        distance from a point to the convex plane. How? We can calculate the distance from
        a point to the furthest intersection of vertical line containing that point and n-1
        lines.
        - We can also see that x-axis of intesection of 2 lines may be the place for us to
        calculate the height. After getting x-axis, we get the height of the landscape at
        that x-axis and calculate the distance from that point to the convex plane.
        - Get min of all cases and print out the result.
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

inline int cmp(ld a, ld b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

using ftype = ld;
struct point {
    ftype x, y;
    point() {}
    point(ftype x, ftype y) : x(x), y(y) {}
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
    point rotate(ftype alpha) {
        return point(x * cos(alpha) - y * sin(alpha), x * sin(alpha) + y * cos(alpha));
    }
};
point operator*(ftype a, point b) {
    return b * a;
}

struct line {
    ftype a, b, c;
    point A, B;
    line(ftype a = 0, ftype b = 0, ftype c = 0) : a(a), b(b), c(c) {}
    line(point A, point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }
    line(point P, ftype m) {
        a = -m; b = 1;
        c = -(a * P.x + b * P.y);
    }
    ftype f(point P) {
        return a * P.x + b * P.y + c;
    }
};

bool areParallel(line l1, line l2) { 
    return cmp(l1.a * l2.b, l1.b * l2.a) == 0; 
}

bool areIntersect(line l1, line l2, point &p) {
    if (areParallel(l1, l2)) return false;
    ftype dx = l1.b*l2.c - l2.b*l1.c;
    ftype dy = l1.c*l2.a - l2.c*l1.a;
    ftype d = l1.a*l2.b - l2.a*l1.b;
    p = point(dx/d, dy/d);
    return true;
}

class WatchTower {
    public:
    int n;
    vector<point> points;
    vector<line> lines;

    ld getHighest(ld x) {
        line l = line(point(x, 0), point(x, 1));
        ld res = -1e18;
        FOR(i,0,n-2) {
            point inter;
            if (areIntersect(lines[i], l, inter)) res = max(res, inter.y);
        }
        return res;
    }

    ld minHeight(vector<int> pos, vector<int> h) {
        n = SZ(pos);
        points.clear();
        FOR(i,0,n-1) points.push_back(point(pos[i], h[i]));

        lines.clear();
        FOR(i,0,n-2) lines.push_back(line(points[i], points[i+1]));
        
        ld res = 1e18;

        FOR(i,0,n-1) res = min(res, getHighest(points[i].x) - points[i].y);

        FOR(i,0,n-2)
            FOR(j,i+1,n-2) {
                point inter;
                if (areIntersect(lines[i], lines[j], inter)) {
                    if (inter.x < points[0].x || inter.x > points[n-1].x) continue;
                    ld H = -1e18;
                    FOR(k,0,n-2)
                        if (points[k].x <= inter.x && inter.x <= points[k+1].x) {
                            point inter2;
                            line l = line(point(inter.x, 0), point(inter.x, 1));
                            if (areIntersect(l, lines[k], inter2)) H = inter2.y;
                        }
                    res = min(res, getHighest(inter.x) - H);
                }
            }
        return res;
    }

};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    WatchTower s;
    cout << fixed << setprecision(9) << s.minHeight({1, 2, 4, 5, 6, 7}, {1, 2, 2, 4, 2, 1}) << endl;
    cout << fixed << setprecision(9) << s.minHeight({10, 20, 49, 59}, {0, 10, 10, 0}) << endl;
    cout << fixed << setprecision(9) << s.minHeight({0, 3, 7, 13}, {4, 17, 23, 3}) << endl;
    return 0;
}
