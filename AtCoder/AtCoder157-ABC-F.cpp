/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let the result be r, so c[i] * sqrt((X-x[i])^2 + (Y-y[i])^2) = x
        => (X-x[i])^2 + (Y-y[i])^2 = (x / c[i])^2
        - So each meat would form a circle. If the heat source is not outside of the circle,
        the meat would be ready to eat. Easy to see that the larger r is, the larger circles are
        and its more likely to get the result when r increases.
        - After choosing r, we get intersections of each pair of circles and check if one of them
        are inside (or on the edge) of at least k circles.
        - Wait, what about cases that one circle is completely inside another one? We can simply
        add centers of circles into the list and check them as well.
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

inline int cmp(ll a, ll b) {
    return (a < b) ? -1 : ((a > b) ? 1 : 0);
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

// dot product
ftype dot(point a, point b) {
    return a.x * b.x + a.y * b.y;
}

// square of length
ftype norm(point a) {
    return dot(a, a);
}

// length of vector
ld abs(point a) {
    return sqrt(norm(a));
}

// projection of vector a on b
ld proj(point a, point b) {
    return dot(a, b) / abs(b);
}

// angle between vectors
ld angle(point a, point b) {
    return acos(dot(a, b) / abs(a) / abs(b));
}

ftype cross(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

ftype cross(point a, point b, point c) {
    return cross(b-a, c-a);
}

// intersection of 2 lines
bool isIntersect(point d1, point d2) {
    return cmp(cross(d1, d2), 0) != 0;
}

// initial point a, direction is d
point intersect(point a1, point d1, point a2, point d2) {
    return a1 + cross(a2 - a1, d2) / cross(d1, d2) * d1;
}

struct circle {
    point center;
    ftype r;
    circle(ftype x = 0, ftype y = 0, ftype r = 0) {
        center.x = x;
        center.y = y;
        this->r = r;
    }
};

bool areIntersect(circle u, circle v) {
    if (cmp(abs(u.center - v.center), u.r + v.r) > 0) return false;
    if (cmp(abs(u.center - v.center) + v.r, u.r) < 0) return false;
    if (cmp(abs(u.center - v.center) + u.r, v.r) < 0) return false;
    return true;
}

vector<point> circleIntersect(circle u, circle v) {
    vector<point> res;
    if (!areIntersect(u, v)) return res;
    ld d = abs(u.center - v.center);
    ld alpha = acos((u.r * u.r + d*d - v.r * v.r) / 2.0 / u.r / d);
    point p1 = (v.center - u.center).rotate(alpha);
    point p2 = (v.center - u.center).rotate(-alpha);
    res.push_back(p1 / abs(p1) * u.r + u.center);
    res.push_back(p2 / abs(p1) * u.r + u.center);
    return res;
}

int n, k, x[MAXN], y[MAXN], c[MAXN];

bool check2(vector<circle> &cc, point &p) {
    int cnt = 0;
    FOR(i,0,n-1) {
        ld dist = abs(cc[i].center - p);
        if (cmp(dist, cc[i].r) <= 0) cnt++;
    }
    return cnt >= k;
}

bool check(ld r) {
    vector<circle> cc;
    // form circles
    FOR(i,1,n) {
        circle p = circle(x[i], y[i], r / c[i]);
        cc.push_back(p);
    }
    vector<point> w;
    // add centers
    FOR(i,1,n) w.push_back(point(x[i], y[i]));
    // add intersections
    FOR(i,0,n-1)
        FOR(j,i+1,n-1) {
            vector<point> v = circleIntersect(cc[i], cc[j]);
            FOR(p,0,SZ(v)-1) w.push_back(v[p]);
        }
    // check each point in the list
    FOR(i,0,SZ(w)-1)
        if (check2(cc, w[i])) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,n) cin >> x[i] >> y[i] >> c[i];
    ld dau = 0, cuoi = 1000000;

    FOR(i,1,1000) {
        ld mid = (dau + cuoi) / 2;
        if (check(mid)) cuoi = mid;
        else dau = mid;
    }
    cout << fixed << setprecision(9) << dau;
    return 0;
}
